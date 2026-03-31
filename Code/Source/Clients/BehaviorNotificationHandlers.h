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

#include <AzCore/RTTI/BehaviorContext.h>
#include <FoundationSteamworks/SteamUserNotificationBus.h>
#include <FoundationSteamworks/SteamAppsNotificationBus.h>
#include <FoundationSteamworks/SteamFriendsNotificationBus.h>
#include <FoundationSteamworks/SteamMatchmakingNotificationBus.h>
#include <FoundationSteamworks/SteamUserStatsNotificationBus.h>
#include <FoundationSteamworks/SteamRemoteStorageNotificationBus.h>
#include <FoundationSteamworks/SteamInventoryNotificationBus.h>
#include <FoundationSteamworks/SteamUGCNotificationBus.h>
#include <FoundationSteamworks/SteamUtilsNotificationBus.h>
#include <FoundationSteamworks/SteamInputNotificationBus.h>
#include <FoundationSteamworks/SteamScreenshotsNotificationBus.h>
#include <FoundationSteamworks/SteamRemotePlayNotificationBus.h>
#include <FoundationSteamworks/SteamGameServerNotificationBus.h>
#include <FoundationSteamworks/SteamGameServerStatsNotificationBus.h>
#include <FoundationSteamworks/SteamTimelineNotificationBus.h>

namespace FoundationSteamworks
{
    class BehaviorSteamUserNotificationHandler
        : public SteamUserNotificationBus::Handler
        , public AZ::BehaviorEBusHandler
    {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(BehaviorSteamUserNotificationHandler,
            "{B1C2D3E4-F5A6-47B8-C9D0-E1F2A3B4C5D6}", AZ::SystemAllocator,
            OnSteamConnected, OnSteamDisconnected, OnPersonaStateChanged,
            OnValidateAuthTicketResponse, OnGameWebCallback,
            OnGetAuthSessionTicketResponse, OnEncryptedAppTicketResponse,
            OnStoreAuthURLResponse, OnMarketEligibilityResponse, OnDurationControl);

        void OnSteamConnected() override { Call(FN_OnSteamConnected); }
        void OnSteamDisconnected(SteamResult reason) override { Call(FN_OnSteamDisconnected, reason); }
        void OnPersonaStateChanged(SteamId userId, AZ::u32 changeFlags) override { Call(FN_OnPersonaStateChanged, userId, changeFlags); }
        void OnValidateAuthTicketResponse(SteamId steamId, AZ::s32 authSessionResponse, SteamId ownerSteamId) override { Call(FN_OnValidateAuthTicketResponse, steamId, authSessionResponse, ownerSteamId); }
        void OnGameWebCallback(const AZStd::string& url) override { Call(FN_OnGameWebCallback, url); }
        void OnGetAuthSessionTicketResponse(SteamAuthTicketHandle h, SteamResult result) override { Call(FN_OnGetAuthSessionTicketResponse, h, result); }
        void OnEncryptedAppTicketResponse(SteamCallHandle ch, SteamResult result) override { Call(FN_OnEncryptedAppTicketResponse, ch, result); }
        void OnStoreAuthURLResponse(SteamCallHandle ch, const AZStd::string& url) override { Call(FN_OnStoreAuthURLResponse, ch, url); }
        void OnMarketEligibilityResponse(SteamCallHandle ch, bool allowed, AZ::u32 notAllowedReason) override { Call(FN_OnMarketEligibilityResponse, ch, allowed, notAllowedReason); }
        void OnDurationControl(SteamCallHandle ch, SteamResult result, AZ::s32 applicable, AZ::s32 secondsLastFiveHours, AZ::s32 progress, AZ::s32 notification) override { Call(FN_OnDurationControl, ch, result, applicable, secondsLastFiveHours, progress, notification); }
    };

