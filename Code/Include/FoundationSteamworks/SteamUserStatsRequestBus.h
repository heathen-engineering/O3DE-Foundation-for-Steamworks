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
#include <AzCore/std/string/string.h>
#include <FoundationSteamworks/SteamTypes.h>

namespace Heathen
{
    // -----------------------------------------------------------------------
    // SteamUserStatsRequests
    // Request bus wrapping ISteamUserStats.
    // Stats, achievements, and leaderboards.
    // -----------------------------------------------------------------------
    class SteamUserStatsRequests
    {
    public:
        AZ_RTTI(SteamUserStatsRequests, "{E5F6A7B8-C9DA-4EBF-C012-C3D4E5F6A7B9}");
        virtual ~SteamUserStatsRequests() = default;

        // --- Local Stats / Achievements ---

        /// Requests the current stats and achievements from Steam for the local user.
        /// The result arrives via SteamUserStatsNotifications::OnUserStatsReceived.
        virtual bool RequestCurrentStats() { return false; }

        /// Uploads the current local stat/achievement state to Steam.
        /// The result arrives via SteamUserStatsNotifications::OnUserStatsStored.
        virtual bool StoreStats() { return false; }

        /// Returns the integer value of a stat for the local user.
        virtual bool GetStatInt(const AZStd::string& name, AZ::s32& outValue) { return false; }

        /// Returns the float value of a stat for the local user.
        virtual bool GetStatFloat(const AZStd::string& name, float& outValue) { return false; }

        /// Sets an integer stat for the local user (call StoreStats to persist).
        virtual bool SetStatInt(const AZStd::string& name, AZ::s32 value) { return false; }

        /// Sets a float stat for the local user (call StoreStats to persist).
        virtual bool SetStatFloat(const AZStd::string& name, float value) { return false; }

        /// Updates an average-rate stat, contributing the given count over the session duration.
        virtual bool UpdateAvgRateStat(const AZStd::string& name, float countThisSession, double sessionLength) { return false; }

        /// Returns whether the local user has unlocked the given achievement.
        virtual bool GetAchievement(const AZStd::string& name, bool& outAchieved) { return false; }

        /// Unlocks an achievement for the local user (call StoreStats to persist).
        virtual bool SetAchievement(const AZStd::string& name) { return false; }

        /// Resets (locks) an achievement for the local user (call StoreStats to persist).
        virtual bool ClearAchievement(const AZStd::string& name) { return false; }

        /// Returns the unlock time of an achievement (0 if locked or unknown).
        /// outAchieved and outUnlockTime are set on success.
        virtual bool GetAchievementAndUnlockTime(const AZStd::string& name, bool& outAchieved, AZ::u32& outUnlockTime) { return false; }

        /// Shows incremental progress toward an achievement.
        /// Does NOT unlock the achievement — call SetAchievement when complete.
        virtual bool IndicateAchievementProgress(const AZStd::string& name, AZ::u32 curProgress, AZ::u32 maxProgress) { return false; }

        /// Resets all stats and optionally all achievements for the local user.
        virtual bool ResetAllStats(bool achievementsToo) { return false; }

        // --- Achievement Metadata ---

        /// Returns the number of achievements defined for this app.
        virtual AZ::u32 GetNumAchievements() { return 0; }

        /// Returns the internal name of the achievement at the given index.
        virtual AZStd::string GetAchievementName(AZ::u32 index) { return {}; }

        /// Returns a display attribute for an achievement (keys: "name", "desc", "hidden").
        virtual AZStd::string GetAchievementDisplayAttribute(const AZStd::string& name, const AZStd::string& key) { return {}; }

        /// Returns the image handle for the achievement icon (use ISteamUtils::GetImageRGBA to decode).
        virtual AZ::s32 GetAchievementIcon(const AZStd::string& name) { return 0; }

        // --- Other Users' Stats ---

        /// Returns the integer stat value for another user. RequestUserStats must have completed first.
        virtual bool GetUserStatInt(SteamId userId, const AZStd::string& name, AZ::s32& outValue) { return false; }

