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
#include <FoundationSteamworks/SteamTypes.h>

namespace Heathen
{
    // -----------------------------------------------------------------------
    // SteamTimelineNotifications
    // Broadcasts for the two ISteamTimeline async call-result responses.
    // There are no push-style callbacks in the Timeline API — only these two
    // async query completions.
    // -----------------------------------------------------------------------
    class SteamTimelineNotifications
    {
    public:
        AZ_RTTI(SteamTimelineNotifications, "{2B3C4D5E-6F7A-4B8C-9D0E-F1A2B3C4D5E6}");
        virtual ~SteamTimelineNotifications() = default;

        /// Fired when DoesEventRecordingExist completes.
        /// callHandle:       The handle returned by DoesEventRecordingExist for matching.
        /// eventHandle:      The timeline event handle that was queried.
        /// recordingExists:  True if a recording exists for this event.
        virtual void OnTimelineEventRecordingExists(
            SteamCallHandle callHandle,
            SteamTimelineEventHandle eventHandle,
            bool recordingExists) {}

        /// Fired when DoesGamePhaseRecordingExist completes.
        /// callHandle:      The handle returned by DoesGamePhaseRecordingExist for matching.
        /// phaseId:         The phase ID that was queried.
        /// recordingMs:     Total duration of the recording in milliseconds.
        /// longestClipMs:   Duration of the longest available clip in milliseconds.
        /// clipCount:       Number of clips available for this phase.
        /// screenshotCount: Number of screenshots taken during this phase.
        virtual void OnTimelineGamePhaseRecordingExists(
            SteamCallHandle callHandle,
            const AZStd::string& phaseId,
            AZ::u64 recordingMs,
            AZ::u64 longestClipMs,
            AZ::u32 clipCount,
            AZ::u32 screenshotCount) {}
    };

    class SteamTimelineNotificationBusTraits : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
    };

    using SteamTimelineNotificationBus = AZ::EBus<SteamTimelineNotifications, SteamTimelineNotificationBusTraits>;

} // namespace Heathen
