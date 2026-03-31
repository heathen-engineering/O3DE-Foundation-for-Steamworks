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
#include <steam/isteamugc.h>
#include <FoundationSteamworks/SteamUGCNotificationBus.h>

using namespace Heathen;

namespace FoundationSteamworks
{
    // -----------------------------------------------------------------------
    // SteamUGCRequestBus
    // -----------------------------------------------------------------------

    AZ::u32 FoundationSteamworksSystemComponent::GetItemState(SteamPublishedFileId publishedFileId)
    {
        return m_steamInitialised && SteamUGC() ? SteamUGC()->GetItemState(static_cast<PublishedFileId_t>(publishedFileId)) : 0;
    }

    bool FoundationSteamworksSystemComponent::GetItemDownloadInfo(SteamPublishedFileId publishedFileId, AZ::u64& outBytesDownloaded, AZ::u64& outBytesTotal)
    {
        if (!m_steamInitialised || !SteamUGC()) return false;
        uint64 dl = 0, total = 0;
        bool ok = SteamUGC()->GetItemDownloadInfo(static_cast<PublishedFileId_t>(publishedFileId), &dl, &total);
        if (ok) { outBytesDownloaded = dl; outBytesTotal = total; }
        return ok;
    }

    bool FoundationSteamworksSystemComponent::GetItemInstallInfo(SteamPublishedFileId publishedFileId, AZ::u64& outSizeOnDisk, AZStd::string& outFolder, AZ::u32& outTimestamp)
    {
        if (!m_steamInitialised || !SteamUGC()) return false;
        uint64 size = 0;
        char folder[1024] = {};
        uint32 timestamp = 0;
        bool ok = SteamUGC()->GetItemInstallInfo(static_cast<PublishedFileId_t>(publishedFileId), &size, folder, sizeof(folder), &timestamp);
        if (ok) { outSizeOnDisk = size; outFolder = AZStd::string(folder); outTimestamp = timestamp; }
        return ok;
    }

    AZ::u32 FoundationSteamworksSystemComponent::GetNumSubscribedItems()
    {
        return m_steamInitialised && SteamUGC() ? SteamUGC()->GetNumSubscribedItems() : 0;
    }

    AZ::u32 FoundationSteamworksSystemComponent::GetSubscribedItems(AZStd::vector<SteamPublishedFileId>& outIds, AZ::u32 maxEntries)
    {
        if (!m_steamInitialised || !SteamUGC()) return 0;
        AZStd::vector<PublishedFileId_t> raw(maxEntries);
        uint32 count = SteamUGC()->GetSubscribedItems(raw.data(), maxEntries);
        outIds.resize(count);
        for (uint32 i = 0; i < count; ++i) outIds[i] = static_cast<SteamPublishedFileId>(raw[i]);
        return count;
    }

    SteamUGCQueryHandle FoundationSteamworksSystemComponent::CreateQueryAllUGCRequest(AZ::s32 queryType, AZ::s32 matchingFileType, SteamAppId creatorAppId, SteamAppId consumerAppId, AZ::u32 page)
    {
        if (!m_steamInitialised || !SteamUGC()) return k_UGCQueryHandleInvalid;
        return static_cast<SteamUGCQueryHandle>(SteamUGC()->CreateQueryAllUGCRequest(
            static_cast<EUGCQuery>(queryType),
            static_cast<EUGCMatchingUGCType>(matchingFileType),
            static_cast<AppId_t>(creatorAppId),
            static_cast<AppId_t>(consumerAppId), page));
    }

    SteamUGCQueryHandle FoundationSteamworksSystemComponent::CreateQueryUserUGCRequest(SteamId accountId, AZ::s32 listType, AZ::s32 matchingFileType, AZ::s32 sortOrder, SteamAppId creatorAppId, SteamAppId consumerAppId, AZ::u32 page)
    {
        if (!m_steamInitialised || !SteamUGC()) return k_UGCQueryHandleInvalid;
        return static_cast<SteamUGCQueryHandle>(SteamUGC()->CreateQueryUserUGCRequest(
            FromSteamId(accountId).GetAccountID(),
            static_cast<EUserUGCList>(listType),
            static_cast<EUGCMatchingUGCType>(matchingFileType),
            static_cast<EUserUGCListSortOrder>(sortOrder),
            static_cast<AppId_t>(creatorAppId),
            static_cast<AppId_t>(consumerAppId), page));
    }

