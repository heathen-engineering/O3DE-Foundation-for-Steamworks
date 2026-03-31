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
    // SteamFriendsNotifications
    // Broadcasts for ISteamFriends callbacks and CallResults.
    // -----------------------------------------------------------------------
    class SteamFriendsNotifications
    {
    public:
        AZ_RTTI(SteamFriendsNotifications, "{C3D5E6F7-9G0B-4C8E-BF5H-4G3D7E0C6F09}");
        virtual ~SteamFriendsNotifications() = default;

        // -----------------------------------------------------------------------
        // Callbacks
        // -----------------------------------------------------------------------

        /// Fired when the local user's persona state changes (name, avatar, status).
        virtual void OnPersonaStateChange(SteamId userId, AZ::u32 changeFlags) {}

        /// Fired when a friend's game info changes (they join or leave a game).
        virtual void OnGameConnectedFriendChatMsg(SteamId friendId, AZ::s32 messageId) {}

        /// Fired when a clan chat message is received in a game.
        virtual void OnGameConnectedClanChatMsg(
            SteamId clanId,
            SteamId userId,
            AZ::s32 messageId) {}

        /// Fired when a user enters or leaves the game from the friends list.
        virtual void OnGameRichPresenceJoinRequested(
            SteamId friendId,
            const AZStd::string& connectString) {}

        /// Fired when the user has accepted a game invite.
        virtual void OnGameLobbyJoinRequested(
            SteamId lobbyId,
            SteamId friendId) {}

        /// Fired when an overlay is opened or closed.
        virtual void OnGameOverlayActivated(bool active) {}

        /// Fired when the user tries to join a game from their friends list or after accepting a game invite.
        virtual void OnGameServerChangeRequested(
            const AZStd::string& server,
            const AZStd::string& password) {}

        /// Fired when a friend's rich presence has changed.
        virtual void OnFriendRichPresenceUpdate(
            SteamId friendId,
            SteamAppId appId) {}

        /// Fired when the user has joined a chat room.
        virtual void OnJoinClanChatRoomCompletion(
            SteamId clanId,
            AZ::s32 result) {}

        /// Fired when a user has entered or left a clan chat.
        virtual void OnGameConnectedChatJoin(
            SteamId clanId,
            SteamId userId) {}

        /// Fired when a user has left a clan chat.
        virtual void OnGameConnectedChatLeave(
            SteamId clanId,
            SteamId userId,
            bool kicked,
            bool dropped) {}

        /// Fired when the avatar image for a user has been loaded.
        virtual void OnAvatarImageLoaded(
            SteamId userId,
            AZ::s32 imageHandle,
            AZ::s32 width,
            AZ::s32 height) {}

        // -----------------------------------------------------------------------
        // CallResults
        // -----------------------------------------------------------------------

        /// Response to RequestClanOfficerList.
        virtual void OnClanOfficerListResponse(
            SteamCallHandle callHandle,
            SteamId clanId,
            AZ::s32 officerCount,
            bool success) {}

        /// Response to GetFollowerCount.
        virtual void OnFriendsGetFollowerCount(
            SteamCallHandle callHandle,
            SteamResult result,
            SteamId steamId,
            AZ::s32 count) {}

        /// Response to IsFollowing.
        virtual void OnFriendsIsFollowing(
            SteamCallHandle callHandle,
            SteamResult result,
            SteamId steamId,
            bool isFollowing) {}

        /// Response to EnumerateFollowingList.
        virtual void OnFriendsEnumerateFollowingList(
            SteamCallHandle callHandle,
            SteamResult result,
            AZ::s32 resultsReturned,
            AZ::s32 totalResultCount) {}
    };

    class SteamFriendsNotificationBusTraits : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
    };

    using SteamFriendsNotificationBus = AZ::EBus<SteamFriendsNotifications, SteamFriendsNotificationBusTraits>;

} // namespace Heathen