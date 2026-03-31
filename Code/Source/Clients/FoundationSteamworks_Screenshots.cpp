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

#include <steam/steam_api.h>
#include <steam/isteamscreenshots.h>

using namespace Heathen;

namespace FoundationSteamworks
{

    // -----------------------------------------------------------------------
    // SteamScreenshotsRequestBus
    // -----------------------------------------------------------------------

    void FoundationSteamworksSystemComponent::TriggerScreenshot()
    {
        if (m_steamInitialised && SteamScreenshots())
            SteamScreenshots()->TriggerScreenshot();
    }

    AZ::u32 FoundationSteamworksSystemComponent::WriteScreenshot(const AZStd::vector<AZ::u8>& data, AZ::u32 width, AZ::u32 height)
    {
        if (!m_steamInitialised || !SteamScreenshots() || data.empty()) return 0;
        return static_cast<AZ::u32>(SteamScreenshots()->WriteScreenshot(
            const_cast<void*>(static_cast<const void*>(data.data())),
            static_cast<uint32>(data.size()), static_cast<int>(width), static_cast<int>(height)));
    }

    AZ::u32 FoundationSteamworksSystemComponent::AddScreenshotToLibrary(const AZStd::string& fileName, const AZStd::string& thumbnailFileName, AZ::u32 width, AZ::u32 height)
    {
        if (!m_steamInitialised || !SteamScreenshots()) return 0;
        const char* thumb = thumbnailFileName.empty() ? nullptr : thumbnailFileName.c_str();
        return static_cast<AZ::u32>(SteamScreenshots()->AddScreenshotToLibrary(fileName.c_str(), thumb, static_cast<int>(width), static_cast<int>(height)));
    }

    bool FoundationSteamworksSystemComponent::SetScreenshotCaption(AZ::u32 screenshotHandle, const AZStd::string& caption)
    {
        return m_steamInitialised && SteamScreenshots()
            && SteamScreenshots()->SetLocation(static_cast<ScreenshotHandle>(screenshotHandle), caption.c_str());
    }

    bool FoundationSteamworksSystemComponent::TagUser(AZ::u32 screenshotHandle, SteamId userId)
    {
        return m_steamInitialised && SteamScreenshots()
            && SteamScreenshots()->TagUser(static_cast<ScreenshotHandle>(screenshotHandle), FromSteamId(userId));
    }

    bool FoundationSteamworksSystemComponent::TagPublishedFile(AZ::u32 screenshotHandle, SteamPublishedFileId publishedFileId)
    {
        return m_steamInitialised && SteamScreenshots()
            && SteamScreenshots()->TagPublishedFile(static_cast<ScreenshotHandle>(screenshotHandle), static_cast<PublishedFileId_t>(publishedFileId));
    }

    bool FoundationSteamworksSystemComponent::IsScreenshotsHooked()
    {
        return m_steamInitialised && SteamScreenshots() && SteamScreenshots()->IsScreenshotsHooked();
    }

    void FoundationSteamworksSystemComponent::HookScreenshots(bool hook)
    {
        if (m_steamInitialised && SteamScreenshots())
            SteamScreenshots()->HookScreenshots(hook);
    }

} // namespace FoundationSteamworks
