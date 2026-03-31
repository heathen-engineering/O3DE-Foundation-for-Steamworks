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
    // SteamInventoryNotifications
    // Broadcasts for ISteamInventory callbacks.
    // ISteamInventory uses SteamInventoryResultHandle rather than SteamCallHandle
    // for result correlation — the handle is returned by the initiating call.
    // -----------------------------------------------------------------------
    class SteamInventoryNotifications
    {
    public:
        AZ_RTTI(SteamInventoryNotifications, "{G7H9I0J1-3K4F-4GCI-FJ9L-8K7H1I4G0J13}");
        virtual ~SteamInventoryNotifications() = default;

        // -----------------------------------------------------------------------
        // Callbacks
        // -----------------------------------------------------------------------

        /// Fired when a Steam Inventory result is ready.
        /// resultHandle matches the handle returned by the initiating API call.
        virtual void OnSteamInventoryResultReady(
            SteamInventoryResultHandle resultHandle,
            SteamResult result) {}

        /// Fired when the full inventory for the current user has been updated.
        virtual void OnSteamInventoryFullUpdate(
            SteamInventoryResultHandle resultHandle) {}

        /// Fired when Steam Inventory definitions are updated.
        virtual void OnSteamInventoryDefinitionUpdate() {}

        /// Fired when a crafting or purchase result is eligible for use.
        virtual void OnSteamInventoryEligiblePromoItemDefIDs(
            SteamResult result,
            SteamId userId,
            AZ::s32 numEligiblePromoItemDefs,
            bool cachedData) {}

        /// Fired when Steam guard eligibility is available.
        virtual void OnSteamInventoryStartPurchaseResult(
            SteamCallHandle callHandle,
            SteamResult result,
            AZ::u64 orderId,
            AZ::u64 transactionId) {}

        /// Fired when a request for eligible promo items completes.
        virtual void OnSteamInventoryRequestPricesResult(
            SteamCallHandle callHandle,
            SteamResult result,
            const AZStd::string& currency) {}
    };

    class SteamInventoryNotificationBusTraits : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
    };

    using SteamInventoryNotificationBus = AZ::EBus<SteamInventoryNotifications, SteamInventoryNotificationBusTraits>;

} // namespace Heathen