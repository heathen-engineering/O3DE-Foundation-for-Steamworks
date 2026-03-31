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

To target a different SDK version, pass the version to CMake at configure time:

```bash
cmake -B build/linux -S . -G "Ninja Multi-Config" \
  -DLY_3RDPARTY_PATH=~/O3DE/3rdParty \
  -DSTEAM_MAJOR=1 \
  -DSTEAM_MINOR=63
```

Or if your SDK is installed outside this folder, point CMake at it directly:

```bash
-DLY_STEAMWORKS_SDK_PATH=/path/to/steamworks_sdk
```

## The sdk/ folder is intentionally excluded from source control

The Steamworks SDK is subject to Valve's SDK license and must not be redistributed
in source form. The `sdk/` directory is listed in `.gitignore`.