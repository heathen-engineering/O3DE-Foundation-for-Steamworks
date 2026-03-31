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

#include <FoundationSteamworks/SteamGameServerStatsNotificationBus.h>

#include <steam/steam_api.h>
#include <steam/steam_gameserver.h>
#include <steam/isteamgameserverstats.h>

using namespace Heathen;

namespace FoundationSteamworks
{

    // -----------------------------------------------------------------------
    // SteamGameServerStatsRequestBus
    // -----------------------------------------------------------------------

    SteamCallHandle FoundationSteamworksSystemComponent::GSRequestUserStats(SteamId steamId)
    {
        if (!m_gameServerInitialised || !SteamGameServerStats()) return 0;
        SteamAPICall_t h = SteamGameServerStats()->RequestUserStats(FromSteamId(steamId));
        if (h == k_uAPICallInvalid) return 0;
        m_callResults->Register<GSStatsReceived_t>(h,
            [](SteamCallHandle ch, GSStatsReceived_t* p, bool ioFail)
            {
                SteamGameServerStatsNotificationBus::Broadcast(
                    &SteamGameServerStatsNotifications::OnGSStatsReceived,
                    ch,
                    ioFail ? SteamResult::Fail : ToSteamResult(p->m_eResult),
                    ToSteamId(p->m_steamIDUser));
            });
        return ToCallHandle(h);
    }

    SteamGSUserStatIntResult FoundationSteamworksSystemComponent::GSGetUserStatInt(SteamId steamId, const AZStd::string& name)
    {
        SteamGSUserStatIntResult out;
        if (!m_gameServerInitialised || !SteamGameServerStats()) return out;
        out.success = SteamGameServerStats()->GetUserStat(FromSteamId(steamId), name.c_str(), &out.value);
        return out;
    }

    SteamGSUserStatFloatResult FoundationSteamworksSystemComponent::GSGetUserStatFloat(SteamId steamId, const AZStd::string& name)
    {
        SteamGSUserStatFloatResult out;
        if (!m_gameServerInitialised || !SteamGameServerStats()) return out;
        out.success = SteamGameServerStats()->GetUserStat(FromSteamId(steamId), name.c_str(), &out.value);
        return out;
    }

    SteamGSUserAchievementResult FoundationSteamworksSystemComponent::GSGetUserAchievement(SteamId steamId, const AZStd::string& name)
    {
        SteamGSUserAchievementResult out;
        if (!m_gameServerInitialised || !SteamGameServerStats()) return out;
        out.success = SteamGameServerStats()->GetUserAchievement(FromSteamId(steamId), name.c_str(), &out.achieved);
        return out;
    }

    bool FoundationSteamworksSystemComponent::GSSetUserStatInt(SteamId steamId, const AZStd::string& name, AZ::s32 value)
    {
        return m_gameServerInitialised && SteamGameServerStats() &&
            SteamGameServerStats()->SetUserStat(FromSteamId(steamId), name.c_str(), value);
    }

    bool FoundationSteamworksSystemComponent::GSSetUserStatFloat(SteamId steamId, const AZStd::string& name, float value)
    {
        return m_gameServerInitialised && SteamGameServerStats() &&
            SteamGameServerStats()->SetUserStat(FromSteamId(steamId), name.c_str(), value);
    }

    bool FoundationSteamworksSystemComponent::GSUpdateUserAvgRateStat(SteamId steamId, const AZStd::string& name, float countThisSession, double sessionLength)
    {
        return m_gameServerInitialised && SteamGameServerStats() &&
            SteamGameServerStats()->UpdateUserAvgRateStat(FromSteamId(steamId), name.c_str(), countThisSession, sessionLength);
    }

    bool FoundationSteamworksSystemComponent::GSSetUserAchievement(SteamId steamId, const AZStd::string& name)
    {
        return m_gameServerInitialised && SteamGameServerStats() &&
            SteamGameServerStats()->SetUserAchievement(FromSteamId(steamId), name.c_str());
    }

    bool FoundationSteamworksSystemComponent::GSClearUserAchievement(SteamId steamId, const AZStd::string& name)
    {
        return m_gameServerInitialised && SteamGameServerStats() &&
            SteamGameServerStats()->ClearUserAchievement(FromSteamId(steamId), name.c_str());
    }

    SteamCallHandle FoundationSteamworksSystemComponent::GSStoreUserStats(SteamId steamId)
    {
        if (!m_gameServerInitialised || !SteamGameServerStats()) return 0;
        SteamAPICall_t h = SteamGameServerStats()->StoreUserStats(FromSteamId(steamId));
        if (h == k_uAPICallInvalid) return 0;
        m_callResults->Register<GSStatsStored_t>(h,
            [](SteamCallHandle ch, GSStatsStored_t* p, bool ioFail)
            {
                SteamGameServerStatsNotificationBus::Broadcast(
                    &SteamGameServerStatsNotifications::OnGSStatsStored,
                    ch,
                    ioFail ? SteamResult::Fail : ToSteamResult(p->m_eResult),
                    ToSteamId(p->m_steamIDUser));
            });
        return ToCallHandle(h);
    }

} // namespace FoundationSteamworks
