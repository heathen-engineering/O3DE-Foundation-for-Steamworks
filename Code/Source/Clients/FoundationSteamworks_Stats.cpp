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
#include <steam/isteamuserstats.h>
#include <FoundationSteamworks/SteamUserStatsNotificationBus.h>

using namespace Heathen;

namespace FoundationSteamworks
{
    // -----------------------------------------------------------------------
    // SteamUserStatsRequestBus
    // -----------------------------------------------------------------------

    bool FoundationSteamworksSystemComponent::RequestCurrentStats()
    {
        // SDK 1.63: RequestCurrentStats() was removed — stats are auto-managed by the Steam client.
        return m_steamInitialised && SteamUserStats() != nullptr;
    }

    bool FoundationSteamworksSystemComponent::StoreStats()
    {
        return m_steamInitialised && SteamUserStats() && SteamUserStats()->StoreStats();
    }

    bool FoundationSteamworksSystemComponent::GetStatInt(const AZStd::string& name, AZ::s32& outValue)
    {
        int32 v = 0;
        bool ok = m_steamInitialised && SteamUserStats() && SteamUserStats()->GetStat(name.c_str(), &v);
        if (ok) outValue = static_cast<AZ::s32>(v);
        return ok;
    }

    bool FoundationSteamworksSystemComponent::GetStatFloat(const AZStd::string& name, float& outValue)
    {
        float v = 0.f;
        bool ok = m_steamInitialised && SteamUserStats() && SteamUserStats()->GetStat(name.c_str(), &v);
        if (ok) outValue = v;
        return ok;
    }

    bool FoundationSteamworksSystemComponent::SetStatInt(const AZStd::string& name, AZ::s32 value)
    {
        return m_steamInitialised && SteamUserStats() && SteamUserStats()->SetStat(name.c_str(), static_cast<int32>(value));
    }

    bool FoundationSteamworksSystemComponent::SetStatFloat(const AZStd::string& name, float value)
    {
        return m_steamInitialised && SteamUserStats() && SteamUserStats()->SetStat(name.c_str(), value);
    }

    bool FoundationSteamworksSystemComponent::UpdateAvgRateStat(const AZStd::string& name, float countThisSession, double sessionLength)
    {
        return m_steamInitialised && SteamUserStats()
            && SteamUserStats()->UpdateAvgRateStat(name.c_str(), countThisSession, sessionLength);
    }

    bool FoundationSteamworksSystemComponent::GetAchievement(const AZStd::string& name, bool& outAchieved)
    {
        bool v = false;
        bool ok = m_steamInitialised && SteamUserStats() && SteamUserStats()->GetAchievement(name.c_str(), &v);
        if (ok) outAchieved = v;
        return ok;
    }

    bool FoundationSteamworksSystemComponent::SetAchievement(const AZStd::string& name)
    {
        return m_steamInitialised && SteamUserStats() && SteamUserStats()->SetAchievement(name.c_str());
    }

    bool FoundationSteamworksSystemComponent::ClearAchievement(const AZStd::string& name)
    {
        return m_steamInitialised && SteamUserStats() && SteamUserStats()->ClearAchievement(name.c_str());
    }

    bool FoundationSteamworksSystemComponent::GetAchievementAndUnlockTime(const AZStd::string& name, bool& outAchieved, AZ::u32& outUnlockTime)
    {
        bool achieved = false;
        uint32 unlockTime = 0;
        bool ok = m_steamInitialised && SteamUserStats()
            && SteamUserStats()->GetAchievementAndUnlockTime(name.c_str(), &achieved, &unlockTime);
        if (ok) { outAchieved = achieved; outUnlockTime = unlockTime; }
        return ok;
    }

    bool FoundationSteamworksSystemComponent::IndicateAchievementProgress(const AZStd::string& name, AZ::u32 curProgress, AZ::u32 maxProgress)
    {
        return m_steamInitialised && SteamUserStats()
            && SteamUserStats()->IndicateAchievementProgress(name.c_str(), curProgress, maxProgress);
    }

