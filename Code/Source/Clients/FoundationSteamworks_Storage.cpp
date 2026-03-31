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

#include <steam/steam_api.h>
#include <steam/isteamremotestorage.h>
#include <FoundationSteamworks/SteamRemoteStorageNotificationBus.h>

using namespace Heathen;

namespace FoundationSteamworks
{
    // -----------------------------------------------------------------------
    // SteamRemoteStorageRequestBus
    // -----------------------------------------------------------------------

    bool FoundationSteamworksSystemComponent::FileWrite(const AZStd::string& fileName, const AZStd::vector<AZ::u8>& data)
    {
        return m_steamInitialised && SteamRemoteStorage()
            && SteamRemoteStorage()->FileWrite(fileName.c_str(), data.data(), static_cast<int32>(data.size()));
    }

    bool FoundationSteamworksSystemComponent::FileRead(const AZStd::string& fileName, AZStd::vector<AZ::u8>& outData)
    {
        if (!m_steamInitialised || !SteamRemoteStorage()) return false;
        int32 size = SteamRemoteStorage()->GetFileSize(fileName.c_str());
        if (size <= 0) return false;
        outData.resize(static_cast<size_t>(size));
        int32 read = SteamRemoteStorage()->FileRead(fileName.c_str(), outData.data(), size);
        return read == size;
    }

    bool FoundationSteamworksSystemComponent::FileExists(const AZStd::string& fileName)
    {
        return m_steamInitialised && SteamRemoteStorage() && SteamRemoteStorage()->FileExists(fileName.c_str());
    }

    bool FoundationSteamworksSystemComponent::FilePersisted(const AZStd::string& fileName)
    {
        return m_steamInitialised && SteamRemoteStorage() && SteamRemoteStorage()->FilePersisted(fileName.c_str());
    }

    AZ::s32 FoundationSteamworksSystemComponent::GetFileSize(const AZStd::string& fileName)
    {
        return m_steamInitialised && SteamRemoteStorage() ? SteamRemoteStorage()->GetFileSize(fileName.c_str()) : -1;
    }

    AZ::s64 FoundationSteamworksSystemComponent::GetFileTimestamp(const AZStd::string& fileName)
    {
        return m_steamInitialised && SteamRemoteStorage() ? SteamRemoteStorage()->GetFileTimestamp(fileName.c_str()) : 0;
    }

    bool FoundationSteamworksSystemComponent::FileForget(const AZStd::string& fileName)
    {
        return m_steamInitialised && SteamRemoteStorage() && SteamRemoteStorage()->FileForget(fileName.c_str());
    }

    bool FoundationSteamworksSystemComponent::FileDelete(const AZStd::string& fileName)
    {
        return m_steamInitialised && SteamRemoteStorage() && SteamRemoteStorage()->FileDelete(fileName.c_str());
    }

    AZ::s32 FoundationSteamworksSystemComponent::GetFileCount()
    {
        return m_steamInitialised && SteamRemoteStorage() ? SteamRemoteStorage()->GetFileCount() : 0;
    }

    AZStd::string FoundationSteamworksSystemComponent::GetFileNameAndSize(AZ::s32 index, AZ::s32& outSize)
    {
        if (!m_steamInitialised || !SteamRemoteStorage()) return {};
        int32 size = 0;
        const char* name = SteamRemoteStorage()->GetFileNameAndSize(index, &size);
        outSize = static_cast<AZ::s32>(size);
        return name ? AZStd::string(name) : AZStd::string{};
    }

    bool FoundationSteamworksSystemComponent::GetQuota(AZ::u64& outTotalBytes, AZ::u64& outAvailableBytes)
    {
        if (!m_steamInitialised || !SteamRemoteStorage()) return false;
        uint64 total = 0, available = 0;
        bool ok = SteamRemoteStorage()->GetQuota(&total, &available);
        if (ok) { outTotalBytes = total; outAvailableBytes = available; }
        return ok;
    }

    bool FoundationSteamworksSystemComponent::IsCloudEnabledForAccount()
    {
        return m_steamInitialised && SteamRemoteStorage() && SteamRemoteStorage()->IsCloudEnabledForAccount();
    }

    bool FoundationSteamworksSystemComponent::IsCloudEnabledForApp()
    {
        return m_steamInitialised && SteamRemoteStorage() && SteamRemoteStorage()->IsCloudEnabledForApp();
    }

