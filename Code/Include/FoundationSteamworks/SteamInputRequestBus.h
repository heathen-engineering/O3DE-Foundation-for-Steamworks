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
    class SteamInputRequests
    {
    public:
        AZ_RTTI(SteamInputRequests, "{K5L6M7N8-O9P0-4Q1R-S2T3-U4V5W6X7Y8Z9}");
        virtual ~SteamInputRequests() = default;

        // --- Device enumeration ---
        virtual AZStd::vector<AZ::u64> GetConnectedControllers() { return {}; }
        virtual void EnableDeviceCallbacks() {}

        // --- Action sets ---
        virtual AZ::u64 GetActionSetHandle(const AZStd::string& actionSetName) { return 0; }
        virtual void ActivateActionSet(AZ::u64 inputHandle, AZ::u64 actionSetHandle) {}
        virtual AZ::u64 GetCurrentActionSet(AZ::u64 inputHandle) { return 0; }
        virtual void ActivateActionSetLayer(AZ::u64 inputHandle, AZ::u64 actionSetLayerHandle) {}
        virtual void DeactivateActionSetLayer(AZ::u64 inputHandle, AZ::u64 actionSetLayerHandle) {}
        virtual void DeactivateAllActionSetLayers(AZ::u64 inputHandle) {}
        virtual AZStd::vector<AZ::u64> GetActiveActionSetLayers(AZ::u64 inputHandle) { return {}; }

        // --- Digital actions ---
        virtual AZ::u64 GetDigitalActionHandle(const AZStd::string& actionName) { return 0; }
        virtual SteamInputDigitalActionData GetDigitalActionData(AZ::u64 inputHandle, AZ::u64 digitalActionHandle) { return {}; }
        virtual AZStd::string GetStringForDigitalActionName(AZ::u64 actionHandle) { return {}; }

        // --- Analog actions ---
        virtual AZ::u64 GetAnalogActionHandle(const AZStd::string& actionName) { return 0; }
        virtual SteamInputAnalogActionData GetAnalogActionData(AZ::u64 inputHandle, AZ::u64 analogActionHandle) { return {}; }
        virtual AZStd::string GetStringForAnalogActionName(AZ::u64 actionHandle) { return {}; }

        // --- Haptics / LED ---
        virtual void TriggerVibration(AZ::u64 inputHandle, AZ::u16 leftSpeed, AZ::u16 rightSpeed) {}
        virtual void TriggerVibrationExtended(AZ::u64 inputHandle, AZ::u16 leftSpeed, AZ::u16 rightSpeed, AZ::u16 leftTriggerSpeed, AZ::u16 rightTriggerSpeed) {}
        virtual void SetLEDColor(AZ::u64 inputHandle, AZ::u8 r, AZ::u8 g, AZ::u8 b, AZ::u32 flags) {}

        // --- Misc ---
        virtual bool ShowBindingPanel(AZ::u64 inputHandle) { return false; }
        virtual AZ::s32 GetInputTypeForHandle(AZ::u64 inputHandle) { return 0; }
        virtual AZ::u64 GetControllerForGamepadIndex(AZ::s32 index) { return 0; }
        virtual AZ::s32 GetGamepadIndexForController(AZ::u64 inputHandle) { return -1; }
        virtual AZ::u32 GetRemotePlaySessionID(AZ::u64 inputHandle) { return 0; }
    };

    class SteamInputBusTraits : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
    };

    using SteamInputRequestBus = AZ::EBus<SteamInputRequests, SteamInputBusTraits>;
} // namespace Heathen
