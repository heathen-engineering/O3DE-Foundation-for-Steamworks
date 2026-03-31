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

// Private header — must NOT be included from any public Include/ header.
// Includes <steam/steam_api.h> and <steam/steam_gameserver.h> deliberately.
// STEAM_CALLBACK_MANUAL must be used inside a class body — placing it here
// keeps Steam SDK headers out of the public FoundationSteamworksSystemComponent.h
// while the member storage remains heap-allocated and stable behind a unique_ptr.

#include "FoundationSteamworksSystemComponent.h"

#include <steam/steam_api.h>
#include <steam/steam_gameserver.h>
#include <steam/isteamapps.h>
#include <steam/isteamfriends.h>
#include <steam/isteammatchmaking.h>
#include <steam/isteamuserstats.h>
#include <steam/isteamremotestorage.h>
#include <steam/isteaminventory.h>
#include <steam/isteamugc.h>
#include <steam/isteamutils.h>
#include <steam/isteaminput.h>
#include <steam/isteamscreenshots.h>
#include <steam/isteamremoteplay.h>
#include <steam/isteamgameserverstats.h>

namespace FoundationSteamworks
{
    struct FoundationSteamworksSystemComponent::SteamCallbackRegistry
    {
        // --- ISteamUser ---
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnSteamServersConnected,       SteamServersConnected_t,               m_cbSteamServersConnected);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnSteamServersDisconnected,    SteamServersDisconnected_t,            m_cbSteamServersDisconnected);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnPersonaStateChange,          PersonaStateChange_t,                  m_cbPersonaStateChange);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnValidateAuthTicketResponse,  ValidateAuthTicketResponse_t,          m_cbValidateAuthTicket);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnGameWebCallback,             GameWebCallback_t,                     m_cbGameWebCallback);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnGetAuthSessionTicketResponse,GetAuthSessionTicketResponse_t,        m_cbGetAuthSessionTicket);

        // --- ISteamApps ---
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnDlcInstalled,               DlcInstalled_t,                        m_cbDlcInstalled);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnTimedTrialStatus,            TimedTrialStatus_t,                    m_cbTimedTrialStatus);

        // --- ISteamFriends ---
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnFriendPersonaStateChange,    PersonaStateChange_t,                  m_cbFriendPersonaStateChange);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnGameConnectedFriendChatMsg,  GameConnectedFriendChatMsg_t,          m_cbFriendChatMsg);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnGameConnectedClanChatMsg,    GameConnectedClanChatMsg_t,            m_cbClanChatMsg);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnGameRichPresenceJoinRequested,GameRichPresenceJoinRequested_t,      m_cbRichPresenceJoin);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnGameLobbyJoinRequested,      GameLobbyJoinRequested_t,              m_cbLobbyJoinRequested);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnGameOverlayActivatedFriends, GameOverlayActivated_t,                m_cbOverlayActivatedFriends);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnGameServerChangeRequested,   GameServerChangeRequested_t,           m_cbGameServerChange);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnFriendRichPresenceUpdate,    FriendRichPresenceUpdate_t,            m_cbFriendRichPresence);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnJoinClanChatRoomCompletion,  JoinClanChatRoomCompletionResult_t,    m_cbJoinClanChat);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnGameConnectedChatJoin,       GameConnectedChatJoin_t,               m_cbChatJoin);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnGameConnectedChatLeave,      GameConnectedChatLeave_t,              m_cbChatLeave);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnAvatarImageLoaded,           AvatarImageLoaded_t,                   m_cbAvatarImageLoaded);

        // --- ISteamMatchmaking ---
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnLobbyDataUpdate,             LobbyDataUpdate_t,                     m_cbLobbyDataUpdate);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnLobbyChatMsg,                LobbyChatMsg_t,                        m_cbLobbyChatMsg);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnLobbyChatUpdate,             LobbyChatUpdate_t,                     m_cbLobbyChatUpdate);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnLobbyGameCreated,            LobbyGameCreated_t,                    m_cbLobbyGameCreated);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnLobbyInvite,                 LobbyInvite_t,                         m_cbLobbyInvite);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnLobbyKicked,                 LobbyKicked_t,                         m_cbLobbyKicked);

        // --- ISteamUserStats ---
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnUserStatsReceived,           UserStatsReceived_t,                   m_cbUserStatsReceived);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnUserStatsStored,             UserStatsStored_t,                     m_cbUserStatsStored);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnUserAchievementStored,       UserAchievementStored_t,               m_cbUserAchievementStored);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnUserStatsUnloaded,           UserStatsUnloaded_t,                   m_cbUserStatsUnloaded);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnUserAchievementIconFetched,  UserAchievementIconFetched_t,          m_cbAchievementIconFetched);

        // --- ISteamUtils ---
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnGameOverlayActivatedUtils,   GameOverlayActivated_t,                m_cbOverlayActivatedUtils);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnSteamShutdown,               SteamShutdown_t,                       m_cbSteamShutdown);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnIPCountryChanged,            IPCountry_t,                           m_cbIPCountryChanged);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnLowBatteryPower,             LowBatteryPower_t,                     m_cbLowBatteryPower);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnFloatingGamepadTextInputDismissed, FloatingGamepadTextInputDismissed_t, m_cbFloatingKeyboard);

        // --- ISteamInput ---
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnSteamInputDeviceConnected,   SteamInputDeviceConnected_t,           m_cbInputDeviceConnected);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnSteamInputDeviceDisconnected,SteamInputDeviceDisconnected_t,        m_cbInputDeviceDisconnected);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnSteamInputConfigurationLoaded,SteamInputConfigurationLoaded_t,      m_cbInputConfigLoaded);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnSteamInputGamepadSlotChange, SteamInputGamepadSlotChange_t,         m_cbInputGamepadSlotChange);

        // --- ISteamScreenshots ---
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnScreenshotRequested,         ScreenshotRequested_t,                 m_cbScreenshotRequested);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnScreenshotReady,             ScreenshotReady_t,                     m_cbScreenshotReady);

        // --- ISteamRemotePlay ---
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnRemotePlaySessionConnected,  SteamRemotePlaySessionConnected_t,     m_cbRemotePlayConnected);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnRemotePlaySessionDisconnected,SteamRemotePlaySessionDisconnected_t, m_cbRemotePlayDisconnected);

        // --- ISteamInventory ---
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnSteamInventoryResultReady,   SteamInventoryResultReady_t,           m_cbInventoryResultReady);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnSteamInventoryFullUpdate,     SteamInventoryFullUpdate_t,            m_cbInventoryFullUpdate);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnSteamInventoryDefinitionUpdate,SteamInventoryDefinitionUpdate_t,    m_cbInventoryDefinitionUpdate);
        STEAM_CALLBACK_MANUAL(SteamCallbackRegistry, OnSteamInventoryEligiblePromoItemDefIDs, SteamInventoryEligiblePromoItemDefIDs_t, m_cbInventoryPromoItems);

        // --- ISteamGameServer (game-server context callbacks) ---
        STEAM_GAMESERVER_CALLBACK_MANUAL(SteamCallbackRegistry, OnGSClientApprove,              GSClientApprove_t,             m_cbGSClientApprove);
        STEAM_GAMESERVER_CALLBACK_MANUAL(SteamCallbackRegistry, OnGSClientDeny,                 GSClientDeny_t,                m_cbGSClientDeny);
        STEAM_GAMESERVER_CALLBACK_MANUAL(SteamCallbackRegistry, OnGSPolicyResponse,             GSPolicyResponse_t,            m_cbGSPolicyResponse);
        STEAM_GAMESERVER_CALLBACK_MANUAL(SteamCallbackRegistry, OnGSValidateAuthTicketResponse, ValidateAuthTicketResponse_t,  m_cbGSValidateAuthTicket);
        STEAM_GAMESERVER_CALLBACK_MANUAL(SteamCallbackRegistry, OnGSClientGroupStatus,          GSClientGroupStatus_t,         m_cbGSClientGroupStatus);

        void RegisterAll();
        void RegisterGameServerCallbacks();
    };

} // namespace FoundationSteamworks
