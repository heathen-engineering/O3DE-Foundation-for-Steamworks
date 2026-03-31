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
    // SteamInputNotifications
    // Broadcasts for ISteamInput callbacks.
    // ISteamController is deprecated — ISteamInput is the current API.
    // -----------------------------------------------------------------------
    class SteamInputNotifications
    {
    public:
        AZ_RTTI(SteamInputNotifications, "{J0K2L3M4-6N7I-4JFL-IM2O-1N0K4L7J3M16}");
        virtual ~SteamInputNotifications() = default;

        /// Fired when a controller is connected.
        /// inputHandle is the ISteamInput InputHandle_t (wrapped as u64).
        virtual void OnSteamInputDeviceConnected(AZ::u64 inputHandle) {}

        /// Fired when a controller is disconnected.
        virtual void OnSteamInputDeviceDisconnected(AZ::u64 inputHandle) {}

        /// Fired when the Steam Input configuration is loaded for a device.
        virtual void OnSteamInputConfigurationLoaded(
            SteamAppId appId,
            AZ::u64 deviceHandle) {}

        /// Fired when the Steam Input game-pad slot changes for a device.
        virtual void OnSteamInputGamepadSlotChange(
            SteamAppId appId,
            AZ::s32 slotIndex,
            AZ::s32 deviceType,
            AZ::u64 deviceHandle) {}
    };

    class SteamInputNotificationBusTraits : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
    };

    using SteamInputNotificationBus = AZ::EBus<SteamInputNotifications, SteamInputNotificationBusTraits>;

} // namespace Heathen