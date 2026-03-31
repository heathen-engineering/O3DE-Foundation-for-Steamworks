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
    // SteamScreenshotsRequests
    // Request bus wrapping ISteamScreenshots.
    // -----------------------------------------------------------------------
    class SteamScreenshotsRequests
    {
    public:
        AZ_RTTI(SteamScreenshotsRequests, "{DAEBFCA0-B1C2-4D3G-H567-H8I9DAEBFCA1}");
        virtual ~SteamScreenshotsRequests() = default;

        /// Triggers a screenshot using the game's own screenshot hook.
        /// Call this in response to OnScreenshotRequested when hooking screenshots.
        virtual void TriggerScreenshot() {}

        /// Writes a raw RGBA screenshot to the Steam screenshot library.
        /// data: RGBA8 pixel buffer, width * height * 4 bytes.
        /// Returns a handle (0 = failure) that is also reported via OnScreenshotReady.
        virtual AZ::u32 WriteScreenshot(
            const AZStd::vector<AZ::u8>& data,
            AZ::u32 width,
            AZ::u32 height) { return 0; }

        /// Adds a screenshot from an on-disk JPEG or PNG file.
        /// Returns a handle (0 = failure).
        virtual AZ::u32 AddScreenshotToLibrary(
            const AZStd::string& fileName,
            const AZStd::string& thumbnailFileName,
            AZ::u32 width,
            AZ::u32 height) { return 0; }

        /// Attaches a user-visible caption string to an existing screenshot handle.
        virtual bool SetScreenshotCaption(AZ::u32 screenshotHandle, const AZStd::string& caption) { return false; }

        /// Associates a tagged user with an existing screenshot.
        virtual bool TagUser(AZ::u32 screenshotHandle, SteamId userId) { return false; }

        /// Associates a tagged published file with an existing screenshot.
        virtual bool TagPublishedFile(AZ::u32 screenshotHandle, SteamPublishedFileId publishedFileId) { return false; }

        /// Returns true if the user has the screenshot sharing UI open.
        virtual bool IsScreenshotsHooked() { return false; }

        /// Enables or disables the automatic screenshot capture hook.
        /// When enabled, OnScreenshotRequested fires instead of Steam capturing automatically.
        virtual void HookScreenshots(bool hook) {}
    };

    class SteamScreenshotsRequestBusTraits : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
    };

    using SteamScreenshotsRequestBus = AZ::EBus<SteamScreenshotsRequests, SteamScreenshotsRequestBusTraits>;

} // namespace Heathen