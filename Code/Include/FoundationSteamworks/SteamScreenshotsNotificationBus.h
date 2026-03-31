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
    // SteamScreenshotsNotifications
    // Broadcasts for ISteamScreenshots callbacks.
    // -----------------------------------------------------------------------
    class SteamScreenshotsNotifications
    {
    public:
        AZ_RTTI(SteamScreenshotsNotifications, "{K1L3M4N5-7O8J-4KGM-JN3P-2O1L5M8K4N17}");
        virtual ~SteamScreenshotsNotifications() = default;

        /// Fired when a screenshot has been requested by the user or the API.
        /// Handle this to supply your own screenshot rather than the automatic capture.
        virtual void OnScreenshotRequested() {}

        /// Fired when a screenshot has been successfully taken and is ready.
        /// screenshotHandle is ScreenshotHandle (uint32) wrapped as AZ::u32.
        virtual void OnScreenshotReady(
            AZ::u32 screenshotHandle,
            SteamResult result) {}
    };

    class SteamScreenshotsNotificationBusTraits : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
    };

    using SteamScreenshotsNotificationBus = AZ::EBus<SteamScreenshotsNotifications, SteamScreenshotsNotificationBusTraits>;

} // namespace Heathen