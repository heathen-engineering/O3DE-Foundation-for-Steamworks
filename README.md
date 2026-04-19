# Foundation for Steamworks
![License](https://img.shields.io/badge/License-Apache_2.0-blue?style=flat-square)
![Maintained](https://img.shields.io/badge/Maintained%3F-yes-green?style=flat-square)
![O3DE](https://img.shields.io/badge/O3DE-25.10%20%2B-%2300AEEF?style=flat-square&logo=data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHZpZXdCb3g9IjAgMCAyNCAyNCI+PHBhdGggZmlsbD0id2hpdGUiIGQ9Ik0xMiAxTDEgNy40djkuMkwxMiAyM2wxMS02LjRWNy40TDEyIDF6bTkuMSAxNC45TDExLjUgMjEuM2wtOC42LTYuNFY4LjFsOC42LTYuNCA5LjEgNi40djYuOHpNMTEuNSA0LjZMMi45IDkuNnY0LjhsOC42IDUuMSA4LjYtNS4xVjkuNmwtOC42LTUuMHoiLz48L3N2Zz4=)

An [Open 3D Engine (O3DE)](https://o3de.org) gem that wraps the [Valve Steamworks SDK](https://partner.steamgames.com/doc/home) and exposes it through O3DE's EBus system and Script Canvas / Lua behaviour context.

- **License:** Apache 2.0
- **Origin:** Heathen Group
- **Platforms:** Windows, Linux

-----

## 🛠 Also Available For
[![Unity](https://img.shields.io/badge/Unity-6%20%2B-black?style=for-the-badge&logo=unity&logoColor=white)](https://github.com/heathen-engineering/Unity-Foundation-for-Steamworks)

-----

## Become a GitHub Sponsor
[![Discord](https://img.shields.io/badge/Discord--1877F2?style=social&logo=discord)](https://discord.gg/6X3xrRc)
[![GitHub followers](https://img.shields.io/github/followers/heathen-engineering?style=social)](https://github.com/heathen-engineering?tab=followers)  
Support Heathen by becoming a [GitHub Sponsor](https://github.com/sponsors/heathen-engineering). Sponsorship directly funds the development and maintenance of free tools like this, as well as our game development [Knowledge Base](https://heathen.group/) and community on [Discord](https://discord.gg/6X3xrRc).

Sponsors also get access to our private SourceRepo, which includes developer tools for O3DE, Unreal, Unity, and Godot.  
Learn more or explore other ways to support @ [heathen.group/kb](https://heathen.group/kb/do-more/)

### Toolkit for Steamworks
The **Toolkit for Steamworks** is a sponsor-exclusive gem that builds on this foundation with high-level, component-driven features — bringing the same no-code-first experience as the Unity com.heathen.steamworks toolkit to O3DE:

- **SteamToolsComponent** — singleton system component with ini-driven configuration; handles Steam initialisation, client/game-server mode selection, and lifecycle automatically — no level entity required
- **Lobbies** — create, join, query, and chat in Steam lobbies through ready-made components and Script Canvas nodes
- **User, Friends & Auth** — persona state, rich presence, overlay, and auth ticket management via high-level components
- **Stats, Achievements & Leaderboards** — read/write stats, unlock achievements, and post leaderboard scores with event-driven SC nodes
- **Steam Input** — action set and digital/analogue action reader components for controller-agnostic input
- **Inventory & Workshop** — item definition management, grants/consume/exchange, and UGC upload/subscribe flows *(in development)*
- **LyShine UI Components** — ready-made LyShine components for avatars, achievement icons, and common Steam UI patterns, plus async Script Canvas nodeables for texture pipeline work *(in development)*

Available to [GitHub Sponsors](https://github.com/sponsors/heathen-engineering) via the private SourceRepo.

---

## What it does

Foundation for Steamworks maps each Steamworks interface to a pair of O3DE buses:

| Bus | Direction | Purpose |
|-----|-----------|---------|
| `SteamXxxRequestBus` | Your code → Steam | Call Steam API methods |
| `SteamXxxNotificationBus` | Steam → Your code | Receive callbacks and async results |

The following Steamworks interfaces are covered:

- **Core** — `SteamAPI_InitEx`, `SteamGameServer_InitEx`, Steam Input lifecycle
- **User** — auth tickets, session tokens, encrypted app tickets
- **Apps** — ownership, DLC, language, VAC status
- **Friends** — persona state, rich presence, overlay, chat, avatars
- **Matchmaking** — lobbies (create, join, query, chat)
- **User Stats** — stats (int/float), achievements, leaderboards
- **Remote Storage** — cloud save file read/write/share/enumerate
- **Inventory** — item definitions, grants, consume, exchange
- **UGC / Workshop** — query, subscribe, upload, update items
- **Utils** — overlay, battery, SteamUI language, IP country, text filter
- **Screenshots** — trigger, write, add to library, tag users/files
- **Remote Play** — session enumeration and invite
- **Input** — device connect/disconnect, action data, config loading
- **Timeline** — game mode bar, events (instantaneous and ranged), game phases, overlay
- **Game Server** — server auth, VAC, server browser, logon/logoff
- **Game Server Stats** — per-user server-side stats and achievements

> **Valve's Steamworks documentation is the canonical reference for all API behaviour.**
> This gem exposes the SDK surface faithfully; consult https://partner.steamgames.com/doc/home for parameter semantics, rate limits, and usage guidelines.

---

## Requirements

- O3DE engine **25.10.2** or compatible
- A registered [Steamworks developer account](https://partner.steamgames.com/) (required to download the SDK)
- Steamworks SDK **1.63** (default; see [Changing the SDK version](#changing-the-sdk-version) below)

---

## Setup

### 1. Download the Steamworks SDK

Log in to the [Steamworks partner portal](https://partner.steamgames.com/) and download the SDK archive.

### 2. Place the SDK

Unpack the SDK so that the following path is valid relative to this gem:

```
Code/Source/ThirdParty/Steamworks/sdk/public/steam/steam_api.h
```

The full expected layout is:

```
FoundationSteamworks/
  Code/
    Source/
      ThirdParty/
        Steamworks/
          sdk/
            public/
              steam/
                steam_api.h
                steam_gameserver.h
                ...
            redistributable_bin/
              ...
```

The `sdk/` directory is excluded from source control (Valve's SDK licence prohibits redistribution). A placeholder file at `Code/Source/ThirdParty/Steamworks/SteamSDKGoesHere.md` marks the correct location.

### 3. Add the gem to your O3DE project

Register the gem with the O3DE Project Manager, or add it to your project's `project.json`:

```json
"gem_names": [
    "FoundationSteamworks"
]
```

Then re-register the engine path if needed

---

## Building

If you have added the gem to your project, you can build it via the O3DE Project Manager.

### Changing the SDK version

The default is SDK **1.63**. To target a different version make sure you update the FindSteamworks.cmake file:

```bash
set(STEAM_MAJOR 1 CACHE STRING "Steamworks SDK major version")
set(STEAM_MINOR 63 CACHE STRING "Steamworks SDK minor version")
```

If your SDK lives outside the `ThirdParty` folder, you can adjust where the make looks:

```bash
if(LY_STEAMWORKS_SDK_PATH)
    set(_steamworks_sdk_root "${LY_STEAMWORKS_SDK_PATH}")
else()
    # Default: sdk/ folder adjacent to this file
    set(_steamworks_sdk_root "${CMAKE_CURRENT_LIST_DIR}/sdk")
endif()

set(STEAMWORKS_SDK_ROOT "${_steamworks_sdk_root}")
```

---

## Editor initialisation

When testing in the O3DE editor, Steam needs to know your App ID. Pass it to the init call so the gem can set the `SteamAppId` environment variable automatically — no `steam_appid.txt` file required:

```lua
-- Lua
local result = Steam.Core.SteamInitialise(480)   -- 480 = Spacewar demo app
if not result.success then
    Debug.Log("Steam init failed: " .. result.errorMsg)
end
```

In packaged builds Steam is launched through the client and already knows the App ID, so pass `0`.

---

## Usage overview

All API calls go through the request buses; all callbacks arrive on the notification buses. The buses follow the naming convention `Steam<Interface>RequestBus` / `Steam<Interface>NotificationBus`.

**C++ example — initialise and listen for overlay activation:**

```cpp
#include <FoundationSteamworks/FoundationSteamworksBus.h>
#include <FoundationSteamworks/SteamUtilsNotificationBus.h>

// Initialise (editor: pass your App ID; shipping: pass 0)
AZStd::string error;
bool ok = false;
FoundationSteamworks::FoundationSteamworksRequestBus::BroadcastResult(
    ok, &FoundationSteamworks::FoundationSteamworksRequests::Initialise, 0u, error);

// Listen for overlay open/close
class MyComponent : public Heathen::SteamUtilsNotificationBus::Handler
{
    void Activate() override { SteamUtilsNotificationBus::Handler::BusConnect(); }
    void Deactivate() override { SteamUtilsNotificationBus::Handler::BusDisconnect(); }
    void OnGameOverlayActivated(bool active) override { /* ... */ }
};
```

**Script Canvas / Lua** — every request bus is exposed under the `Steam` category in the node palette. Notification buses can be connected as event nodes.
<img width="1845" height="424" alt="image" src="https://github.com/user-attachments/assets/2e16c241-014f-4b63-94d8-3b713953e434" />

---

## Public headers

All public headers live under `Code/Include/FoundationSteamworks/`. Steam SDK headers are never exposed publicly — all Steam types are converted to O3DE (`AZ::`) types at the implementation boundary.

| Header | Contents |
|--------|----------|
| `FoundationSteamworksBus.h` | Core lifecycle bus (init, shutdown) |
| `SteamTypes.h` | All O3DE-normalised enums, aliases, and result structs |
| `Steam<Interface>RequestBus.h` | One per Steamworks interface |
| `Steam<Interface>NotificationBus.h` | One per Steamworks interface |
