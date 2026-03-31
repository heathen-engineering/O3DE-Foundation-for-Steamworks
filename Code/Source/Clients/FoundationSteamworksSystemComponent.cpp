/*
 * Copyright (c) 2026 Heathen Engineering Limited
 * Irish Registered Company #556277
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "FoundationSteamworksSystemComponent.h"
#include "SteamTypeConverters.h"
#include "SteamCallResultInfrastructure.h"
#include "SteamCallbackRegistry.h"

#include <FoundationSteamworks/FoundationSteamworksTypeIds.h>

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/RTTI/BehaviorContext.h>
#include <AzCore/std/containers/vector.h>

// Platform includes for IP string → uint32 conversion (GameServerInitialise).
#if AZ_TRAIT_OS_PLATFORM_APPLE || defined(__linux__)
#   include <arpa/inet.h>
#   include <stdlib.h>   // setenv / unsetenv
#elif defined(AZ_PLATFORM_WINDOWS)
#   include <ws2tcpip.h>
#   include <windows.h>  // SetEnvironmentVariableA
#endif

// Editor detection + project-path utilities (used by ScopedSteamAppIdEnv below).
#include <AzCore/Component/ComponentApplicationBus.h>
#include <AzCore/Utils/Utils.h>

// Steam SDK — lifecycle only; per-subsystem headers live in FoundationSteamworks_Xxx.cpp.
#include <steam/steam_api.h>
#include <steam/steam_gameserver.h>
#include <steam/isteaminput.h>

// Bus types live in namespace Heathen
using namespace Heathen;

// ---------------------------------------------------------------------------
// ScopedSteamAppIdEnv
// Editor-only helper: temporarily sets the SteamAppId environment variable
// so that SteamAPI_InitEx / SteamGameServer_InitEx can find the App ID without
// needing a steam_appid.txt file in the working directory.
//
// Constructed with the App ID the caller wants to advertise.
// - If appId == 0, or we are not running inside the O3DE editor, it is a no-op.
// - Otherwise it sets SteamAppId=<appId> in the process environment, saves any
//   pre-existing value, and restores it (or removes the variable) in the dtor.
// ---------------------------------------------------------------------------
namespace
{

struct ScopedSteamAppIdEnv
{
    explicit ScopedSteamAppIdEnv(AZ::u32 appId)
    {
        if (appId == 0)
            return;

        AZ::ApplicationTypeQuery appType;
        AZ::ComponentApplicationBus::Broadcast(
            &AZ::ComponentApplicationRequests::QueryApplicationType, appType);
        if (!appType.IsEditor())
            return;

        // Stash any value already present so we can restore it on exit.
        const char* existing = std::getenv("SteamAppId");
        m_hadPrevious = (existing != nullptr);
        if (m_hadPrevious)
            m_previous = existing;

        char buf[32];
        azsnprintf(buf, sizeof(buf), "%u", appId);

#if defined(AZ_PLATFORM_WINDOWS)
        SetEnvironmentVariableA("SteamAppId", buf);
#else
        setenv("SteamAppId", buf, /*overwrite=*/1);
#endif
        m_set = true;
        AZ_TracePrintf("FoundationSteamworks",
            "Editor: set SteamAppId=%u in environment for Steam init.", appId);
    }

    ~ScopedSteamAppIdEnv()
    {
        if (!m_set)
            return;

        if (m_hadPrevious)
        {
#if defined(AZ_PLATFORM_WINDOWS)
            SetEnvironmentVariableA("SteamAppId", m_previous.c_str());
#else
            setenv("SteamAppId", m_previous.c_str(), 1);
#endif
        }
        else
        {
#if defined(AZ_PLATFORM_WINDOWS)
            SetEnvironmentVariableA("SteamAppId", nullptr);
#else
            unsetenv("SteamAppId");
#endif
        }
    }

    // Non-copyable.
    ScopedSteamAppIdEnv(const ScopedSteamAppIdEnv&) = delete;
    ScopedSteamAppIdEnv& operator=(const ScopedSteamAppIdEnv&) = delete;

    bool         m_set         = false;
    bool         m_hadPrevious = false;
    AZStd::string m_previous;
};

} // anonymous namespace

namespace FoundationSteamworks
{

    // -----------------------------------------------------------------------
    // Component boilerplate
    // -----------------------------------------------------------------------
    AZ_COMPONENT_IMPL(FoundationSteamworksSystemComponent, "FoundationSteamworksSystemComponent",
        FoundationSteamworksSystemComponentTypeId);

