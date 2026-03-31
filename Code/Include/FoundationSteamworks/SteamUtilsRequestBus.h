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
    // SteamUtilsRequests
    // Request bus wrapping ISteamUtils.
    // Miscellaneous utility methods: time, country, image decoding, overlay.
    // -----------------------------------------------------------------------
    class SteamUtilsRequests
    {
    public:
        AZ_RTTI(SteamUtilsRequests, "{C9DAEBFC-A0B1-4C2F-G456-G7H8C9DAEBFD}");
        virtual ~SteamUtilsRequests() = default;

        // --- Time ---

        /// Returns the current Steam server Unix timestamp.
        virtual AZ::u32 GetServerRealTime() { return 0; }

        // --- Country / Language ---

        /// Returns the 2-letter ISO 3166-1 alpha-2 country code for the user (e.g. "US", "GB").
        virtual AZStd::string GetIPCountry() { return {}; }

        /// Returns the Steam UI language (e.g. "english", "german").
        virtual AZStd::string GetSteamUILanguage() { return {}; }

        // --- Image Decoding ---

        /// Returns the dimensions (width and height) of an image referenced by its handle.
        virtual bool GetImageSize(AZ::s32 imageHandle, AZ::u32& outWidth, AZ::u32& outHeight) { return false; }

        /// Decodes an image from the Steam image cache into an RGBA8 byte buffer.
        /// outData will be resized to width * height * 4 bytes.
        virtual bool GetImageRGBA(AZ::s32 imageHandle, AZStd::vector<AZ::u8>& outData, AZ::u32 width, AZ::u32 height) { return false; }

        // --- App / Overlay ---

        /// Returns true if the Steam overlay is running and the user can access it.
        virtual bool IsOverlayEnabled() { return false; }

        /// Returns true if Steam is running in Big Picture mode.
        virtual bool IsSteamInBigPictureMode() { return false; }

        /// Returns true if Steam is running on a Steam Deck.
        virtual bool IsSteamRunningOnSteamDeck() { return false; }

        /// Returns true if the Steam client is running in VR mode.
        virtual bool IsSteamRunningInVR() { return false; }

        // --- Floating Keyboard ---

        /// Shows the floating on-screen keyboard for text input.
        /// inputMode: EFloatingGamepadTextInputMode cast to s32 (e.g. 0 = SingleLine, 1 = MultiLine).
        /// Returns false if the floating keyboard is not available on this platform.
        virtual bool ShowFloatingGamepadTextInput(
            AZ::s32 inputMode,
            AZ::s32 textFieldXPosition,
            AZ::s32 textFieldYPosition,
            AZ::s32 textFieldWidth,
            AZ::s32 textFieldHeight) { return false; }

        /// Dismisses the floating keyboard.
        virtual bool DismissFloatingGamepadTextInput() { return false; }

        // --- Text Filtering ---

        /// Filters the given text according to local norms.
        /// context: ETextFilteringContext cast to s32.
        /// outFiltered receives the result; returns true on success.
        virtual bool FilterText(AZ::s32 context, SteamId sourceSteamId, const AZStd::string& inputMessage, AZStd::string& outFiltered) { return false; }

        // --- Misc ---

        /// Returns the battery power level [0..100] or 255 if plugged in / unknown.
        virtual AZ::u8 GetCurrentBatteryPower() { return 255; }

        /// Returns true if the current launcher type matches.
        /// launcherType: EGamepadTextInputLineMode cast to s32.
        virtual bool IsSteamChinaLauncher() { return false; }
    };

    class SteamUtilsRequestBusTraits : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
    };

    using SteamUtilsRequestBus = AZ::EBus<SteamUtilsRequests, SteamUtilsRequestBusTraits>;

} // namespace Heathen