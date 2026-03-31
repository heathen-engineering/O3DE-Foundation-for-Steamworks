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
#include <steam/isteammatchmaking.h>
#include <FoundationSteamworks/SteamMatchmakingNotificationBus.h>

using namespace Heathen;

namespace FoundationSteamworks
{
    // -----------------------------------------------------------------------
    // SteamMatchmakingRequestBus
    // -----------------------------------------------------------------------

    AZ::s32 FoundationSteamworksSystemComponent::GetNumLobbyMembers(SteamId lobbyId)
    {
        return m_steamInitialised && SteamMatchmaking() ? SteamMatchmaking()->GetNumLobbyMembers(FromSteamId(lobbyId)) : 0;
    }

    SteamId FoundationSteamworksSystemComponent::GetLobbyMemberByIndex(SteamId lobbyId, AZ::s32 index)
    {
        return m_steamInitialised && SteamMatchmaking() ? ToSteamId(SteamMatchmaking()->GetLobbyMemberByIndex(FromSteamId(lobbyId), index)) : 0;
    }

    AZStd::string FoundationSteamworksSystemComponent::GetLobbyData(SteamId lobbyId, const AZStd::string& key)
    {
        if (!m_steamInitialised || !SteamMatchmaking()) return {};
        const char* val = SteamMatchmaking()->GetLobbyData(FromSteamId(lobbyId), key.c_str());
        return val ? AZStd::string(val) : AZStd::string{};
    }

    bool FoundationSteamworksSystemComponent::SetLobbyData(SteamId lobbyId, const AZStd::string& key, const AZStd::string& value)
    {
        return m_steamInitialised && SteamMatchmaking()
            && SteamMatchmaking()->SetLobbyData(FromSteamId(lobbyId), key.c_str(), value.c_str());
    }

    bool FoundationSteamworksSystemComponent::DeleteLobbyData(SteamId lobbyId, const AZStd::string& key)
    {
        return m_steamInitialised && SteamMatchmaking()
            && SteamMatchmaking()->DeleteLobbyData(FromSteamId(lobbyId), key.c_str());
    }

    AZStd::string FoundationSteamworksSystemComponent::GetLobbyMemberData(SteamId lobbyId, SteamId memberId, const AZStd::string& key)
    {
        if (!m_steamInitialised || !SteamMatchmaking()) return {};
        const char* val = SteamMatchmaking()->GetLobbyMemberData(FromSteamId(lobbyId), FromSteamId(memberId), key.c_str());
        return val ? AZStd::string(val) : AZStd::string{};
    }

    void FoundationSteamworksSystemComponent::SetLobbyMemberData(SteamId lobbyId, const AZStd::string& key, const AZStd::string& value)
    {
        if (m_steamInitialised && SteamMatchmaking())
            SteamMatchmaking()->SetLobbyMemberData(FromSteamId(lobbyId), key.c_str(), value.c_str());
    }

    SteamId FoundationSteamworksSystemComponent::GetLobbyOwner(SteamId lobbyId)
    {
        return m_steamInitialised && SteamMatchmaking() ? ToSteamId(SteamMatchmaking()->GetLobbyOwner(FromSteamId(lobbyId))) : 0;
    }

    bool FoundationSteamworksSystemComponent::SetLobbyOwner(SteamId lobbyId, SteamId newOwnerId)
    {
        return m_steamInitialised && SteamMatchmaking()
            && SteamMatchmaking()->SetLobbyOwner(FromSteamId(lobbyId), FromSteamId(newOwnerId));
    }

    bool FoundationSteamworksSystemComponent::RequestLobbyData(SteamId lobbyId)
    {
        return m_steamInitialised && SteamMatchmaking() && SteamMatchmaking()->RequestLobbyData(FromSteamId(lobbyId));
    }

    bool FoundationSteamworksSystemComponent::SetLobbyJoinable(SteamId lobbyId, bool joinable)
    {
        return m_steamInitialised && SteamMatchmaking() && SteamMatchmaking()->SetLobbyJoinable(FromSteamId(lobbyId), joinable);
    }

    bool FoundationSteamworksSystemComponent::SetLobbyMemberLimit(SteamId lobbyId, AZ::s32 maxMembers)
    {
        return m_steamInitialised && SteamMatchmaking() && SteamMatchmaking()->SetLobbyMemberLimit(FromSteamId(lobbyId), maxMembers);
    }

    AZ::s32 FoundationSteamworksSystemComponent::GetLobbyMemberLimit(SteamId lobbyId)
    {
        return m_steamInitialised && SteamMatchmaking() ? SteamMatchmaking()->GetLobbyMemberLimit(FromSteamId(lobbyId)) : 0;
    }

