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
#include "SteamCallResultInfrastructure.h"

#include <steam/steam_api.h>
#include <steam/isteaminventory.h>
#include <FoundationSteamworks/SteamInventoryNotificationBus.h>

using namespace Heathen;

namespace FoundationSteamworks
{
    // -----------------------------------------------------------------------
    // SteamInventoryRequestBus
    // -----------------------------------------------------------------------

    void FoundationSteamworksSystemComponent::DestroyResult(SteamInventoryResultHandle resultHandle)
    {
        if (m_steamInitialised && SteamInventory())
            SteamInventory()->DestroyResult(static_cast<SteamInventoryResult_t>(resultHandle));
    }

    SteamResult FoundationSteamworksSystemComponent::GetResultStatus(SteamInventoryResultHandle resultHandle)
    {
        if (!m_steamInitialised || !SteamInventory()) return SteamResult::Fail;
        return ToSteamResult(SteamInventory()->GetResultStatus(static_cast<SteamInventoryResult_t>(resultHandle)));
    }

    AZ::u32 FoundationSteamworksSystemComponent::GetResultTimestamp(SteamInventoryResultHandle resultHandle)
    {
        return m_steamInitialised && SteamInventory()
            ? SteamInventory()->GetResultTimestamp(static_cast<SteamInventoryResult_t>(resultHandle)) : 0;
    }

    SteamInventoryResultHandle FoundationSteamworksSystemComponent::GetAllItems()
    {
        if (!m_steamInitialised || !SteamInventory()) return k_SteamInventoryResultInvalid;
        SteamInventoryResult_t result = k_SteamInventoryResultInvalid;
        SteamInventory()->GetAllItems(&result);
        return static_cast<SteamInventoryResultHandle>(result);
    }

    SteamInventoryResultHandle FoundationSteamworksSystemComponent::GetItemsByID(const AZStd::vector<SteamItemInstanceId>& instanceIds)
    {
        if (!m_steamInitialised || !SteamInventory() || instanceIds.empty()) return k_SteamInventoryResultInvalid;
        AZStd::vector<SteamItemInstanceID_t> ids;
        ids.reserve(instanceIds.size());
        for (auto id : instanceIds) ids.push_back(static_cast<SteamItemInstanceID_t>(id));
        SteamInventoryResult_t result = k_SteamInventoryResultInvalid;
        SteamInventory()->GetItemsByID(&result, ids.data(), static_cast<uint32>(ids.size()));
        return static_cast<SteamInventoryResultHandle>(result);
    }

    SteamInventoryResultHandle FoundationSteamworksSystemComponent::AddPromoItem(SteamItemDefId itemDefId)
    {
        if (!m_steamInitialised || !SteamInventory()) return k_SteamInventoryResultInvalid;
        SteamInventoryResult_t result = k_SteamInventoryResultInvalid;
        SteamInventory()->AddPromoItem(&result, static_cast<SteamItemDef_t>(itemDefId));
        return static_cast<SteamInventoryResultHandle>(result);
    }

    SteamInventoryResultHandle FoundationSteamworksSystemComponent::AddPromoItems(const AZStd::vector<SteamItemDefId>& itemDefIds)
    {
        if (!m_steamInitialised || !SteamInventory() || itemDefIds.empty()) return k_SteamInventoryResultInvalid;
        AZStd::vector<SteamItemDef_t> defs;
        defs.reserve(itemDefIds.size());
        for (auto id : itemDefIds) defs.push_back(static_cast<SteamItemDef_t>(id));
        SteamInventoryResult_t result = k_SteamInventoryResultInvalid;
        SteamInventory()->AddPromoItems(&result, defs.data(), static_cast<uint32>(defs.size()));
        return static_cast<SteamInventoryResultHandle>(result);
    }

    SteamInventoryResultHandle FoundationSteamworksSystemComponent::ConsumeItem(SteamItemInstanceId instanceId, AZ::u32 quantity)
    {
        if (!m_steamInitialised || !SteamInventory()) return k_SteamInventoryResultInvalid;
        SteamInventoryResult_t result = k_SteamInventoryResultInvalid;
        SteamInventory()->ConsumeItem(&result, static_cast<SteamItemInstanceID_t>(instanceId), quantity);
        return static_cast<SteamInventoryResultHandle>(result);
    }

