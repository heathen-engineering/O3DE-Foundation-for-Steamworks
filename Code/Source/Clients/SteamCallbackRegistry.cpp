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

#include "SteamCallbackRegistry.h"
#include "SteamTypeConverters.h"

#include <FoundationSteamworks/SteamUserNotificationBus.h>
#include <FoundationSteamworks/SteamAppsNotificationBus.h>
#include <FoundationSteamworks/SteamFriendsNotificationBus.h>
#include <FoundationSteamworks/SteamMatchmakingNotificationBus.h>
#include <FoundationSteamworks/SteamUserStatsNotificationBus.h>
#include <FoundationSteamworks/SteamUtilsNotificationBus.h>
#include <FoundationSteamworks/SteamInputNotificationBus.h>
#include <FoundationSteamworks/SteamScreenshotsNotificationBus.h>
#include <FoundationSteamworks/SteamRemotePlayNotificationBus.h>
#include <FoundationSteamworks/SteamInventoryNotificationBus.h>
#include <FoundationSteamworks/SteamGameServerNotificationBus.h>

using namespace Heathen;

namespace FoundationSteamworks
{
    // -----------------------------------------------------------------------
    // SteamCallbackRegistry method definitions
    // Each method converts Steam types to O3DE types and broadcasts on the
    // corresponding Heathen notification bus.
    // -----------------------------------------------------------------------

