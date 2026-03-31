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
#include <FoundationSteamworks/SteamTypes.h>

namespace Heathen
{
    // -----------------------------------------------------------------------
    // SteamUGCNotifications
    // Broadcasts for ISteamUGC callbacks and CallResults.
    // -----------------------------------------------------------------------
    class SteamUGCNotifications
    {
    public:
        AZ_RTTI(SteamUGCNotifications, "{H8I0J1K2-4L5G-4HDJ-GK0M-9L8I2J5H1K14}");
        virtual ~SteamUGCNotifications() = default;

        // -----------------------------------------------------------------------
        // Callbacks
        // -----------------------------------------------------------------------

        /// Fired when a workshop item download completes or fails.
        virtual void OnDownloadItemResult(
            SteamAppId appId,
            SteamPublishedFileId publishedFileId,
            SteamResult result) {}

        /// Fired when a workshop item is installed or updated.
        virtual void OnItemInstalled(
            SteamAppId appId,
            SteamPublishedFileId publishedFileId) {}

        /// Fired when a user has subscribed to a workshop item.
        virtual void OnUserSubscribedItemsListChanged(SteamAppId appId) {}

        // -----------------------------------------------------------------------
        // CallResults
        // -----------------------------------------------------------------------

        /// Response to SendQueryUGCRequest.
        virtual void OnSteamUGCQueryCompleted(
            SteamCallHandle callHandle,
            SteamResult result,
            SteamUGCQueryHandle queryHandle,
            AZ::u32 numResultsReturned,
            AZ::u32 totalMatchingResults,
            bool cachedData) {}

        /// Response to RequestUGCDetails (deprecated in newer SDKs, use queries instead).
        virtual void OnSteamUGCRequestUGCDetails(
            SteamCallHandle callHandle,
            SteamResult result,
            bool cachedData) {}

        /// Response to CreateItem.
        virtual void OnCreateItem(
            SteamCallHandle callHandle,
            SteamResult result,
            SteamPublishedFileId publishedFileId,
            bool userNeedsToAcceptWorkshopLegalAgreement) {}

        /// Response to SubmitItemUpdate.
        virtual void OnSubmitItemUpdate(
            SteamCallHandle callHandle,
            SteamResult result,
            bool userNeedsToAcceptWorkshopLegalAgreement) {}

        /// Response to AddItemToFavorites / RemoveItemFromFavorites.
        virtual void OnUserFavoriteItemsListChanged(
            SteamCallHandle callHandle,
            SteamResult result,
            SteamPublishedFileId publishedFileId,
            bool wasAddRequest) {}

        /// Response to SetUserItemVote.
        virtual void OnSetUserItemVote(
            SteamCallHandle callHandle,
            SteamResult result,
            SteamPublishedFileId publishedFileId,
            bool voteUp) {}

        /// Response to GetUserItemVote.
        virtual void OnGetUserItemVote(
            SteamCallHandle callHandle,
            SteamResult result,
            SteamPublishedFileId publishedFileId,
            bool votedUp,
            bool votedDown,
            bool voteSkipped) {}

        /// Response to StartPlaytimeTracking.
        virtual void OnStartPlaytimeTracking(
            SteamCallHandle callHandle,
            SteamResult result) {}

        /// Response to StopPlaytimeTracking / StopPlaytimeTrackingForAllItems.
        virtual void OnStopPlaytimeTracking(
            SteamCallHandle callHandle,
            SteamResult result) {}

        /// Response to AddDependency.
        virtual void OnAddUGCDependency(
            SteamCallHandle callHandle,
            SteamResult result,
            SteamPublishedFileId publishedFileId,
            SteamPublishedFileId childPublishedFileId) {}

        /// Response to RemoveDependency.
        virtual void OnRemoveUGCDependency(
            SteamCallHandle callHandle,
            SteamResult result,
            SteamPublishedFileId publishedFileId,
            SteamPublishedFileId childPublishedFileId) {}

        /// Response to AddAppDependency.
        virtual void OnAddAppDependency(
            SteamCallHandle callHandle,
            SteamResult result,
            SteamPublishedFileId publishedFileId,
            SteamAppId appId) {}

        /// Response to RemoveAppDependency.
        virtual void OnRemoveAppDependency(
            SteamCallHandle callHandle,
            SteamResult result,
            SteamPublishedFileId publishedFileId,
            SteamAppId appId) {}

        /// Response to GetAppDependencies.
        virtual void OnGetAppDependencies(
            SteamCallHandle callHandle,
            SteamResult result,
            SteamPublishedFileId publishedFileId,
            AZ::u32 numAppDependencies,
            AZ::u32 totalNumAppDependencies) {}

        /// Response to DeleteItem.
        virtual void OnDeleteItem(
            SteamCallHandle callHandle,
            SteamResult result,
            SteamPublishedFileId publishedFileId) {}

        /// Response to GetWorkshopEULAStatus.
        virtual void OnWorkshopEULAStatus(
            SteamCallHandle callHandle,
            SteamResult result,
            SteamAppId appId,
            AZ::u32 version,
            AZ::u32 action,
            bool accepted,
            bool needsAction) {}
    };

    class SteamUGCNotificationBusTraits : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
    };

    using SteamUGCNotificationBus = AZ::EBus<SteamUGCNotifications, SteamUGCNotificationBusTraits>;

} // namespace Heathen