    SteamInventoryResultHandle FoundationSteamworksSystemComponent::TransferItemQuantity(SteamItemInstanceId sourceId, AZ::u32 quantity, SteamItemInstanceId destId)
    {
        if (!m_steamInitialised || !SteamInventory()) return k_SteamInventoryResultInvalid;
        SteamInventoryResult_t result = k_SteamInventoryResultInvalid;
        SteamInventory()->TransferItemQuantity(&result, static_cast<SteamItemInstanceID_t>(sourceId), quantity, static_cast<SteamItemInstanceID_t>(destId));
        return static_cast<SteamInventoryResultHandle>(result);
    }

    SteamInventoryResultHandle FoundationSteamworksSystemComponent::GetAllItemsServer()
    {
        if (!m_steamInitialised || !SteamInventory()) return k_SteamInventoryResultInvalid;
        SteamInventoryResult_t result = k_SteamInventoryResultInvalid;
        SteamInventory()->GetAllItems(&result);
        return static_cast<SteamInventoryResultHandle>(result);
    }

    AZ::u32 FoundationSteamworksSystemComponent::GetNumItemDefinitions()
    {
        if (!m_steamInitialised || !SteamInventory()) return 0;
        uint32 count = 0;
        SteamInventory()->GetItemDefinitionIDs(nullptr, &count);
        return count;
    }

    AZStd::string FoundationSteamworksSystemComponent::GetItemDefinitionProperty(SteamItemDefId defId, const AZStd::string& propertyName)
    {
        if (!m_steamInitialised || !SteamInventory()) return {};
        uint32 bufLen = 0;
        if (!SteamInventory()->GetItemDefinitionProperty(static_cast<SteamItemDef_t>(defId), propertyName.c_str(), nullptr, &bufLen) || bufLen == 0)
            return {};
        AZStd::string result(bufLen, '\0');
        SteamInventory()->GetItemDefinitionProperty(static_cast<SteamItemDef_t>(defId), propertyName.c_str(), result.data(), &bufLen);
        result.resize(bufLen > 0 ? bufLen - 1 : 0); // trim null terminator
        return result;
    }

    bool FoundationSteamworksSystemComponent::LoadItemDefinitions()
    {
        return m_steamInitialised && SteamInventory() && SteamInventory()->LoadItemDefinitions();
    }

    SteamCallHandle FoundationSteamworksSystemComponent::StartPurchase(const AZStd::vector<SteamItemDefId>& itemDefIds, const AZStd::vector<AZ::u32>& quantities)
    {
        if (!m_steamInitialised || !SteamInventory() || itemDefIds.size() != quantities.size()) return 0;
        AZStd::vector<SteamItemDef_t> defs;
        defs.reserve(itemDefIds.size());
        for (auto id : itemDefIds) defs.push_back(static_cast<SteamItemDef_t>(id));
        SteamAPICall_t call = SteamInventory()->StartPurchase(defs.data(), quantities.data(), static_cast<uint32>(defs.size()));
        m_callResults->Register<SteamInventoryStartPurchaseResult_t>(call, [](SteamCallHandle h, SteamInventoryStartPurchaseResult_t* p, bool ioFail)
        {
            SteamInventoryNotificationBus::Broadcast(&SteamInventoryNotifications::OnSteamInventoryStartPurchaseResult,
                h, ToSteamResult(p->m_result), p->m_ulOrderID, p->m_ulTransID);
        });
        return ToCallHandle(call);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::RequestPrices()
    {
        if (!m_steamInitialised || !SteamInventory()) return 0;
        SteamAPICall_t call = SteamInventory()->RequestPrices();
        m_callResults->Register<SteamInventoryRequestPricesResult_t>(call, [](SteamCallHandle h, SteamInventoryRequestPricesResult_t* p, bool ioFail)
        {
            SteamInventoryNotificationBus::Broadcast(&SteamInventoryNotifications::OnSteamInventoryRequestPricesResult,
                h, ToSteamResult(p->m_result), AZStd::string(p->m_rgchCurrency));
        });
        return ToCallHandle(call);
    }

} // namespace FoundationSteamworks
