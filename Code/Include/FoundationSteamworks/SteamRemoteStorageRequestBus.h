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
    // SteamRemoteStorageRequests
    // Request bus wrapping ISteamRemoteStorage (Steam Cloud).
    // File I/O uses AZStd::vector<AZ::u8> for binary data.
    // -----------------------------------------------------------------------
    class SteamRemoteStorageRequests
    {
    public:
        AZ_RTTI(SteamRemoteStorageRequests, "{F6A7B8C9-DAEB-4FC0-D123-D4E5F6A7B8CA}");
        virtual ~SteamRemoteStorageRequests() = default;

        // --- Synchronous File Operations ---

        /// Writes binary data to a cloud file, creating or overwriting it.
        /// Returns true on success.
        virtual bool FileWrite(const AZStd::string& fileName, const AZStd::vector<AZ::u8>& data) { return false; }

        /// Reads the entire contents of a cloud file into a byte buffer.
        /// Returns true on success; outData is populated.
        virtual bool FileRead(const AZStd::string& fileName, AZStd::vector<AZ::u8>& outData) { return false; }

        /// Returns true if the named cloud file exists.
        virtual bool FileExists(const AZStd::string& fileName) { return false; }

        /// Returns true if the named file is currently persisted to the cloud.
        virtual bool FilePersisted(const AZStd::string& fileName) { return false; }

        /// Returns the size in bytes of the named cloud file, or -1 if not found.
        virtual AZ::s32 GetFileSize(const AZStd::string& fileName) { return -1; }

        /// Returns the last-modified Unix timestamp of the named cloud file.
        virtual AZ::s64 GetFileTimestamp(const AZStd::string& fileName) { return 0; }

        /// Removes the Steam Cloud mapping for a file without deleting the local copy.
        /// The file will no longer sync across machines.
        virtual bool FileForget(const AZStd::string& fileName) { return false; }

        /// Permanently deletes a cloud file (both local and cloud copies).
        virtual bool FileDelete(const AZStd::string& fileName) { return false; }

        /// Returns the total number of files stored in the cloud for this app.
        virtual AZ::s32 GetFileCount() { return 0; }

        /// Returns the name of the file at the given index. outSize is set to file size.
        virtual AZStd::string GetFileNameAndSize(AZ::s32 index, AZ::s32& outSize) { return {}; }

        // --- Quota ---

        /// Returns the total and available cloud storage in bytes for the current user.
        virtual bool GetQuota(AZ::u64& outTotalBytes, AZ::u64& outAvailableBytes) { return false; }

        // --- Cloud Enable / Disable ---

        /// Returns true if Steam Cloud is enabled for this user's account.
        virtual bool IsCloudEnabledForAccount() { return false; }

        /// Returns true if Steam Cloud is enabled for this app by the user.
        virtual bool IsCloudEnabledForApp() { return false; }

        /// Enables or disables Steam Cloud sync for this app for the current user.
        virtual void SetCloudEnabledForApp(bool enabled) {}

        // --- Async (result via SteamRemoteStorageNotificationBus) ---

        /// Shares a file from cloud storage, making it accessible via a UGC handle.
        /// Returns a SteamCallHandle correlating with OnRemoteStorageFileShareResult.
        virtual SteamCallHandle FileShare(const AZStd::string& fileName) { return 0; }

        /// Writes a file asynchronously to cloud storage.
        /// Returns a SteamCallHandle correlating with OnRemoteStorageFileWriteAsyncComplete.
        virtual SteamCallHandle FileWriteAsync(const AZStd::string& fileName, const AZStd::vector<AZ::u8>& data) { return 0; }

        /// Reads a portion of a file asynchronously from cloud storage.
        /// Returns a SteamCallHandle correlating with OnRemoteStorageFileReadAsyncComplete.
        virtual SteamCallHandle FileReadAsync(const AZStd::string& fileName, AZ::u32 offset, AZ::u32 bytesToRead) { return 0; }

        /// Subscribes to a published UGC file.
        /// Returns a SteamCallHandle correlating with OnRemoteStorageSubscribePublishedFile.
        virtual SteamCallHandle SubscribePublishedFile(SteamPublishedFileId publishedFileId) { return 0; }

        /// Unsubscribes from a published UGC file.
        /// Returns a SteamCallHandle correlating with OnRemoteStorageUnsubscribePublishedFile.
        virtual SteamCallHandle UnsubscribePublishedFile(SteamPublishedFileId publishedFileId) { return 0; }
    };

    class SteamRemoteStorageRequestBusTraits : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
    };

    using SteamRemoteStorageRequestBus = AZ::EBus<SteamRemoteStorageRequests, SteamRemoteStorageRequestBusTraits>;

} // namespace Heathen