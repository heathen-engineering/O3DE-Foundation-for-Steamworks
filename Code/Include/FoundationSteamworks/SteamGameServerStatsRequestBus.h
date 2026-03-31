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
    // SteamGameServerStatsRequests
    // Request bus wrapping ISteamGameServerStats.
    // Methods return result structs to be compatible with Script Canvas.
    // -----------------------------------------------------------------------
    class SteamGameServerStatsRequests
    {
    public:
        AZ_RTTI(SteamGameServerStatsRequests, "{I3J4K5L6-M7N8-4O9P-Q0R1-S2T3U4V5W6X7}");
        virtual ~SteamGameServerStatsRequests() = default;

        /// Download stats for a user. Result arrives via OnGSStatsReceived.
        virtual SteamCallHandle GSRequestUserStats(SteamId steamId) { return 0; }

        /// Returns integer stat value for a user (requires prior GSRequestUserStats).
        virtual SteamGSUserStatIntResult GSGetUserStatInt(SteamId steamId, const AZStd::string& name) { return {}; }

        /// Returns float stat value for a user (requires prior GSRequestUserStats).
        virtual SteamGSUserStatFloatResult GSGetUserStatFloat(SteamId steamId, const AZStd::string& name) { return {}; }

        /// Returns achievement unlock state for a user (requires prior GSRequestUserStats).
        virtual SteamGSUserAchievementResult GSGetUserAchievement(SteamId steamId, const AZStd::string& name) { return {}; }

        /// Set an integer stat for a user. Call GSStoreUserStats to persist.
        virtual bool GSSetUserStatInt(SteamId steamId, const AZStd::string& name, AZ::s32 value) { return false; }

        /// Set a float stat for a user. Call GSStoreUserStats to persist.
        virtual bool GSSetUserStatFloat(SteamId steamId, const AZStd::string& name, float value) { return false; }

        /// Update an average-rate stat for a user. Call GSStoreUserStats to persist.
        virtual bool GSUpdateUserAvgRateStat(SteamId steamId, const AZStd::string& name, float countThisSession, double sessionLength) { return false; }

        /// Unlock an achievement for a user. Call GSStoreUserStats to persist.
        virtual bool GSSetUserAchievement(SteamId steamId, const AZStd::string& name) { return false; }

        /// Lock (clear) an achievement for a user. Call GSStoreUserStats to persist.
        virtual bool GSClearUserAchievement(SteamId steamId, const AZStd::string& name) { return false; }

        /// Upload stat/achievement changes for a user. Result arrives via OnGSStatsStored.
        virtual SteamCallHandle GSStoreUserStats(SteamId steamId) { return 0; }
    };

    class SteamGameServerStatsBusTraits : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
    };

    using SteamGameServerStatsRequestBus = AZ::EBus<SteamGameServerStatsRequests, SteamGameServerStatsBusTraits>;
} // namespace Heathen
