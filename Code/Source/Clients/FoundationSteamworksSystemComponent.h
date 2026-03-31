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

#include <AzCore/Component/Component.h>
#include <AzCore/Component/TickBus.h>
#include <AzCore/std/containers/unordered_map.h>
#include <AzCore/std/containers/vector.h>
#include <AzCore/std/smart_ptr/unique_ptr.h>

#include <FoundationSteamworks/FoundationSteamworksBus.h>
#include <FoundationSteamworks/SteamUserRequestBus.h>
#include <FoundationSteamworks/SteamAppsRequestBus.h>
#include <FoundationSteamworks/SteamFriendsRequestBus.h>
#include <FoundationSteamworks/SteamMatchmakingRequestBus.h>
#include <FoundationSteamworks/SteamUserStatsRequestBus.h>
#include <FoundationSteamworks/SteamRemoteStorageRequestBus.h>
#include <FoundationSteamworks/SteamInventoryRequestBus.h>
#include <FoundationSteamworks/SteamUGCRequestBus.h>
#include <FoundationSteamworks/SteamUtilsRequestBus.h>
#include <FoundationSteamworks/SteamScreenshotsRequestBus.h>
#include <FoundationSteamworks/SteamRemotePlayRequestBus.h>
#include <FoundationSteamworks/SteamInputRequestBus.h>
#include <FoundationSteamworks/SteamGameServerRequestBus.h>
#include <FoundationSteamworks/SteamGameServerStatsRequestBus.h>
#include <FoundationSteamworks/SteamTimelineRequestBus.h>