    class BehaviorSteamAppsNotificationHandler
        : public SteamAppsNotificationBus::Handler
        , public AZ::BehaviorEBusHandler
    {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(BehaviorSteamAppsNotificationHandler,
            "{C2D3E4F5-A6B7-48C9-D0E1-F2A3B4C5D6E7}", AZ::SystemAllocator,
            OnDlcInstalled, OnTimedTrialStatus);
        // OnFileDetailsResult has AZStd::array<u8,20> — not scriptable; C++ handlers receive it normally.

        void OnDlcInstalled(SteamAppId appId) override { Call(FN_OnDlcInstalled, appId); }
        void OnTimedTrialStatus(SteamAppId appId, bool isOffline, AZ::u32 secondsAllowed, AZ::u32 secondsPlayed) override { Call(FN_OnTimedTrialStatus, appId, isOffline, secondsAllowed, secondsPlayed); }
    };

    class BehaviorSteamFriendsNotificationHandler
        : public SteamFriendsNotificationBus::Handler
        , public AZ::BehaviorEBusHandler
    {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(BehaviorSteamFriendsNotificationHandler,
            "{D3E4F5A6-B7C8-49D0-E1F2-A3B4C5D6E7F8}", AZ::SystemAllocator,
            OnPersonaStateChange, OnGameConnectedFriendChatMsg, OnGameConnectedClanChatMsg,
            OnGameRichPresenceJoinRequested, OnGameLobbyJoinRequested, OnGameOverlayActivated,
            OnGameServerChangeRequested, OnFriendRichPresenceUpdate, OnJoinClanChatRoomCompletion,
            OnGameConnectedChatJoin, OnGameConnectedChatLeave, OnAvatarImageLoaded,
            OnClanOfficerListResponse, OnFriendsGetFollowerCount, OnFriendsIsFollowing,
            OnFriendsEnumerateFollowingList);

        void OnPersonaStateChange(SteamId userId, AZ::u32 changeFlags) override { Call(FN_OnPersonaStateChange, userId, changeFlags); }
        void OnGameConnectedFriendChatMsg(SteamId friendId, AZ::s32 messageId) override { Call(FN_OnGameConnectedFriendChatMsg, friendId, messageId); }
        void OnGameConnectedClanChatMsg(SteamId clanId, SteamId userId, AZ::s32 messageId) override { Call(FN_OnGameConnectedClanChatMsg, clanId, userId, messageId); }
        void OnGameRichPresenceJoinRequested(SteamId friendId, const AZStd::string& connectString) override { Call(FN_OnGameRichPresenceJoinRequested, friendId, connectString); }
        void OnGameLobbyJoinRequested(SteamId lobbyId, SteamId friendId) override { Call(FN_OnGameLobbyJoinRequested, lobbyId, friendId); }
        void OnGameOverlayActivated(bool active) override { Call(FN_OnGameOverlayActivated, active); }
        void OnGameServerChangeRequested(const AZStd::string& server, const AZStd::string& password) override { Call(FN_OnGameServerChangeRequested, server, password); }
        void OnFriendRichPresenceUpdate(SteamId friendId, SteamAppId appId) override { Call(FN_OnFriendRichPresenceUpdate, friendId, appId); }
        void OnJoinClanChatRoomCompletion(SteamId clanId, AZ::s32 result) override { Call(FN_OnJoinClanChatRoomCompletion, clanId, result); }
        void OnGameConnectedChatJoin(SteamId clanId, SteamId userId) override { Call(FN_OnGameConnectedChatJoin, clanId, userId); }
        void OnGameConnectedChatLeave(SteamId clanId, SteamId userId, bool kicked, bool dropped) override { Call(FN_OnGameConnectedChatLeave, clanId, userId, kicked, dropped); }
        void OnAvatarImageLoaded(SteamId userId, AZ::s32 imageHandle, AZ::s32 width, AZ::s32 height) override { Call(FN_OnAvatarImageLoaded, userId, imageHandle, width, height); }
        void OnClanOfficerListResponse(SteamCallHandle ch, SteamId clanId, AZ::s32 officerCount, bool success) override { Call(FN_OnClanOfficerListResponse, ch, clanId, officerCount, success); }
        void OnFriendsGetFollowerCount(SteamCallHandle ch, SteamResult result, SteamId steamId, AZ::s32 count) override { Call(FN_OnFriendsGetFollowerCount, ch, result, steamId, count); }
        void OnFriendsIsFollowing(SteamCallHandle ch, SteamResult result, SteamId steamId, bool isFollowing) override { Call(FN_OnFriendsIsFollowing, ch, result, steamId, isFollowing); }
        void OnFriendsEnumerateFollowingList(SteamCallHandle ch, SteamResult result, AZ::s32 resultsReturned, AZ::s32 totalResultCount) override { Call(FN_OnFriendsEnumerateFollowingList, ch, result, resultsReturned, totalResultCount); }
    };

