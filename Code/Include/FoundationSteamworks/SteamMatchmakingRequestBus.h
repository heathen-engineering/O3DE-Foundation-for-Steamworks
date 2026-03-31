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
    // SteamMatchmakingRequests
    // Request bus wrapping ISteamMatchmaking (lobby API).
    // -----------------------------------------------------------------------
    class SteamMatchmakingRequests
    {
    public:
        AZ_RTTI(SteamMatchmakingRequests, "{D4E5F6A7-B8C9-4DAE-BF01-B2C3D4E5F6A8}");
        virtual ~SteamMatchmakingRequests() = default;

        // --- Lobby Queries ---

        /// Returns the number of members currently in the given lobby.
        virtual AZ::s32 GetNumLobbyMembers(SteamId lobbyId) { return 0; }

        /// Returns the SteamID of the lobby member at the given index (0-based).
        virtual SteamId GetLobbyMemberByIndex(SteamId lobbyId, AZ::s32 index) { return 0; }

        /// Returns the value of a lobby metadata key, or empty string if not set.
        virtual AZStd::string GetLobbyData(SteamId lobbyId, const AZStd::string& key) { return {}; }

        /// Sets a lobby metadata key/value pair. Only the lobby owner may call this.
        virtual bool SetLobbyData(SteamId lobbyId, const AZStd::string& key, const AZStd::string& value) { return false; }

        /// Deletes a lobby metadata key. Only the lobby owner may call this.
        virtual bool DeleteLobbyData(SteamId lobbyId, const AZStd::string& key) { return false; }

        /// Returns the per-member metadata for a given lobby member.
        virtual AZStd::string GetLobbyMemberData(SteamId lobbyId, SteamId memberId, const AZStd::string& key) { return {}; }

        /// Sets per-member metadata for the local user in the given lobby.
        virtual void SetLobbyMemberData(SteamId lobbyId, const AZStd::string& key, const AZStd::string& value) {}

        /// Returns the SteamID of the owner of the given lobby.
        virtual SteamId GetLobbyOwner(SteamId lobbyId) { return 0; }

        /// Transfers ownership of the lobby to another member.
        virtual bool SetLobbyOwner(SteamId lobbyId, SteamId newOwnerId) { return false; }

        /// Requests a refresh of the metadata for the given lobby.
        virtual bool RequestLobbyData(SteamId lobbyId) { return false; }

        /// Sets whether the lobby allows new members to join.
        virtual bool SetLobbyJoinable(SteamId lobbyId, bool joinable) { return false; }

        /// Sets the maximum number of members allowed in the lobby.
        virtual bool SetLobbyMemberLimit(SteamId lobbyId, AZ::s32 maxMembers) { return false; }

        /// Returns the maximum number of members allowed in the lobby.
        virtual AZ::s32 GetLobbyMemberLimit(SteamId lobbyId) { return 0; }

        // --- Lobby Lifecycle ---

        /// Invites a user to the given lobby.
        virtual bool InviteUserToLobby(SteamId lobbyId, SteamId inviteeId) { return false; }

        /// Leaves the given lobby.
        virtual void LeaveLobby(SteamId lobbyId) {}

        // --- Lobby List Filters (call before RequestLobbyList) ---

        /// Filters lobby list results to lobbies with matching string metadata.
        virtual void AddRequestLobbyListStringFilter(
            const AZStd::string& keyToMatch,
            const AZStd::string& valueToMatch,
            SteamLobbyComparison comparison) {}

        /// Filters lobby list results to lobbies with matching numeric metadata.
        virtual void AddRequestLobbyListNumericalFilter(
            const AZStd::string& keyToMatch,
            AZ::s32 valueToMatch,
            SteamLobbyComparison comparison) {}

        /// Filters lobby list results by proximity to a numeric metadata value.
        virtual void AddRequestLobbyListNearValueFilter(
            const AZStd::string& keyToMatch,
            AZ::s32 valueToBeCloseTo) {}

        /// Filters lobby list results by the number of open slots available.
        virtual void AddRequestLobbyListFilterSlotsAvailable(AZ::s32 slotsAvailable) {}

        /// Filters lobby list results by geographic distance.
        virtual void AddRequestLobbyListDistanceFilter(SteamLobbyDistanceFilter distanceFilter) {}

        /// Limits the maximum number of results returned by RequestLobbyList.
        virtual void AddRequestLobbyListResultCountFilter(AZ::s32 maxResults) {}

        // --- Async (result via SteamMatchmakingNotificationBus) ---

        /// Creates a new lobby of the given type.
        /// Returns a SteamCallHandle correlating with OnLobbyCreated.
        virtual SteamCallHandle CreateLobby(SteamLobbyType lobbyType, AZ::s32 maxMembers) { return 0; }

        /// Joins an existing lobby.
        /// Returns a SteamCallHandle correlating with OnLobbyEntered.
        virtual SteamCallHandle JoinLobby(SteamId lobbyId) { return 0; }

        /// Requests a list of lobbies matching the active filters.
        /// Returns a SteamCallHandle correlating with OnLobbyMatchList.
        virtual SteamCallHandle RequestLobbyList() { return 0; }
    };

    class SteamMatchmakingRequestBusTraits : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
    };

    using SteamMatchmakingRequestBus = AZ::EBus<SteamMatchmakingRequests, SteamMatchmakingRequestBusTraits>;

} // namespace Heathen