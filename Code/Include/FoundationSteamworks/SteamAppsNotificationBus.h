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
#include <AzCore/std/containers/array.h>
#include <FoundationSteamworks/SteamTypes.h>

namespace Heathen
{
    // -----------------------------------------------------------------------
    // SteamAppsNotifications
    // Broadcasts for ISteamApps callbacks and CallResults.
    // -----------------------------------------------------------------------
    class SteamAppsNotifications
    {
    public:
        AZ_RTTI(SteamAppsNotifications, "{B2C4D5E6-8F9A-4B7D-AE4G-3F2C6D9B5E08}");
        virtual ~SteamAppsNotifications() = default;

        /// Fired when a DLC subscription status changes.
        virtual void OnDlcInstalled(SteamAppId appId) {}

        // -----------------------------------------------------------------------
        // CallResults
        // -----------------------------------------------------------------------

        /// Response to GetFileDetails.
        virtual void OnFileDetailsResult(
            SteamCallHandle callHandle,
            SteamResult result,
            AZ::u64 fileSize,
            const AZStd::array<AZ::u8, 20>& fileSha,
            AZ::u32 flags) {}

        /// Fired when the user's time trial status changes for the app.
        virtual void OnTimedTrialStatus(
            SteamAppId appId,
            bool isOffline,
            AZ::u32 secondsAllowed,
            AZ::u32 secondsPlayed) {}
    };

    class SteamAppsNotificationBusTraits : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
    };

    using SteamAppsNotificationBus = AZ::EBus<SteamAppsNotifications, SteamAppsNotificationBusTraits>;

} // namespace Heathen