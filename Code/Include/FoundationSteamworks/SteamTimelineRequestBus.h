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
    // SteamTimelineRequests
    // Request bus wrapping ISteamTimeline.
    // All methods silently no-op if the Steam client API is not initialised
    // or if the user's Steam client does not support Timeline (pre-2024 clients).
    // -----------------------------------------------------------------------
    class SteamTimelineRequests
    {
    public:
        AZ_RTTI(SteamTimelineRequests, "{1A2B3C4D-5E6F-4A7B-8C9D-E0F1A2B3C4D5}");
        virtual ~SteamTimelineRequests() = default;

        // --- Tooltip and bar colour ---

        /// Sets a text description shown when the user hovers over the timeline bar.
        /// description: Localised string in the language from SteamUtils()->GetSteamUILanguage().
        /// timeDelta:   Seconds offset from now (negative = past).
        virtual void SetTimelineTooltip(const AZStd::string& description, float timeDelta) {}

        /// Clears any previously set tooltip.
        /// timeDelta: Seconds offset from now.
        virtual void ClearTimelineTooltip(float timeDelta) {}

        /// Sets the colour / mode of the timeline bar.
        virtual void SetTimelineGameMode(SteamTimelineGameMode mode) {}

        // --- Timeline events ---

        /// Adds a zero-duration (instantaneous) marker to the timeline.
        /// Returns a handle that can be passed to DoesEventRecordingExist, or 0 on failure.
        virtual SteamTimelineEventHandle AddInstantaneousTimelineEvent(
            const AZStd::string& title,
            const AZStd::string& description,
            const AZStd::string& icon,
            AZ::u32 iconPriority,
            float startOffsetSeconds,
            SteamTimelineClipPriority clipPriority) { return 0; }

        /// Adds a time-range marker to the timeline in a single call (closed immediately).
        /// Returns a handle, or 0 on failure.
        virtual SteamTimelineEventHandle AddRangeTimelineEvent(
            const AZStd::string& title,
            const AZStd::string& description,
            const AZStd::string& icon,
            AZ::u32 iconPriority,
            float startOffsetSeconds,
            float duration,
            SteamTimelineClipPriority clipPriority) { return 0; }

        /// Starts an open-ended range event. Must be closed with EndRangeTimelineEvent.
        /// Returns a handle for the open event, or 0 on failure.
        virtual SteamTimelineEventHandle StartRangeTimelineEvent(
            const AZStd::string& title,
            const AZStd::string& description,
            const AZStd::string& icon,
            AZ::u32 priority,
            float startOffsetSeconds,
            SteamTimelineClipPriority clipPriority) { return 0; }

        /// Updates the display fields of an open range event started with StartRangeTimelineEvent.
        virtual void UpdateRangeTimelineEvent(
            SteamTimelineEventHandle eventHandle,
            const AZStd::string& title,
            const AZStd::string& description,
            const AZStd::string& icon,
            AZ::u32 priority,
            SteamTimelineClipPriority clipPriority) {}

        /// Closes an open range event and submits it to the timeline.
        /// endOffsetSeconds: Seconds offset from now for the end time.
        virtual void EndRangeTimelineEvent(SteamTimelineEventHandle eventHandle, float endOffsetSeconds) {}

        /// Removes a previously created timeline event.
        virtual void RemoveTimelineEvent(SteamTimelineEventHandle eventHandle) {}

        /// Asynchronously queries whether a recording exists for a timeline event.
        /// Returns a SteamCallHandle for matching the result in OnTimelineEventRecordingExists,
        /// or 0 if the request could not be issued.
        virtual SteamCallHandle DoesEventRecordingExist(SteamTimelineEventHandle eventHandle) { return 0; }

        // --- Game phases ---

        /// Starts a new game phase. If one is already active it is ended first.
        virtual void StartGamePhase() {}

        /// Ends the current game phase.
        virtual void EndGamePhase() {}

        /// Sets a persistent ID for the current phase so it can be referenced later.
        virtual void SetGamePhaseID(const AZStd::string& phaseId) {}

        /// Asynchronously queries whether a recording exists for a game phase.
        /// Returns a SteamCallHandle for matching the result in OnTimelineGamePhaseRecordingExists,
        /// or 0 if the request could not be issued.
        virtual SteamCallHandle DoesGamePhaseRecordingExist(const AZStd::string& phaseId) { return 0; }

        /// Adds a tag that applies to the entire current game phase.
        virtual void AddGamePhaseTag(
            const AZStd::string& tagName,
            const AZStd::string& tagIcon,
            const AZStd::string& tagGroup,
            AZ::u32 priority) {}

        /// Sets a text attribute that applies to the entire current game phase.
        /// Calling this multiple times with the same group overwrites the previous value.
        virtual void SetGamePhaseAttribute(
            const AZStd::string& attributeGroup,
            const AZStd::string& attributeValue,
            AZ::u32 priority) {}

        // --- Overlay ---

        /// Opens the Steam overlay to a previously recorded game phase.
        virtual void OpenOverlayToGamePhase(const AZStd::string& phaseId) {}

        /// Opens the Steam overlay to a specific timeline event.
        virtual void OpenOverlayToTimelineEvent(SteamTimelineEventHandle eventHandle) {}
    };

    class SteamTimelineRequestBusTraits : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
    };

    using SteamTimelineRequestBus = AZ::EBus<SteamTimelineRequests, SteamTimelineRequestBusTraits>;

} // namespace Heathen
