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

// Private header — must NOT be included from any public Include/ header.
// This header includes <steam/steam_api.h> deliberately.

#include <FoundationSteamworks/SteamTypes.h>

#include <steam/steam_api.h>
#include <steam/isteamuserstats.h>
#include <steam/isteamugc.h>

namespace FoundationSteamworks
{
    // Steam → O3DE
    inline Heathen::SteamResult     ToSteamResult(EResult r)        { return static_cast<Heathen::SteamResult>(r); }
    inline Heathen::SteamId         ToSteamId(CSteamID id)          { return id.ConvertToUint64(); }
    inline Heathen::SteamCallHandle ToCallHandle(SteamAPICall_t h)   { return static_cast<AZ::u64>(h); }

    // O3DE → Steam
    inline CSteamID           FromSteamId(Heathen::SteamId id)                         { return CSteamID(id); }
    inline SteamLeaderboard_t FromLeaderboardHandle(Heathen::SteamLeaderboardHandle h)  { return static_cast<SteamLeaderboard_t>(h); }
    inline UGCQueryHandle_t   FromUGCQueryHandle(Heathen::SteamUGCQueryHandle h)        { return static_cast<UGCQueryHandle_t>(h); }
    inline UGCUpdateHandle_t  FromUGCUpdateHandle(Heathen::SteamUGCUpdateHandle h)      { return static_cast<UGCUpdateHandle_t>(h); }

} // namespace FoundationSteamworks
