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
    // SteamGameServerRequests
    // Request bus wrapping ISteamGameServer.
    // Requires GameServerInitialise() to have been called first.
    // -----------------------------------------------------------------------
    class SteamGameServerRequests
    {
    public:
        AZ_RTTI(SteamGameServerRequests, "{G1H2I3J4-K5L6-4M7N-O8P9-Q0R1S2T3U4V5}");
        virtual ~SteamGameServerRequests() = default;

        // --- Server identity / metadata (set before LogOn) ---
        virtual void SetProduct(const AZStd::string& product) {}
        virtual void SetGameDescription(const AZStd::string& description) {}
        virtual void SetModDir(const AZStd::string& modDir) {}
        virtual void SetDedicatedServer(bool dedicated) {}

        // --- Login ---
        virtual void LogOn(const AZStd::string& token) {}
        virtual void LogOnAnonymous() {}
        virtual void LogOff() {}
        virtual bool GSIsLoggedOn() { return false; }
        virtual bool GSIsSecure() { return false; }
        virtual SteamId GSGetSteamID() { return 0; }
        virtual bool WasRestartRequested() { return false; }

        // --- Server state (may change at any time) ---
        virtual void SetMaxPlayerCount(AZ::s32 maxPlayers) {}
        virtual void SetBotPlayerCount(AZ::s32 botPlayers) {}
        virtual void SetServerName(const AZStd::string& serverName) {}
        virtual void SetMapName(const AZStd::string& mapName) {}
        virtual void SetPasswordProtected(bool passwordProtected) {}
        virtual void SetSpectatorPort(AZ::u16 spectatorPort) {}
        virtual void SetSpectatorServerName(const AZStd::string& spectatorServerName) {}
        virtual void ClearAllKeyValues() {}
        virtual void SetKeyValue(const AZStd::string& key, const AZStd::string& value) {}
        virtual void SetGameTags(const AZStd::string& gameTags) {}
        virtual void SetGameData(const AZStd::string& gameData) {}
        virtual void SetRegion(const AZStd::string& region) {}
        virtual void SetAdvertiseServerActive(bool active) {}

        // --- Authentication ---
        /// Begin authenticating a client connection. authTicket is the raw auth ticket bytes
        /// received from the client. Returns EBeginAuthSessionResult as s32 (0 = OK).
        virtual AZ::s32 BeginAuthSession(const AZStd::vector<AZ::u8>& authTicket, SteamId steamId) { return -1; }

        /// Stop tracking a previously begun auth session.
        virtual void EndAuthSession(SteamId steamId) {}

        /// Cancel an auth ticket obtained from GetAuthSessionTicket.
        virtual void GSCancelAuthTicket(SteamAuthTicketHandle handle) {}

        /// Returns EUserHasLicenseForAppResult as s32.
        virtual AZ::s32 UserHasLicenseForApp(SteamId steamId, SteamAppId appId) { return 0; }

        /// Returns true if the request was sent. Result arrives via OnGSClientGroupStatus.
        virtual bool RequestUserGroupStatus(SteamId userId, SteamId groupId) { return false; }

        /// Update data shown in the server browser for a connected player. Score is the
        /// player's displayed score. Returns true on success.
        virtual bool UpdateUserData(SteamId userId, const AZStd::string& playerName, AZ::u32 score) { return false; }

        // --- Async operations ---
        virtual SteamCallHandle AssociateWithClan(SteamId clanId) { return 0; }
        virtual SteamCallHandle ComputeNewPlayerCompatibility(SteamId newPlayerId) { return 0; }
        virtual SteamCallHandle GetServerReputation() { return 0; }
    };

    class SteamGameServerBusTraits : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
    };

    using SteamGameServerRequestBus = AZ::EBus<SteamGameServerRequests, SteamGameServerBusTraits>;
} // namespace Heathen
