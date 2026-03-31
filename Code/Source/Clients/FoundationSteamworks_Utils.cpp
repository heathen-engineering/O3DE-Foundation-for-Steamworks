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
#include <steam/isteamutils.h>

using namespace Heathen;

namespace FoundationSteamworks
{

    // -----------------------------------------------------------------------
    // SteamUtilsRequestBus
    // -----------------------------------------------------------------------

    AZ::u32 FoundationSteamworksSystemComponent::GetServerRealTime()
    {
        return m_steamInitialised && SteamUtils() ? SteamUtils()->GetServerRealTime() : 0;
    }

    AZStd::string FoundationSteamworksSystemComponent::GetIPCountry()
    {
        if (!m_steamInitialised || !SteamUtils()) return {};
        const char* cc = SteamUtils()->GetIPCountry();
        return cc ? AZStd::string(cc) : AZStd::string{};
    }

    AZStd::string FoundationSteamworksSystemComponent::GetSteamUILanguage()
    {
        if (!m_steamInitialised || !SteamUtils()) return {};
        const char* lang = SteamUtils()->GetSteamUILanguage();
        return lang ? AZStd::string(lang) : AZStd::string{};
    }

    bool FoundationSteamworksSystemComponent::GetImageSize(AZ::s32 imageHandle, AZ::u32& outWidth, AZ::u32& outHeight)
    {
        if (!m_steamInitialised || !SteamUtils()) return false;
        uint32 w = 0, h = 0;
        bool ok = SteamUtils()->GetImageSize(imageHandle, &w, &h);
        if (ok) { outWidth = w; outHeight = h; }
        return ok;
    }

    bool FoundationSteamworksSystemComponent::GetImageRGBA(AZ::s32 imageHandle, AZStd::vector<AZ::u8>& outData, AZ::u32 width, AZ::u32 height)
    {
        if (!m_steamInitialised || !SteamUtils()) return false;
        outData.resize(static_cast<size_t>(width) * height * 4);
        return SteamUtils()->GetImageRGBA(imageHandle, outData.data(), static_cast<int>(outData.size()));
    }

    bool FoundationSteamworksSystemComponent::IsOverlayEnabled()
    {
        return m_steamInitialised && SteamUtils() && SteamUtils()->IsOverlayEnabled();
    }

    bool FoundationSteamworksSystemComponent::IsSteamInBigPictureMode()
    {
        return m_steamInitialised && SteamUtils() && SteamUtils()->IsSteamInBigPictureMode();
    }

    bool FoundationSteamworksSystemComponent::IsSteamRunningOnSteamDeck()
    {
        return m_steamInitialised && SteamUtils() && SteamUtils()->IsSteamRunningOnSteamDeck();
    }

    bool FoundationSteamworksSystemComponent::IsSteamRunningInVR()
    {
        return m_steamInitialised && SteamUtils() && SteamUtils()->IsSteamRunningInVR();
    }

    bool FoundationSteamworksSystemComponent::ShowFloatingGamepadTextInput(AZ::s32 inputMode, AZ::s32 x, AZ::s32 y, AZ::s32 width, AZ::s32 height)
    {
        return m_steamInitialised && SteamUtils()
            && SteamUtils()->ShowFloatingGamepadTextInput(static_cast<EFloatingGamepadTextInputMode>(inputMode), x, y, width, height);
    }

    bool FoundationSteamworksSystemComponent::DismissFloatingGamepadTextInput()
    {
        return m_steamInitialised && SteamUtils() && SteamUtils()->DismissFloatingGamepadTextInput();
    }

    bool FoundationSteamworksSystemComponent::FilterText(AZ::s32 context, SteamId sourceSteamId, const AZStd::string& inputMessage, AZStd::string& outFiltered)
    {
        if (!m_steamInitialised || !SteamUtils()) return false;
        char buf[2048] = {};
        bool ok = SteamUtils()->FilterText(static_cast<ETextFilteringContext>(context), FromSteamId(sourceSteamId), inputMessage.c_str(), buf, sizeof(buf));
        if (ok) outFiltered = AZStd::string(buf);
        return ok;
    }

    AZ::u8 FoundationSteamworksSystemComponent::GetCurrentBatteryPower()
    {
        return m_steamInitialised && SteamUtils() ? SteamUtils()->GetCurrentBatteryPower() : 255;
    }

    bool FoundationSteamworksSystemComponent::IsSteamChinaLauncher()
    {
        return m_steamInitialised && SteamUtils() && SteamUtils()->IsSteamChinaLauncher();
    }

} // namespace FoundationSteamworks