    bool FoundationSteamworksSystemComponent::ResetAllStats(bool achievementsToo)
    {
        return m_steamInitialised && SteamUserStats() && SteamUserStats()->ResetAllStats(achievementsToo);
    }

    AZ::u32 FoundationSteamworksSystemComponent::GetNumAchievements()
    {
        return m_steamInitialised && SteamUserStats() ? SteamUserStats()->GetNumAchievements() : 0;
    }

    AZStd::string FoundationSteamworksSystemComponent::GetAchievementName(AZ::u32 index)
    {
        if (!m_steamInitialised || !SteamUserStats()) return {};
        const char* name = SteamUserStats()->GetAchievementName(index);
        return name ? AZStd::string(name) : AZStd::string{};
    }

    AZStd::string FoundationSteamworksSystemComponent::GetAchievementDisplayAttribute(const AZStd::string& name, const AZStd::string& key)
    {
        if (!m_steamInitialised || !SteamUserStats()) return {};
        const char* val = SteamUserStats()->GetAchievementDisplayAttribute(name.c_str(), key.c_str());
        return val ? AZStd::string(val) : AZStd::string{};
    }

    AZ::s32 FoundationSteamworksSystemComponent::GetAchievementIcon(const AZStd::string& name)
    {
        return m_steamInitialised && SteamUserStats() ? SteamUserStats()->GetAchievementIcon(name.c_str()) : 0;
    }

    bool FoundationSteamworksSystemComponent::GetUserStatInt(SteamId userId, const AZStd::string& name, AZ::s32& outValue)
    {
        int32 v = 0;
        bool ok = m_steamInitialised && SteamUserStats() && SteamUserStats()->GetUserStat(FromSteamId(userId), name.c_str(), &v);
        if (ok) outValue = static_cast<AZ::s32>(v);
        return ok;
    }

    bool FoundationSteamworksSystemComponent::GetUserStatFloat(SteamId userId, const AZStd::string& name, float& outValue)
    {
        float v = 0.f;
        bool ok = m_steamInitialised && SteamUserStats() && SteamUserStats()->GetUserStat(FromSteamId(userId), name.c_str(), &v);
        if (ok) outValue = v;
        return ok;
    }

    bool FoundationSteamworksSystemComponent::GetUserAchievement(SteamId userId, const AZStd::string& name, bool& outAchieved)
    {
        bool v = false;
        bool ok = m_steamInitialised && SteamUserStats() && SteamUserStats()->GetUserAchievement(FromSteamId(userId), name.c_str(), &v);
        if (ok) outAchieved = v;
        return ok;
    }

    bool FoundationSteamworksSystemComponent::GetUserAchievementAndUnlockTime(SteamId userId, const AZStd::string& name, bool& outAchieved, AZ::u32& outUnlockTime)
    {
        bool achieved = false;
        uint32 unlockTime = 0;
        bool ok = m_steamInitialised && SteamUserStats()
            && SteamUserStats()->GetUserAchievementAndUnlockTime(FromSteamId(userId), name.c_str(), &achieved, &unlockTime);
        if (ok) { outAchieved = achieved; outUnlockTime = unlockTime; }
        return ok;
    }

    AZStd::string FoundationSteamworksSystemComponent::GetLeaderboardName(SteamLeaderboardHandle leaderboard)
    {
        if (!m_steamInitialised || !SteamUserStats()) return {};
        const char* name = SteamUserStats()->GetLeaderboardName(FromLeaderboardHandle(leaderboard));
        return name ? AZStd::string(name) : AZStd::string{};
    }

    AZ::s32 FoundationSteamworksSystemComponent::GetLeaderboardEntryCount(SteamLeaderboardHandle leaderboard)
    {
        return m_steamInitialised && SteamUserStats() ? SteamUserStats()->GetLeaderboardEntryCount(FromLeaderboardHandle(leaderboard)) : 0;
    }