    bool FoundationSteamworksSystemComponent::InviteUserToLobby(SteamId lobbyId, SteamId inviteeId)
    {
        return m_steamInitialised && SteamMatchmaking()
            && SteamMatchmaking()->InviteUserToLobby(FromSteamId(lobbyId), FromSteamId(inviteeId));
    }

    void FoundationSteamworksSystemComponent::LeaveLobby(SteamId lobbyId)
    {
        if (m_steamInitialised && SteamMatchmaking())
            SteamMatchmaking()->LeaveLobby(FromSteamId(lobbyId));
    }

    void FoundationSteamworksSystemComponent::AddRequestLobbyListStringFilter(const AZStd::string& key, const AZStd::string& value, SteamLobbyComparison comparison)
    {
        if (m_steamInitialised && SteamMatchmaking())
            SteamMatchmaking()->AddRequestLobbyListStringFilter(key.c_str(), value.c_str(), static_cast<ELobbyComparison>(comparison));
    }

    void FoundationSteamworksSystemComponent::AddRequestLobbyListNumericalFilter(const AZStd::string& key, AZ::s32 value, SteamLobbyComparison comparison)
    {
        if (m_steamInitialised && SteamMatchmaking())
            SteamMatchmaking()->AddRequestLobbyListNumericalFilter(key.c_str(), value, static_cast<ELobbyComparison>(comparison));
    }

    void FoundationSteamworksSystemComponent::AddRequestLobbyListNearValueFilter(const AZStd::string& key, AZ::s32 valueToBeCloseTo)
    {
        if (m_steamInitialised && SteamMatchmaking())
            SteamMatchmaking()->AddRequestLobbyListNearValueFilter(key.c_str(), valueToBeCloseTo);
    }

    void FoundationSteamworksSystemComponent::AddRequestLobbyListFilterSlotsAvailable(AZ::s32 slotsAvailable)
    {
        if (m_steamInitialised && SteamMatchmaking())
            SteamMatchmaking()->AddRequestLobbyListFilterSlotsAvailable(slotsAvailable);
    }

    void FoundationSteamworksSystemComponent::AddRequestLobbyListDistanceFilter(SteamLobbyDistanceFilter distanceFilter)
    {
        if (m_steamInitialised && SteamMatchmaking())
            SteamMatchmaking()->AddRequestLobbyListDistanceFilter(static_cast<ELobbyDistanceFilter>(distanceFilter));
    }

    void FoundationSteamworksSystemComponent::AddRequestLobbyListResultCountFilter(AZ::s32 maxResults)
    {
        if (m_steamInitialised && SteamMatchmaking())
            SteamMatchmaking()->AddRequestLobbyListResultCountFilter(maxResults);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::CreateLobby(SteamLobbyType lobbyType, AZ::s32 maxMembers)
    {
        if (!m_steamInitialised || !SteamMatchmaking()) return 0;
        SteamAPICall_t call = SteamMatchmaking()->CreateLobby(static_cast<ELobbyType>(lobbyType), maxMembers);
        m_callResults->Register<LobbyCreated_t>(call, [](SteamCallHandle h, LobbyCreated_t* p, bool ioFail)
        {
            SteamMatchmakingNotificationBus::Broadcast(&SteamMatchmakingNotifications::OnLobbyCreated,
                h, ToSteamResult(p->m_eResult), ToSteamId(p->m_ulSteamIDLobby));
        });
        return ToCallHandle(call);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::JoinLobby(SteamId lobbyId)
    {
        if (!m_steamInitialised || !SteamMatchmaking()) return 0;
        SteamAPICall_t call = SteamMatchmaking()->JoinLobby(FromSteamId(lobbyId));
        m_callResults->Register<LobbyEnter_t>(call, [](SteamCallHandle h, LobbyEnter_t* p, bool ioFail)
        {
            SteamMatchmakingNotificationBus::Broadcast(&SteamMatchmakingNotifications::OnLobbyEntered,
                h, ToSteamId(p->m_ulSteamIDLobby),
                p->m_rgfChatPermissions,
                p->m_bLocked != 0,
                p->m_EChatRoomEnterResponse);
        });
        return ToCallHandle(call);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::RequestLobbyList()
    {
        if (!m_steamInitialised || !SteamMatchmaking()) return 0;
        SteamAPICall_t call = SteamMatchmaking()->RequestLobbyList();
        m_callResults->Register<LobbyMatchList_t>(call, [](SteamCallHandle h, LobbyMatchList_t* p, bool ioFail)
        {
            SteamMatchmakingNotificationBus::Broadcast(&SteamMatchmakingNotifications::OnLobbyMatchList,
                h, p->m_nLobbiesMatching);
        });
        return ToCallHandle(call);
    }

} // namespace FoundationSteamworks