    // Forward declaration — defined in SteamAPIReflect.cpp
    void ReflectSteamBehaviorContext(AZ::BehaviorContext* bc);

    void FoundationSteamworksSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<FoundationSteamworksSystemComponent, AZ::Component>()
                ->Version(0);

            // --- Result structs ---
            serializeContext->Class<SteamInitResult>()->Version(0)
                ->Field("success", &SteamInitResult::success)
                ->Field("errorMsg", &SteamInitResult::errorMsg);
            serializeContext->Class<SteamStatIntResult>()->Version(0)
                ->Field("success", &SteamStatIntResult::success)
                ->Field("value", &SteamStatIntResult::value);
            serializeContext->Class<SteamStatFloatResult>()->Version(0)
                ->Field("success", &SteamStatFloatResult::success)
                ->Field("value", &SteamStatFloatResult::value);
            serializeContext->Class<SteamAchievementResult>()->Version(0)
                ->Field("success", &SteamAchievementResult::success)
                ->Field("achieved", &SteamAchievementResult::achieved);
            serializeContext->Class<SteamAchievementAndUnlockTimeResult>()->Version(0)
                ->Field("success", &SteamAchievementAndUnlockTimeResult::success)
                ->Field("achieved", &SteamAchievementAndUnlockTimeResult::achieved)
                ->Field("unlockTime", &SteamAchievementAndUnlockTimeResult::unlockTime);
            serializeContext->Class<SteamImageSizeResult>()->Version(0)
                ->Field("success", &SteamImageSizeResult::success)
                ->Field("width", &SteamImageSizeResult::width)
                ->Field("height", &SteamImageSizeResult::height);
            serializeContext->Class<SteamFilterTextResult>()->Version(0)
                ->Field("success", &SteamFilterTextResult::success)
                ->Field("filtered", &SteamFilterTextResult::filtered);
            serializeContext->Class<SteamFileNameAndSizeResult>()->Version(0)
                ->Field("fileName", &SteamFileNameAndSizeResult::fileName)
                ->Field("size", &SteamFileNameAndSizeResult::size);
            serializeContext->Class<SteamQuotaResult>()->Version(0)
                ->Field("success", &SteamQuotaResult::success)
                ->Field("totalBytes", &SteamQuotaResult::totalBytes)
                ->Field("availableBytes", &SteamQuotaResult::availableBytes);
            serializeContext->Class<SteamItemDownloadInfoResult>()->Version(0)
                ->Field("success", &SteamItemDownloadInfoResult::success)
                ->Field("bytesDownloaded", &SteamItemDownloadInfoResult::bytesDownloaded)
                ->Field("bytesTotal", &SteamItemDownloadInfoResult::bytesTotal);
            serializeContext->Class<SteamItemInstallInfoResult>()->Version(0)
                ->Field("success", &SteamItemInstallInfoResult::success)
                ->Field("sizeOnDisk", &SteamItemInstallInfoResult::sizeOnDisk)
                ->Field("folder", &SteamItemInstallInfoResult::folder)
                ->Field("timestamp", &SteamItemInstallInfoResult::timestamp);
            serializeContext->Class<SteamSessionClientResolutionResult>()->Version(0)
                ->Field("success", &SteamSessionClientResolutionResult::success)
                ->Field("width", &SteamSessionClientResolutionResult::width)
                ->Field("height", &SteamSessionClientResolutionResult::height);
            serializeContext->Class<SteamInputDigitalActionData>()->Version(0)
                ->Field("active", &SteamInputDigitalActionData::active)
                ->Field("state", &SteamInputDigitalActionData::state);
            serializeContext->Class<SteamInputAnalogActionData>()->Version(0)
                ->Field("mode", &SteamInputAnalogActionData::mode)
                ->Field("x", &SteamInputAnalogActionData::x)
                ->Field("y", &SteamInputAnalogActionData::y)
                ->Field("active", &SteamInputAnalogActionData::active);
            serializeContext->Class<SteamGSUserStatIntResult>()->Version(0)
                ->Field("success", &SteamGSUserStatIntResult::success)
                ->Field("value", &SteamGSUserStatIntResult::value);
            serializeContext->Class<SteamGSUserStatFloatResult>()->Version(0)
                ->Field("success", &SteamGSUserStatFloatResult::success)
                ->Field("value", &SteamGSUserStatFloatResult::value);
            serializeContext->Class<SteamGSUserAchievementResult>()->Version(0)
                ->Field("success", &SteamGSUserAchievementResult::success)
                ->Field("achieved", &SteamGSUserAchievementResult::achieved);
        }

        if (auto bc = azrtti_cast<AZ::BehaviorContext*>(context))
            ReflectSteamBehaviorContext(bc);
    }

    void FoundationSteamworksSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("FoundationSteamworksService"));
    }

    void FoundationSteamworksSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC_CE("FoundationSteamworksService"));
    }

    void FoundationSteamworksSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void FoundationSteamworksSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }

    FoundationSteamworksSystemComponent::FoundationSteamworksSystemComponent()
    {
        if (FoundationSteamworksInterface::Get() == nullptr)
            FoundationSteamworksInterface::Register(this);
    }

    FoundationSteamworksSystemComponent::~FoundationSteamworksSystemComponent()
    {
        if (FoundationSteamworksInterface::Get() == this)
            FoundationSteamworksInterface::Unregister(this);
    }

    void FoundationSteamworksSystemComponent::Init()
    {
    }

    void FoundationSteamworksSystemComponent::Activate()
    {
        m_callResults = AZStd::make_unique<CallResultRegistry>();
        m_callbacks   = AZStd::make_unique<SteamCallbackRegistry>();

        FoundationSteamworksRequestBus::Handler::BusConnect();
        SteamUserRequestBus::Handler::BusConnect();
        SteamAppsRequestBus::Handler::BusConnect();
        SteamFriendsRequestBus::Handler::BusConnect();
        SteamMatchmakingRequestBus::Handler::BusConnect();
        SteamUserStatsRequestBus::Handler::BusConnect();
        SteamRemoteStorageRequestBus::Handler::BusConnect();
        SteamInventoryRequestBus::Handler::BusConnect();
        SteamUGCRequestBus::Handler::BusConnect();
        SteamUtilsRequestBus::Handler::BusConnect();
        SteamScreenshotsRequestBus::Handler::BusConnect();
        SteamRemotePlayRequestBus::Handler::BusConnect();
        SteamInputRequestBus::Handler::BusConnect();
        SteamGameServerRequestBus::Handler::BusConnect();
        SteamGameServerStatsRequestBus::Handler::BusConnect();
        AZ::TickBus::Handler::BusConnect();
    }

    void FoundationSteamworksSystemComponent::Deactivate()
    {
        AZ::TickBus::Handler::BusDisconnect();
        SteamGameServerStatsRequestBus::Handler::BusDisconnect();
        SteamGameServerRequestBus::Handler::BusDisconnect();
        SteamInputRequestBus::Handler::BusDisconnect();
        SteamRemotePlayRequestBus::Handler::BusDisconnect();
        SteamScreenshotsRequestBus::Handler::BusDisconnect();
        SteamUtilsRequestBus::Handler::BusDisconnect();
        SteamUGCRequestBus::Handler::BusDisconnect();
        SteamInventoryRequestBus::Handler::BusDisconnect();
        SteamRemoteStorageRequestBus::Handler::BusDisconnect();
        SteamUserStatsRequestBus::Handler::BusDisconnect();
        SteamMatchmakingRequestBus::Handler::BusDisconnect();
        SteamFriendsRequestBus::Handler::BusDisconnect();
        SteamAppsRequestBus::Handler::BusDisconnect();
        SteamUserRequestBus::Handler::BusDisconnect();
        FoundationSteamworksRequestBus::Handler::BusDisconnect();

        // Shut down any APIs that are still active.
        if (m_inputInitialised)
        {
            SteamInput()->Shutdown();
            m_inputInitialised = false;
        }
        if (m_gameServerInitialised)
        {
            SteamGameServer_Shutdown();
            m_gameServerInitialised = false;
        }
        if (m_steamInitialised)
        {
            m_callbacks.reset();
            m_callResults->Clear();
            SteamAPI_Shutdown();
            m_steamInitialised = false;
            AZ_TracePrintf("FoundationSteamworks", "Steam client API shut down.");
        }

        m_callbacks.reset();
        m_callResults.reset();
    }

    void FoundationSteamworksSystemComponent::OnTick([[maybe_unused]] float deltaTime, [[maybe_unused]] AZ::ScriptTimePoint time)
    {
        if (m_steamInitialised)
        {
            SteamAPI_RunCallbacks();
            m_callResults->Sweep();
        }
        if (m_gameServerInitialised)
        {
            SteamGameServer_RunCallbacks();
        }
        if (m_inputInitialised)
        {
            SteamInput()->RunFrame();
        }
    }


    // -----------------------------------------------------------------------
    // FoundationSteamworksRequestBus — lifecycle implementations
    // -----------------------------------------------------------------------

    bool FoundationSteamworksSystemComponent::Initialise(AZ::u32 appId, AZStd::string& outErrorMsg)
    {
        if (m_steamInitialised)
        {
            outErrorMsg = "Steam client API is already initialised.";
            return false;
        }

        ScopedSteamAppIdEnv appIdGuard(appId);

        SteamErrMsg errMsg{};
        ESteamAPIInitResult result = SteamAPI_InitEx(&errMsg);
        if (result != k_ESteamAPIInitResult_OK)
        {
            outErrorMsg = errMsg;
            return false;
        }

        m_steamInitialised = true;
        m_callbacks->RegisterAll();
        return true;
    }

    void FoundationSteamworksSystemComponent::Shutdown()
    {
        if (!m_steamInitialised)
        {
            return;
        }
        m_callResults->Clear();
        SteamAPI_Shutdown();
        m_steamInitialised = false;
        // Re-registering callbacks after a subsequent Initialise() call is safe —
        // RegisterAll() will bind the already-allocated STEAM_CALLBACK_MANUAL members again.
    }

    bool FoundationSteamworksSystemComponent::IsInitialised()
    {
        return m_steamInitialised;
    }

    bool FoundationSteamworksSystemComponent::GameServerInitialise(
        AZ::u32 appId,
        const AZStd::string& localIP,
        AZ::u16 gamePort,
        AZ::u16 queryPort,
        SteamServerMode serverMode,
        const AZStd::string& versionString,
        AZStd::string& outErrorMsg)
    {
        if (m_gameServerInitialised)
        {
            outErrorMsg = "Steam game server API is already initialised.";
            return false;
        }

        // Convert IP string to host-order uint32.
        // Empty string → 0 (INADDR_ANY).
        uint32 ipv4 = 0;
        if (!localIP.empty())
        {
            struct in_addr addr{};
            if (inet_pton(AF_INET, localIP.c_str(), &addr) != 1)
            {
                outErrorMsg = AZStd::string::format("Invalid IP address: \"%s\"", localIP.c_str());
                return false;
            }
            // Steam expects host byte order.
            ipv4 = ntohl(addr.s_addr);
        }

        EServerMode eMode = static_cast<EServerMode>(static_cast<AZ::s32>(serverMode));

        ScopedSteamAppIdEnv appIdGuard(appId);

        SteamErrMsg errMsg{};
        ESteamAPIInitResult result = SteamGameServer_InitEx(
            ipv4,
            gamePort,
            queryPort,
            eMode,
            versionString.c_str(),
            &errMsg);

        if (result != k_ESteamAPIInitResult_OK)
        {
            outErrorMsg = errMsg;
            return false;
        }

        m_gameServerInitialised = true;
        m_callbacks->RegisterGameServerCallbacks();
        return true;
    }

    void FoundationSteamworksSystemComponent::GameServerShutdown()
    {
        if (!m_gameServerInitialised)
        {
            return;
        }
        SteamGameServer_Shutdown();
        m_gameServerInitialised = false;
    }

    bool FoundationSteamworksSystemComponent::IsGameServerInitialised()
    {
        return m_gameServerInitialised;
    }

    bool FoundationSteamworksSystemComponent::InputInitialise()
    {
        if (!m_steamInitialised)
        {
            AZ_Warning("FoundationSteamworks", false,
                "Steam Input cannot be initialised before the Steam client API. Call Initialise() first.");
            return false;
        }
        if (m_inputInitialised)
        {
            return true;
        }
        if (!SteamInput())
        {
            return false;
        }
        bool ok = SteamInput()->Init(false);
        if (ok)
        {
            m_inputInitialised = true;
        }
        return ok;
    }

    void FoundationSteamworksSystemComponent::InputShutdown()
    {
        if (!m_inputInitialised)
        {
            return;
        }
        if (SteamInput())
        {
            SteamInput()->Shutdown();
        }
        m_inputInitialised = false;
    }

    bool FoundationSteamworksSystemComponent::IsInputInitialised()
    {
        return m_inputInitialised;
    }

    // Bus implementations for Utils, Screenshots, RemotePlay, Input, GameServer,
    // and GameServerStats live in their respective FoundationSteamworks_Xxx.cpp files.

} // namespace FoundationSteamworks
