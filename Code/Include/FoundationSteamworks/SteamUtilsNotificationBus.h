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
    // SteamUtilsNotifications
    // Broadcasts for ISteamUtils callbacks.
    // ISteamUtils has no CallResults — all events are unsolicited callbacks.
    // -----------------------------------------------------------------------
    class SteamUtilsNotifications
    {
    public:
        AZ_RTTI(SteamUtilsNotifications, "{I9J1K2L3-5M6H-4IEK-HL1N-0M9J3K6I2L15}");
        virtual ~SteamUtilsNotifications() = default;

        /// Fired when the Steam overlay is activated or deactivated.
        virtual void OnGameOverlayActivated(bool active) {}

        /// Fired when Steam wants to shut down the game.
        virtual void OnSteamShutdown() {}

        /// Fired when the user's IP country changes.
        virtual void OnIPCountryChanged() {}

        /// Fired when the user's low battery warning changes.
        virtual void OnLowBatteryPower(AZ::u8 minutesBatteryLeft) {}

        /// Fired when the Steam server time changes.
        virtual void OnSteamAPICallCompleted(
            SteamCallHandle callHandle,
            AZ::s32 callback,
            bool ioFailure) {}

        /// Fired when floating keyboard is dismissed.
        virtual void OnFloatingGamepadTextInputDismissed() {}

        /// Fired when text filtering has finished.
        virtual void OnFilterTextDictionaryChanged(AZ::s32 language) {}
    };

    class SteamUtilsNotificationBusTraits : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
    };

    using SteamUtilsNotificationBus = AZ::EBus<SteamUtilsNotifications, SteamUtilsNotificationBusTraits>;

} // namespace Heathen