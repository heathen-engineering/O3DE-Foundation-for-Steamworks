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
#include <steam/isteamuser.h>
#include <FoundationSteamworks/SteamUserNotificationBus.h>

using namespace Heathen;

namespace FoundationSteamworks
{
    // -----------------------------------------------------------------------
    // SteamUserRequestBus
    // -----------------------------------------------------------------------

    bool FoundationSteamworksSystemComponent::IsLoggedOn()
    {
        return m_steamInitialised && SteamUser() && SteamUser()->BLoggedOn();
    }

    SteamId FoundationSteamworksSystemComponent::GetSteamID()
    {
        return m_steamInitialised && SteamUser() ? ToSteamId(SteamUser()->GetSteamID()) : 0;
    }

    AZ::s32 FoundationSteamworksSystemComponent::GetPlayerSteamLevel()
    {
        return m_steamInitialised && SteamUser() ? SteamUser()->GetPlayerSteamLevel() : 0;
    }

    AZ::s32 FoundationSteamworksSystemComponent::GetGameBadgeLevel(AZ::s32 series, bool foil)
    {
        return m_steamInitialised && SteamUser() ? SteamUser()->GetGameBadgeLevel(series, foil) : 0;
    }

    SteamAuthTicketHandle FoundationSteamworksSystemComponent::GetAuthTicketForWebApi(const AZStd::string& identity)
    {
        if (!m_steamInitialised || !SteamUser()) return k_HAuthTicketInvalid;
        return static_cast<SteamAuthTicketHandle>(SteamUser()->GetAuthTicketForWebApi(identity.c_str()));
    }

    void FoundationSteamworksSystemComponent::CancelAuthTicket(SteamAuthTicketHandle handle)
    {
        if (m_steamInitialised && SteamUser())
            SteamUser()->CancelAuthTicket(static_cast<HAuthTicket>(handle));
    }

    SteamCallHandle FoundationSteamworksSystemComponent::RequestStoreAuthURL(const AZStd::string& redirectURL)
    {
        if (!m_steamInitialised || !SteamUser()) return 0;
        SteamAPICall_t call = SteamUser()->RequestStoreAuthURL(redirectURL.c_str());
        m_callResults->Register<StoreAuthURLResponse_t>(call, [](SteamCallHandle h, StoreAuthURLResponse_t* p, bool ioFail)
        {
            SteamUserNotificationBus::Broadcast(&SteamUserNotifications::OnStoreAuthURLResponse,
                h, ioFail ? AZStd::string{} : AZStd::string(p->m_szURL));
        });
        return ToCallHandle(call);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::GetMarketEligibility()
    {
        if (!m_steamInitialised || !SteamUser()) return 0;
        SteamAPICall_t call = SteamUser()->GetMarketEligibility();
        m_callResults->Register<MarketEligibilityResponse_t>(call, [](SteamCallHandle h, MarketEligibilityResponse_t* p, bool ioFail)
        {
            SteamUserNotificationBus::Broadcast(&SteamUserNotifications::OnMarketEligibilityResponse,
                h, p->m_bAllowed, static_cast<AZ::u32>(p->m_eNotAllowedReason));
        });
        return ToCallHandle(call);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::GetDurationControl()
    {
        if (!m_steamInitialised || !SteamUser()) return 0;
        SteamAPICall_t call = SteamUser()->GetDurationControl();
        m_callResults->Register<DurationControl_t>(call, [](SteamCallHandle h, DurationControl_t* p, bool ioFail)
        {
            SteamUserNotificationBus::Broadcast(&SteamUserNotifications::OnDurationControl,
                h, ToSteamResult(p->m_eResult),
                p->m_bApplicable ? 1 : 0,
                static_cast<AZ::s32>(p->m_csecsLast5h),
                static_cast<AZ::s32>(p->m_progress),
                static_cast<AZ::s32>(p->m_notification));
        });
        return ToCallHandle(call);
    }

    SteamCallHandle FoundationSteamworksSystemComponent::RequestEncryptedAppTicket(const AZStd::vector<AZ::u8>& dataToInclude)
    {
        if (!m_steamInitialised || !SteamUser()) return 0;
        const void* pData = dataToInclude.empty() ? nullptr : dataToInclude.data();
        int cbData = static_cast<int>(dataToInclude.size());
        SteamAPICall_t call = SteamUser()->RequestEncryptedAppTicket(const_cast<void*>(pData), cbData);
        m_callResults->Register<EncryptedAppTicketResponse_t>(call, [](SteamCallHandle h, EncryptedAppTicketResponse_t* p, bool ioFail)
        {
            SteamUserNotificationBus::Broadcast(&SteamUserNotifications::OnEncryptedAppTicketResponse,
                h, ToSteamResult(p->m_eResult));
        });
        return ToCallHandle(call);
    }

} // namespace FoundationSteamworks
