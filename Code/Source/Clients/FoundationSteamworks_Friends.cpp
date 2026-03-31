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

#include "FoundationSteamworksSystemComponent.h"
#include "SteamTypeConverters.h"
#include "SteamCallResultInfrastructure.h"

#include <steam/steam_api.h>
#include <steam/isteamfriends.h>
#include <FoundationSteamworks/SteamFriendsNotificationBus.h>

using namespace Heathen;

namespace FoundationSteamworks
{
    // -----------------------------------------------------------------------
    // SteamFriendsRequestBus
    // -----------------------------------------------------------------------

    AZStd::string FoundationSteamworksSystemComponent::GetPersonaName()
    {
        if (!m_steamInitialised || !SteamFriends()) return {};
        return AZStd::string(SteamFriends()->GetPersonaName());
    }

    SteamPersonaState FoundationSteamworksSystemComponent::GetPersonaState()
    {
        if (!m_steamInitialised || !SteamFriends()) return SteamPersonaState::Offline;
        return static_cast<SteamPersonaState>(SteamFriends()->GetPersonaState());
    }

    AZ::s32 FoundationSteamworksSystemComponent::GetFriendCount(AZ::s32 friendFlags)
    {
        return m_steamInitialised && SteamFriends() ? SteamFriends()->GetFriendCount(friendFlags) : 0;
    }

    SteamId FoundationSteamworksSystemComponent::GetFriendByIndex(AZ::s32 index, AZ::s32 friendFlags)
    {
        return m_steamInitialised && SteamFriends() ? ToSteamId(SteamFriends()->GetFriendByIndex(index, friendFlags)) : 0;
    }

    AZ::s32 FoundationSteamworksSystemComponent::GetFriendRelationship(SteamId steamId)
    {
        return m_steamInitialised && SteamFriends()
            ? static_cast<AZ::s32>(SteamFriends()->GetFriendRelationship(FromSteamId(steamId))) : 0;
    }

    SteamPersonaState FoundationSteamworksSystemComponent::GetFriendPersonaState(SteamId steamId)
    {
        if (!m_steamInitialised || !SteamFriends()) return SteamPersonaState::Offline;
        return static_cast<SteamPersonaState>(SteamFriends()->GetFriendPersonaState(FromSteamId(steamId)));
    }

    AZStd::string FoundationSteamworksSystemComponent::GetFriendPersonaName(SteamId steamId)
    {
        if (!m_steamInitialised || !SteamFriends()) return {};
        const char* name = SteamFriends()->GetFriendPersonaName(FromSteamId(steamId));
        return name ? AZStd::string(name) : AZStd::string{};
    }

    AZ::s32 FoundationSteamworksSystemComponent::GetFriendSteamLevel(SteamId steamId)
    {
        return m_steamInitialised && SteamFriends() ? SteamFriends()->GetFriendSteamLevel(FromSteamId(steamId)) : 0;
    }

    AZStd::string FoundationSteamworksSystemComponent::GetPlayerNickname(SteamId steamId)
    {
        if (!m_steamInitialised || !SteamFriends()) return {};
        const char* nick = SteamFriends()->GetPlayerNickname(FromSteamId(steamId));
        return nick ? AZStd::string(nick) : AZStd::string{};
    }

    bool FoundationSteamworksSystemComponent::HasFriend(SteamId steamId, AZ::s32 friendFlags)
    {
        return m_steamInitialised && SteamFriends() && SteamFriends()->HasFriend(FromSteamId(steamId), friendFlags);
    }

    AZ::s32 FoundationSteamworksSystemComponent::GetSmallFriendAvatar(SteamId steamId)
    {
        return m_steamInitialised && SteamFriends() ? SteamFriends()->GetSmallFriendAvatar(FromSteamId(steamId)) : 0;
    }

    AZ::s32 FoundationSteamworksSystemComponent::GetMediumFriendAvatar(SteamId steamId)
    {
        return m_steamInitialised && SteamFriends() ? SteamFriends()->GetMediumFriendAvatar(FromSteamId(steamId)) : 0;
    }

