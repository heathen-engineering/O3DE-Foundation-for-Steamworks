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

#pragma once

#include <AzCore/EBus/EBus.h>
#include <AzCore/Interface/Interface.h>
#include <AzCore/std/string/string.h>
#include <FoundationSteamworks/SteamTypes.h>

namespace FoundationSteamworks
{
    // -----------------------------------------------------------------------
    // FoundationSteamworksRequests
    // Core lifecycle bus — on-demand init and shutdown for each Steam API.
    // The developer controls timing and which surfaces are brought up.
    // -----------------------------------------------------------------------
    class FoundationSteamworksRequests
    {
    public:
        AZ_RTTI(FoundationSteamworksRequests, "{2EC1E2D0-CF46-4F7C-ABC2-754D86125D95}");
        virtual ~FoundationSteamworksRequests() = default;

        // --- Steam Client API ---

        /// Initialise the Steam client API. Returns true on success.
        /// appId:      Your Steam App ID. When non-zero and running inside the O3DE
        ///             editor, the SDK is told the App ID via the SteamAppId environment
        ///             variable so that steam_appid.txt is not required.
        ///             Pass 0 in packaged builds — Steam is launched through the client
        ///             and already knows the App ID.
        /// outErrorMsg is populated on failure.
        virtual bool Initialise(AZ::u32 appId, AZStd::string& outErrorMsg) { (void)appId; outErrorMsg = "Not implemented"; return false; }

        /// Shut down the Steam client API. Safe to call if not initialised.
        virtual void Shutdown() {}

        /// Returns true if the Steam client API is active.
        virtual bool IsInitialised() { return false; }

        // --- Steam Game Server API ---

        /// Initialise the Steam game server API.
        /// appId:         Your Steam App ID. When non-zero and running inside the O3DE
        ///                editor, the SDK is told the App ID via the SteamAppId environment
        ///                variable so that steam_appid.txt is not required.
        ///                Pass 0 in packaged builds.
        /// localIP:       Bind address as "x.x.x.x", or "" to use any interface.
        /// gamePort:      Port clients connect to for gameplay.
        /// queryPort:     Port for server browser queries.
        ///                Pass SteamGameServerQueryPortShared (0xFFFF) to share gamePort.
        /// serverMode:    Authentication and VAC policy (SteamServerMode enum).
        /// versionString: App version string in "x.x.x.x" format.
        /// outErrorMsg:   Populated on failure.
        /// Returns true on success.
        virtual bool GameServerInitialise(
            AZ::u32 appId,
            const AZStd::string& localIP,
            AZ::u16 gamePort,
            AZ::u16 queryPort,
            Heathen::SteamServerMode serverMode,
            const AZStd::string& versionString,
            AZStd::string& outErrorMsg)
        {
            (void)appId; (void)localIP; (void)gamePort; (void)queryPort;
            (void)serverMode; (void)versionString;
            outErrorMsg = "Not implemented"; return false;
        }

        /// Shut down the Steam game server API. Safe to call if not initialised.
        virtual void GameServerShutdown() {}

        /// Returns true if the Steam game server API is active.
        virtual bool IsGameServerInitialised() { return false; }

        // --- Steam Input API ---

        /// Initialise Steam Input. RunFrame is called automatically each tick.
        /// Returns true on success.
        virtual bool InputInitialise() { return false; }

        /// Shut down Steam Input. Safe to call if not initialised.
        virtual void InputShutdown() {}

        /// Returns true if Steam Input is active.
        virtual bool IsInputInitialised() { return false; }
    };

    class FoundationSteamworksBusTraits : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
    };

    using FoundationSteamworksRequestBus = AZ::EBus<FoundationSteamworksRequests, FoundationSteamworksBusTraits>;
    using FoundationSteamworksInterface  = AZ::Interface<FoundationSteamworksRequests>;

} // namespace FoundationSteamworks