    // --- ISteamUser ---

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnSteamServersConnected(SteamServersConnected_t*)
    {
        SteamUserNotificationBus::Broadcast(&SteamUserNotifications::OnSteamConnected);
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnSteamServersDisconnected(SteamServersDisconnected_t* pParam)
    {
        SteamUserNotificationBus::Broadcast(&SteamUserNotifications::OnSteamDisconnected,
            ToSteamResult(pParam->m_eResult));
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnPersonaStateChange(PersonaStateChange_t* pParam)
    {
        SteamUserNotificationBus::Broadcast(&SteamUserNotifications::OnPersonaStateChanged,
            ToSteamId(pParam->m_ulSteamID),
            static_cast<AZ::u32>(pParam->m_nChangeFlags));
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnValidateAuthTicketResponse(ValidateAuthTicketResponse_t* pParam)
    {
        SteamUserNotificationBus::Broadcast(&SteamUserNotifications::OnValidateAuthTicketResponse,
            ToSteamId(pParam->m_SteamID),
            static_cast<AZ::s32>(pParam->m_eAuthSessionResponse),
            ToSteamId(pParam->m_OwnerSteamID));
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnGameWebCallback(GameWebCallback_t* pParam)
    {
        SteamUserNotificationBus::Broadcast(&SteamUserNotifications::OnGameWebCallback,
            AZStd::string(pParam->m_szURL));
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnGetAuthSessionTicketResponse(GetAuthSessionTicketResponse_t* pParam)
    {
        SteamUserNotificationBus::Broadcast(&SteamUserNotifications::OnGetAuthSessionTicketResponse,
            static_cast<SteamAuthTicketHandle>(pParam->m_hAuthTicket),
            ToSteamResult(pParam->m_eResult));
    }

    // --- ISteamApps ---

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnDlcInstalled(DlcInstalled_t* pParam)
    {
        SteamAppsNotificationBus::Broadcast(&SteamAppsNotifications::OnDlcInstalled,
            static_cast<SteamAppId>(pParam->m_nAppID));
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnTimedTrialStatus(TimedTrialStatus_t* pParam)
    {
        SteamAppsNotificationBus::Broadcast(&SteamAppsNotifications::OnTimedTrialStatus,
            static_cast<SteamAppId>(pParam->m_unAppID),
            pParam->m_bIsOffline,
            pParam->m_unSecondsAllowed,
            pParam->m_unSecondsPlayed);
    }

    // --- ISteamFriends ---

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnFriendPersonaStateChange(PersonaStateChange_t* pParam)
    {
        SteamFriendsNotificationBus::Broadcast(&SteamFriendsNotifications::OnPersonaStateChange,
            ToSteamId(pParam->m_ulSteamID),
            static_cast<AZ::u32>(pParam->m_nChangeFlags));
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnGameConnectedFriendChatMsg(GameConnectedFriendChatMsg_t* pParam)
    {
        SteamFriendsNotificationBus::Broadcast(&SteamFriendsNotifications::OnGameConnectedFriendChatMsg,
            ToSteamId(pParam->m_steamIDUser),
            pParam->m_iMessageID);
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnGameConnectedClanChatMsg(GameConnectedClanChatMsg_t* pParam)
    {
        SteamFriendsNotificationBus::Broadcast(&SteamFriendsNotifications::OnGameConnectedClanChatMsg,
            ToSteamId(pParam->m_steamIDClanChat),
            ToSteamId(pParam->m_steamIDUser),
            pParam->m_iMessageID);
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnGameRichPresenceJoinRequested(GameRichPresenceJoinRequested_t* pParam)
    {
        SteamFriendsNotificationBus::Broadcast(&SteamFriendsNotifications::OnGameRichPresenceJoinRequested,
            ToSteamId(pParam->m_steamIDFriend),
            AZStd::string(pParam->m_rgchConnect));
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnGameLobbyJoinRequested(GameLobbyJoinRequested_t* pParam)
    {
        SteamFriendsNotificationBus::Broadcast(&SteamFriendsNotifications::OnGameLobbyJoinRequested,
            ToSteamId(pParam->m_steamIDLobby),
            ToSteamId(pParam->m_steamIDFriend));
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnGameOverlayActivatedFriends(GameOverlayActivated_t* pParam)
    {
        SteamFriendsNotificationBus::Broadcast(&SteamFriendsNotifications::OnGameOverlayActivated,
            pParam->m_bActive != 0);
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnGameServerChangeRequested(GameServerChangeRequested_t* pParam)
    {
        SteamFriendsNotificationBus::Broadcast(&SteamFriendsNotifications::OnGameServerChangeRequested,
            AZStd::string(pParam->m_rgchServer),
            AZStd::string(pParam->m_rgchPassword));
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnFriendRichPresenceUpdate(FriendRichPresenceUpdate_t* pParam)
    {
        SteamFriendsNotificationBus::Broadcast(&SteamFriendsNotifications::OnFriendRichPresenceUpdate,
            ToSteamId(pParam->m_steamIDFriend),
            static_cast<SteamAppId>(pParam->m_nAppID));
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnJoinClanChatRoomCompletion(JoinClanChatRoomCompletionResult_t* pParam)
    {
        SteamFriendsNotificationBus::Broadcast(&SteamFriendsNotifications::OnJoinClanChatRoomCompletion,
            ToSteamId(pParam->m_steamIDClanChat),
            static_cast<AZ::s32>(pParam->m_eChatRoomEnterResponse));
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnGameConnectedChatJoin(GameConnectedChatJoin_t* pParam)
    {
        SteamFriendsNotificationBus::Broadcast(&SteamFriendsNotifications::OnGameConnectedChatJoin,
            ToSteamId(pParam->m_steamIDClanChat),
            ToSteamId(pParam->m_steamIDUser));
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnGameConnectedChatLeave(GameConnectedChatLeave_t* pParam)
    {
        SteamFriendsNotificationBus::Broadcast(&SteamFriendsNotifications::OnGameConnectedChatLeave,
            ToSteamId(pParam->m_steamIDClanChat),
            ToSteamId(pParam->m_steamIDUser),
            pParam->m_bKicked,
            pParam->m_bDropped);
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnAvatarImageLoaded(AvatarImageLoaded_t* pParam)
    {
        SteamFriendsNotificationBus::Broadcast(&SteamFriendsNotifications::OnAvatarImageLoaded,
            ToSteamId(pParam->m_steamID),
            pParam->m_iImage,
            pParam->m_iWide,
            pParam->m_iTall);
    }

    // --- ISteamMatchmaking ---

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnLobbyDataUpdate(LobbyDataUpdate_t* pParam)
    {
        SteamMatchmakingNotificationBus::Broadcast(&SteamMatchmakingNotifications::OnLobbyDataUpdate,
            ToSteamId(pParam->m_ulSteamIDLobby),
            ToSteamId(pParam->m_ulSteamIDMember),
            pParam->m_bSuccess != 0);
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnLobbyChatMsg(LobbyChatMsg_t* pParam)
    {
        SteamMatchmakingNotificationBus::Broadcast(&SteamMatchmakingNotifications::OnLobbyChatMsg,
            ToSteamId(pParam->m_ulSteamIDLobby),
            ToSteamId(pParam->m_ulSteamIDUser),
            pParam->m_eChatEntryType,
            pParam->m_iChatID);
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnLobbyChatUpdate(LobbyChatUpdate_t* pParam)
    {
        SteamMatchmakingNotificationBus::Broadcast(&SteamMatchmakingNotifications::OnLobbyChatUpdate,
            ToSteamId(pParam->m_ulSteamIDLobby),
            ToSteamId(pParam->m_ulSteamIDUserChanged),
            ToSteamId(pParam->m_ulSteamIDMakingChange),
            pParam->m_rgfChatMemberStateChange);
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnLobbyGameCreated(LobbyGameCreated_t* pParam)
    {
        SteamMatchmakingNotificationBus::Broadcast(&SteamMatchmakingNotifications::OnLobbyGameCreated,
            ToSteamId(pParam->m_ulSteamIDLobby),
            ToSteamId(pParam->m_ulSteamIDGameServer),
            pParam->m_unIP,
            pParam->m_usPort);
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnLobbyInvite(LobbyInvite_t* pParam)
    {
        SteamMatchmakingNotificationBus::Broadcast(&SteamMatchmakingNotifications::OnLobbyInvite,
            ToSteamId(pParam->m_ulSteamIDUser),
            ToSteamId(pParam->m_ulSteamIDLobby),
            pParam->m_ulGameID);
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnLobbyKicked(LobbyKicked_t* pParam)
    {
        SteamMatchmakingNotificationBus::Broadcast(&SteamMatchmakingNotifications::OnLobbyKicked,
            ToSteamId(pParam->m_ulSteamIDLobby),
            ToSteamId(pParam->m_ulSteamIDAdmin),
            pParam->m_bKickedDueToDisconnect != 0);
    }

    // --- ISteamUserStats ---

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnUserStatsReceived(UserStatsReceived_t* pParam)
    {
        SteamUserStatsNotificationBus::Broadcast(&SteamUserStatsNotifications::OnUserStatsReceived,
            pParam->m_nGameID,
            ToSteamResult(pParam->m_eResult),
            ToSteamId(pParam->m_steamIDUser));
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnUserStatsStored(UserStatsStored_t* pParam)
    {
        SteamUserStatsNotificationBus::Broadcast(&SteamUserStatsNotifications::OnUserStatsStored,
            pParam->m_nGameID,
            ToSteamResult(pParam->m_eResult));
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnUserAchievementStored(UserAchievementStored_t* pParam)
    {
        SteamUserStatsNotificationBus::Broadcast(&SteamUserStatsNotifications::OnUserAchievementStored,
            pParam->m_nGameID,
            pParam->m_bGroupAchievement,
            AZStd::string(pParam->m_rgchAchievementName),
            pParam->m_nCurProgress,
            pParam->m_nMaxProgress);
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnUserStatsUnloaded(UserStatsUnloaded_t* pParam)
    {
        SteamUserStatsNotificationBus::Broadcast(&SteamUserStatsNotifications::OnUserStatsUnloaded,
            ToSteamId(pParam->m_steamIDUser));
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnUserAchievementIconFetched(UserAchievementIconFetched_t* pParam)
    {
        SteamUserStatsNotificationBus::Broadcast(&SteamUserStatsNotifications::OnUserAchievementIconFetched,
            pParam->m_nGameID.ToUint64(),
            AZStd::string(pParam->m_rgchAchievementName),
            pParam->m_bAchieved,
            pParam->m_nIconHandle);
    }

    // --- ISteamUtils ---

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnGameOverlayActivatedUtils(GameOverlayActivated_t* pParam)
    {
        SteamUtilsNotificationBus::Broadcast(&SteamUtilsNotifications::OnGameOverlayActivated,
            pParam->m_bActive != 0);
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnSteamShutdown(SteamShutdown_t*)
    {
        SteamUtilsNotificationBus::Broadcast(&SteamUtilsNotifications::OnSteamShutdown);
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnIPCountryChanged(IPCountry_t*)
    {
        SteamUtilsNotificationBus::Broadcast(&SteamUtilsNotifications::OnIPCountryChanged);
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnLowBatteryPower(LowBatteryPower_t* pParam)
    {
        SteamUtilsNotificationBus::Broadcast(&SteamUtilsNotifications::OnLowBatteryPower,
            pParam->m_nMinutesBatteryLeft);
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnFloatingGamepadTextInputDismissed(FloatingGamepadTextInputDismissed_t*)
    {
        SteamUtilsNotificationBus::Broadcast(&SteamUtilsNotifications::OnFloatingGamepadTextInputDismissed);
    }

    // --- ISteamInput ---

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnSteamInputDeviceConnected(SteamInputDeviceConnected_t* pParam)
    {
        SteamInputNotificationBus::Broadcast(&SteamInputNotifications::OnSteamInputDeviceConnected,
            static_cast<AZ::u64>(pParam->m_ulConnectedDeviceHandle));
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnSteamInputDeviceDisconnected(SteamInputDeviceDisconnected_t* pParam)
    {
        SteamInputNotificationBus::Broadcast(&SteamInputNotifications::OnSteamInputDeviceDisconnected,
            static_cast<AZ::u64>(pParam->m_ulDisconnectedDeviceHandle));
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnSteamInputConfigurationLoaded(SteamInputConfigurationLoaded_t* pParam)
    {
        SteamInputNotificationBus::Broadcast(&SteamInputNotifications::OnSteamInputConfigurationLoaded,
            static_cast<SteamAppId>(pParam->m_unAppID),
            static_cast<AZ::u64>(pParam->m_ulDeviceHandle));
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnSteamInputGamepadSlotChange(SteamInputGamepadSlotChange_t* pParam)
    {
        SteamInputNotificationBus::Broadcast(&SteamInputNotifications::OnSteamInputGamepadSlotChange,
            static_cast<SteamAppId>(pParam->m_unAppID),
            pParam->m_nOldGamepadSlot,
            static_cast<AZ::s32>(pParam->m_eDeviceType),
            static_cast<AZ::u64>(pParam->m_ulDeviceHandle));
    }

    // --- ISteamScreenshots ---

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnScreenshotRequested(ScreenshotRequested_t*)
    {
        SteamScreenshotsNotificationBus::Broadcast(&SteamScreenshotsNotifications::OnScreenshotRequested);
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnScreenshotReady(ScreenshotReady_t* pParam)
    {
        SteamScreenshotsNotificationBus::Broadcast(&SteamScreenshotsNotifications::OnScreenshotReady,
            static_cast<AZ::u32>(pParam->m_hLocal),
            ToSteamResult(pParam->m_eResult));
    }

    // --- ISteamRemotePlay ---

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnRemotePlaySessionConnected(SteamRemotePlaySessionConnected_t* pParam)
    {
        SteamRemotePlayNotificationBus::Broadcast(&SteamRemotePlayNotifications::OnRemotePlaySessionConnected,
            static_cast<AZ::u32>(pParam->m_unSessionID));
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnRemotePlaySessionDisconnected(SteamRemotePlaySessionDisconnected_t* pParam)
    {
        SteamRemotePlayNotificationBus::Broadcast(&SteamRemotePlayNotifications::OnRemotePlaySessionDisconnected,
            static_cast<AZ::u32>(pParam->m_unSessionID));
    }

    // --- ISteamInventory ---

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnSteamInventoryResultReady(SteamInventoryResultReady_t* pParam)
    {
        SteamInventoryNotificationBus::Broadcast(&SteamInventoryNotifications::OnSteamInventoryResultReady,
            static_cast<SteamInventoryResultHandle>(pParam->m_handle),
            ToSteamResult(pParam->m_result));
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnSteamInventoryFullUpdate(SteamInventoryFullUpdate_t* pParam)
    {
        SteamInventoryNotificationBus::Broadcast(&SteamInventoryNotifications::OnSteamInventoryFullUpdate,
            static_cast<SteamInventoryResultHandle>(pParam->m_handle));
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnSteamInventoryDefinitionUpdate(SteamInventoryDefinitionUpdate_t*)
    {
        SteamInventoryNotificationBus::Broadcast(&SteamInventoryNotifications::OnSteamInventoryDefinitionUpdate);
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnSteamInventoryEligiblePromoItemDefIDs(SteamInventoryEligiblePromoItemDefIDs_t* pParam)
    {
        SteamInventoryNotificationBus::Broadcast(&SteamInventoryNotifications::OnSteamInventoryEligiblePromoItemDefIDs,
            ToSteamResult(pParam->m_result),
            ToSteamId(pParam->m_steamID),
            pParam->m_numEligiblePromoItemDefs,
            pParam->m_bCachedData);
    }

    // --- ISteamGameServer ---

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnGSClientApprove(GSClientApprove_t* pParam)
    {
        SteamGameServerNotificationBus::Broadcast(&SteamGameServerNotifications::OnGSClientApprove,
            ToSteamId(pParam->m_SteamID),
            ToSteamId(pParam->m_OwnerSteamID));
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnGSClientDeny(GSClientDeny_t* pParam)
    {
        SteamGameServerNotificationBus::Broadcast(&SteamGameServerNotifications::OnGSClientDeny,
            ToSteamId(pParam->m_SteamID),
            static_cast<AZ::s32>(pParam->m_eDenyReason),
            AZStd::string(pParam->m_rgchOptionalText));
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnGSPolicyResponse(GSPolicyResponse_t* pParam)
    {
        SteamGameServerNotificationBus::Broadcast(&SteamGameServerNotifications::OnGSPolicyResponse,
            pParam->m_bSecure != 0);
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnGSValidateAuthTicketResponse(ValidateAuthTicketResponse_t* pParam)
    {
        SteamGameServerNotificationBus::Broadcast(&SteamGameServerNotifications::OnGSValidateAuthTicketResponse,
            ToSteamId(pParam->m_SteamID),
            static_cast<AZ::s32>(pParam->m_eAuthSessionResponse),
            ToSteamId(pParam->m_OwnerSteamID));
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::OnGSClientGroupStatus(GSClientGroupStatus_t* pParam)
    {
        SteamGameServerNotificationBus::Broadcast(&SteamGameServerNotifications::OnGSClientGroupStatus,
            ToSteamId(pParam->m_SteamIDUser),
            ToSteamId(pParam->m_SteamIDGroup),
            pParam->m_bMember,
            pParam->m_bOfficer);
    }

    // -----------------------------------------------------------------------
    // Registration helpers
    // -----------------------------------------------------------------------

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::RegisterAll()
    {
        m_cbSteamServersConnected.Register(this, &SteamCallbackRegistry::OnSteamServersConnected);
        m_cbSteamServersDisconnected.Register(this, &SteamCallbackRegistry::OnSteamServersDisconnected);
        m_cbPersonaStateChange.Register(this, &SteamCallbackRegistry::OnPersonaStateChange);
        m_cbValidateAuthTicket.Register(this, &SteamCallbackRegistry::OnValidateAuthTicketResponse);
        m_cbGameWebCallback.Register(this, &SteamCallbackRegistry::OnGameWebCallback);
        m_cbGetAuthSessionTicket.Register(this, &SteamCallbackRegistry::OnGetAuthSessionTicketResponse);

        m_cbDlcInstalled.Register(this, &SteamCallbackRegistry::OnDlcInstalled);
        m_cbTimedTrialStatus.Register(this, &SteamCallbackRegistry::OnTimedTrialStatus);

        m_cbFriendPersonaStateChange.Register(this, &SteamCallbackRegistry::OnFriendPersonaStateChange);
        m_cbFriendChatMsg.Register(this, &SteamCallbackRegistry::OnGameConnectedFriendChatMsg);
        m_cbClanChatMsg.Register(this, &SteamCallbackRegistry::OnGameConnectedClanChatMsg);
        m_cbRichPresenceJoin.Register(this, &SteamCallbackRegistry::OnGameRichPresenceJoinRequested);
        m_cbLobbyJoinRequested.Register(this, &SteamCallbackRegistry::OnGameLobbyJoinRequested);
        m_cbOverlayActivatedFriends.Register(this, &SteamCallbackRegistry::OnGameOverlayActivatedFriends);
        m_cbGameServerChange.Register(this, &SteamCallbackRegistry::OnGameServerChangeRequested);
        m_cbFriendRichPresence.Register(this, &SteamCallbackRegistry::OnFriendRichPresenceUpdate);
        m_cbJoinClanChat.Register(this, &SteamCallbackRegistry::OnJoinClanChatRoomCompletion);
        m_cbChatJoin.Register(this, &SteamCallbackRegistry::OnGameConnectedChatJoin);
        m_cbChatLeave.Register(this, &SteamCallbackRegistry::OnGameConnectedChatLeave);
        m_cbAvatarImageLoaded.Register(this, &SteamCallbackRegistry::OnAvatarImageLoaded);

        m_cbLobbyDataUpdate.Register(this, &SteamCallbackRegistry::OnLobbyDataUpdate);
        m_cbLobbyChatMsg.Register(this, &SteamCallbackRegistry::OnLobbyChatMsg);
        m_cbLobbyChatUpdate.Register(this, &SteamCallbackRegistry::OnLobbyChatUpdate);
        m_cbLobbyGameCreated.Register(this, &SteamCallbackRegistry::OnLobbyGameCreated);
        m_cbLobbyInvite.Register(this, &SteamCallbackRegistry::OnLobbyInvite);
        m_cbLobbyKicked.Register(this, &SteamCallbackRegistry::OnLobbyKicked);

        m_cbUserStatsReceived.Register(this, &SteamCallbackRegistry::OnUserStatsReceived);
        m_cbUserStatsStored.Register(this, &SteamCallbackRegistry::OnUserStatsStored);
        m_cbUserAchievementStored.Register(this, &SteamCallbackRegistry::OnUserAchievementStored);
        m_cbUserStatsUnloaded.Register(this, &SteamCallbackRegistry::OnUserStatsUnloaded);
        m_cbAchievementIconFetched.Register(this, &SteamCallbackRegistry::OnUserAchievementIconFetched);

        m_cbOverlayActivatedUtils.Register(this, &SteamCallbackRegistry::OnGameOverlayActivatedUtils);
        m_cbSteamShutdown.Register(this, &SteamCallbackRegistry::OnSteamShutdown);
        m_cbIPCountryChanged.Register(this, &SteamCallbackRegistry::OnIPCountryChanged);
        m_cbLowBatteryPower.Register(this, &SteamCallbackRegistry::OnLowBatteryPower);
        m_cbFloatingKeyboard.Register(this, &SteamCallbackRegistry::OnFloatingGamepadTextInputDismissed);

        m_cbInputDeviceConnected.Register(this, &SteamCallbackRegistry::OnSteamInputDeviceConnected);
        m_cbInputDeviceDisconnected.Register(this, &SteamCallbackRegistry::OnSteamInputDeviceDisconnected);
        m_cbInputConfigLoaded.Register(this, &SteamCallbackRegistry::OnSteamInputConfigurationLoaded);
        m_cbInputGamepadSlotChange.Register(this, &SteamCallbackRegistry::OnSteamInputGamepadSlotChange);

        m_cbScreenshotRequested.Register(this, &SteamCallbackRegistry::OnScreenshotRequested);
        m_cbScreenshotReady.Register(this, &SteamCallbackRegistry::OnScreenshotReady);

        m_cbRemotePlayConnected.Register(this, &SteamCallbackRegistry::OnRemotePlaySessionConnected);
        m_cbRemotePlayDisconnected.Register(this, &SteamCallbackRegistry::OnRemotePlaySessionDisconnected);

        m_cbInventoryResultReady.Register(this, &SteamCallbackRegistry::OnSteamInventoryResultReady);
        m_cbInventoryFullUpdate.Register(this, &SteamCallbackRegistry::OnSteamInventoryFullUpdate);
        m_cbInventoryDefinitionUpdate.Register(this, &SteamCallbackRegistry::OnSteamInventoryDefinitionUpdate);
        m_cbInventoryPromoItems.Register(this, &SteamCallbackRegistry::OnSteamInventoryEligiblePromoItemDefIDs);
    }

    void FoundationSteamworksSystemComponent::SteamCallbackRegistry::RegisterGameServerCallbacks()
    {
        m_cbGSClientApprove.Register(this, &SteamCallbackRegistry::OnGSClientApprove);
        m_cbGSClientDeny.Register(this, &SteamCallbackRegistry::OnGSClientDeny);
        m_cbGSPolicyResponse.Register(this, &SteamCallbackRegistry::OnGSPolicyResponse);
        m_cbGSValidateAuthTicket.Register(this, &SteamCallbackRegistry::OnGSValidateAuthTicketResponse);
        m_cbGSClientGroupStatus.Register(this, &SteamCallbackRegistry::OnGSClientGroupStatus);
    }

} // namespace FoundationSteamworks