    class BehaviorSteamMatchmakingNotificationHandler
        : public SteamMatchmakingNotificationBus::Handler
        , public AZ::BehaviorEBusHandler
    {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(BehaviorSteamMatchmakingNotificationHandler,
            "{E4F5A6B7-C8D9-4AE1-F2A3-B4C5D6E7F8A9}", AZ::SystemAllocator,
            OnLobbyDataUpdate, OnLobbyChatMsg, OnLobbyChatUpdate, OnLobbyGameCreated,
            OnLobbyInvite, OnLobbyKicked, OnLobbyCreated, OnLobbyEntered, OnLobbyMatchList);

        void OnLobbyDataUpdate(SteamId lobbyId, SteamId memberId, bool success) override { Call(FN_OnLobbyDataUpdate, lobbyId, memberId, success); }
        void OnLobbyChatMsg(SteamId lobbyId, SteamId userId, AZ::u8 chatEntryType, AZ::u32 chatId) override { Call(FN_OnLobbyChatMsg, lobbyId, userId, chatEntryType, chatId); }
        void OnLobbyChatUpdate(SteamId lobbyId, SteamId userChangedId, SteamId makingChangeId, AZ::u32 chatMemberStateChange) override { Call(FN_OnLobbyChatUpdate, lobbyId, userChangedId, makingChangeId, chatMemberStateChange); }
        void OnLobbyGameCreated(SteamId lobbyId, SteamId gameServerId, AZ::u32 ip, AZ::u16 port) override { Call(FN_OnLobbyGameCreated, lobbyId, gameServerId, ip, port); }
        void OnLobbyInvite(SteamId inviterUserId, SteamId lobbyId, AZ::u64 gameId) override { Call(FN_OnLobbyInvite, inviterUserId, lobbyId, gameId); }
        void OnLobbyKicked(SteamId lobbyId, SteamId adminId, bool kickedDueToDisconnect) override { Call(FN_OnLobbyKicked, lobbyId, adminId, kickedDueToDisconnect); }
        void OnLobbyCreated(SteamCallHandle ch, SteamResult result, SteamId lobbyId) override { Call(FN_OnLobbyCreated, ch, result, lobbyId); }
        void OnLobbyEntered(SteamCallHandle ch, SteamId lobbyId, AZ::u32 chatPermissions, bool blocked, AZ::u32 chatRoomEnterResponse) override { Call(FN_OnLobbyEntered, ch, lobbyId, chatPermissions, blocked, chatRoomEnterResponse); }
        void OnLobbyMatchList(SteamCallHandle ch, AZ::u32 lobbiesMatching) override { Call(FN_OnLobbyMatchList, ch, lobbiesMatching); }
    };

