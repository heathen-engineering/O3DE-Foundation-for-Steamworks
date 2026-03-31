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
    // SteamMatchmakingNotifications
    // Broadcasts for ISteamMatchmaking callbacks and CallResults.
    // -----------------------------------------------------------------------
    class SteamMatchmakingNotifications
    {
    public:
        AZ_RTTI(SteamMatchmakingNotifications, "{D4E6F7G8-0H1C-4D9F-CG6I-5H4E8F1D7G10}");
        virtual ~SteamMatchmakingNotifications() = default;

        // -----------------------------------------------------------------------
        // Callbacks
        // -----------------------------------------------------------------------

        /// Fired when lobby metadata changes or a member joins/leaves.
        virtual void OnLobbyDataUpdate(
            SteamId lobbyId,
            SteamId memberId,
            bool success) {}

        /// Fired when a chat message is received in a lobby.
        virtual void OnLobbyChatMsg(
            SteamId lobbyId,
            SteamId userId,
            AZ::u8 chatEntryType,
            AZ::u32 chatId) {}

        /// Fired when the lobby chat state changes (member join/leave/kick/ban).
        virtual void OnLobbyChatUpdate(
            SteamId lobbyId,
            SteamId userChangedId,
            SteamId makingChangeId,
            AZ::u32 chatMemberStateChange) {}

        /// Fired when a user attempts to join this user's lobby via Steam.
        virtual void OnLobbyGameCreated(
            SteamId lobbyId,
            SteamId gameServerId,
            AZ::u32 ip,
            AZ::u16 port) {}

        /// Fired when a user attempts to join this user's lobby from the friends list or via invite.
        virtual void OnLobbyInvite(
            SteamId inviterUserId,
            SteamId lobbyId,
            AZ::u64 gameId) {}

        /// Fired when the user has been kicked from a lobby.
        virtual void OnLobbyKicked(
            SteamId lobbyId,
            SteamId adminId,
            bool kickedDueToDisconnect) {}

        // -----------------------------------------------------------------------
        // CallResults
        // -----------------------------------------------------------------------

        /// Response to CreateLobby.
        virtual void OnLobbyCreated(
            SteamCallHandle callHandle,
            SteamResult result,
            SteamId lobbyId) {}

        /// Response to JoinLobby.
        virtual void OnLobbyEntered(
            SteamCallHandle callHandle,
            SteamId lobbyId,
            AZ::u32 chatPermissions,
            bool blocked,
            AZ::u32 chatRoomEnterResponse) {}

        /// Response to RequestLobbyList.
        virtual void OnLobbyMatchList(
            SteamCallHandle callHandle,
            AZ::u32 lobbiesMatching) {}
    };

    class SteamMatchmakingNotificationBusTraits : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
    };

    using SteamMatchmakingNotificationBus = AZ::EBus<SteamMatchmakingNotifications, SteamMatchmakingNotificationBusTraits>;

} // namespace Heathen