        /// Returns the float stat value for another user. RequestUserStats must have completed first.
        virtual bool GetUserStatFloat(SteamId userId, const AZStd::string& name, float& outValue) { return false; }

        /// Returns whether another user has unlocked an achievement. RequestUserStats must have completed first.
        virtual bool GetUserAchievement(SteamId userId, const AZStd::string& name, bool& outAchieved) { return false; }

        /// Returns unlock achievement info for another user. RequestUserStats must have completed first.
        virtual bool GetUserAchievementAndUnlockTime(SteamId userId, const AZStd::string& name, bool& outAchieved, AZ::u32& outUnlockTime) { return false; }

        // --- Leaderboard Queries (synchronous, requires handle) ---

        /// Returns the display name of a leaderboard.
        virtual AZStd::string GetLeaderboardName(SteamLeaderboardHandle leaderboard) { return {}; }

        /// Returns the total number of entries in a leaderboard.
        virtual AZ::s32 GetLeaderboardEntryCount(SteamLeaderboardHandle leaderboard) { return 0; }

        /// Returns the sort method of a leaderboard.
        virtual SteamLeaderboardSortMethod GetLeaderboardSortMethod(SteamLeaderboardHandle leaderboard) { return SteamLeaderboardSortMethod::None; }

        /// Returns the display type of a leaderboard.
        virtual SteamLeaderboardDisplayType GetLeaderboardDisplayType(SteamLeaderboardHandle leaderboard) { return SteamLeaderboardDisplayType::None; }

        // --- Async (result via SteamUserStatsNotificationBus) ---

        /// Requests stats for another user.
        /// Returns a SteamCallHandle correlating with OnUserStatsReceived.
        virtual SteamCallHandle RequestUserStats(SteamId userId) { return 0; }

        /// Finds a leaderboard by name, creating it if it does not exist.
        /// Returns a SteamCallHandle correlating with OnFindOrCreateLeaderboard / OnFindLeaderboard.
        virtual SteamCallHandle FindOrCreateLeaderboard(
            const AZStd::string& name,
            SteamLeaderboardSortMethod sortMethod,
            SteamLeaderboardDisplayType displayType) { return 0; }

        /// Finds an existing leaderboard by name.
        /// Returns a SteamCallHandle correlating with OnFindOrCreateLeaderboard / OnFindLeaderboard.
        virtual SteamCallHandle FindLeaderboard(const AZStd::string& name) { return 0; }

        /// Downloads leaderboard entries for a range of ranks.
        /// Returns a SteamCallHandle correlating with OnLeaderboardScoresDownloaded.
        virtual SteamCallHandle DownloadLeaderboardEntries(
            SteamLeaderboardHandle leaderboard,
            SteamLeaderboardDataRequest dataRequest,
            AZ::s32 rangeStart,
            AZ::s32 rangeEnd) { return 0; }

        /// Uploads a score to a leaderboard.
        /// Returns a SteamCallHandle correlating with OnLeaderboardScoreUploaded.
        virtual SteamCallHandle UploadLeaderboardScore(
            SteamLeaderboardHandle leaderboard,
            SteamLeaderboardUploadScoreMethod method,
            AZ::s32 score) { return 0; }

        /// Returns the number of players currently playing this app.
        /// Returns a SteamCallHandle correlating with OnNumberOfCurrentPlayers.
        virtual SteamCallHandle GetNumberOfCurrentPlayers() { return 0; }

        /// Requests the global achievement unlock percentages for this app.
        /// Returns a SteamCallHandle correlating with OnGlobalAchievementPercentagesReady.
        virtual SteamCallHandle RequestGlobalAchievementPercentages() { return 0; }

        /// Requests historical global stat data.
        /// historyDays: number of days of history to request (max 60).
        /// Returns a SteamCallHandle correlating with OnGlobalStatsReceived.
        virtual SteamCallHandle RequestGlobalStats(AZ::s32 historyDays) { return 0; }
    };

    class SteamUserStatsRequestBusTraits : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
    };

    using SteamUserStatsRequestBus = AZ::EBus<SteamUserStatsRequests, SteamUserStatsRequestBusTraits>;

} // namespace Heathen