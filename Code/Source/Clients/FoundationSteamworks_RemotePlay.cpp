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
#include <steam/isteamremoteplay.h>

using namespace Heathen;

namespace FoundationSteamworks
{

    // -----------------------------------------------------------------------
    // SteamRemotePlayRequestBus
    // -----------------------------------------------------------------------

    AZ::u32 FoundationSteamworksSystemComponent::GetSessionCount()
    {
        return m_steamInitialised && SteamRemotePlay() ? SteamRemotePlay()->GetSessionCount() : 0;
    }

    AZ::u32 FoundationSteamworksSystemComponent::GetSessionID(AZ::u32 index)
    {
        return m_steamInitialised && SteamRemotePlay() ? SteamRemotePlay()->GetSessionID(index) : 0;
    }

    SteamId FoundationSteamworksSystemComponent::GetSessionSteamID(AZ::u32 sessionId)
    {
        return m_steamInitialised && SteamRemotePlay() ? ToSteamId(SteamRemotePlay()->GetSessionSteamID(sessionId)) : 0;
    }

    AZStd::string FoundationSteamworksSystemComponent::GetSessionClientName(AZ::u32 sessionId)
    {
        if (!m_steamInitialised || !SteamRemotePlay()) return {};
        const char* name = SteamRemotePlay()->GetSessionClientName(sessionId);
        return name ? AZStd::string(name) : AZStd::string{};
    }

    AZ::s32 FoundationSteamworksSystemComponent::GetSessionClientFormFactor(AZ::u32 sessionId)
    {
        return m_steamInitialised && SteamRemotePlay()
            ? static_cast<AZ::s32>(SteamRemotePlay()->GetSessionClientFormFactor(sessionId)) : 0;
    }

    bool FoundationSteamworksSystemComponent::GetSessionClientResolution(AZ::u32 sessionId, AZ::s32& outWidth, AZ::s32& outHeight)
    {
        if (!m_steamInitialised || !SteamRemotePlay()) return false;
        int w = 0, h = 0;
        bool ok = SteamRemotePlay()->BGetSessionClientResolution(sessionId, &w, &h);
        if (ok) { outWidth = w; outHeight = h; }
        return ok;
    }

    bool FoundationSteamworksSystemComponent::SendRemotePlayTogetherInvite(SteamId friendId)
    {
        return m_steamInitialised && SteamRemotePlay() && SteamRemotePlay()->BSendRemotePlayTogetherInvite(FromSteamId(friendId));
    }

} // namespace FoundationSteamworks