    AZ::s32 FoundationSteamworksSystemComponent::GetLargeFriendAvatar(SteamId steamId)
    {
        return m_steamInitialised && SteamFriends() ? SteamFriends()->GetLargeFriendAvatar(FromSteamId(steamId)) : 0;
    }

    bool FoundationSteamworksSystemComponent::RequestUserInformation(SteamId steamId, bool requireNameOnly)
    {
        return m_steamInitialised && SteamFriends() && SteamFriends()->RequestUserInformation(FromSteamId(steamId), requireNameOnly);
    }

    bool FoundationSteamworksSystemComponent::SetRichPresence(const AZStd::string& key, const AZStd::string& value)
    {
        return m_steamInitialised && SteamFriends() && SteamFriends()->SetRichPresence(key.c_str(), value.c_str());
    }

    void FoundationSteamworksSystemComponent::ClearRichPresence()
    {
        if (m_steamInitialised && SteamFriends())
            SteamFriends()->ClearRichPresence();
    }

    AZStd::string FoundationSteamworksSystemComponent::GetFriendRichPresence(SteamId steamId, const AZStd::string& key)
    {
        if (!m_steamInitialised || !SteamFriends()) return {};
        const char* val = SteamFriends()->GetFriendRichPresence(FromSteamId(steamId), key.c_str());
        return val ? AZStd::string(val) : AZStd::string{};
    }

    AZ::s32 FoundationSteamworksSystemComponent::GetFriendRichPresenceKeyCount(SteamId steamId)
    {
        return m_steamInitialised && SteamFriends() ? SteamFriends()->GetFriendRichPresenceKeyCount(FromSteamId(steamId)) : 0;
    }

    AZStd::string FoundationSteamworksSystemComponent::GetFriendRichPresenceKeyByIndex(SteamId steamId, AZ::s32 index)
    {
        if (!m_steamInitialised || !SteamFriends()) return {};
        const char* key = SteamFriends()->GetFriendRichPresenceKeyByIndex(FromSteamId(steamId), index);
        return key ? AZStd::string(key) : AZStd::string{};
    }

    void FoundationSteamworksSystemComponent::RequestFriendRichPresence(SteamId steamId)
    {
        if (m_steamInitialised && SteamFriends())
            SteamFriends()->RequestFriendRichPresence(FromSteamId(steamId));
    }

    void FoundationSteamworksSystemComponent::ActivateGameOverlay(const AZStd::string& dialog)
    {
        if (m_steamInitialised && SteamFriends())
            SteamFriends()->ActivateGameOverlay(dialog.c_str());
    }

    void FoundationSteamworksSystemComponent::ActivateGameOverlayToUser(const AZStd::string& dialog, SteamId steamId)
    {
        if (m_steamInitialised && SteamFriends())
            SteamFriends()->ActivateGameOverlayToUser(dialog.c_str(), FromSteamId(steamId));
    }

    void FoundationSteamworksSystemComponent::ActivateGameOverlayToWebPage(const AZStd::string& url, SteamOverlayToWebPageMode mode)
    {
        if (m_steamInitialised && SteamFriends())
            SteamFriends()->ActivateGameOverlayToWebPage(url.c_str(), static_cast<EActivateGameOverlayToWebPageMode>(mode));
    }

    void FoundationSteamworksSystemComponent::ActivateGameOverlayToStore(SteamAppId appId, SteamOverlayToStoreFlag flag)
    {
        if (m_steamInitialised && SteamFriends())
            SteamFriends()->ActivateGameOverlayToStore(static_cast<AppId_t>(appId), static_cast<EOverlayToStoreFlag>(flag));
    }

    void FoundationSteamworksSystemComponent::ActivateGameOverlayInviteDialog(SteamId lobbyId)
    {
        if (m_steamInitialised && SteamFriends())
            SteamFriends()->ActivateGameOverlayInviteDialog(FromSteamId(lobbyId));
    }

    void FoundationSteamworksSystemComponent::SetPlayedWith(SteamId steamId)
    {
        if (m_steamInitialised && SteamFriends())
            SteamFriends()->SetPlayedWith(FromSteamId(steamId));
    }

