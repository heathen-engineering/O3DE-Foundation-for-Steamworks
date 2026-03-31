# FindSteamworks.cmake
# Locates the Steamworks SDK for the FoundationSteamworks gem.
#
# Copyright (c) 2026 Heathen Engineering Limited
# Irish Registered Company #556277
# Licensed under the Apache License, Version 2.0
#
# Inputs (all optional — defaults are used if not set):
#   LY_STEAMWORKS_SDK_PATH   Override the SDK root directory.
#                            If not set, looks for sdk/ next to this file.
#   STEAM_MAJOR              SDK major version for preprocessor guards (default: 1)
#   STEAM_MINOR              SDK minor version for preprocessor guards (default: 63)
#
# Outputs:
#   STEAMWORKS_FOUND         TRUE if the SDK headers were located
#   STEAMWORKS_INCLUDE_DIR   Path to the sdk/public/steam/ parent (sdk/public)
#   STEAMWORKS_SDK_ROOT      Path to the sdk/ root
#   STEAM_MAJOR              Set to default if not provided
#   STEAM_MINOR              Set to default if not provided

# ------------------------------------------------------------------
# Version selection — mirrors the Godot/Unreal pattern exactly.
# Developers can override at cmake configure time:
#   cmake ... -DSTEAM_MAJOR=1 -DSTEAM_MINOR=63
# ------------------------------------------------------------------
set(STEAM_MAJOR 1 CACHE STRING "Steamworks SDK major version")
set(STEAM_MINOR 63 CACHE STRING "Steamworks SDK minor version")

# ------------------------------------------------------------------
# SDK root resolution
# ------------------------------------------------------------------
if(LY_STEAMWORKS_SDK_PATH)
    set(_steamworks_sdk_root "${LY_STEAMWORKS_SDK_PATH}")
else()
    # Default: sdk/ folder adjacent to this file
    set(_steamworks_sdk_root "${CMAKE_CURRENT_LIST_DIR}/sdk")
endif()

set(STEAMWORKS_SDK_ROOT "${_steamworks_sdk_root}")

# ------------------------------------------------------------------
# Verify the SDK is present by checking for the primary header
# ------------------------------------------------------------------
find_path(STEAMWORKS_INCLUDE_DIR
    NAMES steam_api.h
    PATHS "${_steamworks_sdk_root}/public/steam"
    NO_DEFAULT_PATH
)

if(STEAMWORKS_INCLUDE_DIR)
    # Strip the trailing /steam so includes work as <steam/steam_api.h>
    get_filename_component(STEAMWORKS_INCLUDE_DIR "${STEAMWORKS_INCLUDE_DIR}" DIRECTORY)
    set(STEAMWORKS_FOUND TRUE)

    message(STATUS
        "Steamworks SDK found at: ${STEAMWORKS_SDK_ROOT} "
        "(version ${STEAM_MAJOR}.${STEAM_MINOR} selected)")
else()
    set(STEAMWORKS_FOUND FALSE)
    message(WARNING
        "Steamworks SDK not found. "
        "Place the SDK at '${_steamworks_sdk_root}' or set LY_STEAMWORKS_SDK_PATH. "
        "See Gems/FoundationSteamworks/Code/Source/ThirdParty/Steamworks/SteamSDKGoesHere.md")
endif()