    SteamUGCQueryHandle FoundationSteamworksSystemComponent::CreateQueryUGCDetailsRequest(const AZStd::vector<SteamPublishedFileId>& publishedFileIds)
    {
        if (!m_steamInitialised || !SteamUGC() || publishedFileIds.empty()) return k_UGCQueryHandleInvalid;
        AZStd::vector<PublishedFileId_t> ids;
        ids.reserve(publishedFileIds.size());
        for (auto id : publishedFileIds) ids.push_back(static_cast<PublishedFileId_t>(id));
        return static_cast<SteamUGCQueryHandle>(SteamUGC()->CreateQueryUGCDetailsRequest(ids.data(), static_cast<uint32>(ids.size())));
    }

    bool FoundationSteamworksSystemComponent::AddRequiredTag(SteamUGCQueryHandle queryHandle, const AZStd::string& tagName)
    {
        return m_steamInitialised && SteamUGC() && SteamUGC()->AddRequiredTag(FromUGCQueryHandle(queryHandle), tagName.c_str());
    }

    bool FoundationSteamworksSystemComponent::AddExcludedTag(SteamUGCQueryHandle queryHandle, const AZStd::string& tagName)
    {
        return m_steamInitialised && SteamUGC() && SteamUGC()->AddExcludedTag(FromUGCQueryHandle(queryHandle), tagName.c_str());
    }

    bool FoundationSteamworksSystemComponent::SetMatchAnyTag(SteamUGCQueryHandle queryHandle, bool matchAnyTag)
    {
        return m_steamInitialised && SteamUGC() && SteamUGC()->SetMatchAnyTag(FromUGCQueryHandle(queryHandle), matchAnyTag);
    }

    bool FoundationSteamworksSystemComponent::AddRequiredKeyValueTag(SteamUGCQueryHandle queryHandle, const AZStd::string& key, const AZStd::string& value)
    {
        return m_steamInitialised && SteamUGC() && SteamUGC()->AddRequiredKeyValueTag(FromUGCQueryHandle(queryHandle), key.c_str(), value.c_str());
    }

    bool FoundationSteamworksSystemComponent::SetReturnLongDescription(SteamUGCQueryHandle queryHandle, bool returnLongDescription)
    {
        return m_steamInitialised && SteamUGC() && SteamUGC()->SetReturnLongDescription(FromUGCQueryHandle(queryHandle), returnLongDescription);
    }

    bool FoundationSteamworksSystemComponent::SetReturnMetadata(SteamUGCQueryHandle queryHandle, bool returnMetadata)
    {
        return m_steamInitialised && SteamUGC() && SteamUGC()->SetReturnMetadata(FromUGCQueryHandle(queryHandle), returnMetadata);
    }

    bool FoundationSteamworksSystemComponent::SetReturnChildren(SteamUGCQueryHandle queryHandle, bool returnChildren)
    {
        return m_steamInitialised && SteamUGC() && SteamUGC()->SetReturnChildren(FromUGCQueryHandle(queryHandle), returnChildren);
    }

    bool FoundationSteamworksSystemComponent::SetReturnAdditionalPreviews(SteamUGCQueryHandle queryHandle, bool returnAdditionalPreviews)
    {
        return m_steamInitialised && SteamUGC() && SteamUGC()->SetReturnAdditionalPreviews(FromUGCQueryHandle(queryHandle), returnAdditionalPreviews);
    }

    bool FoundationSteamworksSystemComponent::SetReturnTotalOnly(SteamUGCQueryHandle queryHandle, bool returnTotalOnly)
    {
        return m_steamInitialised && SteamUGC() && SteamUGC()->SetReturnTotalOnly(FromUGCQueryHandle(queryHandle), returnTotalOnly);
    }

    bool FoundationSteamworksSystemComponent::SetLanguage(SteamUGCQueryHandle queryHandle, const AZStd::string& language)
    {
        return m_steamInitialised && SteamUGC() && SteamUGC()->SetLanguage(FromUGCQueryHandle(queryHandle), language.c_str());
    }

