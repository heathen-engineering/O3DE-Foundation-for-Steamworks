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
#include "SteamCallResultInfrastructure.h"
#include "SteamTypeConverters.h"

#include <FoundationSteamworks/SteamTimelineNotificationBus.h>

#include <steam/steam_api.h>
#include <steam/isteamtimeline.h>

using namespace Heathen;

namespace FoundationSteamworks
{

    // -----------------------------------------------------------------------
    // SteamTimelineRequestBus — tooltip and bar colour
    // -----------------------------------------------------------------------

    void FoundationSteamworksSystemComponent::SetTimelineTooltip(const AZStd::string& description, float timeDelta)
    {
        if (m_steamInitialised && SteamTimeline())
            SteamTimeline()->SetTimelineTooltip(description.c_str(), timeDelta);
    }

    void FoundationSteamworksSystemComponent::ClearTimelineTooltip(float timeDelta)
    {
        if (m_steamInitialised && SteamTimeline())
            SteamTimeline()->ClearTimelineTooltip(timeDelta);
    }

    void FoundationSteamworksSystemComponent::SetTimelineGameMode(SteamTimelineGameMode mode)
    {
        if (m_steamInitialised && SteamTimeline())
            SteamTimeline()->SetTimelineGameMode(static_cast<ETimelineGameMode>(static_cast<AZ::s32>(mode)));
    }

    // -----------------------------------------------------------------------
    // SteamTimelineRequestBus — timeline events
    // -----------------------------------------------------------------------

    SteamTimelineEventHandle FoundationSteamworksSystemComponent::AddInstantaneousTimelineEvent(
        const AZStd::string& title,
        const AZStd::string& description,
        const AZStd::string& icon,
        AZ::u32 iconPriority,
        float startOffsetSeconds,
        SteamTimelineClipPriority clipPriority)
    {
        if (!m_steamInitialised || !SteamTimeline()) return 0;
        return static_cast<SteamTimelineEventHandle>(
            SteamTimeline()->AddInstantaneousTimelineEvent(
                title.c_str(), description.c_str(), icon.c_str(),
                static_cast<uint32>(iconPriority),
                startOffsetSeconds,
                static_cast<ETimelineEventClipPriority>(static_cast<AZ::s32>(clipPriority))));
    }

    SteamTimelineEventHandle FoundationSteamworksSystemComponent::AddRangeTimelineEvent(
        const AZStd::string& title,
        const AZStd::string& description,
        const AZStd::string& icon,
        AZ::u32 iconPriority,
        float startOffsetSeconds,
        float duration,
        SteamTimelineClipPriority clipPriority)
    {
        if (!m_steamInitialised || !SteamTimeline()) return 0;
        return static_cast<SteamTimelineEventHandle>(
            SteamTimeline()->AddRangeTimelineEvent(
                title.c_str(), description.c_str(), icon.c_str(),
                static_cast<uint32>(iconPriority),
                startOffsetSeconds,
                duration,
                static_cast<ETimelineEventClipPriority>(static_cast<AZ::s32>(clipPriority))));
    }

    SteamTimelineEventHandle FoundationSteamworksSystemComponent::StartRangeTimelineEvent(
        const AZStd::string& title,
        const AZStd::string& description,
        const AZStd::string& icon,
        AZ::u32 priority,
        float startOffsetSeconds,
        SteamTimelineClipPriority clipPriority)
    {
        if (!m_steamInitialised || !SteamTimeline()) return 0;
        return static_cast<SteamTimelineEventHandle>(
            SteamTimeline()->StartRangeTimelineEvent(
                title.c_str(), description.c_str(), icon.c_str(),
                static_cast<uint32>(priority),
                startOffsetSeconds,
                static_cast<ETimelineEventClipPriority>(static_cast<AZ::s32>(clipPriority))));
    }

    void FoundationSteamworksSystemComponent::UpdateRangeTimelineEvent(
        SteamTimelineEventHandle eventHandle,
        const AZStd::string& title,
        const AZStd::string& description,
        const AZStd::string& icon,
        AZ::u32 priority,
        SteamTimelineClipPriority clipPriority)
    {
        if (!m_steamInitialised || !SteamTimeline()) return;
        SteamTimeline()->UpdateRangeTimelineEvent(
            static_cast<TimelineEventHandle_t>(eventHandle),
            title.c_str(), description.c_str(), icon.c_str(),
            static_cast<uint32>(priority),
            static_cast<ETimelineEventClipPriority>(static_cast<AZ::s32>(clipPriority)));
    }

    void FoundationSteamworksSystemComponent::EndRangeTimelineEvent(SteamTimelineEventHandle eventHandle, float endOffsetSeconds)
    {
        if (m_steamInitialised && SteamTimeline())
            SteamTimeline()->EndRangeTimelineEvent(static_cast<TimelineEventHandle_t>(eventHandle), endOffsetSeconds);
    }

