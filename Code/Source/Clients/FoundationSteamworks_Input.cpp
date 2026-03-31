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

#include <steam/steam_api.h>
#include <steam/isteaminput.h>

using namespace Heathen;

namespace FoundationSteamworks
{

    // -----------------------------------------------------------------------
    // SteamInputRequestBus
    // -----------------------------------------------------------------------

    AZStd::vector<AZ::u64> FoundationSteamworksSystemComponent::GetConnectedControllers()
    {
        AZStd::vector<AZ::u64> result;
        if (!m_inputInitialised) return result;
        InputHandle_t handles[STEAM_INPUT_MAX_COUNT];
        int count = SteamInput()->GetConnectedControllers(handles);
        result.reserve(static_cast<size_t>(count));
        for (int i = 0; i < count; ++i)
            result.push_back(static_cast<AZ::u64>(handles[i]));
        return result;
    }

    void FoundationSteamworksSystemComponent::EnableDeviceCallbacks()
    {
        if (m_inputInitialised) SteamInput()->EnableDeviceCallbacks();
    }

    AZ::u64 FoundationSteamworksSystemComponent::GetActionSetHandle(const AZStd::string& actionSetName)
    {
        return m_inputInitialised ? static_cast<AZ::u64>(SteamInput()->GetActionSetHandle(actionSetName.c_str())) : 0;
    }

    void FoundationSteamworksSystemComponent::ActivateActionSet(AZ::u64 inputHandle, AZ::u64 actionSetHandle)
    {
        if (m_inputInitialised)
            SteamInput()->ActivateActionSet(static_cast<InputHandle_t>(inputHandle), static_cast<InputActionSetHandle_t>(actionSetHandle));
    }

    AZ::u64 FoundationSteamworksSystemComponent::GetCurrentActionSet(AZ::u64 inputHandle)
    {
        return m_inputInitialised ? static_cast<AZ::u64>(SteamInput()->GetCurrentActionSet(static_cast<InputHandle_t>(inputHandle))) : 0;
    }

    void FoundationSteamworksSystemComponent::ActivateActionSetLayer(AZ::u64 inputHandle, AZ::u64 actionSetLayerHandle)
    {
        if (m_inputInitialised)
            SteamInput()->ActivateActionSetLayer(static_cast<InputHandle_t>(inputHandle), static_cast<InputActionSetHandle_t>(actionSetLayerHandle));
    }

    void FoundationSteamworksSystemComponent::DeactivateActionSetLayer(AZ::u64 inputHandle, AZ::u64 actionSetLayerHandle)
    {
        if (m_inputInitialised)
            SteamInput()->DeactivateActionSetLayer(static_cast<InputHandle_t>(inputHandle), static_cast<InputActionSetHandle_t>(actionSetLayerHandle));
    }

    void FoundationSteamworksSystemComponent::DeactivateAllActionSetLayers(AZ::u64 inputHandle)
    {
        if (m_inputInitialised)
            SteamInput()->DeactivateAllActionSetLayers(static_cast<InputHandle_t>(inputHandle));
    }

    AZStd::vector<AZ::u64> FoundationSteamworksSystemComponent::GetActiveActionSetLayers(AZ::u64 inputHandle)
    {
        AZStd::vector<AZ::u64> result;
        if (!m_inputInitialised) return result;
        InputActionSetHandle_t layers[STEAM_INPUT_MAX_ACTIVE_LAYERS];
        int count = SteamInput()->GetActiveActionSetLayers(static_cast<InputHandle_t>(inputHandle), layers);
        result.reserve(static_cast<size_t>(count));
        for (int i = 0; i < count; ++i)
            result.push_back(static_cast<AZ::u64>(layers[i]));
        return result;
    }

    AZ::u64 FoundationSteamworksSystemComponent::GetDigitalActionHandle(const AZStd::string& actionName)
    {
        return m_inputInitialised ? static_cast<AZ::u64>(SteamInput()->GetDigitalActionHandle(actionName.c_str())) : 0;
    }

    SteamInputDigitalActionData FoundationSteamworksSystemComponent::GetDigitalActionData(AZ::u64 inputHandle, AZ::u64 digitalActionHandle)
    {
        SteamInputDigitalActionData out;
        if (!m_inputInitialised) return out;
        InputDigitalActionData_t d = SteamInput()->GetDigitalActionData(
            static_cast<InputHandle_t>(inputHandle),
            static_cast<InputDigitalActionHandle_t>(digitalActionHandle));
        out.active = d.bActive;
        out.state  = d.bState;
        return out;
    }