    bool FoundationSteamworksSystemComponent::SetAllowCachedResponse(SteamUGCQueryHandle queryHandle, AZ::u32 maxAgeSeconds)
    {
        return m_steamInitialised && SteamUGC() && SteamUGC()->SetAllowCachedResponse(FromUGCQueryHandle(queryHandle), maxAgeSeconds);
    }

    void FoundationSteamworksSystemComponent::ReleaseQueryUGCRequest(SteamUGCQueryHandle queryHandle)
    {
        if (m_steamInitialised && SteamUGC())
            SteamUGC()->ReleaseQueryUGCRequest(FromUGCQueryHandle(queryHandle));
    }

    SteamUGCUpdateHandle FoundationSteamworksSystemComponent::StartItemUpdate(SteamAppId consumerAppId, SteamPublishedFileId publishedFileId)
    {
        if (!m_steamInitialised || !SteamUGC()) return k_UGCUpdateHandleInvalid;
        return static_cast<SteamUGCUpdateHandle>(SteamUGC()->StartItemUpdate(static_cast<AppId_t>(consumerAppId), static_cast<PublishedFileId_t>(publishedFileId)));
    }

    bool FoundationSteamworksSystemComponent::SetItemTitle(SteamUGCUpdateHandle updateHandle, const AZStd::string& title)
    {
        return m_steamInitialised && SteamUGC() && SteamUGC()->SetItemTitle(FromUGCUpdateHandle(updateHandle), title.c_str());
    }

    bool FoundationSteamworksSystemComponent::SetItemDescription(SteamUGCUpdateHandle updateHandle, const AZStd::string& description)
    {
        return m_steamInitialised && SteamUGC() && SteamUGC()->SetItemDescription(FromUGCUpdateHandle(updateHandle), description.c_str());
    }

    bool FoundationSteamworksSystemComponent::SetItemMetadata(SteamUGCUpdateHandle updateHandle, const AZStd::string& metaData)
    {
        return m_steamInitialised && SteamUGC() && SteamUGC()->SetItemMetadata(FromUGCUpdateHandle(updateHandle), metaData.c_str());
    }

    bool FoundationSteamworksSystemComponent::SetItemVisibility(SteamUGCUpdateHandle updateHandle, SteamUGCVisibility visibility)
    {
        return m_steamInitialised && SteamUGC()
            && SteamUGC()->SetItemVisibility(FromUGCUpdateHandle(updateHandle), static_cast<ERemoteStoragePublishedFileVisibility>(visibility));
    }

    bool FoundationSteamworksSystemComponent::SetItemTags(SteamUGCUpdateHandle updateHandle, const AZStd::vector<AZStd::string>& tags)
    {
        if (!m_steamInitialised || !SteamUGC()) return false;
        AZStd::vector<const char*> ptrs;
        ptrs.reserve(tags.size());
        for (const auto& t : tags) ptrs.push_back(t.c_str());
        SteamParamStringArray_t arr;
        arr.m_ppStrings = ptrs.data();
        arr.m_nNumStrings = static_cast<int32>(ptrs.size());
        return SteamUGC()->SetItemTags(FromUGCUpdateHandle(updateHandle), &arr);
    }

    bool FoundationSteamworksSystemComponent::SetItemContent(SteamUGCUpdateHandle updateHandle, const AZStd::string& contentFolder)
    {
        return m_steamInitialised && SteamUGC() && SteamUGC()->SetItemContent(FromUGCUpdateHandle(updateHandle), contentFolder.c_str());
    }

    bool FoundationSteamworksSystemComponent::SetItemPreview(SteamUGCUpdateHandle updateHandle, const AZStd::string& previewFile)
    {
        return m_steamInitialised && SteamUGC() && SteamUGC()->SetItemPreview(FromUGCUpdateHandle(updateHandle), previewFile.c_str());
    }

