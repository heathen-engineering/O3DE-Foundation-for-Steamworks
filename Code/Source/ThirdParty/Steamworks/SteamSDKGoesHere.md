# Steamworks SDK

To build FoundationSteamworks from source, place the Steamworks SDK here so that the following path is valid:

```
Gems/FoundationSteamworks/Code/Source/ThirdParty/Steamworks/sdk/public/steam/steam_api.h
```

## Where to get it

Download the Steamworks SDK from the Steamworks developer portal:
https://partner.steamgames.com/

You must be a registered Steamworks developer to access the SDK.

## Version

By default the gem compiles against SDK **1.63** (STEAM_MAJOR=1, STEAM_MINOR=63).

To target a different SDK version, update the version in the FindSteamworks.cmake file:

```bash
set(STEAM_MAJOR 1 CACHE STRING "Steamworks SDK major version")
set(STEAM_MINOR 63 CACHE STRING "Steamworks SDK minor version")
```

Or if your SDK is installed outside this folder, point CMake at it directly:

```bash
if(LY_STEAMWORKS_SDK_PATH)
    set(_steamworks_sdk_root "${LY_STEAMWORKS_SDK_PATH}")
else()
    # Default: sdk/ folder adjacent to this file
    set(_steamworks_sdk_root "${CMAKE_CURRENT_LIST_DIR}/sdk")
endif()

set(STEAMWORKS_SDK_ROOT "${_steamworks_sdk_root}")
```

## The sdk/ folder is intentionally excluded from source control

The Steamworks SDK is subject to Valve's SDK license and must not be redistributed
in source form. The `sdk/` directory is listed in `.gitignore`.