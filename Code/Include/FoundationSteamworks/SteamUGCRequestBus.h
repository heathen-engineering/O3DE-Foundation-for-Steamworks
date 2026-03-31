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
    // SteamUGCRequests
    // Request bus wrapping ISteamUGC (Workshop / User Generated Content).
    // -----------------------------------------------------------------------
    class SteamUGCRequests
    {
    public:
        AZ_RTTI(SteamUGCRequests, "{B8C9DAEB-FCA0-4B1E-F345-F6A7B8C9DAEC}");
        virtual ~SteamUGCRequests() = default;

        // --- Item State ---

        /// Returns the item state flags for the given published file (bitmask of EItemState).
        virtual AZ::u32 GetItemState(SteamPublishedFileId publishedFileId) { return 0; }

        /// Returns the download progress for an item (0..1 each, or 0 if complete/not downloading).
        virtual bool GetItemDownloadInfo(SteamPublishedFileId publishedFileId, AZ::u64& outBytesDownloaded, AZ::u64& outBytesTotal) { return false; }

        /// Returns the install folder path for a downloaded item.
        virtual bool GetItemInstallInfo(SteamPublishedFileId publishedFileId, AZ::u64& outSizeOnDisk, AZStd::string& outFolder, AZ::u32& outTimestamp) { return false; }

        // --- Subscription Management ---

        /// Returns the number of items the local user is subscribed to.
        virtual AZ::u32 GetNumSubscribedItems() { return 0; }

        /// Returns up to maxEntries subscribed published file IDs.
        virtual AZ::u32 GetSubscribedItems(AZStd::vector<SteamPublishedFileId>& outIds, AZ::u32 maxEntries) { return 0; }

        // --- Query Building ---

        /// Creates a query for items from all users (AllItems, TopRated, etc.).
        /// queryType: EUGCQuery cast to s32. fileType: EUGCMatchingUGCType cast to s32.
        virtual SteamUGCQueryHandle CreateQueryAllUGCRequest(
            AZ::s32 queryType,
            AZ::s32 matchingFileType,
            SteamAppId creatorAppId,
            SteamAppId consumerAppId,
            AZ::u32 page) { return 0; }

        /// Creates a query for items published by specific users.
        virtual SteamUGCQueryHandle CreateQueryUserUGCRequest(
            SteamId accountId,
            AZ::s32 listType,
            AZ::s32 matchingFileType,
            AZ::s32 sortOrder,
            SteamAppId creatorAppId,
            SteamAppId consumerAppId,
            AZ::u32 page) { return 0; }

        /// Creates a query for specific item IDs.
        virtual SteamUGCQueryHandle CreateQueryUGCDetailsRequest(
            const AZStd::vector<SteamPublishedFileId>& publishedFileIds) { return 0; }

        // --- Query Options (call before SendQueryUGCRequest) ---

        /// Adds a required tag filter to a pending query.
        virtual bool AddRequiredTag(SteamUGCQueryHandle queryHandle, const AZStd::string& tagName) { return false; }

        /// Adds an excluded tag filter to a pending query.
        virtual bool AddExcludedTag(SteamUGCQueryHandle queryHandle, const AZStd::string& tagName) { return false; }

        /// Sets whether to return only items that match ALL required tags (true) or ANY (false).
        virtual bool SetMatchAnyTag(SteamUGCQueryHandle queryHandle, bool matchAnyTag) { return false; }

        /// Sets a key/value filter on a pending query.
        virtual bool AddRequiredKeyValueTag(SteamUGCQueryHandle queryHandle, const AZStd::string& key, const AZStd::string& value) { return false; }

        /// Requests additional long-description text in query results.
        virtual bool SetReturnLongDescription(SteamUGCQueryHandle queryHandle, bool returnLongDescription) { return false; }

        /// Requests metadata in query results.
        virtual bool SetReturnMetadata(SteamUGCQueryHandle queryHandle, bool returnMetadata) { return false; }

        /// Requests children (dependencies) in query results.
        virtual bool SetReturnChildren(SteamUGCQueryHandle queryHandle, bool returnChildren) { return false; }

        /// Requests additional previews in query results.
        virtual bool SetReturnAdditionalPreviews(SteamUGCQueryHandle queryHandle, bool returnAdditionalPreviews) { return false; }

        /// Limits the number of items returned by a query.
        virtual bool SetReturnTotalOnly(SteamUGCQueryHandle queryHandle, bool returnTotalOnly) { return false; }

        /// Sets a language preference for returned localised strings.
        virtual bool SetLanguage(SteamUGCQueryHandle queryHandle, const AZStd::string& language) { return false; }

        /// Sets whether to allow cached query results.
        virtual bool SetAllowCachedResponse(SteamUGCQueryHandle queryHandle, AZ::u32 maxAgeSeconds) { return false; }

        /// Releases a query handle. Must be called after the result has been processed.
        virtual void ReleaseQueryUGCRequest(SteamUGCQueryHandle queryHandle) {}

        // --- Item Update ---

        /// Starts an item update session, returning a handle for subsequent SetItem* calls.
        virtual SteamUGCUpdateHandle StartItemUpdate(SteamAppId consumerAppId, SteamPublishedFileId publishedFileId) { return 0; }

        /// Sets the title of an item being updated.
        virtual bool SetItemTitle(SteamUGCUpdateHandle updateHandle, const AZStd::string& title) { return false; }

        /// Sets the description of an item being updated.
        virtual bool SetItemDescription(SteamUGCUpdateHandle updateHandle, const AZStd::string& description) { return false; }

        /// Sets the metadata of an item being updated.
        virtual bool SetItemMetadata(SteamUGCUpdateHandle updateHandle, const AZStd::string& metaData) { return false; }

        /// Sets the visibility of an item being updated.
        virtual bool SetItemVisibility(SteamUGCUpdateHandle updateHandle, SteamUGCVisibility visibility) { return false; }

        /// Sets the tags of an item being updated.
        virtual bool SetItemTags(SteamUGCUpdateHandle updateHandle, const AZStd::vector<AZStd::string>& tags) { return false; }

        /// Sets the content folder for an item being updated.
        virtual bool SetItemContent(SteamUGCUpdateHandle updateHandle, const AZStd::string& contentFolder) { return false; }

        /// Sets the preview image for an item being updated.
        virtual bool SetItemPreview(SteamUGCUpdateHandle updateHandle, const AZStd::string& previewFile) { return false; }

        // --- Download ---

        /// Forces a download (or update) of an item.
        virtual bool DownloadItem(SteamPublishedFileId publishedFileId, bool highPriority) { return false; }

        // --- Async (result via SteamUGCNotificationBus) ---

        /// Sends a UGC query to Steam.
        /// Returns a SteamCallHandle correlating with OnSteamUGCQueryCompleted.
        virtual SteamCallHandle SendQueryUGCRequest(SteamUGCQueryHandle queryHandle) { return 0; }

        /// Requests full details for a single item (wraps CreateQueryUGCDetailsRequest + Send).
        /// Returns a SteamCallHandle correlating with OnSteamUGCRequestUGCDetails.
        virtual SteamCallHandle RequestUGCDetails(SteamPublishedFileId publishedFileId, AZ::u32 maxAgeSeconds) { return 0; }

        /// Creates a new workshop item.
        /// Returns a SteamCallHandle correlating with OnCreateItem.
        virtual SteamCallHandle CreateItem(SteamAppId consumerAppId, AZ::s32 fileType) { return 0; }

        /// Submits an item update.
        /// Returns a SteamCallHandle correlating with OnSubmitItemUpdate.
        virtual SteamCallHandle SubmitItemUpdate(SteamUGCUpdateHandle updateHandle, const AZStd::string& changeNote) { return 0; }

        /// Adds or removes a workshop item from the user's favourites.
        /// Returns a SteamCallHandle correlating with OnUserFavoriteItemsListChanged.
        virtual SteamCallHandle AddItemToFavorites(SteamAppId appId, SteamPublishedFileId publishedFileId) { return 0; }
        virtual SteamCallHandle RemoveItemFromFavorites(SteamAppId appId, SteamPublishedFileId publishedFileId) { return 0; }

        /// Submits a user vote on a workshop item.
        /// Returns a SteamCallHandle correlating with OnSetUserItemVote.
        virtual SteamCallHandle SetUserItemVote(SteamPublishedFileId publishedFileId, bool voteUp) { return 0; }

        /// Retrieves the user's existing vote on a workshop item.
        /// Returns a SteamCallHandle correlating with OnGetUserItemVote.
        virtual SteamCallHandle GetUserItemVote(SteamPublishedFileId publishedFileId) { return 0; }

        /// Starts tracking playtime for a set of items (for ranking purposes).
        /// Returns a SteamCallHandle correlating with OnStartPlaytimeTracking.
        virtual SteamCallHandle StartPlaytimeTracking(const AZStd::vector<SteamPublishedFileId>& publishedFileIds) { return 0; }

        /// Stops tracking playtime for a set of items.
        /// Returns a SteamCallHandle correlating with OnStopPlaytimeTracking.
        virtual SteamCallHandle StopPlaytimeTracking(const AZStd::vector<SteamPublishedFileId>& publishedFileIds) { return 0; }

        /// Stops playtime tracking for all items.
        virtual SteamCallHandle StopPlaytimeTrackingForAllItems() { return 0; }

        /// Adds a dependency between two items.
        /// Returns a SteamCallHandle correlating with OnAddUGCDependencyResult.
        virtual SteamCallHandle AddDependency(SteamPublishedFileId parentId, SteamPublishedFileId childId) { return 0; }

        /// Removes a dependency between two items.
        /// Returns a SteamCallHandle correlating with OnRemoveUGCDependencyResult.
        virtual SteamCallHandle RemoveDependency(SteamPublishedFileId parentId, SteamPublishedFileId childId) { return 0; }

        /// Deletes a workshop item.
        /// Returns a SteamCallHandle correlating with OnDeleteItemResult.
        virtual SteamCallHandle DeleteItem(SteamPublishedFileId publishedFileId) { return 0; }

        /// Shows the item's EULA to the user if required.
        /// Returns a SteamCallHandle correlating with OnWorkshopEULAStatus.
        virtual SteamCallHandle GetWorkshopEULAStatus() { return 0; }
    };

    class SteamUGCRequestBusTraits : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
    };

    using SteamUGCRequestBus = AZ::EBus<SteamUGCRequests, SteamUGCRequestBusTraits>;

} // namespace Heathen