    void FoundationSteamworksSystemComponent::SetCloudEnabledForApp(bool enabled)
    {
        if (m_steamInitialised && SteamRemoteStorage())
            SteamRemoteStorage()->SetCloudEnabledForApp(enabled);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::FileShare(const AZStd::string& fileName)
    {
        if (!m_steamInitialised || !SteamRemoteStorage()) return 0;
        SteamAPICall_t call = SteamRemoteStorage()->FileShare(fileName.c_str());
        m_callResults->Register<RemoteStorageFileShareResult_t>(call, [](SteamCallHandle h, RemoteStorageFileShareResult_t* p, bool ioFail)
        {
            SteamRemoteStorageNotificationBus::Broadcast(&SteamRemoteStorageNotifications::OnRemoteStorageFileShareResult,
                h, ToSteamResult(p->m_eResult), static_cast<SteamUGCHandle>(p->m_hFile),
                AZStd::string(p->m_rgchFilename));
        });
        return ToCallHandle(call);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::FileWriteAsync(const AZStd::string& fileName, const AZStd::vector<AZ::u8>& data)
    {
        if (!m_steamInitialised || !SteamRemoteStorage()) return 0;
        SteamAPICall_t call = SteamRemoteStorage()->FileWriteAsync(fileName.c_str(), data.data(), static_cast<uint32>(data.size()));
        m_callResults->Register<RemoteStorageFileWriteAsyncComplete_t>(call, [](SteamCallHandle h, RemoteStorageFileWriteAsyncComplete_t* p, bool ioFail)
        {
            SteamRemoteStorageNotificationBus::Broadcast(&SteamRemoteStorageNotifications::OnRemoteStorageFileWriteAsyncComplete,
                h, ToSteamResult(p->m_eResult));
        });
        return ToCallHandle(call);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::FileReadAsync(const AZStd::string& fileName, AZ::u32 offset, AZ::u32 bytesToRead)
    {
        if (!m_steamInitialised || !SteamRemoteStorage()) return 0;
        SteamAPICall_t call = SteamRemoteStorage()->FileReadAsync(fileName.c_str(), offset, bytesToRead);
        m_callResults->Register<RemoteStorageFileReadAsyncComplete_t>(call, [](SteamCallHandle h, RemoteStorageFileReadAsyncComplete_t* p, bool ioFail)
        {
            SteamRemoteStorageNotificationBus::Broadcast(&SteamRemoteStorageNotifications::OnRemoteStorageFileReadAsyncComplete,
                h, ToSteamResult(p->m_eResult), p->m_nOffset, p->m_cubRead);
        });
        return ToCallHandle(call);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::SubscribePublishedFile(SteamPublishedFileId publishedFileId)
    {
        if (!m_steamInitialised || !SteamRemoteStorage()) return 0;
        SteamAPICall_t call = SteamRemoteStorage()->SubscribePublishedFile(static_cast<PublishedFileId_t>(publishedFileId));
        m_callResults->Register<RemoteStorageSubscribePublishedFileResult_t>(call, [](SteamCallHandle h, RemoteStorageSubscribePublishedFileResult_t* p, bool ioFail)
        {
            SteamRemoteStorageNotificationBus::Broadcast(&SteamRemoteStorageNotifications::OnRemoteStorageSubscribePublishedFile,
                h, ToSteamResult(p->m_eResult), static_cast<SteamPublishedFileId>(p->m_nPublishedFileId));
        });
        return ToCallHandle(call);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::UnsubscribePublishedFile(SteamPublishedFileId publishedFileId)
    {
        if (!m_steamInitialised || !SteamRemoteStorage()) return 0;
        SteamAPICall_t call = SteamRemoteStorage()->UnsubscribePublishedFile(static_cast<PublishedFileId_t>(publishedFileId));
        m_callResults->Register<RemoteStorageUnsubscribePublishedFileResult_t>(call, [](SteamCallHandle h, RemoteStorageUnsubscribePublishedFileResult_t* p, bool ioFail)
        {
            SteamRemoteStorageNotificationBus::Broadcast(&SteamRemoteStorageNotifications::OnRemoteStorageUnsubscribePublishedFile,
                h, ToSteamResult(p->m_eResult), static_cast<SteamPublishedFileId>(p->m_nPublishedFileId));
        });
        return ToCallHandle(call);
    }

} // namespace FoundationSteamworks