    class BehaviorSteamUserStatsNotificationHandler
        : public SteamUserStatsNotificationBus::Handler
        , public AZ::BehaviorEBusHandler
    {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(BehaviorSteamUserStatsNotificationHandler,
            "{F5A6B7C8-D9E0-4BF2-A3B4-C5D6E7F8A9B0}", AZ::SystemAllocator,
            OnUserStatsReceived, OnUserStatsStored, OnUserAchievementStored,
            OnUserStatsUnloaded, OnUserAchievementIconFetched,
            OnRequestUserStats, OnFindOrCreateLeaderboard, OnFindLeaderboard,
            OnLeaderboardScoreUploaded, OnLeaderboardScoresDownloaded,
            OnLeaderboardUGCSet, OnNumberOfCurrentPlayers,
            OnGlobalAchievementPercentagesReady, OnGlobalStatsReceived);

        void OnUserStatsReceived(AZ::u64 gameId, SteamResult result, SteamId userId) override { Call(FN_OnUserStatsReceived, gameId, result, userId); }
        void OnUserStatsStored(AZ::u64 gameId, SteamResult result) override { Call(FN_OnUserStatsStored, gameId, result); }
        void OnUserAchievementStored(AZ::u64 gameId, bool groupAchievement, const AZStd::string& achievementName, AZ::u32 curProgress, AZ::u32 maxProgress) override { Call(FN_OnUserAchievementStored, gameId, groupAchievement, achievementName, curProgress, maxProgress); }
        void OnUserStatsUnloaded(SteamId userId) override { Call(FN_OnUserStatsUnloaded, userId); }
        void OnUserAchievementIconFetched(AZ::u64 gameId, const AZStd::string& achievementName, bool achieved, AZ::s32 iconHandle) override { Call(FN_OnUserAchievementIconFetched, gameId, achievementName, achieved, iconHandle); }
        void OnRequestUserStats(SteamCallHandle ch, SteamResult result, SteamId userId) override { Call(FN_OnRequestUserStats, ch, result, userId); }
        void OnFindOrCreateLeaderboard(SteamCallHandle ch, SteamResult result, SteamLeaderboardHandle leaderboard, bool leaderboardFound) override { Call(FN_OnFindOrCreateLeaderboard, ch, result, leaderboard, leaderboardFound); }
        void OnFindLeaderboard(SteamCallHandle ch, SteamResult result, SteamLeaderboardHandle leaderboard, bool leaderboardFound) override { Call(FN_OnFindLeaderboard, ch, result, leaderboard, leaderboardFound); }
        void OnLeaderboardScoreUploaded(SteamCallHandle ch, bool success, SteamLeaderboardHandle leaderboard, AZ::s32 score, bool scoreChanged, AZ::s32 globalRankNew, AZ::s32 globalRankPrev) override { Call(FN_OnLeaderboardScoreUploaded, ch, success, leaderboard, score, scoreChanged, globalRankNew, globalRankPrev); }
        void OnLeaderboardScoresDownloaded(SteamCallHandle ch, SteamResult result, SteamLeaderboardHandle leaderboard, SteamLeaderboardEntriesHandle entries, AZ::s32 entryCount) override { Call(FN_OnLeaderboardScoresDownloaded, ch, result, leaderboard, entries, entryCount); }
        void OnLeaderboardUGCSet(SteamCallHandle ch, SteamResult result, SteamLeaderboardHandle leaderboard) override { Call(FN_OnLeaderboardUGCSet, ch, result, leaderboard); }
        void OnNumberOfCurrentPlayers(SteamCallHandle ch, bool success, AZ::s32 players) override { Call(FN_OnNumberOfCurrentPlayers, ch, success, players); }
        void OnGlobalAchievementPercentagesReady(SteamCallHandle ch, AZ::u64 gameId, SteamResult result) override { Call(FN_OnGlobalAchievementPercentagesReady, ch, gameId, result); }
        void OnGlobalStatsReceived(SteamCallHandle ch, AZ::u64 gameId, SteamResult result) override { Call(FN_OnGlobalStatsReceived, ch, gameId, result); }
    };

    class BehaviorSteamRemoteStorageNotificationHandler
        : public SteamRemoteStorageNotificationBus::Handler
        , public AZ::BehaviorEBusHandler
    {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(BehaviorSteamRemoteStorageNotificationHandler,
            "{A6B7C8D9-E0F1-4CA3-B4C5-D6E7F8A9B0C1}", AZ::SystemAllocator,
            OnRemoteStorageLocalFileChange,
            OnRemoteStorageFileShareResult, OnRemoteStorageFileWriteAsyncComplete,
            OnRemoteStorageFileReadAsyncComplete,
            OnRemoteStorageSubscribePublishedFile, OnRemoteStorageUnsubscribePublishedFile);

        void OnRemoteStorageLocalFileChange() override { Call(FN_OnRemoteStorageLocalFileChange); }
        void OnRemoteStorageFileShareResult(SteamCallHandle ch, SteamResult result, SteamUGCHandle handle, const AZStd::string& filename) override { Call(FN_OnRemoteStorageFileShareResult, ch, result, handle, filename); }
        void OnRemoteStorageFileWriteAsyncComplete(SteamCallHandle ch, SteamResult result) override { Call(FN_OnRemoteStorageFileWriteAsyncComplete, ch, result); }
        void OnRemoteStorageFileReadAsyncComplete(SteamCallHandle ch, SteamResult result, AZ::u32 offset, AZ::u32 read) override { Call(FN_OnRemoteStorageFileReadAsyncComplete, ch, result, offset, read); }
        void OnRemoteStorageSubscribePublishedFile(SteamCallHandle ch, SteamResult result, SteamPublishedFileId publishedFileId) override { Call(FN_OnRemoteStorageSubscribePublishedFile, ch, result, publishedFileId); }
        void OnRemoteStorageUnsubscribePublishedFile(SteamCallHandle ch, SteamResult result, SteamPublishedFileId publishedFileId) override { Call(FN_OnRemoteStorageUnsubscribePublishedFile, ch, result, publishedFileId); }
    };

