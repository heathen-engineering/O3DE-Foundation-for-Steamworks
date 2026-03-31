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
    // SteamGameServerStatsNotifications
    // Broadcasts for ISteamGameServerStats callbacks and CallResults.
    // -----------------------------------------------------------------------
    class SteamGameServerStatsNotifications
    {
    public:
        AZ_RTTI(SteamGameServerStatsNotifications, "{J4K5L6M7-N8O9-4P0Q-R1S2-T3U4V5W6X7Y8}");
        virtual ~SteamGameServerStatsNotifications() = default;

        /// Fired when stat/achievement data for a user has been downloaded from Steam.
        /// This is the CallResult from GSRequestUserStats.
        virtual void OnGSStatsReceived(SteamCallHandle callHandle, SteamResult result, SteamId steamId) {}

        /// Fired when stat/achievement data for a user has been stored to Steam.
        /// This is the CallResult from GSStoreUserStats.
        virtual void OnGSStatsStored(SteamCallHandle callHandle, SteamResult result, SteamId steamId) {}
    };

    class SteamGameServerStatsNotificationBusTraits : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
    };

    using SteamGameServerStatsNotificationBus = AZ::EBus<SteamGameServerStatsNotifications, SteamGameServerStatsNotificationBusTraits>;
} // namespace Heathen
