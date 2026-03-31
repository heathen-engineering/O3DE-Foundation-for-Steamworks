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
    // SteamRemoteStorageNotifications
    // Broadcasts for ISteamRemoteStorage callbacks and CallResults.
    // -----------------------------------------------------------------------
    class SteamRemoteStorageNotifications
    {
    public:
        AZ_RTTI(SteamRemoteStorageNotifications, "{F6G8H9I0-2J3E-4FBH-EI8K-7J6G0H3F9I12}");
        virtual ~SteamRemoteStorageNotifications() = default;

        // -----------------------------------------------------------------------
        // Callbacks
        // -----------------------------------------------------------------------

        /// Fired when a file has been shared from the local client.
        virtual void OnRemoteStorageLocalFileChange() {}

        // -----------------------------------------------------------------------
        // CallResults
        // -----------------------------------------------------------------------

        /// Response to FileShare.
        virtual void OnRemoteStorageFileShareResult(
            SteamCallHandle callHandle,
            SteamResult result,
            SteamUGCHandle handle,
            const AZStd::string& filename) {}

        /// Response to FileWriteAsync.
        virtual void OnRemoteStorageFileWriteAsyncComplete(
            SteamCallHandle callHandle,
            SteamResult result) {}

        /// Response to FileReadAsync.
        virtual void OnRemoteStorageFileReadAsyncComplete(
            SteamCallHandle callHandle,
            SteamResult result,
            AZ::u32 offset,
            AZ::u32 read) {}

        /// Response to SubscribePublishedFile.
        virtual void OnRemoteStorageSubscribePublishedFile(
            SteamCallHandle callHandle,
            SteamResult result,
            SteamPublishedFileId publishedFileId) {}

        /// Response to UnsubscribePublishedFile.
        virtual void OnRemoteStorageUnsubscribePublishedFile(
            SteamCallHandle callHandle,
            SteamResult result,
            SteamPublishedFileId publishedFileId) {}
    };

    class SteamRemoteStorageNotificationBusTraits : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
    };

    using SteamRemoteStorageNotificationBus = AZ::EBus<SteamRemoteStorageNotifications, SteamRemoteStorageNotificationBusTraits>;

} // namespace Heathen