    bool FoundationSteamworksSystemComponent::DownloadItem(SteamPublishedFileId publishedFileId, bool highPriority)
    {
        return m_steamInitialised && SteamUGC() && SteamUGC()->DownloadItem(static_cast<PublishedFileId_t>(publishedFileId), highPriority);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::SendQueryUGCRequest(SteamUGCQueryHandle queryHandle)
    {
        if (!m_steamInitialised || !SteamUGC()) return 0;
        SteamAPICall_t call = SteamUGC()->SendQueryUGCRequest(FromUGCQueryHandle(queryHandle));
        m_callResults->Register<SteamUGCQueryCompleted_t>(call, [](SteamCallHandle h, SteamUGCQueryCompleted_t* p, bool ioFail)
        {
            SteamUGCNotificationBus::Broadcast(&SteamUGCNotifications::OnSteamUGCQueryCompleted,
                h, ToSteamResult(p->m_eResult), static_cast<SteamUGCQueryHandle>(p->m_handle),
                p->m_unNumResultsReturned, p->m_unTotalMatchingResults, p->m_bCachedData);
        });
        return ToCallHandle(call);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::RequestUGCDetails(SteamPublishedFileId publishedFileId, AZ::u32 maxAgeSeconds)
    {
        if (!m_steamInitialised || !SteamUGC()) return 0;
        PublishedFileId_t pfid = static_cast<PublishedFileId_t>(publishedFileId);
        UGCQueryHandle_t qHandle = SteamUGC()->CreateQueryUGCDetailsRequest(&pfid, 1);
        if (maxAgeSeconds > 0) SteamUGC()->SetAllowCachedResponse(qHandle, maxAgeSeconds);
        SteamAPICall_t call = SteamUGC()->SendQueryUGCRequest(qHandle);
        m_callResults->Register<SteamUGCQueryCompleted_t>(call, [](SteamCallHandle h, SteamUGCQueryCompleted_t* p, bool ioFail)
        {
            SteamUGCNotificationBus::Broadcast(&SteamUGCNotifications::OnSteamUGCQueryCompleted,
                h, ToSteamResult(p->m_eResult), static_cast<SteamUGCQueryHandle>(p->m_handle),
                p->m_unNumResultsReturned, p->m_unTotalMatchingResults, p->m_bCachedData);
        });
        return ToCallHandle(call);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::CreateItem(SteamAppId consumerAppId, AZ::s32 fileType)
    {
        if (!m_steamInitialised || !SteamUGC()) return 0;
        SteamAPICall_t call = SteamUGC()->CreateItem(static_cast<AppId_t>(consumerAppId), static_cast<EWorkshopFileType>(fileType));
        m_callResults->Register<CreateItemResult_t>(call, [](SteamCallHandle h, CreateItemResult_t* p, bool ioFail)
        {
            SteamUGCNotificationBus::Broadcast(&SteamUGCNotifications::OnCreateItem,
                h, ToSteamResult(p->m_eResult), static_cast<SteamPublishedFileId>(p->m_nPublishedFileId), p->m_bUserNeedsToAcceptWorkshopLegalAgreement);
        });
        return ToCallHandle(call);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::SubmitItemUpdate(SteamUGCUpdateHandle updateHandle, const AZStd::string& changeNote)
    {
        if (!m_steamInitialised || !SteamUGC()) return 0;
        SteamAPICall_t call = SteamUGC()->SubmitItemUpdate(FromUGCUpdateHandle(updateHandle), changeNote.c_str());
        m_callResults->Register<SubmitItemUpdateResult_t>(call, [](SteamCallHandle h, SubmitItemUpdateResult_t* p, bool ioFail)
        {
            SteamUGCNotificationBus::Broadcast(&SteamUGCNotifications::OnSubmitItemUpdate,
                h, ToSteamResult(p->m_eResult), p->m_bUserNeedsToAcceptWorkshopLegalAgreement);
        });
        return ToCallHandle(call);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::AddItemToFavorites(SteamAppId appId, SteamPublishedFileId publishedFileId)
    {
        if (!m_steamInitialised || !SteamUGC()) return 0;
        SteamAPICall_t call = SteamUGC()->AddItemToFavorites(static_cast<AppId_t>(appId), static_cast<PublishedFileId_t>(publishedFileId));
        m_callResults->Register<UserFavoriteItemsListChanged_t>(call, [](SteamCallHandle h, UserFavoriteItemsListChanged_t* p, bool ioFail)
        {
            SteamUGCNotificationBus::Broadcast(&SteamUGCNotifications::OnUserFavoriteItemsListChanged,
                h, ToSteamResult(p->m_eResult), static_cast<SteamPublishedFileId>(p->m_nPublishedFileId), p->m_bWasAddRequest);
        });
        return ToCallHandle(call);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::RemoveItemFromFavorites(SteamAppId appId, SteamPublishedFileId publishedFileId)
    {
        if (!m_steamInitialised || !SteamUGC()) return 0;
        SteamAPICall_t call = SteamUGC()->RemoveItemFromFavorites(static_cast<AppId_t>(appId), static_cast<PublishedFileId_t>(publishedFileId));
        m_callResults->Register<UserFavoriteItemsListChanged_t>(call, [](SteamCallHandle h, UserFavoriteItemsListChanged_t* p, bool ioFail)
        {
            SteamUGCNotificationBus::Broadcast(&SteamUGCNotifications::OnUserFavoriteItemsListChanged,
                h, ToSteamResult(p->m_eResult), static_cast<SteamPublishedFileId>(p->m_nPublishedFileId), p->m_bWasAddRequest);
        });
        return ToCallHandle(call);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::SetUserItemVote(SteamPublishedFileId publishedFileId, bool voteUp)
    {
        if (!m_steamInitialised || !SteamUGC()) return 0;
        SteamAPICall_t call = SteamUGC()->SetUserItemVote(static_cast<PublishedFileId_t>(publishedFileId), voteUp);
        m_callResults->Register<SetUserItemVoteResult_t>(call, [](SteamCallHandle h, SetUserItemVoteResult_t* p, bool ioFail)
        {
            SteamUGCNotificationBus::Broadcast(&SteamUGCNotifications::OnSetUserItemVote,
                h, ToSteamResult(p->m_eResult), static_cast<SteamPublishedFileId>(p->m_nPublishedFileId), p->m_bVoteUp);
        });
        return ToCallHandle(call);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::GetUserItemVote(SteamPublishedFileId publishedFileId)
    {
        if (!m_steamInitialised || !SteamUGC()) return 0;
        SteamAPICall_t call = SteamUGC()->GetUserItemVote(static_cast<PublishedFileId_t>(publishedFileId));
        m_callResults->Register<GetUserItemVoteResult_t>(call, [](SteamCallHandle h, GetUserItemVoteResult_t* p, bool ioFail)
        {
            SteamUGCNotificationBus::Broadcast(&SteamUGCNotifications::OnGetUserItemVote,
                h, ToSteamResult(p->m_eResult), static_cast<SteamPublishedFileId>(p->m_nPublishedFileId),
                p->m_bVotedUp, p->m_bVotedDown, p->m_bVoteSkipped);
        });
        return ToCallHandle(call);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::StartPlaytimeTracking(const AZStd::vector<SteamPublishedFileId>& publishedFileIds)
    {
        if (!m_steamInitialised || !SteamUGC() || publishedFileIds.empty()) return 0;
        AZStd::vector<PublishedFileId_t> ids;
        ids.reserve(publishedFileIds.size());
        for (auto id : publishedFileIds) ids.push_back(static_cast<PublishedFileId_t>(id));
        SteamAPICall_t call = SteamUGC()->StartPlaytimeTracking(ids.data(), static_cast<uint32>(ids.size()));
        m_callResults->Register<StartPlaytimeTrackingResult_t>(call, [](SteamCallHandle h, StartPlaytimeTrackingResult_t* p, bool ioFail)
        {
            SteamUGCNotificationBus::Broadcast(&SteamUGCNotifications::OnStartPlaytimeTracking,
                h, ToSteamResult(p->m_eResult));
        });
        return ToCallHandle(call);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::StopPlaytimeTracking(const AZStd::vector<SteamPublishedFileId>& publishedFileIds)
    {
        if (!m_steamInitialised || !SteamUGC() || publishedFileIds.empty()) return 0;
        AZStd::vector<PublishedFileId_t> ids;
        ids.reserve(publishedFileIds.size());
        for (auto id : publishedFileIds) ids.push_back(static_cast<PublishedFileId_t>(id));
        SteamAPICall_t call = SteamUGC()->StopPlaytimeTracking(ids.data(), static_cast<uint32>(ids.size()));
        m_callResults->Register<StopPlaytimeTrackingResult_t>(call, [](SteamCallHandle h, StopPlaytimeTrackingResult_t* p, bool ioFail)
        {
            SteamUGCNotificationBus::Broadcast(&SteamUGCNotifications::OnStopPlaytimeTracking,
                h, ToSteamResult(p->m_eResult));
        });
        return ToCallHandle(call);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::StopPlaytimeTrackingForAllItems()
    {
        if (!m_steamInitialised || !SteamUGC()) return 0;
        SteamAPICall_t call = SteamUGC()->StopPlaytimeTrackingForAllItems();
        m_callResults->Register<StopPlaytimeTrackingResult_t>(call, [](SteamCallHandle h, StopPlaytimeTrackingResult_t* p, bool ioFail)
        {
            SteamUGCNotificationBus::Broadcast(&SteamUGCNotifications::OnStopPlaytimeTracking,
                h, ToSteamResult(p->m_eResult));
        });
        return ToCallHandle(call);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::AddDependency(SteamPublishedFileId parentId, SteamPublishedFileId childId)
    {
        if (!m_steamInitialised || !SteamUGC()) return 0;
        SteamAPICall_t call = SteamUGC()->AddDependency(static_cast<PublishedFileId_t>(parentId), static_cast<PublishedFileId_t>(childId));
        m_callResults->Register<AddUGCDependencyResult_t>(call, [](SteamCallHandle h, AddUGCDependencyResult_t* p, bool ioFail)
        {
            SteamUGCNotificationBus::Broadcast(&SteamUGCNotifications::OnAddUGCDependency,
                h, ToSteamResult(p->m_eResult), static_cast<SteamPublishedFileId>(p->m_nPublishedFileId), static_cast<SteamPublishedFileId>(p->m_nChildPublishedFileId));
        });
        return ToCallHandle(call);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::RemoveDependency(SteamPublishedFileId parentId, SteamPublishedFileId childId)
    {
        if (!m_steamInitialised || !SteamUGC()) return 0;
        SteamAPICall_t call = SteamUGC()->RemoveDependency(static_cast<PublishedFileId_t>(parentId), static_cast<PublishedFileId_t>(childId));
        m_callResults->Register<RemoveUGCDependencyResult_t>(call, [](SteamCallHandle h, RemoveUGCDependencyResult_t* p, bool ioFail)
        {
            SteamUGCNotificationBus::Broadcast(&SteamUGCNotifications::OnRemoveUGCDependency,
                h, ToSteamResult(p->m_eResult), static_cast<SteamPublishedFileId>(p->m_nPublishedFileId), static_cast<SteamPublishedFileId>(p->m_nChildPublishedFileId));
        });
        return ToCallHandle(call);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::DeleteItem(SteamPublishedFileId publishedFileId)
    {
        if (!m_steamInitialised || !SteamUGC()) return 0;
        SteamAPICall_t call = SteamUGC()->DeleteItem(static_cast<PublishedFileId_t>(publishedFileId));
        m_callResults->Register<DeleteItemResult_t>(call, [](SteamCallHandle h, DeleteItemResult_t* p, bool ioFail)
        {
            SteamUGCNotificationBus::Broadcast(&SteamUGCNotifications::OnDeleteItem,
                h, ToSteamResult(p->m_eResult), static_cast<SteamPublishedFileId>(p->m_nPublishedFileId));
        });
        return ToCallHandle(call);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::GetWorkshopEULAStatus()
    {
        if (!m_steamInitialised || !SteamUGC()) return 0;
        SteamAPICall_t call = SteamUGC()->GetWorkshopEULAStatus();
        m_callResults->Register<WorkshopEULAStatus_t>(call, [](SteamCallHandle h, WorkshopEULAStatus_t* p, bool ioFail)
        {
            SteamUGCNotificationBus::Broadcast(&SteamUGCNotifications::OnWorkshopEULAStatus,
                h, ToSteamResult(p->m_eResult), static_cast<SteamAppId>(p->m_nAppID), p->m_unVersion, p->m_rtAction, p->m_bAccepted, p->m_bNeedsAction);
        });
        return ToCallHandle(call);
    }

} // namespace FoundationSteamworks
