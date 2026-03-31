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
#include <AzCore/std/containers/vector.h>
#include <FoundationSteamworks/SteamTypes.h>

namespace Heathen
{
    // -----------------------------------------------------------------------
    // SteamUserRequests
    // Request bus wrapping ISteamUser.
    // Synchronous calls return values directly.
    // Async calls return a SteamCallHandle (0 = invalid) that correlates with
    // the matching SteamUserNotificationBus callback when the result arrives.
    // -----------------------------------------------------------------------
    class SteamUserRequests
    {
    public:
        AZ_RTTI(SteamUserRequests, "{A1B2C3D4-E5F6-4A7B-8C9D-E0F1A2B3C4D5}");
        virtual ~SteamUserRequests() = default;

        // --- Identity ---

        /// Returns true if the user is currently connected to Steam.
        virtual bool IsLoggedOn() { return false; }

        /// Returns the SteamID of the currently logged-in local user.
        virtual SteamId GetSteamID() { return 0; }

        /// Returns the current Steam level of the local user.
        virtual AZ::s32 GetPlayerSteamLevel() { return 0; }

        /// Returns the badge level for the given app badge series.
        /// series: 1 for the standard badge, higher for foil/special.
        virtual AZ::s32 GetGameBadgeLevel(AZ::s32 series, bool foil) { return 0; }

        // --- Auth Tickets ---

        /// Requests an auth session ticket for web API use.
        /// identity: the service identity string (e.g. "steamcommunity.com").
        /// Returns a HAuthTicket handle. The actual ticket data arrives via
        /// SteamUserNotifications::OnGetAuthSessionTicketResponse.
        virtual SteamAuthTicketHandle GetAuthTicketForWebApi(const AZStd::string& identity) { return 0; }

        /// Cancels a previously requested auth ticket.
        virtual void CancelAuthTicket(SteamAuthTicketHandle handle) {}

        // --- Async calls (result via SteamUserNotificationBus) ---

        /// Requests a store auth URL for the overlay browser.
        /// Returns a SteamCallHandle correlating with OnStoreAuthURLResponse.
        virtual SteamCallHandle RequestStoreAuthURL(const AZStd::string& redirectURL) { return 0; }

        /// Checks whether this user is eligible for the Steam market.
        /// Returns a SteamCallHandle correlating with OnMarketEligibilityResponse.
        virtual SteamCallHandle GetMarketEligibility() { return 0; }

        /// Retrieves duration-control status for the current user.
        /// Returns a SteamCallHandle correlating with OnDurationControl.
        virtual SteamCallHandle GetDurationControl() { return 0; }

        /// Requests an encrypted app ticket to send to your own game server.
        /// dataToInclude: optional user data to embed in the ticket.
        /// Returns a SteamCallHandle correlating with OnEncryptedAppTicketResponse.
        virtual SteamCallHandle RequestEncryptedAppTicket(const AZStd::vector<AZ::u8>& dataToInclude) { return 0; }
    };

    class SteamUserRequestBusTraits : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
    };

    using SteamUserRequestBus = AZ::EBus<SteamUserRequests, SteamUserRequestBusTraits>;

} // namespace Heathen