    class BehaviorSteamInventoryNotificationHandler
        : public SteamInventoryNotificationBus::Handler
        , public AZ::BehaviorEBusHandler
    {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(BehaviorSteamInventoryNotificationHandler,
            "{B7C8D9E0-F1A2-4DB4-C5D6-E7F8A9B0C1D2}", AZ::SystemAllocator,
            OnSteamInventoryResultReady, OnSteamInventoryFullUpdate,
            OnSteamInventoryDefinitionUpdate, OnSteamInventoryEligiblePromoItemDefIDs,
            OnSteamInventoryStartPurchaseResult, OnSteamInventoryRequestPricesResult);

        void OnSteamInventoryResultReady(SteamInventoryResultHandle resultHandle, SteamResult result) override { Call(FN_OnSteamInventoryResultReady, resultHandle, result); }
        void OnSteamInventoryFullUpdate(SteamInventoryResultHandle resultHandle) override { Call(FN_OnSteamInventoryFullUpdate, resultHandle); }
        void OnSteamInventoryDefinitionUpdate() override { Call(FN_OnSteamInventoryDefinitionUpdate); }
        void OnSteamInventoryEligiblePromoItemDefIDs(SteamResult result, SteamId userId, AZ::s32 numEligible, bool cachedData) override { Call(FN_OnSteamInventoryEligiblePromoItemDefIDs, result, userId, numEligible, cachedData); }
        void OnSteamInventoryStartPurchaseResult(SteamCallHandle ch, SteamResult result, AZ::u64 orderId, AZ::u64 transactionId) override { Call(FN_OnSteamInventoryStartPurchaseResult, ch, result, orderId, transactionId); }
        void OnSteamInventoryRequestPricesResult(SteamCallHandle ch, SteamResult result, const AZStd::string& currency) override { Call(FN_OnSteamInventoryRequestPricesResult, ch, result, currency); }
    };

