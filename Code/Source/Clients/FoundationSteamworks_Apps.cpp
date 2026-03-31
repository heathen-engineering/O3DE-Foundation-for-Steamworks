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

#include <steam/steam_api.h>
#include <steam/isteamapps.h>
#include <FoundationSteamworks/SteamAppsNotificationBus.h>

using namespace Heathen;

namespace FoundationSteamworks
{
    // -----------------------------------------------------------------------
    // SteamAppsRequestBus
    // -----------------------------------------------------------------------

    bool FoundationSteamworksSystemComponent::IsSubscribed()
    {
        return m_steamInitialised && SteamApps() && SteamApps()->BIsSubscribed();
    }

    bool FoundationSteamworksSystemComponent::IsSubscribedFromFreeWeekend()
    {
        return m_steamInitialised && SteamApps() && SteamApps()->BIsSubscribedFromFreeWeekend();
    }

    bool FoundationSteamworksSystemComponent::IsSubscribedFromFamilySharing()
    {
        return m_steamInitialised && SteamApps() && SteamApps()->BIsSubscribedFromFamilySharing();
    }

    bool FoundationSteamworksSystemComponent::IsSubscribedApp(SteamAppId appId)
    {
        return m_steamInitialised && SteamApps() && SteamApps()->BIsSubscribedApp(static_cast<AppId_t>(appId));
    }

    bool FoundationSteamworksSystemComponent::IsDlcInstalled(SteamAppId appId)
    {
        return m_steamInitialised && SteamApps() && SteamApps()->BIsDlcInstalled(static_cast<AppId_t>(appId));
    }

    AZ::u32 FoundationSteamworksSystemComponent::GetEarliestPurchaseUnixTime(SteamAppId appId)
    {
        return m_steamInitialised && SteamApps() ? SteamApps()->GetEarliestPurchaseUnixTime(static_cast<AppId_t>(appId)) : 0;
    }

    bool FoundationSteamworksSystemComponent::IsLowViolence()
    {
        return m_steamInitialised && SteamApps() && SteamApps()->BIsLowViolence();
    }

    bool FoundationSteamworksSystemComponent::IsCybercafe()
    {
        return m_steamInitialised && SteamApps() && SteamApps()->BIsCybercafe();
    }

    bool FoundationSteamworksSystemComponent::IsVACBanned()
    {
        return m_steamInitialised && SteamApps() && SteamApps()->BIsVACBanned();
    }

    AZStd::string FoundationSteamworksSystemComponent::GetCurrentGameLanguage()
    {
        if (!m_steamInitialised || !SteamApps()) return {};
        const char* lang = SteamApps()->GetCurrentGameLanguage();
        return lang ? AZStd::string(lang) : AZStd::string{};
    }

    AZStd::string FoundationSteamworksSystemComponent::GetAvailableGameLanguages()
    {
        if (!m_steamInitialised || !SteamApps()) return {};
        const char* langs = SteamApps()->GetAvailableGameLanguages();
        return langs ? AZStd::string(langs) : AZStd::string{};
    }

    SteamAppId FoundationSteamworksSystemComponent::GetAppID()
    {
        return m_steamInitialised && SteamUtils() ? static_cast<SteamAppId>(SteamUtils()->GetAppID()) : 0;
    }

    AZ::s32 FoundationSteamworksSystemComponent::GetDLCCount()
    {
        return m_steamInitialised && SteamApps() ? SteamApps()->GetDLCCount() : 0;
    }

    void FoundationSteamworksSystemComponent::InstallDLC(SteamAppId appId)
    {
        if (m_steamInitialised && SteamApps())
            SteamApps()->InstallDLC(static_cast<AppId_t>(appId));
    }

    void FoundationSteamworksSystemComponent::UninstallDLC(SteamAppId appId)
    {
        if (m_steamInitialised && SteamApps())
            SteamApps()->UninstallDLC(static_cast<AppId_t>(appId));
    }

    AZStd::string FoundationSteamworksSystemComponent::GetCurrentBetaName()
    {
        if (!m_steamInitialised || !SteamApps()) return {};
        char name[256] = {};
        return SteamApps()->GetCurrentBetaName(name, sizeof(name)) ? AZStd::string(name) : AZStd::string{};
    }

    AZ::s32 FoundationSteamworksSystemComponent::GetAppBuildId()
    {
        return m_steamInitialised && SteamApps() ? SteamApps()->GetAppBuildId() : 0;
    }

    bool FoundationSteamworksSystemComponent::MarkContentCorrupt(bool missingFilesOnly)
    {
        return m_steamInitialised && SteamApps() && SteamApps()->MarkContentCorrupt(missingFilesOnly);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::GetFileDetails(const AZStd::string& fileName)
    {
        if (!m_steamInitialised || !SteamApps()) return 0;
        SteamAPICall_t call = SteamApps()->GetFileDetails(fileName.c_str());
        m_callResults->Register<FileDetailsResult_t>(call, [](SteamCallHandle h, FileDetailsResult_t* p, bool ioFail)
        {
            AZStd::array<AZ::u8, 20> sha;
            AZStd::copy(p->m_FileSHA, p->m_FileSHA + 20, sha.begin());
            SteamAppsNotificationBus::Broadcast(&SteamAppsNotifications::OnFileDetailsResult,
                h, ToSteamResult(p->m_eResult), p->m_ulFileSize, sha, p->m_unFlags);
        });
        return ToCallHandle(call);
    }

} // namespace FoundationSteamworks