namespace FoundationSteamworks
{
    /// System component for FoundationSteamworks.
    ///
    /// Responsibilities:
    ///   - Initialise and shut down the Steamworks API.
    ///   - Pump SteamAPI_RunCallbacks() each tick via AZ::TickBus.
    ///   - Register STEAM_CALLBACK handlers and forward each event to the
    ///     corresponding O3DE notification bus.
    ///   - Own CCallResult<> instances for in-flight async operations and
    ///     broadcast results on the notification buses when they arrive.
    ///   - Handle all request bus calls, invoking the Steam API and returning
    ///     O3DE-normalised results.
    ///
    /// Public headers (Include/) never include steam_api.h.
    /// All Steam types are converted to O3DE types at this boundary.
    class FoundationSteamworksSystemComponent
        : public AZ::Component
        , protected FoundationSteamworksRequestBus::Handler
        , protected Heathen::SteamUserRequestBus::Handler
        , protected Heathen::SteamAppsRequestBus::Handler
        , protected Heathen::SteamFriendsRequestBus::Handler
        , protected Heathen::SteamMatchmakingRequestBus::Handler
        , protected Heathen::SteamUserStatsRequestBus::Handler
        , protected Heathen::SteamRemoteStorageRequestBus::Handler
        , protected Heathen::SteamInventoryRequestBus::Handler
        , protected Heathen::SteamUGCRequestBus::Handler
        , protected Heathen::SteamUtilsRequestBus::Handler
        , protected Heathen::SteamScreenshotsRequestBus::Handler
        , protected Heathen::SteamRemotePlayRequestBus::Handler
        , protected Heathen::SteamInputRequestBus::Handler
        , protected Heathen::SteamGameServerRequestBus::Handler
        , protected Heathen::SteamGameServerStatsRequestBus::Handler
        , protected Heathen::SteamTimelineRequestBus::Handler
        , public AZ::TickBus::Handler
    {
    public:
        AZ_COMPONENT_DECL(FoundationSteamworksSystemComponent);

        static void Reflect(AZ::ReflectContext* context);

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        FoundationSteamworksSystemComponent();
        ~FoundationSteamworksSystemComponent();

    protected:
        // AZ::Component
        void Init() override;
        void Activate() override;
        void Deactivate() override;

        // AZ::TickBus
        void OnTick(float deltaTime, AZ::ScriptTimePoint time) override;

        // ------------------------------------------------------------------
        // SteamUserRequestBus
        // ------------------------------------------------------------------
        bool IsLoggedOn() override;
        Heathen::SteamId GetSteamID() override;
        AZ::s32 GetPlayerSteamLevel() override;
        AZ::s32 GetGameBadgeLevel(AZ::s32 series, bool foil) override;
        Heathen::SteamAuthTicketHandle GetAuthTicketForWebApi(const AZStd::string& identity) override;
        void CancelAuthTicket(Heathen::SteamAuthTicketHandle handle) override;
        Heathen::SteamCallHandle RequestStoreAuthURL(const AZStd::string& redirectURL) override;
        Heathen::SteamCallHandle GetMarketEligibility() override;
        Heathen::SteamCallHandle GetDurationControl() override;
        Heathen::SteamCallHandle RequestEncryptedAppTicket(const AZStd::vector<AZ::u8>& dataToInclude) override;

        // ------------------------------------------------------------------
        // SteamAppsRequestBus
        // ------------------------------------------------------------------
        bool IsSubscribed() override;
        bool IsSubscribedFromFreeWeekend() override;
        bool IsSubscribedFromFamilySharing() override;
        bool IsSubscribedApp(Heathen::SteamAppId appId) override;
        bool IsDlcInstalled(Heathen::SteamAppId appId) override;
        AZ::u32 GetEarliestPurchaseUnixTime(Heathen::SteamAppId appId) override;
        bool IsLowViolence() override;
        bool IsCybercafe() override;
        bool IsVACBanned() override;
        AZStd::string GetCurrentGameLanguage() override;
        AZStd::string GetAvailableGameLanguages() override;
        Heathen::SteamAppId GetAppID() override;
        AZ::s32 GetDLCCount() override;
        void InstallDLC(Heathen::SteamAppId appId) override;
        void UninstallDLC(Heathen::SteamAppId appId) override;
        AZStd::string GetCurrentBetaName() override;
        AZ::s32 GetAppBuildId() override;
        bool MarkContentCorrupt(bool missingFilesOnly) override;
        Heathen::SteamCallHandle GetFileDetails(const AZStd::string& fileName) override;

        // ------------------------------------------------------------------
        // SteamFriendsRequestBus
        // ------------------------------------------------------------------
        AZStd::string GetPersonaName() override;
        Heathen::SteamPersonaState GetPersonaState() override;
        AZ::s32 GetFriendCount(AZ::s32 friendFlags) override;
        Heathen::SteamId GetFriendByIndex(AZ::s32 index, AZ::s32 friendFlags) override;
        AZ::s32 GetFriendRelationship(Heathen::SteamId steamId) override;
        Heathen::SteamPersonaState GetFriendPersonaState(Heathen::SteamId steamId) override;
        AZStd::string GetFriendPersonaName(Heathen::SteamId steamId) override;
        AZ::s32 GetFriendSteamLevel(Heathen::SteamId steamId) override;
        AZStd::string GetPlayerNickname(Heathen::SteamId steamId) override;
        bool HasFriend(Heathen::SteamId steamId, AZ::s32 friendFlags) override;
        AZ::s32 GetSmallFriendAvatar(Heathen::SteamId steamId) override;
        AZ::s32 GetMediumFriendAvatar(Heathen::SteamId steamId) override;
        AZ::s32 GetLargeFriendAvatar(Heathen::SteamId steamId) override;
        bool RequestUserInformation(Heathen::SteamId steamId, bool requireNameOnly) override;
        bool SetRichPresence(const AZStd::string& key, const AZStd::string& value) override;
        void ClearRichPresence() override;
        AZStd::string GetFriendRichPresence(Heathen::SteamId steamId, const AZStd::string& key) override;
        AZ::s32 GetFriendRichPresenceKeyCount(Heathen::SteamId steamId) override;
        AZStd::string GetFriendRichPresenceKeyByIndex(Heathen::SteamId steamId, AZ::s32 index) override;
        void RequestFriendRichPresence(Heathen::SteamId steamId) override;
        void ActivateGameOverlay(const AZStd::string& dialog) override;
        void ActivateGameOverlayToUser(const AZStd::string& dialog, Heathen::SteamId steamId) override;
        void ActivateGameOverlayToWebPage(const AZStd::string& url, Heathen::SteamOverlayToWebPageMode mode) override;
        void ActivateGameOverlayToStore(Heathen::SteamAppId appId, Heathen::SteamOverlayToStoreFlag flag) override;
        void ActivateGameOverlayInviteDialog(Heathen::SteamId lobbyId) override;
        void SetPlayedWith(Heathen::SteamId steamId) override;
        Heathen::SteamId GetClanByIndex(AZ::s32 index) override;
        AZ::s32 GetClanCount() override;
        AZStd::string GetClanName(Heathen::SteamId clanId) override;
        AZStd::string GetClanTag(Heathen::SteamId clanId) override;
        Heathen::SteamCallHandle RequestClanOfficerList(Heathen::SteamId clanId) override;
        Heathen::SteamCallHandle GetFollowerCount(Heathen::SteamId steamId) override;
        Heathen::SteamCallHandle IsFollowing(Heathen::SteamId steamId) override;
        Heathen::SteamCallHandle EnumerateFollowingList(AZ::u32 startIndex) override;

        // ------------------------------------------------------------------
        // SteamMatchmakingRequestBus
        // ------------------------------------------------------------------
        AZ::s32 GetNumLobbyMembers(Heathen::SteamId lobbyId) override;
        Heathen::SteamId GetLobbyMemberByIndex(Heathen::SteamId lobbyId, AZ::s32 index) override;
        AZStd::string GetLobbyData(Heathen::SteamId lobbyId, const AZStd::string& key) override;
        bool SetLobbyData(Heathen::SteamId lobbyId, const AZStd::string& key, const AZStd::string& value) override;
        bool DeleteLobbyData(Heathen::SteamId lobbyId, const AZStd::string& key) override;
        AZStd::string GetLobbyMemberData(Heathen::SteamId lobbyId, Heathen::SteamId memberId, const AZStd::string& key) override;
        void SetLobbyMemberData(Heathen::SteamId lobbyId, const AZStd::string& key, const AZStd::string& value) override;
        Heathen::SteamId GetLobbyOwner(Heathen::SteamId lobbyId) override;
        bool SetLobbyOwner(Heathen::SteamId lobbyId, Heathen::SteamId newOwnerId) override;
        bool RequestLobbyData(Heathen::SteamId lobbyId) override;
        bool SetLobbyJoinable(Heathen::SteamId lobbyId, bool joinable) override;
        bool SetLobbyMemberLimit(Heathen::SteamId lobbyId, AZ::s32 maxMembers) override;
        AZ::s32 GetLobbyMemberLimit(Heathen::SteamId lobbyId) override;
        bool InviteUserToLobby(Heathen::SteamId lobbyId, Heathen::SteamId inviteeId) override;
        void LeaveLobby(Heathen::SteamId lobbyId) override;
        void AddRequestLobbyListStringFilter(const AZStd::string& key, const AZStd::string& value, Heathen::SteamLobbyComparison comparison) override;
        void AddRequestLobbyListNumericalFilter(const AZStd::string& key, AZ::s32 value, Heathen::SteamLobbyComparison comparison) override;
        void AddRequestLobbyListNearValueFilter(const AZStd::string& key, AZ::s32 valueToBeCloseTo) override;
        void AddRequestLobbyListFilterSlotsAvailable(AZ::s32 slotsAvailable) override;
        void AddRequestLobbyListDistanceFilter(Heathen::SteamLobbyDistanceFilter distanceFilter) override;
        void AddRequestLobbyListResultCountFilter(AZ::s32 maxResults) override;
        Heathen::SteamCallHandle CreateLobby(Heathen::SteamLobbyType lobbyType, AZ::s32 maxMembers) override;
        Heathen::SteamCallHandle JoinLobby(Heathen::SteamId lobbyId) override;
        Heathen::SteamCallHandle RequestLobbyList() override;

        // ------------------------------------------------------------------
        // SteamUserStatsRequestBus
        // ------------------------------------------------------------------
        bool RequestCurrentStats() override;
        bool StoreStats() override;
        bool GetStatInt(const AZStd::string& name, AZ::s32& outValue) override;
        bool GetStatFloat(const AZStd::string& name, float& outValue) override;
        bool SetStatInt(const AZStd::string& name, AZ::s32 value) override;
        bool SetStatFloat(const AZStd::string& name, float value) override;
        bool UpdateAvgRateStat(const AZStd::string& name, float countThisSession, double sessionLength) override;
        bool GetAchievement(const AZStd::string& name, bool& outAchieved) override;
        bool SetAchievement(const AZStd::string& name) override;
        bool ClearAchievement(const AZStd::string& name) override;
        bool GetAchievementAndUnlockTime(const AZStd::string& name, bool& outAchieved, AZ::u32& outUnlockTime) override;
        bool IndicateAchievementProgress(const AZStd::string& name, AZ::u32 curProgress, AZ::u32 maxProgress) override;
        bool ResetAllStats(bool achievementsToo) override;
        AZ::u32 GetNumAchievements() override;
        AZStd::string GetAchievementName(AZ::u32 index) override;
        AZStd::string GetAchievementDisplayAttribute(const AZStd::string& name, const AZStd::string& key) override;
        AZ::s32 GetAchievementIcon(const AZStd::string& name) override;
        bool GetUserStatInt(Heathen::SteamId userId, const AZStd::string& name, AZ::s32& outValue) override;
        bool GetUserStatFloat(Heathen::SteamId userId, const AZStd::string& name, float& outValue) override;
        bool GetUserAchievement(Heathen::SteamId userId, const AZStd::string& name, bool& outAchieved) override;
        bool GetUserAchievementAndUnlockTime(Heathen::SteamId userId, const AZStd::string& name, bool& outAchieved, AZ::u32& outUnlockTime) override;
        AZStd::string GetLeaderboardName(Heathen::SteamLeaderboardHandle leaderboard) override;
        AZ::s32 GetLeaderboardEntryCount(Heathen::SteamLeaderboardHandle leaderboard) override;
        Heathen::SteamLeaderboardSortMethod GetLeaderboardSortMethod(Heathen::SteamLeaderboardHandle leaderboard) override;
        Heathen::SteamLeaderboardDisplayType GetLeaderboardDisplayType(Heathen::SteamLeaderboardHandle leaderboard) override;
        Heathen::SteamCallHandle RequestUserStats(Heathen::SteamId userId) override;
        Heathen::SteamCallHandle FindOrCreateLeaderboard(const AZStd::string& name, Heathen::SteamLeaderboardSortMethod sortMethod, Heathen::SteamLeaderboardDisplayType displayType) override;
        Heathen::SteamCallHandle FindLeaderboard(const AZStd::string& name) override;
        Heathen::SteamCallHandle DownloadLeaderboardEntries(Heathen::SteamLeaderboardHandle leaderboard, Heathen::SteamLeaderboardDataRequest dataRequest, AZ::s32 rangeStart, AZ::s32 rangeEnd) override;
        Heathen::SteamCallHandle UploadLeaderboardScore(Heathen::SteamLeaderboardHandle leaderboard, Heathen::SteamLeaderboardUploadScoreMethod method, AZ::s32 score) override;
        Heathen::SteamCallHandle GetNumberOfCurrentPlayers() override;
        Heathen::SteamCallHandle RequestGlobalAchievementPercentages() override;
        Heathen::SteamCallHandle RequestGlobalStats(AZ::s32 historyDays) override;

        // ------------------------------------------------------------------
        // SteamRemoteStorageRequestBus
        // ------------------------------------------------------------------
        bool FileWrite(const AZStd::string& fileName, const AZStd::vector<AZ::u8>& data) override;
        bool FileRead(const AZStd::string& fileName, AZStd::vector<AZ::u8>& outData) override;
        bool FileExists(const AZStd::string& fileName) override;
        bool FilePersisted(const AZStd::string& fileName) override;
        AZ::s32 GetFileSize(const AZStd::string& fileName) override;
        AZ::s64 GetFileTimestamp(const AZStd::string& fileName) override;
        bool FileForget(const AZStd::string& fileName) override;
        bool FileDelete(const AZStd::string& fileName) override;
        AZ::s32 GetFileCount() override;
        AZStd::string GetFileNameAndSize(AZ::s32 index, AZ::s32& outSize) override;
        bool GetQuota(AZ::u64& outTotalBytes, AZ::u64& outAvailableBytes) override;
        bool IsCloudEnabledForAccount() override;
        bool IsCloudEnabledForApp() override;
        void SetCloudEnabledForApp(bool enabled) override;
        Heathen::SteamCallHandle FileShare(const AZStd::string& fileName) override;
        Heathen::SteamCallHandle FileWriteAsync(const AZStd::string& fileName, const AZStd::vector<AZ::u8>& data) override;
        Heathen::SteamCallHandle FileReadAsync(const AZStd::string& fileName, AZ::u32 offset, AZ::u32 bytesToRead) override;
        Heathen::SteamCallHandle SubscribePublishedFile(Heathen::SteamPublishedFileId publishedFileId) override;
        Heathen::SteamCallHandle UnsubscribePublishedFile(Heathen::SteamPublishedFileId publishedFileId) override;

        // ------------------------------------------------------------------
        // SteamInventoryRequestBus
        // ------------------------------------------------------------------
        void DestroyResult(Heathen::SteamInventoryResultHandle resultHandle) override;
        Heathen::SteamResult GetResultStatus(Heathen::SteamInventoryResultHandle resultHandle) override;
        AZ::u32 GetResultTimestamp(Heathen::SteamInventoryResultHandle resultHandle) override;
        Heathen::SteamInventoryResultHandle GetAllItems() override;
        Heathen::SteamInventoryResultHandle GetItemsByID(const AZStd::vector<Heathen::SteamItemInstanceId>& instanceIds) override;
        Heathen::SteamInventoryResultHandle AddPromoItem(Heathen::SteamItemDefId itemDefId) override;
        Heathen::SteamInventoryResultHandle AddPromoItems(const AZStd::vector<Heathen::SteamItemDefId>& itemDefIds) override;
        Heathen::SteamInventoryResultHandle ConsumeItem(Heathen::SteamItemInstanceId instanceId, AZ::u32 quantity) override;
        Heathen::SteamInventoryResultHandle TransferItemQuantity(Heathen::SteamItemInstanceId sourceId, AZ::u32 quantity, Heathen::SteamItemInstanceId destId) override;
        Heathen::SteamInventoryResultHandle GetAllItemsServer() override;
        AZ::u32 GetNumItemDefinitions() override;
        AZStd::string GetItemDefinitionProperty(Heathen::SteamItemDefId defId, const AZStd::string& propertyName) override;
        bool LoadItemDefinitions() override;
        Heathen::SteamCallHandle StartPurchase(const AZStd::vector<Heathen::SteamItemDefId>& itemDefIds, const AZStd::vector<AZ::u32>& quantities) override;
        Heathen::SteamCallHandle RequestPrices() override;

        // ------------------------------------------------------------------
        // SteamUGCRequestBus
        // ------------------------------------------------------------------
        AZ::u32 GetItemState(Heathen::SteamPublishedFileId publishedFileId) override;
        bool GetItemDownloadInfo(Heathen::SteamPublishedFileId publishedFileId, AZ::u64& outBytesDownloaded, AZ::u64& outBytesTotal) override;
        bool GetItemInstallInfo(Heathen::SteamPublishedFileId publishedFileId, AZ::u64& outSizeOnDisk, AZStd::string& outFolder, AZ::u32& outTimestamp) override;
        AZ::u32 GetNumSubscribedItems() override;
        AZ::u32 GetSubscribedItems(AZStd::vector<Heathen::SteamPublishedFileId>& outIds, AZ::u32 maxEntries) override;
        Heathen::SteamUGCQueryHandle CreateQueryAllUGCRequest(AZ::s32 queryType, AZ::s32 matchingFileType, Heathen::SteamAppId creatorAppId, Heathen::SteamAppId consumerAppId, AZ::u32 page) override;
        Heathen::SteamUGCQueryHandle CreateQueryUserUGCRequest(Heathen::SteamId accountId, AZ::s32 listType, AZ::s32 matchingFileType, AZ::s32 sortOrder, Heathen::SteamAppId creatorAppId, Heathen::SteamAppId consumerAppId, AZ::u32 page) override;
        Heathen::SteamUGCQueryHandle CreateQueryUGCDetailsRequest(const AZStd::vector<Heathen::SteamPublishedFileId>& publishedFileIds) override;
        bool AddRequiredTag(Heathen::SteamUGCQueryHandle queryHandle, const AZStd::string& tagName) override;
        bool AddExcludedTag(Heathen::SteamUGCQueryHandle queryHandle, const AZStd::string& tagName) override;
        bool SetMatchAnyTag(Heathen::SteamUGCQueryHandle queryHandle, bool matchAnyTag) override;
        bool AddRequiredKeyValueTag(Heathen::SteamUGCQueryHandle queryHandle, const AZStd::string& key, const AZStd::string& value) override;
        bool SetReturnLongDescription(Heathen::SteamUGCQueryHandle queryHandle, bool returnLongDescription) override;
        bool SetReturnMetadata(Heathen::SteamUGCQueryHandle queryHandle, bool returnMetadata) override;
        bool SetReturnChildren(Heathen::SteamUGCQueryHandle queryHandle, bool returnChildren) override;
        bool SetReturnAdditionalPreviews(Heathen::SteamUGCQueryHandle queryHandle, bool returnAdditionalPreviews) override;
        bool SetReturnTotalOnly(Heathen::SteamUGCQueryHandle queryHandle, bool returnTotalOnly) override;
        bool SetLanguage(Heathen::SteamUGCQueryHandle queryHandle, const AZStd::string& language) override;
        bool SetAllowCachedResponse(Heathen::SteamUGCQueryHandle queryHandle, AZ::u32 maxAgeSeconds) override;
        void ReleaseQueryUGCRequest(Heathen::SteamUGCQueryHandle queryHandle) override;
        Heathen::SteamUGCUpdateHandle StartItemUpdate(Heathen::SteamAppId consumerAppId, Heathen::SteamPublishedFileId publishedFileId) override;
        bool SetItemTitle(Heathen::SteamUGCUpdateHandle updateHandle, const AZStd::string& title) override;
        bool SetItemDescription(Heathen::SteamUGCUpdateHandle updateHandle, const AZStd::string& description) override;
        bool SetItemMetadata(Heathen::SteamUGCUpdateHandle updateHandle, const AZStd::string& metaData) override;
        bool SetItemVisibility(Heathen::SteamUGCUpdateHandle updateHandle, Heathen::SteamUGCVisibility visibility) override;
        bool SetItemTags(Heathen::SteamUGCUpdateHandle updateHandle, const AZStd::vector<AZStd::string>& tags) override;
        bool SetItemContent(Heathen::SteamUGCUpdateHandle updateHandle, const AZStd::string& contentFolder) override;
        bool SetItemPreview(Heathen::SteamUGCUpdateHandle updateHandle, const AZStd::string& previewFile) override;
        bool DownloadItem(Heathen::SteamPublishedFileId publishedFileId, bool highPriority) override;
        Heathen::SteamCallHandle SendQueryUGCRequest(Heathen::SteamUGCQueryHandle queryHandle) override;
        Heathen::SteamCallHandle RequestUGCDetails(Heathen::SteamPublishedFileId publishedFileId, AZ::u32 maxAgeSeconds) override;
        Heathen::SteamCallHandle CreateItem(Heathen::SteamAppId consumerAppId, AZ::s32 fileType) override;
        Heathen::SteamCallHandle SubmitItemUpdate(Heathen::SteamUGCUpdateHandle updateHandle, const AZStd::string& changeNote) override;
        Heathen::SteamCallHandle AddItemToFavorites(Heathen::SteamAppId appId, Heathen::SteamPublishedFileId publishedFileId) override;
        Heathen::SteamCallHandle RemoveItemFromFavorites(Heathen::SteamAppId appId, Heathen::SteamPublishedFileId publishedFileId) override;
        Heathen::SteamCallHandle SetUserItemVote(Heathen::SteamPublishedFileId publishedFileId, bool voteUp) override;
        Heathen::SteamCallHandle GetUserItemVote(Heathen::SteamPublishedFileId publishedFileId) override;
        Heathen::SteamCallHandle StartPlaytimeTracking(const AZStd::vector<Heathen::SteamPublishedFileId>& publishedFileIds) override;
        Heathen::SteamCallHandle StopPlaytimeTracking(const AZStd::vector<Heathen::SteamPublishedFileId>& publishedFileIds) override;
        Heathen::SteamCallHandle StopPlaytimeTrackingForAllItems() override;
        Heathen::SteamCallHandle AddDependency(Heathen::SteamPublishedFileId parentId, Heathen::SteamPublishedFileId childId) override;
        Heathen::SteamCallHandle RemoveDependency(Heathen::SteamPublishedFileId parentId, Heathen::SteamPublishedFileId childId) override;
        Heathen::SteamCallHandle DeleteItem(Heathen::SteamPublishedFileId publishedFileId) override;
        Heathen::SteamCallHandle GetWorkshopEULAStatus() override;

        // ------------------------------------------------------------------
        // SteamUtilsRequestBus
        // ------------------------------------------------------------------
        AZ::u32 GetServerRealTime() override;
        AZStd::string GetIPCountry() override;
        AZStd::string GetSteamUILanguage() override;
        bool GetImageSize(AZ::s32 imageHandle, AZ::u32& outWidth, AZ::u32& outHeight) override;
        bool GetImageRGBA(AZ::s32 imageHandle, AZStd::vector<AZ::u8>& outData, AZ::u32 width, AZ::u32 height) override;
        bool IsOverlayEnabled() override;
        bool IsSteamInBigPictureMode() override;
        bool IsSteamRunningOnSteamDeck() override;
        bool IsSteamRunningInVR() override;
        bool ShowFloatingGamepadTextInput(AZ::s32 inputMode, AZ::s32 x, AZ::s32 y, AZ::s32 width, AZ::s32 height) override;
        bool DismissFloatingGamepadTextInput() override;
        bool FilterText(AZ::s32 context, Heathen::SteamId sourceSteamId, const AZStd::string& inputMessage, AZStd::string& outFiltered) override;
        AZ::u8 GetCurrentBatteryPower() override;
        bool IsSteamChinaLauncher() override;

        // ------------------------------------------------------------------
        // SteamScreenshotsRequestBus
        // ------------------------------------------------------------------
        void TriggerScreenshot() override;
        AZ::u32 WriteScreenshot(const AZStd::vector<AZ::u8>& data, AZ::u32 width, AZ::u32 height) override;
        AZ::u32 AddScreenshotToLibrary(const AZStd::string& fileName, const AZStd::string& thumbnailFileName, AZ::u32 width, AZ::u32 height) override;
        bool SetScreenshotCaption(AZ::u32 screenshotHandle, const AZStd::string& caption) override;
        bool TagUser(AZ::u32 screenshotHandle, Heathen::SteamId userId) override;
        bool TagPublishedFile(AZ::u32 screenshotHandle, Heathen::SteamPublishedFileId publishedFileId) override;
        bool IsScreenshotsHooked() override;
        void HookScreenshots(bool hook) override;

        // ------------------------------------------------------------------
        // SteamRemotePlayRequestBus
        // ------------------------------------------------------------------
        AZ::u32 GetSessionCount() override;
        AZ::u32 GetSessionID(AZ::u32 index) override;
        Heathen::SteamId GetSessionSteamID(AZ::u32 sessionId) override;
        AZStd::string GetSessionClientName(AZ::u32 sessionId) override;
        AZ::s32 GetSessionClientFormFactor(AZ::u32 sessionId) override;
        bool GetSessionClientResolution(AZ::u32 sessionId, AZ::s32& outWidth, AZ::s32& outHeight) override;
        bool SendRemotePlayTogetherInvite(Heathen::SteamId friendId) override;

        // ------------------------------------------------------------------
        // SteamInputRequestBus
        // ------------------------------------------------------------------
        AZStd::vector<AZ::u64> GetConnectedControllers() override;
        void EnableDeviceCallbacks() override;
        AZ::u64 GetActionSetHandle(const AZStd::string& actionSetName) override;
        void ActivateActionSet(AZ::u64 inputHandle, AZ::u64 actionSetHandle) override;
        AZ::u64 GetCurrentActionSet(AZ::u64 inputHandle) override;
        void ActivateActionSetLayer(AZ::u64 inputHandle, AZ::u64 actionSetLayerHandle) override;
        void DeactivateActionSetLayer(AZ::u64 inputHandle, AZ::u64 actionSetLayerHandle) override;
        void DeactivateAllActionSetLayers(AZ::u64 inputHandle) override;
        AZStd::vector<AZ::u64> GetActiveActionSetLayers(AZ::u64 inputHandle) override;
        AZ::u64 GetDigitalActionHandle(const AZStd::string& actionName) override;
        Heathen::SteamInputDigitalActionData GetDigitalActionData(AZ::u64 inputHandle, AZ::u64 digitalActionHandle) override;
        AZStd::string GetStringForDigitalActionName(AZ::u64 actionHandle) override;
        AZ::u64 GetAnalogActionHandle(const AZStd::string& actionName) override;
        Heathen::SteamInputAnalogActionData GetAnalogActionData(AZ::u64 inputHandle, AZ::u64 analogActionHandle) override;
        AZStd::string GetStringForAnalogActionName(AZ::u64 actionHandle) override;
        void TriggerVibration(AZ::u64 inputHandle, AZ::u16 leftSpeed, AZ::u16 rightSpeed) override;
        void TriggerVibrationExtended(AZ::u64 inputHandle, AZ::u16 leftSpeed, AZ::u16 rightSpeed, AZ::u16 leftTriggerSpeed, AZ::u16 rightTriggerSpeed) override;
        void SetLEDColor(AZ::u64 inputHandle, AZ::u8 r, AZ::u8 g, AZ::u8 b, AZ::u32 flags) override;
        bool ShowBindingPanel(AZ::u64 inputHandle) override;
        AZ::s32 GetInputTypeForHandle(AZ::u64 inputHandle) override;
        AZ::u64 GetControllerForGamepadIndex(AZ::s32 index) override;
        AZ::s32 GetGamepadIndexForController(AZ::u64 inputHandle) override;
        AZ::u32 GetRemotePlaySessionID(AZ::u64 inputHandle) override;

        // ------------------------------------------------------------------
        // SteamGameServerRequestBus
        // ------------------------------------------------------------------
        void SetProduct(const AZStd::string& product) override;
        void SetGameDescription(const AZStd::string& description) override;
        void SetModDir(const AZStd::string& modDir) override;
        void SetDedicatedServer(bool dedicated) override;
        void LogOn(const AZStd::string& token) override;
        void LogOnAnonymous() override;
        void LogOff() override;
        bool GSIsLoggedOn() override;
        bool GSIsSecure() override;
        Heathen::SteamId GSGetSteamID() override;
        bool WasRestartRequested() override;
        void SetMaxPlayerCount(AZ::s32 maxPlayers) override;
        void SetBotPlayerCount(AZ::s32 botPlayers) override;
        void SetServerName(const AZStd::string& serverName) override;
        void SetMapName(const AZStd::string& mapName) override;
        void SetPasswordProtected(bool passwordProtected) override;
        void SetSpectatorPort(AZ::u16 spectatorPort) override;
        void SetSpectatorServerName(const AZStd::string& spectatorServerName) override;
        void ClearAllKeyValues() override;
        void SetKeyValue(const AZStd::string& key, const AZStd::string& value) override;
        void SetGameTags(const AZStd::string& gameTags) override;
        void SetGameData(const AZStd::string& gameData) override;
        void SetRegion(const AZStd::string& region) override;
        void SetAdvertiseServerActive(bool active) override;
        AZ::s32 BeginAuthSession(const AZStd::vector<AZ::u8>& authTicket, Heathen::SteamId steamId) override;
        void EndAuthSession(Heathen::SteamId steamId) override;
        void GSCancelAuthTicket(Heathen::SteamAuthTicketHandle handle) override;
        AZ::s32 UserHasLicenseForApp(Heathen::SteamId steamId, Heathen::SteamAppId appId) override;
        bool RequestUserGroupStatus(Heathen::SteamId userId, Heathen::SteamId groupId) override;
        bool UpdateUserData(Heathen::SteamId userId, const AZStd::string& playerName, AZ::u32 score) override;
        Heathen::SteamCallHandle AssociateWithClan(Heathen::SteamId clanId) override;
        Heathen::SteamCallHandle ComputeNewPlayerCompatibility(Heathen::SteamId newPlayerId) override;
        Heathen::SteamCallHandle GetServerReputation() override;

        // ------------------------------------------------------------------
        // SteamGameServerStatsRequestBus
        // ------------------------------------------------------------------
        Heathen::SteamCallHandle GSRequestUserStats(Heathen::SteamId steamId) override;
        Heathen::SteamGSUserStatIntResult GSGetUserStatInt(Heathen::SteamId steamId, const AZStd::string& name) override;
        Heathen::SteamGSUserStatFloatResult GSGetUserStatFloat(Heathen::SteamId steamId, const AZStd::string& name) override;
        Heathen::SteamGSUserAchievementResult GSGetUserAchievement(Heathen::SteamId steamId, const AZStd::string& name) override;
        bool GSSetUserStatInt(Heathen::SteamId steamId, const AZStd::string& name, AZ::s32 value) override;
        bool GSSetUserStatFloat(Heathen::SteamId steamId, const AZStd::string& name, float value) override;
        bool GSUpdateUserAvgRateStat(Heathen::SteamId steamId, const AZStd::string& name, float countThisSession, double sessionLength) override;
        bool GSSetUserAchievement(Heathen::SteamId steamId, const AZStd::string& name) override;
        bool GSClearUserAchievement(Heathen::SteamId steamId, const AZStd::string& name) override;
        Heathen::SteamCallHandle GSStoreUserStats(Heathen::SteamId steamId) override;

        // SteamTimelineRequestBus
        void SetTimelineTooltip(const AZStd::string& description, float timeDelta) override;
        void ClearTimelineTooltip(float timeDelta) override;
        void SetTimelineGameMode(Heathen::SteamTimelineGameMode mode) override;
        Heathen::SteamTimelineEventHandle AddInstantaneousTimelineEvent(const AZStd::string& title, const AZStd::string& description, const AZStd::string& icon, AZ::u32 iconPriority, float startOffsetSeconds, Heathen::SteamTimelineClipPriority clipPriority) override;
        Heathen::SteamTimelineEventHandle AddRangeTimelineEvent(const AZStd::string& title, const AZStd::string& description, const AZStd::string& icon, AZ::u32 iconPriority, float startOffsetSeconds, float duration, Heathen::SteamTimelineClipPriority clipPriority) override;
        Heathen::SteamTimelineEventHandle StartRangeTimelineEvent(const AZStd::string& title, const AZStd::string& description, const AZStd::string& icon, AZ::u32 priority, float startOffsetSeconds, Heathen::SteamTimelineClipPriority clipPriority) override;
        void UpdateRangeTimelineEvent(Heathen::SteamTimelineEventHandle eventHandle, const AZStd::string& title, const AZStd::string& description, const AZStd::string& icon, AZ::u32 priority, Heathen::SteamTimelineClipPriority clipPriority) override;
        void EndRangeTimelineEvent(Heathen::SteamTimelineEventHandle eventHandle, float endOffsetSeconds) override;
        void RemoveTimelineEvent(Heathen::SteamTimelineEventHandle eventHandle) override;
        Heathen::SteamCallHandle DoesEventRecordingExist(Heathen::SteamTimelineEventHandle eventHandle) override;
        void StartGamePhase() override;
        void EndGamePhase() override;
        void SetGamePhaseID(const AZStd::string& phaseId) override;
        Heathen::SteamCallHandle DoesGamePhaseRecordingExist(const AZStd::string& phaseId) override;
        void AddGamePhaseTag(const AZStd::string& tagName, const AZStd::string& tagIcon, const AZStd::string& tagGroup, AZ::u32 priority) override;
        void SetGamePhaseAttribute(const AZStd::string& attributeGroup, const AZStd::string& attributeValue, AZ::u32 priority) override;
        void OpenOverlayToGamePhase(const AZStd::string& phaseId) override;
        void OpenOverlayToTimelineEvent(Heathen::SteamTimelineEventHandle eventHandle) override;

        // FoundationSteamworksRequestBus — lifecycle
        bool Initialise(AZ::u32 appId, AZStd::string& outErrorMsg) override;
        void Shutdown() override;
        bool IsInitialised() override;
        bool GameServerInitialise(AZ::u32 appId, const AZStd::string& localIP, AZ::u16 gamePort, AZ::u16 queryPort,
            Heathen::SteamServerMode serverMode, const AZStd::string& versionString, AZStd::string& outErrorMsg) override;
        void GameServerShutdown() override;
        bool IsGameServerInitialised() override;
        bool InputInitialise() override;
        void InputShutdown() override;
        bool IsInputInitialised() override;

    private:
        bool m_steamInitialised      = false;
        bool m_gameServerInitialised = false;
        bool m_inputInitialised      = false;

        // Steam callback storage — STEAM_CALLBACK_MANUAL members must live
        // inside a class body; this pimpl keeps steam_api.h out of the header.
        struct SteamCallbackRegistry;
        AZStd::unique_ptr<SteamCallbackRegistry> m_callbacks;

        // CallResult storage — defined fully in the .cpp.
        struct CallResultRegistry;
        AZStd::unique_ptr<CallResultRegistry> m_callResults;
    };

} // namespace FoundationSteamworks