    class BehaviorSteamUGCNotificationHandler
        : public SteamUGCNotificationBus::Handler
        , public AZ::BehaviorEBusHandler
    {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(BehaviorSteamUGCNotificationHandler,
            "{C8D9E0F1-A2B3-4EC5-D6E7-F8A9B0C1D2E3}", AZ::SystemAllocator,
            OnDownloadItemResult, OnItemInstalled, OnUserSubscribedItemsListChanged,
            OnSteamUGCQueryCompleted, OnSteamUGCRequestUGCDetails,
            OnCreateItem, OnSubmitItemUpdate, OnUserFavoriteItemsListChanged,
            OnSetUserItemVote, OnGetUserItemVote,
            OnStartPlaytimeTracking, OnStopPlaytimeTracking,
            OnAddUGCDependency, OnRemoveUGCDependency,
            OnAddAppDependency, OnRemoveAppDependency, OnGetAppDependencies,
            OnDeleteItem, OnWorkshopEULAStatus);

        void OnDownloadItemResult(SteamAppId appId, SteamPublishedFileId pfid, SteamResult result) override { Call(FN_OnDownloadItemResult, appId, pfid, result); }
        void OnItemInstalled(SteamAppId appId, SteamPublishedFileId pfid) override { Call(FN_OnItemInstalled, appId, pfid); }
        void OnUserSubscribedItemsListChanged(SteamAppId appId) override { Call(FN_OnUserSubscribedItemsListChanged, appId); }
        void OnSteamUGCQueryCompleted(SteamCallHandle ch, SteamResult result, SteamUGCQueryHandle queryHandle, AZ::u32 numResultsReturned, AZ::u32 totalMatchingResults, bool cachedData) override { Call(FN_OnSteamUGCQueryCompleted, ch, result, queryHandle, numResultsReturned, totalMatchingResults, cachedData); }
        void OnSteamUGCRequestUGCDetails(SteamCallHandle ch, SteamResult result, bool cachedData) override { Call(FN_OnSteamUGCRequestUGCDetails, ch, result, cachedData); }
        void OnCreateItem(SteamCallHandle ch, SteamResult result, SteamPublishedFileId pfid, bool needsLegalAgreement) override { Call(FN_OnCreateItem, ch, result, pfid, needsLegalAgreement); }
        void OnSubmitItemUpdate(SteamCallHandle ch, SteamResult result, bool needsLegalAgreement) override { Call(FN_OnSubmitItemUpdate, ch, result, needsLegalAgreement); }
        void OnUserFavoriteItemsListChanged(SteamCallHandle ch, SteamResult result, SteamPublishedFileId pfid, bool wasAddRequest) override { Call(FN_OnUserFavoriteItemsListChanged, ch, result, pfid, wasAddRequest); }
        void OnSetUserItemVote(SteamCallHandle ch, SteamResult result, SteamPublishedFileId pfid, bool voteUp) override { Call(FN_OnSetUserItemVote, ch, result, pfid, voteUp); }
        void OnGetUserItemVote(SteamCallHandle ch, SteamResult result, SteamPublishedFileId pfid, bool votedUp, bool votedDown, bool voteSkipped) override { Call(FN_OnGetUserItemVote, ch, result, pfid, votedUp, votedDown, voteSkipped); }
        void OnStartPlaytimeTracking(SteamCallHandle ch, SteamResult result) override { Call(FN_OnStartPlaytimeTracking, ch, result); }
        void OnStopPlaytimeTracking(SteamCallHandle ch, SteamResult result) override { Call(FN_OnStopPlaytimeTracking, ch, result); }
        void OnAddUGCDependency(SteamCallHandle ch, SteamResult result, SteamPublishedFileId pfid, SteamPublishedFileId childPfid) override { Call(FN_OnAddUGCDependency, ch, result, pfid, childPfid); }
        void OnRemoveUGCDependency(SteamCallHandle ch, SteamResult result, SteamPublishedFileId pfid, SteamPublishedFileId childPfid) override { Call(FN_OnRemoveUGCDependency, ch, result, pfid, childPfid); }
        void OnAddAppDependency(SteamCallHandle ch, SteamResult result, SteamPublishedFileId pfid, SteamAppId appId) override { Call(FN_OnAddAppDependency, ch, result, pfid, appId); }
        void OnRemoveAppDependency(SteamCallHandle ch, SteamResult result, SteamPublishedFileId pfid, SteamAppId appId) override { Call(FN_OnRemoveAppDependency, ch, result, pfid, appId); }
        void OnGetAppDependencies(SteamCallHandle ch, SteamResult result, SteamPublishedFileId pfid, AZ::u32 numAppDeps, AZ::u32 totalNumAppDeps) override { Call(FN_OnGetAppDependencies, ch, result, pfid, numAppDeps, totalNumAppDeps); }
        void OnDeleteItem(SteamCallHandle ch, SteamResult result, SteamPublishedFileId pfid) override { Call(FN_OnDeleteItem, ch, result, pfid); }
        void OnWorkshopEULAStatus(SteamCallHandle ch, SteamResult result, SteamAppId appId, AZ::u32 version, AZ::u32 action, bool accepted, bool needsAction) override { Call(FN_OnWorkshopEULAStatus, ch, result, appId, version, action, accepted, needsAction); }
    };

