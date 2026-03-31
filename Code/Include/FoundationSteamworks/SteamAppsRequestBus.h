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
    // SteamAppsRequests
    // Request bus wrapping ISteamApps.
    // All calls are synchronous except GetFileDetails.
    // -----------------------------------------------------------------------
    class SteamAppsRequests
    {
    public:
        AZ_RTTI(SteamAppsRequests, "{B2C3D4E5-F6A7-4B8C-9DAE-F0A1B2C3D4E6}");
        virtual ~SteamAppsRequests() = default;

        // --- Subscription / Ownership ---

        /// Returns true if the local user has a license for this app.
        virtual bool IsSubscribed() { return false; }

        /// Returns true if the local user is subscribed to the app via a free weekend.
        virtual bool IsSubscribedFromFreeWeekend() { return false; }

        /// Returns true if the user has the app via a Family Sharing licence.
        virtual bool IsSubscribedFromFamilySharing() { return false; }

        /// Returns true if the given app is owned by the local user.
        virtual bool IsSubscribedApp(SteamAppId appId) { return false; }

        /// Returns true if the given DLC is installed.
        virtual bool IsDlcInstalled(SteamAppId appId) { return false; }

        /// Returns the Unix purchase timestamp for the given app (0 if unknown).
        virtual AZ::u32 GetEarliestPurchaseUnixTime(SteamAppId appId) { return 0; }

        // --- Content Flags ---

        /// True if the app is marked as low-violence.
        virtual bool IsLowViolence() { return false; }

        /// True if the app is running in a cybercafe.
        virtual bool IsCybercafe() { return false; }

        /// True if VAC has banned the current user.
        virtual bool IsVACBanned() { return false; }

        // --- Language ---

        /// Returns the current language the user has set for this app (e.g. "english").
        virtual AZStd::string GetCurrentGameLanguage() { return {}; }

        /// Returns a comma-separated list of all languages available for this app.
        virtual AZStd::string GetAvailableGameLanguages() { return {}; }

        // --- App Identity ---

        /// Returns the AppID of the running app.
        virtual SteamAppId GetAppID() { return 0; }

        // --- DLC ---

        /// Returns the number of DLC entries for this app.
        virtual AZ::s32 GetDLCCount() { return 0; }

        /// Triggers download/install of a DLC.
        virtual void InstallDLC(SteamAppId appId) {}

        /// Uninstalls a DLC (keeps entitlement).
        virtual void UninstallDLC(SteamAppId appId) {}

        // --- Beta / Build ---

        /// Returns the name of the beta branch the user is currently on.
        /// Returns an empty string if not on a beta branch.
        virtual AZStd::string GetCurrentBetaName() { return {}; }

        /// Returns the build ID of the currently installed app.
        virtual AZ::s32 GetAppBuildId() { return 0; }

        // --- Misc ---

        /// Signals to Steam that the app content may be corrupt.
        /// bMissingFilesOnly: if true only marks files that are missing rather than all content.
        virtual bool MarkContentCorrupt(bool missingFilesOnly) { return false; }

        // --- Async (result via SteamAppsNotificationBus) ---

        /// Requests details about an installed file from the CDN.
        /// Returns a SteamCallHandle correlating with OnFileDetailsResult.
        virtual SteamCallHandle GetFileDetails(const AZStd::string& fileName) { return 0; }
    };

    class SteamAppsRequestBusTraits : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
    };

    using SteamAppsRequestBus = AZ::EBus<SteamAppsRequests, SteamAppsRequestBusTraits>;

} // namespace Heathen