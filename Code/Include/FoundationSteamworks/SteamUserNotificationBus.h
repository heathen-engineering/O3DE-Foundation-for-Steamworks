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
    // SteamUserNotifications
    // Broadcasts for ISteamUser callbacks and CallResults.
    // CallResult notifications include the SteamCallHandle returned by the
    // initiating request so listeners can correlate responses to requests.
    // -----------------------------------------------------------------------
    class SteamUserNotifications
    {
    public:
        AZ_RTTI(SteamUserNotifications, "{A1F3C2D4-7B8E-4A6C-9D3F-2E1B5C8A4F07}");
        virtual ~SteamUserNotifications() = default;

        // -----------------------------------------------------------------------
        // Callbacks — unsolicited broadcasts from Steam
        // -----------------------------------------------------------------------

        /// Fired when the current user's Steam client has connected to Steam backend servers.
        virtual void OnSteamConnected() {}

        /// Fired when the connection to Steam backend servers is lost.
        /// bSteamServersDisconnected_t::m_eResult normalised to SteamResult.
        virtual void OnSteamDisconnected(SteamResult reason) {}

        /// Fired when the current user's persona name or avatar has changed.
        virtual void OnPersonaStateChanged(SteamId userId, AZ::u32 changeFlags) {}

        /// Fired when a Steam authentication ticket has been validated.
        /// Corresponds to ValidateAuthTicketResponse_t.
        virtual void OnValidateAuthTicketResponse(
            SteamId steamId,
            AZ::s32 authSessionResponse,
            SteamId ownerSteamId) {}

        /// Fired when a game web callback is received.
        virtual void OnGameWebCallback(const AZStd::string& url) {}

        /// Fired when a GetAuthSessionTicket call completes (callback, not CallResult).
        virtual void OnGetAuthSessionTicketResponse(
            SteamAuthTicketHandle ticketHandle,
            SteamResult result) {}

        // -----------------------------------------------------------------------
        // CallResults — responses to explicit API requests
        // All include the SteamCallHandle for request correlation.
        // -----------------------------------------------------------------------

        /// Response to RequestEncryptedAppTicket.
        virtual void OnEncryptedAppTicketResponse(
            SteamCallHandle callHandle,
            SteamResult result) {}

        /// Response to RequestStoreAuthURL.
        virtual void OnStoreAuthURLResponse(
            SteamCallHandle callHandle,
            const AZStd::string& url) {}

        /// Response to GetMarketEligibility.
        virtual void OnMarketEligibilityResponse(
            SteamCallHandle callHandle,
            bool allowed,
            AZ::u32 notAllowedReason) {}

        /// Response to GetDurationControl.
        virtual void OnDurationControl(
            SteamCallHandle callHandle,
            SteamResult result,
            AZ::s32 applicable,
            AZ::s32 secondsLastFiveHours,
            AZ::s32 progress,
            AZ::s32 notification) {}
    };

    class SteamUserNotificationBusTraits : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
    };

    using SteamUserNotificationBus = AZ::EBus<SteamUserNotifications, SteamUserNotificationBusTraits>;

} // namespace Heathen