    class BehaviorSteamUtilsNotificationHandler
        : public SteamUtilsNotificationBus::Handler
        , public AZ::BehaviorEBusHandler
    {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(BehaviorSteamUtilsNotificationHandler,
            "{D9E0F1A2-B3C4-4FD6-E7F8-A9B0C1D2E3F4}", AZ::SystemAllocator,
            OnGameOverlayActivated, OnSteamShutdown, OnIPCountryChanged,
            OnLowBatteryPower, OnSteamAPICallCompleted,
            OnFloatingGamepadTextInputDismissed, OnFilterTextDictionaryChanged);

        void OnGameOverlayActivated(bool active) override { Call(FN_OnGameOverlayActivated, active); }
        void OnSteamShutdown() override { Call(FN_OnSteamShutdown); }
        void OnIPCountryChanged() override { Call(FN_OnIPCountryChanged); }
        void OnLowBatteryPower(AZ::u8 minutesBatteryLeft) override { Call(FN_OnLowBatteryPower, minutesBatteryLeft); }
        void OnSteamAPICallCompleted(SteamCallHandle callHandle, AZ::s32 callback, bool ioFailure) override { Call(FN_OnSteamAPICallCompleted, callHandle, callback, ioFailure); }
        void OnFloatingGamepadTextInputDismissed() override { Call(FN_OnFloatingGamepadTextInputDismissed); }
        void OnFilterTextDictionaryChanged(AZ::s32 language) override { Call(FN_OnFilterTextDictionaryChanged, language); }
    };

    class BehaviorSteamInputNotificationHandler
        : public SteamInputNotificationBus::Handler
        , public AZ::BehaviorEBusHandler
    {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(BehaviorSteamInputNotificationHandler,
            "{E0F1A2B3-C4D5-40E7-F8A9-B0C1D2E3F4A5}", AZ::SystemAllocator,
            OnSteamInputDeviceConnected, OnSteamInputDeviceDisconnected,
            OnSteamInputConfigurationLoaded, OnSteamInputGamepadSlotChange);

        void OnSteamInputDeviceConnected(AZ::u64 inputHandle) override { Call(FN_OnSteamInputDeviceConnected, inputHandle); }
        void OnSteamInputDeviceDisconnected(AZ::u64 inputHandle) override { Call(FN_OnSteamInputDeviceDisconnected, inputHandle); }
        void OnSteamInputConfigurationLoaded(SteamAppId appId, AZ::u64 deviceHandle) override { Call(FN_OnSteamInputConfigurationLoaded, appId, deviceHandle); }
        void OnSteamInputGamepadSlotChange(SteamAppId appId, AZ::s32 slotIndex, AZ::s32 deviceType, AZ::u64 deviceHandle) override { Call(FN_OnSteamInputGamepadSlotChange, appId, slotIndex, deviceType, deviceHandle); }
    };

    class BehaviorSteamScreenshotsNotificationHandler
        : public SteamScreenshotsNotificationBus::Handler
        , public AZ::BehaviorEBusHandler
    {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(BehaviorSteamScreenshotsNotificationHandler,
            "{F1A2B3C4-D5E6-41F8-A9B0-C1D2E3F4A5B6}", AZ::SystemAllocator,
            OnScreenshotRequested, OnScreenshotReady);

        void OnScreenshotRequested() override { Call(FN_OnScreenshotRequested); }
        void OnScreenshotReady(AZ::u32 screenshotHandle, SteamResult result) override { Call(FN_OnScreenshotReady, screenshotHandle, result); }
    };

    class BehaviorSteamRemotePlayNotificationHandler
        : public SteamRemotePlayNotificationBus::Handler
        , public AZ::BehaviorEBusHandler
    {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(BehaviorSteamRemotePlayNotificationHandler,
            "{A2B3C4D5-E6F7-42A9-B0C1-D2E3F4A5B6C7}", AZ::SystemAllocator,
            OnRemotePlaySessionConnected, OnRemotePlaySessionDisconnected);

        void OnRemotePlaySessionConnected(AZ::u32 sessionId) override { Call(FN_OnRemotePlaySessionConnected, sessionId); }
        void OnRemotePlaySessionDisconnected(AZ::u32 sessionId) override { Call(FN_OnRemotePlaySessionDisconnected, sessionId); }
    };