    AZStd::string FoundationSteamworksSystemComponent::GetStringForDigitalActionName(AZ::u64 actionHandle)
    {
        if (!m_inputInitialised) return {};
        const char* name = SteamInput()->GetStringForDigitalActionName(static_cast<InputDigitalActionHandle_t>(actionHandle));
        return name ? AZStd::string(name) : AZStd::string();
    }

    AZ::u64 FoundationSteamworksSystemComponent::GetAnalogActionHandle(const AZStd::string& actionName)
    {
        return m_inputInitialised ? static_cast<AZ::u64>(SteamInput()->GetAnalogActionHandle(actionName.c_str())) : 0;
    }

    SteamInputAnalogActionData FoundationSteamworksSystemComponent::GetAnalogActionData(AZ::u64 inputHandle, AZ::u64 analogActionHandle)
    {
        SteamInputAnalogActionData out;
        if (!m_inputInitialised) return out;
        InputAnalogActionData_t d = SteamInput()->GetAnalogActionData(
            static_cast<InputHandle_t>(inputHandle),
            static_cast<InputAnalogActionHandle_t>(analogActionHandle));
        out.mode   = static_cast<AZ::s32>(d.eMode);
        out.x      = d.x;
        out.y      = d.y;
        out.active = d.bActive;
        return out;
    }

    AZStd::string FoundationSteamworksSystemComponent::GetStringForAnalogActionName(AZ::u64 actionHandle)
    {
        if (!m_inputInitialised) return {};
        const char* name = SteamInput()->GetStringForAnalogActionName(static_cast<InputAnalogActionHandle_t>(actionHandle));
        return name ? AZStd::string(name) : AZStd::string();
    }

    void FoundationSteamworksSystemComponent::TriggerVibration(AZ::u64 inputHandle, AZ::u16 leftSpeed, AZ::u16 rightSpeed)
    {
        if (m_inputInitialised)
            SteamInput()->TriggerVibration(static_cast<InputHandle_t>(inputHandle), leftSpeed, rightSpeed);
    }

    void FoundationSteamworksSystemComponent::TriggerVibrationExtended(AZ::u64 inputHandle, AZ::u16 leftSpeed, AZ::u16 rightSpeed, AZ::u16 leftTriggerSpeed, AZ::u16 rightTriggerSpeed)
    {
        if (m_inputInitialised)
            SteamInput()->TriggerVibrationExtended(static_cast<InputHandle_t>(inputHandle), leftSpeed, rightSpeed, leftTriggerSpeed, rightTriggerSpeed);
    }

    void FoundationSteamworksSystemComponent::SetLEDColor(AZ::u64 inputHandle, AZ::u8 r, AZ::u8 g, AZ::u8 b, AZ::u32 flags)
    {
        if (m_inputInitialised)
            SteamInput()->SetLEDColor(static_cast<InputHandle_t>(inputHandle), r, g, b, flags);
    }

    bool FoundationSteamworksSystemComponent::ShowBindingPanel(AZ::u64 inputHandle)
    {
        return m_inputInitialised && SteamInput()->ShowBindingPanel(static_cast<InputHandle_t>(inputHandle));
    }

    AZ::s32 FoundationSteamworksSystemComponent::GetInputTypeForHandle(AZ::u64 inputHandle)
    {
        return m_inputInitialised ? static_cast<AZ::s32>(SteamInput()->GetInputTypeForHandle(static_cast<InputHandle_t>(inputHandle))) : 0;
    }

    AZ::u64 FoundationSteamworksSystemComponent::GetControllerForGamepadIndex(AZ::s32 index)
    {
        return m_inputInitialised ? static_cast<AZ::u64>(SteamInput()->GetControllerForGamepadIndex(index)) : 0;
    }

    AZ::s32 FoundationSteamworksSystemComponent::GetGamepadIndexForController(AZ::u64 inputHandle)
    {
        return m_inputInitialised ? SteamInput()->GetGamepadIndexForController(static_cast<InputHandle_t>(inputHandle)) : -1;
    }

    AZ::u32 FoundationSteamworksSystemComponent::GetRemotePlaySessionID(AZ::u64 inputHandle)
    {
        return m_inputInitialised ? SteamInput()->GetRemotePlaySessionID(static_cast<InputHandle_t>(inputHandle)) : 0;
    }

} // namespace FoundationSteamworks
