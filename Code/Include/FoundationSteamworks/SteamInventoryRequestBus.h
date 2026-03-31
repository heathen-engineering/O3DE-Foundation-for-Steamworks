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
    // SteamInventoryRequests
    // Request bus wrapping ISteamInventory.
    // Result handles are returned via SteamInventoryResultHandle.
    // The SteamInventoryNotificationBus fires OnSteamInventoryResultReady
    // when the result is ready to be read with GetResultItems.
    // -----------------------------------------------------------------------
    class SteamInventoryRequests
    {
    public:
        AZ_RTTI(SteamInventoryRequests, "{A7B8C9DA-EBFC-4A0D-E234-E5F6A7B8C9DB}");
        virtual ~SteamInventoryRequests() = default;

        // --- Result Management ---

        /// Releases memory for a result handle obtained from any inventory call.
        virtual void DestroyResult(SteamInventoryResultHandle resultHandle) {}

        /// Returns the result status for a given result handle.
        virtual SteamResult GetResultStatus(SteamInventoryResultHandle resultHandle) { return SteamResult::Fail; }

        /// Returns the Unix timestamp at which the result was generated.
        virtual AZ::u32 GetResultTimestamp(SteamInventoryResultHandle resultHandle) { return 0; }

        // --- Item Queries ---

        /// Requests all items in the local user's inventory.
        /// The result is fired via OnSteamInventoryResultReady.
        virtual SteamInventoryResultHandle GetAllItems() { return -1; }

        /// Requests a specific set of items by instance ID.
        virtual SteamInventoryResultHandle GetItemsByID(const AZStd::vector<SteamItemInstanceId>& instanceIds) { return -1; }

        // --- Item Modification ---

        /// Grants a promotional item if the user is eligible.
        /// Triggered automatically — this is for forcing a check.
        virtual SteamInventoryResultHandle AddPromoItem(SteamItemDefId itemDefId) { return -1; }

        /// Grants a set of promotional items if eligible.
        virtual SteamInventoryResultHandle AddPromoItems(const AZStd::vector<SteamItemDefId>& itemDefIds) { return -1; }

        /// Consumes a quantity of a stackable item.
        virtual SteamInventoryResultHandle ConsumeItem(SteamItemInstanceId instanceId, AZ::u32 quantity) { return -1; }

        /// Transfers items between stacks (merge or partial move).
        virtual SteamInventoryResultHandle TransferItemQuantity(
            SteamItemInstanceId sourceId,
            AZ::u32 quantity,
            SteamItemInstanceId destId) { return -1; }

        // --- Serialisation (for server verification) ---

        /// Triggers a full inventory update from the Steam back-end.
        /// Fires OnSteamInventoryFullUpdate on completion.
        virtual SteamInventoryResultHandle GetAllItemsServer() { return -1; }

        // --- Item Definition Queries ---

        /// Returns the number of item definition IDs loaded for this app.
        virtual AZ::u32 GetNumItemDefinitions() { return 0; }

        /// Returns the string property value for a given item definition.
        virtual AZStd::string GetItemDefinitionProperty(SteamItemDefId defId, const AZStd::string& propertyName) { return {}; }

        /// Requests a fresh download of item definitions from Steam.
        /// Fires OnSteamInventoryDefinitionUpdate when complete.
        virtual bool LoadItemDefinitions() { return false; }

        // --- Async (result via SteamInventoryNotificationBus) ---

        /// Triggers an in-app purchase flow for one or more items.
        /// Returns a SteamCallHandle correlating with OnSteamInventoryStartPurchaseResult.
        virtual SteamCallHandle StartPurchase(const AZStd::vector<SteamItemDefId>& itemDefIds, const AZStd::vector<AZ::u32>& quantities) { return 0; }

        /// Requests current prices for all purchasable items.
        /// Returns a SteamCallHandle correlating with OnSteamInventoryRequestPricesResult.
        virtual SteamCallHandle RequestPrices() { return 0; }
    };

    class SteamInventoryRequestBusTraits : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
    };

    using SteamInventoryRequestBus = AZ::EBus<SteamInventoryRequests, SteamInventoryRequestBusTraits>;

} // namespace Heathen