    class BehaviorSteamGameServerNotificationHandler
        : public SteamGameServerNotificationBus::Handler
        , public AZ::BehaviorEBusHandler
    {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(BehaviorSteamGameServerNotificationHandler,
            "{B3C4D5E6-F7A8-4B9C-D0E1-F2A3B4C5D6E7}", AZ::SystemAllocator,
            OnGSClientApprove, OnGSClientDeny, OnGSPolicyResponse,
            OnGSValidateAuthTicketResponse, OnGSClientGroupStatus,
            OnAssociateWithClanResult, OnComputeNewPlayerCompatibilityResult,
            OnServerReputation);

        void OnGSClientApprove(SteamId steamId, SteamId ownerSteamId) override { Call(FN_OnGSClientApprove, steamId, ownerSteamId); }
        void OnGSClientDeny(SteamId steamId, AZ::s32 denyReason, const AZStd::string& optionalText) override { Call(FN_OnGSClientDeny, steamId, denyReason, optionalText); }
        void OnGSPolicyResponse(bool secure) override { Call(FN_OnGSPolicyResponse, secure); }
        void OnGSValidateAuthTicketResponse(SteamId steamId, AZ::s32 authSessionResponse, SteamId ownerSteamId) override { Call(FN_OnGSValidateAuthTicketResponse, steamId, authSessionResponse, ownerSteamId); }
        void OnGSClientGroupStatus(SteamId userId, SteamId groupId, bool member, bool officer) override { Call(FN_OnGSClientGroupStatus, userId, groupId, member, officer); }
        void OnAssociateWithClanResult(SteamCallHandle callHandle, SteamResult result) override { Call(FN_OnAssociateWithClanResult, callHandle, result); }
        void OnComputeNewPlayerCompatibilityResult(SteamCallHandle callHandle, SteamResult result, AZ::s32 playersThatDontLikeCandidate, AZ::s32 playersThatCandidateDoesntLike, AZ::s32 clanPlayersThatDontLikeCandidate, SteamId candidateSteamId) override { Call(FN_OnComputeNewPlayerCompatibilityResult, callHandle, result, playersThatDontLikeCandidate, playersThatCandidateDoesntLike, clanPlayersThatDontLikeCandidate, candidateSteamId); }
        void OnServerReputation(SteamCallHandle callHandle, SteamResult result, AZ::u32 reputationScore, bool banned, AZ::u32 bannedIp, AZ::u16 bannedPort, AZ::u64 bannedGameId, AZ::u32 banExpires) override { Call(FN_OnServerReputation, callHandle, result, reputationScore, banned, bannedIp, bannedPort, bannedGameId, banExpires); }
    };

    class BehaviorSteamGameServerStatsNotificationHandler
        : public SteamGameServerStatsNotificationBus::Handler
        , public AZ::BehaviorEBusHandler
    {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(BehaviorSteamGameServerStatsNotificationHandler,
            "{C4D5E6F7-A8B9-4C0D-E1F2-A3B4C5D6E7F8}", AZ::SystemAllocator,
            OnGSStatsReceived, OnGSStatsStored);

        void OnGSStatsReceived(SteamCallHandle callHandle, SteamResult result, SteamId steamId) override { Call(FN_OnGSStatsReceived, callHandle, result, steamId); }
        void OnGSStatsStored(SteamCallHandle callHandle, SteamResult result, SteamId steamId) override { Call(FN_OnGSStatsStored, callHandle, result, steamId); }
    };

    class BehaviorSteamTimelineNotificationHandler
        : public SteamTimelineNotificationBus::Handler
        , public AZ::BehaviorEBusHandler
    {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(BehaviorSteamTimelineNotificationHandler,
            "{D5E6F7A8-B9C0-4D1E-2F3A-B4C5D6E7F8A9}", AZ::SystemAllocator,
            OnTimelineEventRecordingExists, OnTimelineGamePhaseRecordingExists);

        void OnTimelineEventRecordingExists(SteamCallHandle callHandle, SteamTimelineEventHandle eventHandle, bool recordingExists) override
        {
            Call(FN_OnTimelineEventRecordingExists, callHandle, eventHandle, recordingExists);
        }

        void OnTimelineGamePhaseRecordingExists(SteamCallHandle callHandle, const AZStd::string& phaseId, AZ::u64 recordingMs, AZ::u64 longestClipMs, AZ::u32 clipCount, AZ::u32 screenshotCount) override
        {
            Call(FN_OnTimelineGamePhaseRecordingExists, callHandle, phaseId, recordingMs, longestClipMs, clipCount, screenshotCount);
        }
    };
} // namespace FoundationSteamworks