    void FoundationSteamworksSystemComponent::RemoveTimelineEvent(SteamTimelineEventHandle eventHandle)
    {
        if (m_steamInitialised && SteamTimeline())
            SteamTimeline()->RemoveTimelineEvent(static_cast<TimelineEventHandle_t>(eventHandle));
    }

    SteamCallHandle FoundationSteamworksSystemComponent::DoesEventRecordingExist(SteamTimelineEventHandle eventHandle)
    {
        if (!m_steamInitialised || !SteamTimeline()) return 0;
        SteamAPICall_t call = SteamTimeline()->DoesEventRecordingExist(static_cast<TimelineEventHandle_t>(eventHandle));
        m_callResults->Register<SteamTimelineEventRecordingExists_t>(call,
            [](SteamCallHandle h, SteamTimelineEventRecordingExists_t* p, bool /*ioFail*/)
            {
                SteamTimelineNotificationBus::Broadcast(
                    &SteamTimelineNotifications::OnTimelineEventRecordingExists,
                    h,
                    static_cast<SteamTimelineEventHandle>(p->m_ulEventID),
                    p->m_bRecordingExists);
            });
        return ToCallHandle(call);
    }

    // -----------------------------------------------------------------------
    // SteamTimelineRequestBus — game phases
    // -----------------------------------------------------------------------

    void FoundationSteamworksSystemComponent::StartGamePhase()
    {
        if (m_steamInitialised && SteamTimeline())
            SteamTimeline()->StartGamePhase();
    }

    void FoundationSteamworksSystemComponent::EndGamePhase()
    {
        if (m_steamInitialised && SteamTimeline())
            SteamTimeline()->EndGamePhase();
    }

    void FoundationSteamworksSystemComponent::SetGamePhaseID(const AZStd::string& phaseId)
    {
        if (m_steamInitialised && SteamTimeline())
            SteamTimeline()->SetGamePhaseID(phaseId.c_str());
    }

    SteamCallHandle FoundationSteamworksSystemComponent::DoesGamePhaseRecordingExist(const AZStd::string& phaseId)
    {
        if (!m_steamInitialised || !SteamTimeline()) return 0;
        SteamAPICall_t call = SteamTimeline()->DoesGamePhaseRecordingExist(phaseId.c_str());
        // Capture phaseId by value for the lambda — the SDK doesn't echo it back in the struct.
        m_callResults->Register<SteamTimelineGamePhaseRecordingExists_t>(call,
            [phaseId](SteamCallHandle h, SteamTimelineGamePhaseRecordingExists_t* p, bool /*ioFail*/)
            {
                SteamTimelineNotificationBus::Broadcast(
                    &SteamTimelineNotifications::OnTimelineGamePhaseRecordingExists,
                    h,
                    phaseId,
                    static_cast<AZ::u64>(p->m_ulRecordingMS),
                    static_cast<AZ::u64>(p->m_ulLongestClipMS),
                    static_cast<AZ::u32>(p->m_unClipCount),
                    static_cast<AZ::u32>(p->m_unScreenshotCount));
            });
        return ToCallHandle(call);
    }

    void FoundationSteamworksSystemComponent::AddGamePhaseTag(
        const AZStd::string& tagName,
        const AZStd::string& tagIcon,
        const AZStd::string& tagGroup,
        AZ::u32 priority)
    {
        if (m_steamInitialised && SteamTimeline())
            SteamTimeline()->AddGamePhaseTag(tagName.c_str(), tagIcon.c_str(), tagGroup.c_str(), static_cast<uint32>(priority));
    }

    void FoundationSteamworksSystemComponent::SetGamePhaseAttribute(
        const AZStd::string& attributeGroup,
        const AZStd::string& attributeValue,
        AZ::u32 priority)
    {
        if (m_steamInitialised && SteamTimeline())
            SteamTimeline()->SetGamePhaseAttribute(attributeGroup.c_str(), attributeValue.c_str(), static_cast<uint32>(priority));
    }

    // -----------------------------------------------------------------------
    // SteamTimelineRequestBus — overlay
    // -----------------------------------------------------------------------

    void FoundationSteamworksSystemComponent::OpenOverlayToGamePhase(const AZStd::string& phaseId)
    {
        if (m_steamInitialised && SteamTimeline())
            SteamTimeline()->OpenOverlayToGamePhase(phaseId.c_str());
    }

    void FoundationSteamworksSystemComponent::OpenOverlayToTimelineEvent(SteamTimelineEventHandle eventHandle)
    {
        if (m_steamInitialised && SteamTimeline())
            SteamTimeline()->OpenOverlayToTimelineEvent(static_cast<TimelineEventHandle_t>(eventHandle));
    }

} // namespace FoundationSteamworks
