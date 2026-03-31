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
#include <FoundationSteamworks/SteamTypes.h>

namespace Heathen
{
    // -----------------------------------------------------------------------
    // SteamRemotePlayRequests
    // Request bus wrapping ISteamRemotePlay.
    // Remote Play Together session queries.
    // -----------------------------------------------------------------------
    class SteamRemotePlayRequests
    {
    public:
        AZ_RTTI(SteamRemotePlayRequests, "{EBFCA0B1-C2D3-4E4H-I678-I9J0EBFCA0B2}");
        virtual ~SteamRemotePlayRequests() = default;

        /// Returns the number of currently active Remote Play sessions.
        virtual AZ::u32 GetSessionCount() { return 0; }

        /// Returns the session ID at the given index (0-based).
        virtual AZ::u32 GetSessionID(AZ::u32 index) { return 0; }

        /// Returns the SteamID of the user associated with the given session.
        virtual SteamId GetSessionSteamID(AZ::u32 sessionId) { return 0; }

        /// Returns the name of the client device for the given session.
        virtual AZStd::string GetSessionClientName(AZ::u32 sessionId) { return {}; }

        /// Returns the form-factor of the client device for the given session.
        /// Returns an ESteamDeviceFormFactor cast to s32:
        ///   0 = Unknown, 1 = Phone, 2 = Tablet, 3 = Computer, 4 = TV
        virtual AZ::s32 GetSessionClientFormFactor(AZ::u32 sessionId) { return 0; }

        /// Returns the resolution of the client display for the given session.
        /// Returns false if the session is not found or has no display info.
        virtual bool GetSessionClientResolution(AZ::u32 sessionId, AZ::s32& outWidth, AZ::s32& outHeight) { return false; }

        /// Sends an invite to a friend to join the current Remote Play Together session.
        virtual bool SendRemotePlayTogetherInvite(SteamId friendId) { return false; }
    };

    class SteamRemotePlayRequestBusTraits : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
    };

    using SteamRemotePlayRequestBus = AZ::EBus<SteamRemotePlayRequests, SteamRemotePlayRequestBusTraits>;

} // namespace Heathen