    SteamId FoundationSteamworksSystemComponent::GetClanByIndex(AZ::s32 index)
    {
        return m_steamInitialised && SteamFriends() ? ToSteamId(SteamFriends()->GetClanByIndex(index)) : 0;
    }

    AZ::s32 FoundationSteamworksSystemComponent::GetClanCount()
    {
        return m_steamInitialised && SteamFriends() ? SteamFriends()->GetClanCount() : 0;
    }

    AZStd::string FoundationSteamworksSystemComponent::GetClanName(SteamId clanId)
    {
        if (!m_steamInitialised || !SteamFriends()) return {};
        const char* name = SteamFriends()->GetClanName(FromSteamId(clanId));
        return name ? AZStd::string(name) : AZStd::string{};
    }

    AZStd::string FoundationSteamworksSystemComponent::GetClanTag(SteamId clanId)
    {
        if (!m_steamInitialised || !SteamFriends()) return {};
        const char* tag = SteamFriends()->GetClanTag(FromSteamId(clanId));
        return tag ? AZStd::string(tag) : AZStd::string{};
    }

    SteamCallHandle FoundationSteamworksSystemComponent::RequestClanOfficerList(SteamId clanId)
    {
        if (!m_steamInitialised || !SteamFriends()) return 0;
        SteamAPICall_t call = SteamFriends()->RequestClanOfficerList(FromSteamId(clanId));
        m_callResults->Register<ClanOfficerListResponse_t>(call, [](SteamCallHandle h, ClanOfficerListResponse_t* p, bool ioFail)
        {
            SteamFriendsNotificationBus::Broadcast(&SteamFriendsNotifications::OnClanOfficerListResponse,
                h, ToSteamId(p->m_steamIDClan), p->m_cOfficers, p->m_bSuccess != 0);
        });
        return ToCallHandle(call);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::GetFollowerCount(SteamId steamId)
    {
        if (!m_steamInitialised || !SteamFriends()) return 0;
        SteamAPICall_t call = SteamFriends()->GetFollowerCount(FromSteamId(steamId));
        m_callResults->Register<FriendsGetFollowerCount_t>(call, [](SteamCallHandle h, FriendsGetFollowerCount_t* p, bool ioFail)
        {
            SteamFriendsNotificationBus::Broadcast(&SteamFriendsNotifications::OnFriendsGetFollowerCount,
                h, ToSteamResult(p->m_eResult), ToSteamId(p->m_steamID), p->m_nCount);
        });
        return ToCallHandle(call);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::IsFollowing(SteamId steamId)
    {
        if (!m_steamInitialised || !SteamFriends()) return 0;
        SteamAPICall_t call = SteamFriends()->IsFollowing(FromSteamId(steamId));
        m_callResults->Register<FriendsIsFollowing_t>(call, [](SteamCallHandle h, FriendsIsFollowing_t* p, bool ioFail)
        {
            SteamFriendsNotificationBus::Broadcast(&SteamFriendsNotifications::OnFriendsIsFollowing,
                h, ToSteamResult(p->m_eResult), ToSteamId(p->m_steamID), p->m_bIsFollowing);
        });
        return ToCallHandle(call);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::EnumerateFollowingList(AZ::u32 startIndex)
    {
        if (!m_steamInitialised || !SteamFriends()) return 0;
        SteamAPICall_t call = SteamFriends()->EnumerateFollowingList(startIndex);
        m_callResults->Register<FriendsEnumerateFollowingList_t>(call, [](SteamCallHandle h, FriendsEnumerateFollowingList_t* p, bool ioFail)
        {
            SteamFriendsNotificationBus::Broadcast(&SteamFriendsNotifications::OnFriendsEnumerateFollowingList,
                h, ToSteamResult(p->m_eResult),
                static_cast<AZ::s32>(p->m_nResultsReturned),
                p->m_nTotalResultCount);
        });
        return ToCallHandle(call);
    }

} // namespace FoundationSteamworks
