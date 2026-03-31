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
    // SteamGameServerNotifications
    // Broadcasts for ISteamGameServer callbacks and CallResults.
    // -----------------------------------------------------------------------
    class SteamGameServerNotifications
    {
    public:
        AZ_RTTI(SteamGameServerNotifications, "{H2I3J4K5-L6M7-4N8O-P9Q0-R1S2T3U4V5W6}");
        virtual ~SteamGameServerNotifications() = default;

        // -----------------------------------------------------------------------
        // Callbacks (game server context)
        // -----------------------------------------------------------------------

        /// A client has been approved to connect.
        virtual void OnGSClientApprove(SteamId steamId, SteamId ownerSteamId) {}

        /// A client has been denied (e.g. VAC ban, wrong version, etc.).
        /// denyReason is EDenyReason cast to s32. optionalText provides extra detail.
        virtual void OnGSClientDeny(SteamId steamId, AZ::s32 denyReason, const AZStd::string& optionalText) {}

        /// Steam has responded to our request to be listed as secure (VAC-enabled).
        virtual void OnGSPolicyResponse(bool secure) {}

        /// Validation result for a ticket from BeginAuthSession.
        /// authSessionResponse is EAuthSessionResponse cast to s32.
        virtual void OnGSValidateAuthTicketResponse(SteamId steamId, AZ::s32 authSessionResponse, SteamId ownerSteamId) {}

        /// Result of RequestUserGroupStatus.
        virtual void OnGSClientGroupStatus(SteamId userId, SteamId groupId, bool member, bool officer) {}

        // -----------------------------------------------------------------------
        // CallResult forwarded notifications
        // -----------------------------------------------------------------------

        /// Result of AssociateWithClan.
        virtual void OnAssociateWithClanResult(SteamCallHandle callHandle, SteamResult result) {}

        /// Result of ComputeNewPlayerCompatibility.
        virtual void OnComputeNewPlayerCompatibilityResult(
            SteamCallHandle callHandle,
            SteamResult result,
            AZ::s32 playersThatDontLikeCandidate,
            AZ::s32 playersThatCandidateDoesntLike,
            AZ::s32 clanPlayersThatDontLikeCandidate,
            SteamId candidateSteamId) {}

        /// Result of GetServerReputation.
        virtual void OnServerReputation(
            SteamCallHandle callHandle,
            SteamResult result,
            AZ::u32 reputationScore,
            bool banned,
            AZ::u32 bannedIp,
            AZ::u16 bannedPort,
            AZ::u64 bannedGameId,
            AZ::u32 banExpires) {}
    };

    class SteamGameServerNotificationBusTraits : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
    };

    using SteamGameServerNotificationBus = AZ::EBus<SteamGameServerNotifications, SteamGameServerNotificationBusTraits>;
} // namespace Heathen
