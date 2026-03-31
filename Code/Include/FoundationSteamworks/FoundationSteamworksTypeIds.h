
#pragma once

namespace FoundationSteamworks
{
    // System Component TypeIds
    inline constexpr const char* FoundationSteamworksSystemComponentTypeId = "{362DFEB2-592B-4545-A1E6-E3022D498A50}";
    inline constexpr const char* FoundationSteamworksEditorSystemComponentTypeId = "{FE59BE30-98DA-4E17-94BD-5CE3718B4A9C}";

    // Module derived classes TypeIds
    inline constexpr const char* FoundationSteamworksModuleInterfaceTypeId = "{D5D9173D-77DE-4DEE-AD2C-C9C6359F8A23}";
    inline constexpr const char* FoundationSteamworksModuleTypeId = "{6A7D90A2-FEF4-4E90-944D-D5FADDB1753E}";
    // The Editor Module by default is mutually exclusive with the Client Module
    // so they use the Same TypeId
    inline constexpr const char* FoundationSteamworksEditorModuleTypeId = FoundationSteamworksModuleTypeId;

    // Interface TypeIds
    inline constexpr const char* FoundationSteamworksRequestsTypeId = "{ABE6A1A0-315F-45E1-8791-B6D8051EA368}";
} // namespace FoundationSteamworks
