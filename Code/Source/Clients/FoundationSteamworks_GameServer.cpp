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

#include <FoundationSteamworks/SteamGameServerNotificationBus.h>

#include <steam/steam_api.h>
#include <steam/steam_gameserver.h>

using namespace Heathen;

namespace FoundationSteamworks
{

    // -----------------------------------------------------------------------
    // SteamGameServerRequestBus
    // -----------------------------------------------------------------------

    void FoundationSteamworksSystemComponent::SetProduct(const AZStd::string& product)
    {
        if (m_gameServerInitialised && SteamGameServer()) SteamGameServer()->SetProduct(product.c_str());
    }

    void FoundationSteamworksSystemComponent::SetGameDescription(const AZStd::string& description)
    {
        if (m_gameServerInitialised && SteamGameServer()) SteamGameServer()->SetGameDescription(description.c_str());
    }

    void FoundationSteamworksSystemComponent::SetModDir(const AZStd::string& modDir)
    {
        if (m_gameServerInitialised && SteamGameServer()) SteamGameServer()->SetModDir(modDir.c_str());
    }

    void FoundationSteamworksSystemComponent::SetDedicatedServer(bool dedicated)
    {
        if (m_gameServerInitialised && SteamGameServer()) SteamGameServer()->SetDedicatedServer(dedicated);
    }

    void FoundationSteamworksSystemComponent::LogOn(const AZStd::string& token)
    {
        if (m_gameServerInitialised && SteamGameServer()) SteamGameServer()->LogOn(token.c_str());
    }

    void FoundationSteamworksSystemComponent::LogOnAnonymous()
    {
        if (m_gameServerInitialised && SteamGameServer()) SteamGameServer()->LogOnAnonymous();
    }

    void FoundationSteamworksSystemComponent::LogOff()
    {
        if (m_gameServerInitialised && SteamGameServer()) SteamGameServer()->LogOff();
    }

    bool FoundationSteamworksSystemComponent::GSIsLoggedOn()
    {
        return m_gameServerInitialised && SteamGameServer() && SteamGameServer()->BLoggedOn();
    }

    bool FoundationSteamworksSystemComponent::GSIsSecure()
    {
        return m_gameServerInitialised && SteamGameServer() && SteamGameServer()->BSecure();
    }

    SteamId FoundationSteamworksSystemComponent::GSGetSteamID()
    {
        return m_gameServerInitialised && SteamGameServer() ? ToSteamId(SteamGameServer()->GetSteamID()) : 0;
    }

    bool FoundationSteamworksSystemComponent::WasRestartRequested()
    {
        return m_gameServerInitialised && SteamGameServer() && SteamGameServer()->WasRestartRequested();
    }

    void FoundationSteamworksSystemComponent::SetMaxPlayerCount(AZ::s32 maxPlayers)
    {
        if (m_gameServerInitialised && SteamGameServer()) SteamGameServer()->SetMaxPlayerCount(maxPlayers);
    }

    void FoundationSteamworksSystemComponent::SetBotPlayerCount(AZ::s32 botPlayers)
    {
        if (m_gameServerInitialised && SteamGameServer()) SteamGameServer()->SetBotPlayerCount(botPlayers);
    }

    void FoundationSteamworksSystemComponent::SetServerName(const AZStd::string& serverName)
    {
        if (m_gameServerInitialised && SteamGameServer()) SteamGameServer()->SetServerName(serverName.c_str());
    }

    void FoundationSteamworksSystemComponent::SetMapName(const AZStd::string& mapName)
    {
        if (m_gameServerInitialised && SteamGameServer()) SteamGameServer()->SetMapName(mapName.c_str());
    }

    void FoundationSteamworksSystemComponent::SetPasswordProtected(bool passwordProtected)
    {
        if (m_gameServerInitialised && SteamGameServer()) SteamGameServer()->SetPasswordProtected(passwordProtected);
    }

    void FoundationSteamworksSystemComponent::SetSpectatorPort(AZ::u16 spectatorPort)
    {
        if (m_gameServerInitialised && SteamGameServer()) SteamGameServer()->SetSpectatorPort(spectatorPort);
    }

    void FoundationSteamworksSystemComponent::SetSpectatorServerName(const AZStd::string& spectatorServerName)
    {
        if (m_gameServerInitialised && SteamGameServer()) SteamGameServer()->SetSpectatorServerName(spectatorServerName.c_str());
    }

    void FoundationSteamworksSystemComponent::ClearAllKeyValues()
    {
        if (m_gameServerInitialised && SteamGameServer()) SteamGameServer()->ClearAllKeyValues();
    }

    void FoundationSteamworksSystemComponent::SetKeyValue(const AZStd::string& key, const AZStd::string& value)
    {
        if (m_gameServerInitialised && SteamGameServer()) SteamGameServer()->SetKeyValue(key.c_str(), value.c_str());
    }

    void FoundationSteamworksSystemComponent::SetGameTags(const AZStd::string& gameTags)
    {
        if (m_gameServerInitialised && SteamGameServer()) SteamGameServer()->SetGameTags(gameTags.c_str());
    }

    void FoundationSteamworksSystemComponent::SetGameData(const AZStd::string& gameData)
    {
        if (m_gameServerInitialised && SteamGameServer()) SteamGameServer()->SetGameData(gameData.c_str());
    }