    SteamLeaderboardSortMethod FoundationSteamworksSystemComponent::GetLeaderboardSortMethod(SteamLeaderboardHandle leaderboard)
    {
        if (!m_steamInitialised || !SteamUserStats()) return SteamLeaderboardSortMethod::None;
        return static_cast<SteamLeaderboardSortMethod>(SteamUserStats()->GetLeaderboardSortMethod(FromLeaderboardHandle(leaderboard)));
    }

    SteamLeaderboardDisplayType FoundationSteamworksSystemComponent::GetLeaderboardDisplayType(SteamLeaderboardHandle leaderboard)
    {
        if (!m_steamInitialised || !SteamUserStats()) return SteamLeaderboardDisplayType::None;
        return static_cast<SteamLeaderboardDisplayType>(SteamUserStats()->GetLeaderboardDisplayType(FromLeaderboardHandle(leaderboard)));
    }

    SteamCallHandle FoundationSteamworksSystemComponent::RequestUserStats(SteamId userId)
    {
        if (!m_steamInitialised || !SteamUserStats()) return 0;
        SteamAPICall_t call = SteamUserStats()->RequestUserStats(FromSteamId(userId));
        m_callResults->Register<UserStatsReceived_t>(call, [](SteamCallHandle h, UserStatsReceived_t* p, bool ioFail)
        {
            SteamUserStatsNotificationBus::Broadcast(&SteamUserStatsNotifications::OnRequestUserStats,
                h, ToSteamResult(p->m_eResult), ToSteamId(p->m_steamIDUser));
        });
        return ToCallHandle(call);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::FindOrCreateLeaderboard(const AZStd::string& name, SteamLeaderboardSortMethod sortMethod, SteamLeaderboardDisplayType displayType)
    {
        if (!m_steamInitialised || !SteamUserStats()) return 0;
        SteamAPICall_t call = SteamUserStats()->FindOrCreateLeaderboard(
            name.c_str(),
            static_cast<ELeaderboardSortMethod>(sortMethod),
            static_cast<ELeaderboardDisplayType>(displayType));
        m_callResults->Register<LeaderboardFindResult_t>(call, [](SteamCallHandle h, LeaderboardFindResult_t* p, bool ioFail)
        {
            bool found = p->m_bLeaderboardFound != 0;
            SteamUserStatsNotificationBus::Broadcast(&SteamUserStatsNotifications::OnFindOrCreateLeaderboard,
                h, found ? SteamResult::OK : SteamResult::Fail,
                static_cast<SteamLeaderboardHandle>(p->m_hSteamLeaderboard), found);
        });
        return ToCallHandle(call);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::FindLeaderboard(const AZStd::string& name)
    {
        if (!m_steamInitialised || !SteamUserStats()) return 0;
        SteamAPICall_t call = SteamUserStats()->FindLeaderboard(name.c_str());
        m_callResults->Register<LeaderboardFindResult_t>(call, [](SteamCallHandle h, LeaderboardFindResult_t* p, bool ioFail)
        {
            bool found = p->m_bLeaderboardFound != 0;
            SteamUserStatsNotificationBus::Broadcast(&SteamUserStatsNotifications::OnFindLeaderboard,
                h, found ? SteamResult::OK : SteamResult::Fail,
                static_cast<SteamLeaderboardHandle>(p->m_hSteamLeaderboard), found);
        });
        return ToCallHandle(call);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::DownloadLeaderboardEntries(SteamLeaderboardHandle leaderboard, SteamLeaderboardDataRequest dataRequest, AZ::s32 rangeStart, AZ::s32 rangeEnd)
    {
        if (!m_steamInitialised || !SteamUserStats()) return 0;
        SteamAPICall_t call = SteamUserStats()->DownloadLeaderboardEntries(
            FromLeaderboardHandle(leaderboard),
            static_cast<ELeaderboardDataRequest>(dataRequest),
            rangeStart, rangeEnd);
        m_callResults->Register<LeaderboardScoresDownloaded_t>(call, [](SteamCallHandle h, LeaderboardScoresDownloaded_t* p, bool ioFail)
        {
            SteamUserStatsNotificationBus::Broadcast(&SteamUserStatsNotifications::OnLeaderboardScoresDownloaded,
                h, ioFail ? SteamResult::Fail : SteamResult::OK,
                static_cast<SteamLeaderboardHandle>(p->m_hSteamLeaderboard),
                static_cast<SteamLeaderboardEntriesHandle>(p->m_hSteamLeaderboardEntries),
                p->m_cEntryCount);
        });
        return ToCallHandle(call);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::UploadLeaderboardScore(SteamLeaderboardHandle leaderboard, SteamLeaderboardUploadScoreMethod method, AZ::s32 score)
    {
        if (!m_steamInitialised || !SteamUserStats()) return 0;
        SteamAPICall_t call = SteamUserStats()->UploadLeaderboardScore(
            FromLeaderboardHandle(leaderboard),
            static_cast<ELeaderboardUploadScoreMethod>(method),
            static_cast<int32>(score), nullptr, 0);
        m_callResults->Register<LeaderboardScoreUploaded_t>(call, [](SteamCallHandle h, LeaderboardScoreUploaded_t* p, bool ioFail)
        {
            SteamUserStatsNotificationBus::Broadcast(&SteamUserStatsNotifications::OnLeaderboardScoreUploaded,
                h, p->m_bSuccess != 0, static_cast<SteamLeaderboardHandle>(p->m_hSteamLeaderboard),
                p->m_nScore, p->m_bScoreChanged != 0, p->m_nGlobalRankNew, p->m_nGlobalRankPrevious);
        });
        return ToCallHandle(call);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::GetNumberOfCurrentPlayers()
    {
        if (!m_steamInitialised || !SteamUserStats()) return 0;
        SteamAPICall_t call = SteamUserStats()->GetNumberOfCurrentPlayers();
        m_callResults->Register<NumberOfCurrentPlayers_t>(call, [](SteamCallHandle h, NumberOfCurrentPlayers_t* p, bool ioFail)
        {
            SteamUserStatsNotificationBus::Broadcast(&SteamUserStatsNotifications::OnNumberOfCurrentPlayers,
                h, p->m_bSuccess != 0, p->m_cPlayers);
        });
        return ToCallHandle(call);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::RequestGlobalAchievementPercentages()
    {
        if (!m_steamInitialised || !SteamUserStats()) return 0;
        SteamAPICall_t call = SteamUserStats()->RequestGlobalAchievementPercentages();
        m_callResults->Register<GlobalAchievementPercentagesReady_t>(call, [](SteamCallHandle h, GlobalAchievementPercentagesReady_t* p, bool ioFail)
        {
            SteamUserStatsNotificationBus::Broadcast(&SteamUserStatsNotifications::OnGlobalAchievementPercentagesReady,
                h, p->m_nGameID, ToSteamResult(p->m_eResult));
        });
        return ToCallHandle(call);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::RequestGlobalStats(AZ::s32 historyDays)
    {
        if (!m_steamInitialised || !SteamUserStats()) return 0;
        SteamAPICall_t call = SteamUserStats()->RequestGlobalStats(historyDays);
        m_callResults->Register<GlobalStatsReceived_t>(call, [](SteamCallHandle h, GlobalStatsReceived_t* p, bool ioFail)
        {
            SteamUserStatsNotificationBus::Broadcast(&SteamUserStatsNotifications::OnGlobalStatsReceived,
                h, p->m_nGameID, ToSteamResult(p->m_eResult));
        });
        return ToCallHandle(call);
    }

} // namespace FoundationSteamworks
