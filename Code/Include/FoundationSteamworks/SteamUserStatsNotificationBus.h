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
#include <FoundationSteamworks/SteamTypes.h>

namespace Heathen
{
    // -----------------------------------------------------------------------
    // SteamUserStatsNotifications
    // Broadcasts for ISteamUserStats callbacks and CallResults.
    // -----------------------------------------------------------------------
    class SteamUserStatsNotifications
    {
    public:
        AZ_RTTI(SteamUserStatsNotifications, "{E5F7G8H9-1I2D-4EAG-DH7J-6I5F9G2E8H11}");
        virtual ~SteamUserStatsNotifications() = default;

        // -----------------------------------------------------------------------
        // Callbacks
        // -----------------------------------------------------------------------

        /// Fired when the current user's stats and achievements have been received from Steam.
        virtual void OnUserStatsReceived(
            AZ::u64 gameId,
            SteamResult result,
            SteamId userId) {}

        /// Fired when stats have been stored to Steam servers.
        virtual void OnUserStatsStored(
            AZ::u64 gameId,
            SteamResult result) {}

        /// Fired when an achievement has been stored.
        virtual void OnUserAchievementStored(
            AZ::u64 gameId,
            bool groupAchievement,
            const AZStd::string& achievementName,
            AZ::u32 curProgress,
            AZ::u32 maxProgress) {}

        /// Fired when the stats for another user have been received.
        virtual void OnUserStatsUnloaded(SteamId userId) {}

        /// Fired when an achievement icon is available.
        virtual void OnUserAchievementIconFetched(
            AZ::u64 gameId,
            const AZStd::string& achievementName,
            bool achieved,
            AZ::s32 iconHandle) {}

        // -----------------------------------------------------------------------
        // CallResults
        // -----------------------------------------------------------------------

        /// Response to RequestUserStats.
        virtual void OnRequestUserStats(
            SteamCallHandle callHandle,
            SteamResult result,
            SteamId userId) {}

        /// Response to FindOrCreateLeaderboard.
        virtual void OnFindOrCreateLeaderboard(
            SteamCallHandle callHandle,
            SteamResult result,
            SteamLeaderboardHandle leaderboard,
            bool leaderboardFound) {}

        /// Response to FindLeaderboard.
        virtual void OnFindLeaderboard(
            SteamCallHandle callHandle,
            SteamResult result,
            SteamLeaderboardHandle leaderboard,
            bool leaderboardFound) {}

        /// Response to UploadLeaderboardScore.
        virtual void OnLeaderboardScoreUploaded(
            SteamCallHandle callHandle,
            bool success,
            SteamLeaderboardHandle leaderboard,
            AZ::s32 score,
            bool scoreChanged,
            AZ::s32 globalRankNew,
            AZ::s32 globalRankPrevious) {}

        /// Response to DownloadLeaderboardEntries / DownloadLeaderboardEntriesForUsers.
        virtual void OnLeaderboardScoresDownloaded(
            SteamCallHandle callHandle,
            SteamResult result,
            SteamLeaderboardHandle leaderboard,
            SteamLeaderboardEntriesHandle entries,
            AZ::s32 entryCount) {}

        /// Response to AttachLeaderboardUGC.
        virtual void OnLeaderboardUGCSet(
            SteamCallHandle callHandle,
            SteamResult result,
            SteamLeaderboardHandle leaderboard) {}

        /// Response to GetNumberOfCurrentPlayers.
        virtual void OnNumberOfCurrentPlayers(
            SteamCallHandle callHandle,
            bool success,
            AZ::s32 players) {}

        /// Response to RequestGlobalAchievementPercentages.
        virtual void OnGlobalAchievementPercentagesReady(
            SteamCallHandle callHandle,
            AZ::u64 gameId,
            SteamResult result) {}

        /// Response to RequestGlobalStats.
        virtual void OnGlobalStatsReceived(
            SteamCallHandle callHandle,
            AZ::u64 gameId,
            SteamResult result) {}
    };

    class SteamUserStatsNotificationBusTraits : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
    };

    using SteamUserStatsNotificationBus = AZ::EBus<SteamUserStatsNotifications, SteamUserStatsNotificationBusTraits>;

} // namespace Heathen