    void FoundationSteamworksSystemComponent::SetRegion(const AZStd::string& region)
    {
        if (m_gameServerInitialised && SteamGameServer()) SteamGameServer()->SetRegion(region.c_str());
    }

    void FoundationSteamworksSystemComponent::SetAdvertiseServerActive(bool active)
    {
        if (m_gameServerInitialised && SteamGameServer()) SteamGameServer()->SetAdvertiseServerActive(active);
    }

    AZ::s32 FoundationSteamworksSystemComponent::BeginAuthSession(const AZStd::vector<AZ::u8>& authTicket, SteamId steamId)
    {
        if (!m_gameServerInitialised || !SteamGameServer()) return -1;
        return static_cast<AZ::s32>(SteamGameServer()->BeginAuthSession(
            authTicket.data(), static_cast<int>(authTicket.size()), FromSteamId(steamId)));
    }

    void FoundationSteamworksSystemComponent::EndAuthSession(SteamId steamId)
    {
        if (m_gameServerInitialised && SteamGameServer()) SteamGameServer()->EndAuthSession(FromSteamId(steamId));
    }

    void FoundationSteamworksSystemComponent::GSCancelAuthTicket(SteamAuthTicketHandle handle)
    {
        if (m_gameServerInitialised && SteamGameServer()) SteamGameServer()->CancelAuthTicket(static_cast<HAuthTicket>(handle));
    }

    AZ::s32 FoundationSteamworksSystemComponent::UserHasLicenseForApp(SteamId steamId, SteamAppId appId)
    {
        if (!m_gameServerInitialised || !SteamGameServer()) return 0;
        return static_cast<AZ::s32>(SteamGameServer()->UserHasLicenseForApp(FromSteamId(steamId), static_cast<AppId_t>(appId)));
    }

    bool FoundationSteamworksSystemComponent::RequestUserGroupStatus(SteamId userId, SteamId groupId)
    {
        return m_gameServerInitialised && SteamGameServer() &&
            SteamGameServer()->RequestUserGroupStatus(FromSteamId(userId), FromSteamId(groupId));
    }

    bool FoundationSteamworksSystemComponent::UpdateUserData(SteamId userId, const AZStd::string& playerName, AZ::u32 score)
    {
        return m_gameServerInitialised && SteamGameServer() &&
            SteamGameServer()->BUpdateUserData(FromSteamId(userId), playerName.c_str(), score);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::AssociateWithClan(SteamId clanId)
    {
        if (!m_gameServerInitialised || !SteamGameServer()) return 0;
        SteamAPICall_t h = SteamGameServer()->AssociateWithClan(FromSteamId(clanId));
        if (h == k_uAPICallInvalid) return 0;
        m_callResults->Register<AssociateWithClanResult_t>(h,
            [](SteamCallHandle ch, AssociateWithClanResult_t* p, bool ioFail)
            {
                SteamGameServerNotificationBus::Broadcast(
                    &SteamGameServerNotifications::OnAssociateWithClanResult,
                    ch,
                    ioFail ? SteamResult::Fail : ToSteamResult(p->m_eResult));
            });
        return ToCallHandle(h);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::ComputeNewPlayerCompatibility(SteamId newPlayerId)
    {
        if (!m_gameServerInitialised || !SteamGameServer()) return 0;
        SteamAPICall_t h = SteamGameServer()->ComputeNewPlayerCompatibility(FromSteamId(newPlayerId));
        if (h == k_uAPICallInvalid) return 0;
        m_callResults->Register<ComputeNewPlayerCompatibilityResult_t>(h,
            [](SteamCallHandle ch, ComputeNewPlayerCompatibilityResult_t* p, bool ioFail)
            {
                SteamGameServerNotificationBus::Broadcast(
                    &SteamGameServerNotifications::OnComputeNewPlayerCompatibilityResult,
                    ch,
                    ioFail ? SteamResult::Fail : ToSteamResult(p->m_eResult),
                    p->m_cPlayersThatDontLikeCandidate,
                    p->m_cPlayersThatCandidateDoesntLike,
                    p->m_cClanPlayersThatDontLikeCandidate,
                    ToSteamId(p->m_SteamIDCandidate));
            });
        return ToCallHandle(h);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::GetServerReputation()
    {
        if (!m_gameServerInitialised || !SteamGameServer()) return 0;
        SteamAPICall_t h = SteamGameServer()->GetServerReputation();
        if (h == k_uAPICallInvalid) return 0;
        m_callResults->Register<GSReputation_t>(h,
            [](SteamCallHandle ch, GSReputation_t* p, bool ioFail)
            {
                SteamGameServerNotificationBus::Broadcast(
                    &SteamGameServerNotifications::OnServerReputation,
                    ch,
                    ioFail ? SteamResult::Fail : ToSteamResult(p->m_eResult),
                    p->m_unReputationScore,
                    p->m_bBanned,
                    p->m_unBannedIP,
                    p->m_usBannedPort,
                    p->m_ulBannedGameID,
                    p->m_unBanExpires);
            });
        return ToCallHandle(h);
    }

} // namespace FoundationSteamworks
