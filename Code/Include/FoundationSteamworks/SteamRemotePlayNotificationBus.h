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
    // SteamRemotePlayNotifications
    // Broadcasts for ISteamRemotePlay callbacks.
    // ISteamRemotePlay has no CallResults — all events are unsolicited callbacks.
    // -----------------------------------------------------------------------
    class SteamRemotePlayNotifications
    {
    public:
        AZ_RTTI(SteamRemotePlayNotifications, "{L2M4N5O6-8P9K-4LHN-KO4Q-3P2M6N9L5O18}");
        virtual ~SteamRemotePlayNotifications() = default;

        /// Fired when a Remote Play session begins.
        /// sessionId is RemotePlaySessionID_t (uint32) wrapped as AZ::u32.
        virtual void OnRemotePlaySessionConnected(AZ::u32 sessionId) {}

        /// Fired when a Remote Play session ends.
        virtual void OnRemotePlaySessionDisconnected(AZ::u32 sessionId) {}
    };

    class SteamRemotePlayNotificationBusTraits : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
    };

    using SteamRemotePlayNotificationBus = AZ::EBus<SteamRemotePlayNotifications, SteamRemotePlayNotificationBusTraits>;

} // namespace Heathen