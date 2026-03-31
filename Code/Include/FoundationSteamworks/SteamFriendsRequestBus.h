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
    // SteamFriendsRequests
    // Request bus wrapping ISteamFriends.
    // -----------------------------------------------------------------------
    class SteamFriendsRequests
    {
    public:
        AZ_RTTI(SteamFriendsRequests, "{C3D4E5F6-A7B8-4C9D-AEF0-A1B2C3D4E5F7}");
        virtual ~SteamFriendsRequests() = default;

        // --- Local User ---

        /// Returns the local user's current display name.
        virtual AZStd::string GetPersonaName() { return {}; }

        /// Returns the local user's current persona state.
        virtual SteamPersonaState GetPersonaState() { return SteamPersonaState::Offline; }

        // --- Friend Enumeration ---

        /// Returns the count of friends matching the given friend-flags bitmask.
        /// friendFlags: bitwise-OR of EFriendFlags values (e.g. 0x04 = k_EFriendFlagImmediate).
        virtual AZ::s32 GetFriendCount(AZ::s32 friendFlags) { return 0; }

        /// Returns the SteamID of the friend at the given index.
        virtual SteamId GetFriendByIndex(AZ::s32 index, AZ::s32 friendFlags) { return 0; }

        /// Returns the friendship relationship enum value for the given user.
        virtual AZ::s32 GetFriendRelationship(SteamId steamId) { return 0; }

        /// Returns the persona state of a friend.
        virtual SteamPersonaState GetFriendPersonaState(SteamId steamId) { return SteamPersonaState::Offline; }

        /// Returns the display name of a friend.
        virtual AZStd::string GetFriendPersonaName(SteamId steamId) { return {}; }

        /// Returns the Steam level of a friend.
        virtual AZ::s32 GetFriendSteamLevel(SteamId steamId) { return 0; }

        /// Returns the per-game nickname the local user has assigned to another player.
        virtual AZStd::string GetPlayerNickname(SteamId steamId) { return {}; }

        /// Returns true if the local user has the given relationship with the friend.
        virtual bool HasFriend(SteamId steamId, AZ::s32 friendFlags) { return false; }

        // --- Avatar ---

        /// Returns a handle to the small (32×32) avatar for the given user, or 0 if unavailable.
        virtual AZ::s32 GetSmallFriendAvatar(SteamId steamId) { return 0; }

        /// Returns a handle to the medium (64×64) avatar for the given user, or 0 if unavailable.
        virtual AZ::s32 GetMediumFriendAvatar(SteamId steamId) { return 0; }

        /// Returns a handle to the large (184×184) avatar for the given user, or 0 if unavailable.
        virtual AZ::s32 GetLargeFriendAvatar(SteamId steamId) { return 0; }

        // --- User Information ---

        /// Requests Steam to fetch persona name and avatar for the given user.
        /// requireNameOnly: if true, only the name is required (avatar download is optional).
        /// Returns true if a callback will be fired; false if the data is already cached.
        virtual bool RequestUserInformation(SteamId steamId, bool requireNameOnly) { return false; }

        // --- Rich Presence ---

        /// Sets a rich-presence key for the local user.
        virtual bool SetRichPresence(const AZStd::string& key, const AZStd::string& value) { return false; }

        /// Clears all rich-presence keys for the local user.
        virtual void ClearRichPresence() {}

        /// Returns the value of a rich-presence key for a friend.
        virtual AZStd::string GetFriendRichPresence(SteamId steamId, const AZStd::string& key) { return {}; }

        /// Returns the number of rich-presence keys set for a friend.
        virtual AZ::s32 GetFriendRichPresenceKeyCount(SteamId steamId) { return 0; }

        /// Returns the name of rich-presence key at the given index for a friend.
        virtual AZStd::string GetFriendRichPresenceKeyByIndex(SteamId steamId, AZ::s32 index) { return {}; }

        /// Requests fresh rich-presence data for a friend.
        virtual void RequestFriendRichPresence(SteamId steamId) {}

        // --- Overlay ---

        /// Opens the Steam overlay to the given dialog (e.g. "Friends", "Community", "Players").
        virtual void ActivateGameOverlay(const AZStd::string& dialog) {}

        /// Opens the Steam overlay to a specific user's page.
        /// dialog: "steamid", "chat", "jointrade", "stats", "achievements", "friendadd", "friendremove", "friendrequestaccept", "friendrequestignore"
        virtual void ActivateGameOverlayToUser(const AZStd::string& dialog, SteamId steamId) {}

        /// Opens the Steam overlay browser to the given URL.
        /// mode: 0 = default, 1 = modal
        virtual void ActivateGameOverlayToWebPage(const AZStd::string& url, SteamOverlayToWebPageMode mode) {}

        /// Opens the Steam overlay store page for the given app.
        virtual void ActivateGameOverlayToStore(SteamAppId appId, SteamOverlayToStoreFlag flag) {}

        /// Opens the Steam overlay invite dialog for the given lobby.
        virtual void ActivateGameOverlayInviteDialog(SteamId lobbyId) {}

        // --- Played With ---

        /// Records that the local user played with the given user in a session.
        virtual void SetPlayedWith(SteamId steamId) {}

        // --- Clan / Group ---

        /// Returns the SteamID of the clan (Steam group) at the given index.
        virtual SteamId GetClanByIndex(AZ::s32 index) { return 0; }

        /// Returns the number of Steam groups the local user is a member of.
        virtual AZ::s32 GetClanCount() { return 0; }

        /// Returns the display name of a clan.
        virtual AZStd::string GetClanName(SteamId clanId) { return {}; }

        /// Returns the tag (short name) of a clan.
        virtual AZStd::string GetClanTag(SteamId clanId) { return {}; }

        // --- Async (result via SteamFriendsNotificationBus) ---

        /// Requests the officer list for a clan.
        /// Returns a SteamCallHandle correlating with OnClanOfficerListResponse.
        virtual SteamCallHandle RequestClanOfficerList(SteamId clanId) { return 0; }

        /// Returns the number of followers the local user has.
        /// Returns a SteamCallHandle correlating with OnFriendsGetFollowerCount.
        virtual SteamCallHandle GetFollowerCount(SteamId steamId) { return 0; }

        /// Checks whether the local user is following the given user.
        /// Returns a SteamCallHandle correlating with OnFriendsIsFollowing.
        virtual SteamCallHandle IsFollowing(SteamId steamId) { return 0; }

        /// Enumerates the list of users the local user is following.
        /// Returns a SteamCallHandle correlating with OnFriendsEnumerateFollowingList.
        virtual SteamCallHandle EnumerateFollowingList(AZ::u32 startIndex) { return 0; }
    };

    class SteamFriendsRequestBusTraits : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
    };

    using SteamFriendsRequestBus = AZ::EBus<SteamFriendsRequests, SteamFriendsRequestBusTraits>;

} // namespace Heathen