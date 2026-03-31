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

#include "BehaviorNotificationHandlers.h"
#include "SteamAPIProxies.h"

#include <AzCore/RTTI/BehaviorContext.h>

using namespace Heathen;

namespace FoundationSteamworks
{
    void ReflectSteamBehaviorContext(AZ::BehaviorContext* bc)
    {
        // --- SteamResult enum ---
        bc->Enum<static_cast<int>(SteamResult::OK)>("SteamResult_OK")
          ->Enum<static_cast<int>(SteamResult::Fail)>("SteamResult_Fail")
          ->Enum<static_cast<int>(SteamResult::NoConnection)>("SteamResult_NoConnection")
          ->Enum<static_cast<int>(SteamResult::InvalidPassword)>("SteamResult_InvalidPassword")
          ->Enum<static_cast<int>(SteamResult::LoggedInElsewhere)>("SteamResult_LoggedInElsewhere")
          ->Enum<static_cast<int>(SteamResult::InvalidProtocolVersion)>("SteamResult_InvalidProtocolVersion")
          ->Enum<static_cast<int>(SteamResult::InvalidParam)>("SteamResult_InvalidParam")
          ->Enum<static_cast<int>(SteamResult::FileNotFound)>("SteamResult_FileNotFound")
          ->Enum<static_cast<int>(SteamResult::Busy)>("SteamResult_Busy")
          ->Enum<static_cast<int>(SteamResult::InvalidState)>("SteamResult_InvalidState")
          ->Enum<static_cast<int>(SteamResult::InvalidName)>("SteamResult_InvalidName")
          ->Enum<static_cast<int>(SteamResult::InvalidEmail)>("SteamResult_InvalidEmail")
          ->Enum<static_cast<int>(SteamResult::DuplicateName)>("SteamResult_DuplicateName")
          ->Enum<static_cast<int>(SteamResult::AccessDenied)>("SteamResult_AccessDenied")
          ->Enum<static_cast<int>(SteamResult::Timeout)>("SteamResult_Timeout")
          ->Enum<static_cast<int>(SteamResult::Banned)>("SteamResult_Banned")
          ->Enum<static_cast<int>(SteamResult::AccountNotFound)>("SteamResult_AccountNotFound")
          ->Enum<static_cast<int>(SteamResult::InvalidSteamID)>("SteamResult_InvalidSteamID")
          ->Enum<static_cast<int>(SteamResult::ServiceUnavailable)>("SteamResult_ServiceUnavailable")
          ->Enum<static_cast<int>(SteamResult::NotLoggedOn)>("SteamResult_NotLoggedOn")
          ->Enum<static_cast<int>(SteamResult::Pending)>("SteamResult_Pending")
          ->Enum<static_cast<int>(SteamResult::EncryptionFailure)>("SteamResult_EncryptionFailure")
          ->Enum<static_cast<int>(SteamResult::InsufficientPrivilege)>("SteamResult_InsufficientPrivilege")
          ->Enum<static_cast<int>(SteamResult::LimitExceeded)>("SteamResult_LimitExceeded")
          ->Enum<static_cast<int>(SteamResult::Revoked)>("SteamResult_Revoked")
          ->Enum<static_cast<int>(SteamResult::Expired)>("SteamResult_Expired")
          ->Enum<static_cast<int>(SteamResult::AlreadyRedeemed)>("SteamResult_AlreadyRedeemed")
          ->Enum<static_cast<int>(SteamResult::DuplicateRequest)>("SteamResult_DuplicateRequest")
          ->Enum<static_cast<int>(SteamResult::AlreadyOwned)>("SteamResult_AlreadyOwned")
          ->Enum<static_cast<int>(SteamResult::IPNotFound)>("SteamResult_IPNotFound")
          ->Enum<static_cast<int>(SteamResult::PersistFailed)>("SteamResult_PersistFailed")
          ->Enum<static_cast<int>(SteamResult::LockingFailed)>("SteamResult_LockingFailed")
          ->Enum<static_cast<int>(SteamResult::LogonSessionReplaced)>("SteamResult_LogonSessionReplaced")
          ->Enum<static_cast<int>(SteamResult::ConnectFailed)>("SteamResult_ConnectFailed")
          ->Enum<static_cast<int>(SteamResult::HandshakeFailed)>("SteamResult_HandshakeFailed")
          ->Enum<static_cast<int>(SteamResult::IOFailure)>("SteamResult_IOFailure")
          ->Enum<static_cast<int>(SteamResult::RemoteDisconnect)>("SteamResult_RemoteDisconnect")
          ->Enum<static_cast<int>(SteamResult::Blocked)>("SteamResult_Blocked")
          ->Enum<static_cast<int>(SteamResult::Ignored)>("SteamResult_Ignored")
          ->Enum<static_cast<int>(SteamResult::NoMatch)>("SteamResult_NoMatch")
          ->Enum<static_cast<int>(SteamResult::AccountDisabled)>("SteamResult_AccountDisabled")
          ->Enum<static_cast<int>(SteamResult::ServiceReadOnly)>("SteamResult_ServiceReadOnly")
          ->Enum<static_cast<int>(SteamResult::NotModified)>("SteamResult_NotModified")
          ->Enum<static_cast<int>(SteamResult::InsufficientFunds)>("SteamResult_InsufficientFunds")
          ->Enum<static_cast<int>(SteamResult::LimitedUserAccount)>("SteamResult_LimitedUserAccount")
          ->Enum<static_cast<int>(SteamResult::RateLimitExceeded)>("SteamResult_RateLimitExceeded");

        // --- SteamPersonaState ---
        bc->Enum<static_cast<int>(SteamPersonaState::Offline)>("SteamPersonaState_Offline")
          ->Enum<static_cast<int>(SteamPersonaState::Online)>("SteamPersonaState_Online")
          ->Enum<static_cast<int>(SteamPersonaState::Busy)>("SteamPersonaState_Busy")
          ->Enum<static_cast<int>(SteamPersonaState::Away)>("SteamPersonaState_Away")
          ->Enum<static_cast<int>(SteamPersonaState::Snooze)>("SteamPersonaState_Snooze")
          ->Enum<static_cast<int>(SteamPersonaState::LookingToTrade)>("SteamPersonaState_LookingToTrade")
          ->Enum<static_cast<int>(SteamPersonaState::LookingToPlay)>("SteamPersonaState_LookingToPlay")
          ->Enum<static_cast<int>(SteamPersonaState::Invisible)>("SteamPersonaState_Invisible");

        // --- SteamLobbyType ---
        bc->Enum<static_cast<int>(SteamLobbyType::Private)>("SteamLobbyType_Private")
          ->Enum<static_cast<int>(SteamLobbyType::FriendsOnly)>("SteamLobbyType_FriendsOnly")
          ->Enum<static_cast<int>(SteamLobbyType::Public)>("SteamLobbyType_Public")
          ->Enum<static_cast<int>(SteamLobbyType::Invisible)>("SteamLobbyType_Invisible")
          ->Enum<static_cast<int>(SteamLobbyType::PrivateUnique)>("SteamLobbyType_PrivateUnique");

        // --- SteamLobbyComparison ---
        bc->Enum<static_cast<int>(SteamLobbyComparison::EqualToOrLessThan)>("SteamLobbyComparison_EqualToOrLessThan")
          ->Enum<static_cast<int>(SteamLobbyComparison::LessThan)>("SteamLobbyComparison_LessThan")
          ->Enum<static_cast<int>(SteamLobbyComparison::Equal)>("SteamLobbyComparison_Equal")
          ->Enum<static_cast<int>(SteamLobbyComparison::GreaterThan)>("SteamLobbyComparison_GreaterThan")
          ->Enum<static_cast<int>(SteamLobbyComparison::EqualToOrGreaterThan)>("SteamLobbyComparison_EqualToOrGreaterThan")
          ->Enum<static_cast<int>(SteamLobbyComparison::NotEqual)>("SteamLobbyComparison_NotEqual");

        // --- SteamLobbyDistanceFilter ---
        bc->Enum<static_cast<int>(SteamLobbyDistanceFilter::Close)>("SteamLobbyDistanceFilter_Close")
          ->Enum<static_cast<int>(SteamLobbyDistanceFilter::Default)>("SteamLobbyDistanceFilter_Default")
          ->Enum<static_cast<int>(SteamLobbyDistanceFilter::Far)>("SteamLobbyDistanceFilter_Far")
          ->Enum<static_cast<int>(SteamLobbyDistanceFilter::Worldwide)>("SteamLobbyDistanceFilter_Worldwide");

        // --- SteamLeaderboardSortMethod ---
        bc->Enum<static_cast<int>(SteamLeaderboardSortMethod::None)>("SteamLeaderboardSortMethod_None")
          ->Enum<static_cast<int>(SteamLeaderboardSortMethod::Ascending)>("SteamLeaderboardSortMethod_Ascending")
          ->Enum<static_cast<int>(SteamLeaderboardSortMethod::Descending)>("SteamLeaderboardSortMethod_Descending");

        // --- SteamLeaderboardDisplayType ---
        bc->Enum<static_cast<int>(SteamLeaderboardDisplayType::None)>("SteamLeaderboardDisplayType_None")
          ->Enum<static_cast<int>(SteamLeaderboardDisplayType::Numeric)>("SteamLeaderboardDisplayType_Numeric")
          ->Enum<static_cast<int>(SteamLeaderboardDisplayType::TimeSeconds)>("SteamLeaderboardDisplayType_TimeSeconds")
          ->Enum<static_cast<int>(SteamLeaderboardDisplayType::TimeMilliSeconds)>("SteamLeaderboardDisplayType_TimeMilliSeconds");

        // --- SteamLeaderboardDataRequest ---
        bc->Enum<static_cast<int>(SteamLeaderboardDataRequest::Global)>("SteamLeaderboardDataRequest_Global")
          ->Enum<static_cast<int>(SteamLeaderboardDataRequest::GlobalAroundUser)>("SteamLeaderboardDataRequest_GlobalAroundUser")
          ->Enum<static_cast<int>(SteamLeaderboardDataRequest::Friends)>("SteamLeaderboardDataRequest_Friends")
          ->Enum<static_cast<int>(SteamLeaderboardDataRequest::Users)>("SteamLeaderboardDataRequest_Users");

        // --- SteamLeaderboardUploadScoreMethod ---
        bc->Enum<static_cast<int>(SteamLeaderboardUploadScoreMethod::None)>("SteamLeaderboardUploadScoreMethod_None")
          ->Enum<static_cast<int>(SteamLeaderboardUploadScoreMethod::KeepBest)>("SteamLeaderboardUploadScoreMethod_KeepBest")
          ->Enum<static_cast<int>(SteamLeaderboardUploadScoreMethod::ForceUpdate)>("SteamLeaderboardUploadScoreMethod_ForceUpdate");

        // --- SteamUGCVisibility ---
        bc->Enum<static_cast<int>(SteamUGCVisibility::Public)>("SteamUGCVisibility_Public")
          ->Enum<static_cast<int>(SteamUGCVisibility::FriendsOnly)>("SteamUGCVisibility_FriendsOnly")
          ->Enum<static_cast<int>(SteamUGCVisibility::Private)>("SteamUGCVisibility_Private")
          ->Enum<static_cast<int>(SteamUGCVisibility::Unlisted)>("SteamUGCVisibility_Unlisted");

        // --- SteamOverlayToStoreFlag ---
        bc->Enum<static_cast<int>(SteamOverlayToStoreFlag::None)>("SteamOverlayToStoreFlag_None")
          ->Enum<static_cast<int>(SteamOverlayToStoreFlag::AddToCart)>("SteamOverlayToStoreFlag_AddToCart")
          ->Enum<static_cast<int>(SteamOverlayToStoreFlag::AddToCartAndShow)>("SteamOverlayToStoreFlag_AddToCartAndShow");

        // --- SteamOverlayToWebPageMode ---
        bc->Enum<static_cast<int>(SteamOverlayToWebPageMode::Default)>("SteamOverlayToWebPageMode_Default")
          ->Enum<static_cast<int>(SteamOverlayToWebPageMode::Modal)>("SteamOverlayToWebPageMode_Modal");

        // --- SteamTimelineGameMode ---
        bc->Enum<static_cast<int>(SteamTimelineGameMode::Invalid)>("SteamTimelineGameMode_Invalid")
          ->Enum<static_cast<int>(SteamTimelineGameMode::Playing)>("SteamTimelineGameMode_Playing")
          ->Enum<static_cast<int>(SteamTimelineGameMode::Staging)>("SteamTimelineGameMode_Staging")
          ->Enum<static_cast<int>(SteamTimelineGameMode::Menus)>("SteamTimelineGameMode_Menus")
          ->Enum<static_cast<int>(SteamTimelineGameMode::LoadingScreen)>("SteamTimelineGameMode_LoadingScreen");

        // --- SteamTimelineClipPriority ---
        bc->Enum<static_cast<int>(SteamTimelineClipPriority::Invalid)>("SteamTimelineClipPriority_Invalid")
          ->Enum<static_cast<int>(SteamTimelineClipPriority::None)>("SteamTimelineClipPriority_None")
          ->Enum<static_cast<int>(SteamTimelineClipPriority::Standard)>("SteamTimelineClipPriority_Standard")
          ->Enum<static_cast<int>(SteamTimelineClipPriority::Featured)>("SteamTimelineClipPriority_Featured");

        // ---------------------------------------------------------------
        // Notification buses — scripts implement these handlers
        // ---------------------------------------------------------------
        bc->EBus<SteamUserNotificationBus>("SteamUserNotificationBus")
            ->Handler<BehaviorSteamUserNotificationHandler>();
        bc->EBus<SteamAppsNotificationBus>("SteamAppsNotificationBus")
            ->Handler<BehaviorSteamAppsNotificationHandler>();
        bc->EBus<SteamFriendsNotificationBus>("SteamFriendsNotificationBus")
            ->Handler<BehaviorSteamFriendsNotificationHandler>();
        bc->EBus<SteamMatchmakingNotificationBus>("SteamMatchmakingNotificationBus")
            ->Handler<BehaviorSteamMatchmakingNotificationHandler>();
        bc->EBus<SteamUserStatsNotificationBus>("SteamUserStatsNotificationBus")
            ->Handler<BehaviorSteamUserStatsNotificationHandler>();
        bc->EBus<SteamRemoteStorageNotificationBus>("SteamRemoteStorageNotificationBus")
            ->Handler<BehaviorSteamRemoteStorageNotificationHandler>();
        bc->EBus<SteamInventoryNotificationBus>("SteamInventoryNotificationBus")
            ->Handler<BehaviorSteamInventoryNotificationHandler>();
        bc->EBus<SteamUGCNotificationBus>("SteamUGCNotificationBus")
            ->Handler<BehaviorSteamUGCNotificationHandler>();
        bc->EBus<SteamUtilsNotificationBus>("SteamUtilsNotificationBus")
            ->Handler<BehaviorSteamUtilsNotificationHandler>();
        bc->EBus<SteamInputNotificationBus>("SteamInputNotificationBus")
            ->Handler<BehaviorSteamInputNotificationHandler>();
        bc->EBus<SteamScreenshotsNotificationBus>("SteamScreenshotsNotificationBus")
            ->Handler<BehaviorSteamScreenshotsNotificationHandler>();
        bc->EBus<SteamRemotePlayNotificationBus>("SteamRemotePlayNotificationBus")
            ->Handler<BehaviorSteamRemotePlayNotificationHandler>();
        bc->EBus<SteamTimelineNotificationBus>("SteamTimelineNotificationBus")
            ->Handler<BehaviorSteamTimelineNotificationHandler>();

        // ---------------------------------------------------------------
        // Request surfaces — bc->Class<Proxy>()->Method() makes these
        // nodes searchable in the Script Canvas node palette.
        // ---------------------------------------------------------------
        // Core lifecycle — init / shutdown / status
        bc->Class<SteamCoreAPI>("Core")
            ->Attribute(AZ::Script::Attributes::Category, "Steam")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Method("Steam Initialise",               &SteamCoreAPI::Initialise,
                {{{ "App ID", "Your Steam App ID. When non-zero and running in the O3DE editor, "
                              "the SDK is told the App ID via environment variable so that "
                              "steam_appid.txt is not required. Pass 0 in packaged builds." }}})
            ->Method("Steam Game Server Initialise",   &SteamCoreAPI::GameServerInitialise,
                {{ { "App ID",         "Your Steam App ID. When non-zero and running in the O3DE editor, "
                                       "the SDK is told the App ID via environment variable so that "
                                       "steam_appid.txt is not required. Pass 0 in packaged builds." },
                { "Local IP",       "Bind address as \"x.x.x.x\", or empty string for any interface." },
                { "Game Port",      "Port that clients connect to for gameplay." },
                { "Query Port",     "Port for server browser queries. Pass 65535 to share the game port." },
                { "Server Mode",    "Authentication / VAC policy: NoAuthentication=1, Authentication=2, AuthenticationAndSecure=3." },
                { "Version String", "App version in \"x.x.x.x\" format." } }})
            ->Method("Steam Input Initialise",            &SteamCoreAPI::InputInitialise)
            ->Method("Steam Shutdown",                 &SteamCoreAPI::Shutdown)
            ->Method("Steam Game Server Shutdown",        &SteamCoreAPI::GameServerShutdown)
            ->Method("Steam Input Shutdown",              &SteamCoreAPI::InputShutdown)
            ->Method("Is Steam Initialised",          &SteamCoreAPI::IsInitialised)
            ->Method("Is Steam Game Server Initialised",  &SteamCoreAPI::IsGameServerInitialised)
            ->Method("Is Steam Input Initialised",        &SteamCoreAPI::IsInputInitialised);

        bc->Class<SteamAppsAPI>("Apps")
            ->Attribute(AZ::Script::Attributes::Category, "Steam")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Method("Steam Apps Is Subscribed",                    &SteamAppsAPI::IsSubscribed)
            ->Method("Steam Apps Is Subscribed From Free Weekend",   &SteamAppsAPI::IsSubscribedFromFreeWeekend)
            ->Method("Steam Apps Is Subscribed From Family Sharing", &SteamAppsAPI::IsSubscribedFromFamilySharing)
            ->Method("Steam Apps Is Subscribed App",                 &SteamAppsAPI::IsSubscribedApp,
                {{{ "App ID", "The AppID of the app to check ownership for." }}})
            ->Method("Steam Apps Is DLC Installed",                  &SteamAppsAPI::IsDlcInstalled,
                {{{ "App ID", "The AppID of the DLC to check." }}})
            ->Method("Steam Apps Get Earliest Purchase Unix Time",   &SteamAppsAPI::GetEarliestPurchaseUnixTime,
                {{{ "App ID", "The AppID to query the purchase time for." }}})
            ->Method("Steam Apps Is Low Violence",                   &SteamAppsAPI::IsLowViolence)
            ->Method("Steam Apps Is Cybercafe",                      &SteamAppsAPI::IsCybercafe)
            ->Method("Steam Apps Is VAC Banned",                     &SteamAppsAPI::IsVACBanned)
            ->Method("Steam Apps Get Current Game Language",         &SteamAppsAPI::GetCurrentGameLanguage)
            ->Method("Steam Apps Get Available Game Languages",      &SteamAppsAPI::GetAvailableGameLanguages)
            ->Method("Steam Apps Get App ID",                        &SteamAppsAPI::GetAppID)
            ->Method("Steam Apps Get DLC Count",                     &SteamAppsAPI::GetDLCCount)
            ->Method("Steam Apps Install DLC",                       &SteamAppsAPI::InstallDLC,
                {{{ "App ID", "The AppID of the DLC to install." }}})
            ->Method("Steam Apps Uninstall DLC",                     &SteamAppsAPI::UninstallDLC,
                {{{ "App ID", "The AppID of the DLC to uninstall. The user retains the entitlement." }}})
            ->Method("Steam Apps Get Current Beta Name",             &SteamAppsAPI::GetCurrentBetaName)
            ->Method("Steam Apps Get App Build ID",                  &SteamAppsAPI::GetAppBuildId)
            ->Method("Steam Apps Mark Content Corrupt",              &SteamAppsAPI::MarkContentCorrupt,
                {{{ "Missing Files Only", "If true, only marks missing files as corrupt rather than all content." }}})
            ->Method("Steam Apps Get File Details",                  &SteamAppsAPI::GetFileDetails,
                {{{ "File Name", "The file name relative to the app's install directory to query from the CDN." }}});

        bc->Class<SteamFriendsAPI>("Friends")
            ->Attribute(AZ::Script::Attributes::Category, "Steam")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Method("Steam Friends Get Persona Name",                   &SteamFriendsAPI::GetPersonaName)
            ->Method("Steam Friends Get Persona State",                  &SteamFriendsAPI::GetPersonaState)
            ->Method("Steam Friends Get Friend Count",                   &SteamFriendsAPI::GetFriendCount,
                {{{ "Friend Flags", "Bitwise-OR of EFriendFlags values. Use 4 (k_EFriendFlagImmediate) for immediate friends." }}})
            ->Method("Steam Friends Get Friend By Index",                &SteamFriendsAPI::GetFriendByIndex,
                {{ { "Index",        "Zero-based index into the friends list." },
                   { "Friend Flags", "The same EFriendFlags bitmask used to call Get Friend Count." } }})
            ->Method("Steam Friends Get Friend Relationship",            &SteamFriendsAPI::GetFriendRelationship,
                {{{ "Steam ID", "The SteamID of the user to query." }}})
            ->Method("Steam Friends Get Friend Persona State",           &SteamFriendsAPI::GetFriendPersonaState,
                {{{ "Steam ID", "The SteamID of the friend to query." }}})
            ->Method("Steam Friends Get Friend Persona Name",            &SteamFriendsAPI::GetFriendPersonaName,
                {{{ "Steam ID", "The SteamID of the friend whose display name to retrieve." }}})
            ->Method("Steam Friends Get Friend Steam Level",             &SteamFriendsAPI::GetFriendSteamLevel,
                {{{ "Steam ID", "The SteamID of the friend to query." }}})
            ->Method("Steam Friends Get Player Nickname",                &SteamFriendsAPI::GetPlayerNickname,
                {{{ "Steam ID", "The SteamID of the user whose per-game nickname to retrieve." }}})
            ->Method("Steam Friends Has Friend",                         &SteamFriendsAPI::HasFriend,
                {{ { "Steam ID",     "The SteamID of the user to test." },
                   { "Friend Flags", "The EFriendFlags relationship bitmask to test against." } }})
            ->Method("Steam Friends Get Small Friend Avatar",            &SteamFriendsAPI::GetSmallFriendAvatar,
                {{{ "Steam ID", "The SteamID of the user whose 32x32 avatar to retrieve." }}})
            ->Method("Steam Friends Get Medium Friend Avatar",           &SteamFriendsAPI::GetMediumFriendAvatar,
                {{{ "Steam ID", "The SteamID of the user whose 64x64 avatar to retrieve." }}})
            ->Method("Steam Friends Get Large Friend Avatar",            &SteamFriendsAPI::GetLargeFriendAvatar,
                {{{ "Steam ID", "The SteamID of the user whose 184x184 avatar to retrieve." }}})
            ->Method("Steam Friends Request User Information",           &SteamFriendsAPI::RequestUserInformation,
                {{ { "Steam ID",           "The SteamID of the user to request information for." },
                   { "Require Name Only",  "If true, only fetches the name; avatar download is skipped." } }})
            ->Method("Steam Friends Set Rich Presence",                  &SteamFriendsAPI::SetRichPresence,
                {{ { "Key",   "The rich presence key to set (max 64 bytes)." },
                   { "Value", "The value to associate with the key (max 256 bytes)." } }})
            ->Method("Steam Friends Clear Rich Presence",                &SteamFriendsAPI::ClearRichPresence)
            ->Method("Steam Friends Get Friend Rich Presence",           &SteamFriendsAPI::GetFriendRichPresence,
                {{ { "Steam ID", "The SteamID of the friend to query." },
                   { "Key",     "The rich presence key to retrieve." } }})
            ->Method("Steam Friends Get Friend Rich Presence Key Count", &SteamFriendsAPI::GetFriendRichPresenceKeyCount,
                {{{ "Steam ID", "The SteamID of the friend to query." }}})
            ->Method("Steam Friends Get Friend Rich Presence Key By Index", &SteamFriendsAPI::GetFriendRichPresenceKeyByIndex,
                {{ { "Steam ID", "The SteamID of the friend to query." },
                   { "Index",   "Zero-based index into the friend's rich presence key list." } }})
            ->Method("Steam Friends Request Friend Rich Presence",       &SteamFriendsAPI::RequestFriendRichPresence,
                {{{ "Steam ID", "The SteamID of the friend whose rich presence to refresh." }}})
            ->Method("Steam Friends Activate Game Overlay",              &SteamFriendsAPI::ActivateGameOverlay,
                {{{ "Dialog", "The overlay dialog to open: \"Friends\", \"Community\", \"Players\", \"Settings\", \"OfficialGameGroup\", \"Stats\", \"Achievements\"." }}})
            ->Method("Steam Friends Activate Game Overlay To User",      &SteamFriendsAPI::ActivateGameOverlayToUser,
                {{ { "Dialog",   "One of: \"steamid\", \"chat\", \"jointrade\", \"stats\", \"achievements\", \"friendadd\", \"friendremove\", \"friendrequestaccept\", \"friendrequestignore\"." },
                   { "Steam ID", "The SteamID of the user to show." } }})
            ->Method("Steam Friends Activate Game Overlay To Web Page",  &SteamFriendsAPI::ActivateGameOverlayToWebPage,
                {{ { "URL",  "The URL to open in the overlay browser." },
                   { "Mode", "0 = default browser, 1 = modal popup." } }})
            ->Method("Steam Friends Activate Game Overlay To Store",     &SteamFriendsAPI::ActivateGameOverlayToStore,
                {{ { "App ID", "The AppID of the game to show on the Steam store." },
                   { "Flag",   "0 = none, 1 = add to cart, 2 = add to cart and show cart." } }})
            ->Method("Steam Friends Activate Game Overlay Invite Dialog", &SteamFriendsAPI::ActivateGameOverlayInviteDialog,
                {{{ "Lobby ID", "The SteamID of the lobby to invite friends to." }}})
            ->Method("Steam Friends Set Played With",                    &SteamFriendsAPI::SetPlayedWith,
                {{{ "Steam ID", "The SteamID of the user to mark as played-with in the recent players list." }}})
            ->Method("Steam Friends Get Clan By Index",                  &SteamFriendsAPI::GetClanByIndex,
                {{{ "Index", "Zero-based index into the list of clans the local user belongs to." }}})
            ->Method("Steam Friends Get Clan Count",                     &SteamFriendsAPI::GetClanCount)
            ->Method("Steam Friends Get Clan Name",                      &SteamFriendsAPI::GetClanName,
                {{{ "Clan ID", "The SteamID of the clan." }}})
            ->Method("Steam Friends Get Clan Tag",                       &SteamFriendsAPI::GetClanTag,
                {{{ "Clan ID", "The SteamID of the clan." }}})
            ->Method("Steam Friends Request Clan Officer List",          &SteamFriendsAPI::RequestClanOfficerList,
                {{{ "Clan ID", "The SteamID of the clan whose officer list to request." }}})
            ->Method("Steam Friends Get Follower Count",                 &SteamFriendsAPI::GetFollowerCount,
                {{{ "Steam ID", "The SteamID of the user to get the follower count for." }}})
            ->Method("Steam Friends Is Following",                       &SteamFriendsAPI::IsFollowing,
                {{{ "Steam ID", "The SteamID of the user to check whether the local user is following." }}})
            ->Method("Steam Friends Enumerate Following List",           &SteamFriendsAPI::EnumerateFollowingList,
                {{{ "Start Index", "Zero-based index into the following list to start enumerating from." }}});

        bc->Class<SteamInventoryAPI>("Inventory")
            ->Attribute(AZ::Script::Attributes::Category, "Steam")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Method("Steam Inventory Destroy Result",              &SteamInventoryAPI::DestroyResult,
                {{{ "Result Handle", "The inventory result handle to free. Always call this when done processing a result." }}})
            ->Method("Steam Inventory Get Result Status",           &SteamInventoryAPI::GetResultStatus,
                {{{ "Result Handle", "The inventory result handle to query." }}})
            ->Method("Steam Inventory Get Result Timestamp",        &SteamInventoryAPI::GetResultTimestamp,
                {{{ "Result Handle", "The inventory result handle to query. Returns a Unix timestamp." }}})
            ->Method("Steam Inventory Get All Items",               &SteamInventoryAPI::GetAllItems)
            ->Method("Steam Inventory Get Items By ID",             &SteamInventoryAPI::GetItemsByID,
                {{{ "Instance IDs", "Array of SteamItemInstanceId values to query." }}})
            ->Method("Steam Inventory Add Promo Item",              &SteamInventoryAPI::AddPromoItem,
                {{{ "Item Def ID", "The SteamItemDef_t ID of the promotional item to grant if eligible." }}})
            ->Method("Steam Inventory Add Promo Items",             &SteamInventoryAPI::AddPromoItems,
                {{{ "Item Def IDs", "Array of SteamItemDef_t IDs of promotional items to grant if eligible." }}})
            ->Method("Steam Inventory Consume Item",                &SteamInventoryAPI::ConsumeItem,
                {{ { "Instance ID", "The SteamItemInstanceID_t of the stack to consume from." },
                   { "Quantity",    "The number of items to consume from the stack." } }})
            ->Method("Steam Inventory Transfer Item Quantity",      &SteamInventoryAPI::TransferItemQuantity,
                {{ { "Source ID",  "The SteamItemInstanceID_t of the source stack." },
                   { "Quantity",   "The number of items to move." },
                   { "Dest ID",    "The SteamItemInstanceID_t of the destination stack, or 0xFFFFFFFFFFFFFFFF to create a new stack." } }})
            ->Method("Steam Inventory Get All Items Server",        &SteamInventoryAPI::GetAllItemsServer)
            ->Method("Steam Inventory Get Num Item Definitions",    &SteamInventoryAPI::GetNumItemDefinitions)
            ->Method("Steam Inventory Get Item Definition Property", &SteamInventoryAPI::GetItemDefinitionProperty,
                {{ { "Def ID",        "The SteamItemDef_t ID of the item definition." },
                   { "Property Name", "The property key to retrieve, e.g. \"name\", \"description\", \"icon_url\"." } }})
            ->Method("Steam Inventory Load Item Definitions",       &SteamInventoryAPI::LoadItemDefinitions)
            ->Method("Steam Inventory Start Purchase",              &SteamInventoryAPI::StartPurchase,
                {{ { "Item Def IDs", "Array of SteamItemDef_t IDs to purchase." },
                   { "Quantities",   "Array of quantities corresponding to each item def ID." } }})
            ->Method("Steam Inventory Request Prices",              &SteamInventoryAPI::RequestPrices);

        bc->Class<SteamMatchmakingAPI>("Matchmaking")
            ->Attribute(AZ::Script::Attributes::Category, "Steam")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Method("Steam Lobby Get Num Members",                       &SteamMatchmakingAPI::GetNumLobbyMembers,
                {{{ "Lobby ID", "The SteamID of the lobby to query." }}})
            ->Method("Steam Lobby Get Member By Index",                   &SteamMatchmakingAPI::GetLobbyMemberByIndex,
                {{ { "Lobby ID", "The SteamID of the lobby." },
                   { "Index",   "Zero-based member index." } }})
            ->Method("Steam Lobby Get Data",                              &SteamMatchmakingAPI::GetLobbyData,
                {{ { "Lobby ID", "The SteamID of the lobby." },
                   { "Key",     "The metadata key to retrieve." } }})
            ->Method("Steam Lobby Set Data",                              &SteamMatchmakingAPI::SetLobbyData,
                {{ { "Lobby ID", "The SteamID of the lobby. Must be the owner." },
                   { "Key",     "The metadata key to set (max 255 bytes)." },
                   { "Value",   "The value to associate with the key (max 8192 bytes)." } }})
            ->Method("Steam Lobby Delete Data",                           &SteamMatchmakingAPI::DeleteLobbyData,
                {{ { "Lobby ID", "The SteamID of the lobby. Must be the owner." },
                   { "Key",     "The metadata key to delete." } }})
            ->Method("Steam Lobby Get Member Data",                       &SteamMatchmakingAPI::GetLobbyMemberData,
                {{ { "Lobby ID",   "The SteamID of the lobby." },
                   { "Member ID",  "The SteamID of the member to query." },
                   { "Key",        "The per-member metadata key to retrieve." } }})
            ->Method("Steam Lobby Set Member Data",                       &SteamMatchmakingAPI::SetLobbyMemberData,
                {{ { "Lobby ID", "The SteamID of the lobby." },
                   { "Key",     "The per-member metadata key to set." },
                   { "Value",   "The value to set." } }})
            ->Method("Steam Lobby Get Owner",                             &SteamMatchmakingAPI::GetLobbyOwner,
                {{{ "Lobby ID", "The SteamID of the lobby." }}})
            ->Method("Steam Lobby Set Owner",                             &SteamMatchmakingAPI::SetLobbyOwner,
                {{ { "Lobby ID",      "The SteamID of the lobby. Must currently be the owner." },
                   { "New Owner ID",  "The SteamID of the new owner." } }})
            ->Method("Steam Lobby Request Data",                          &SteamMatchmakingAPI::RequestLobbyData,
                {{{ "Lobby ID", "The SteamID of the lobby to refresh metadata for." }}})
            ->Method("Steam Lobby Set Joinable",                          &SteamMatchmakingAPI::SetLobbyJoinable,
                {{ { "Lobby ID",  "The SteamID of the lobby." },
                   { "Joinable",  "Pass true to allow new members; false to prevent new joins." } }})
            ->Method("Steam Lobby Set Member Limit",                      &SteamMatchmakingAPI::SetLobbyMemberLimit,
                {{ { "Lobby ID",    "The SteamID of the lobby." },
                   { "Max Members", "The maximum number of members to allow." } }})
            ->Method("Steam Lobby Get Member Limit",                      &SteamMatchmakingAPI::GetLobbyMemberLimit,
                {{{ "Lobby ID", "The SteamID of the lobby." }}})
            ->Method("Steam Lobby Invite User",                           &SteamMatchmakingAPI::InviteUserToLobby,
                {{ { "Lobby ID",   "The SteamID of the lobby." },
                   { "Invitee ID", "The SteamID of the user to invite." } }})
            ->Method("Steam Lobby Leave",                                 &SteamMatchmakingAPI::LeaveLobby,
                {{{ "Lobby ID", "The SteamID of the lobby to leave." }}})
            ->Method("Steam Lobby List Filter String",                    &SteamMatchmakingAPI::AddRequestLobbyListStringFilter,
                {{ { "Key",        "The metadata key to filter on." },
                   { "Value",      "The value to match." },
                   { "Comparison", "The SteamLobbyComparison enum value for the comparison operator." } }})
            ->Method("Steam Lobby List Filter Numerical",                 &SteamMatchmakingAPI::AddRequestLobbyListNumericalFilter,
                {{ { "Key",        "The metadata key to filter on." },
                   { "Value",      "The integer value to compare against." },
                   { "Comparison", "The SteamLobbyComparison enum value for the comparison operator." } }})
            ->Method("Steam Lobby List Filter Near Value",                &SteamMatchmakingAPI::AddRequestLobbyListNearValueFilter,
                {{ { "Key",   "The metadata key to sort by." },
                   { "Value", "The reference value; results are sorted by proximity to this number." } }})
            ->Method("Steam Lobby List Filter Slots Available",           &SteamMatchmakingAPI::AddRequestLobbyListFilterSlotsAvailable,
                {{{ "Slots Available", "Only return lobbies with at least this many open slots." }}})
            ->Method("Steam Lobby List Filter Distance",                  &SteamMatchmakingAPI::AddRequestLobbyListDistanceFilter,
                {{{ "Distance Filter", "The SteamLobbyDistanceFilter enum value: Close, Default, Far, or Worldwide." }}})
            ->Method("Steam Lobby List Filter Result Count",              &SteamMatchmakingAPI::AddRequestLobbyListResultCountFilter,
                {{{ "Max Results", "Maximum number of lobbies to return from Request Lobby List." }}})
            ->Method("Steam Lobby Create",                                &SteamMatchmakingAPI::CreateLobby,
                {{ { "Lobby Type",   "The SteamLobbyType enum value: Private, FriendsOnly, Public, or Invisible." },
                   { "Max Members",  "The maximum number of members for the lobby (1-250)." } }})
            ->Method("Steam Lobby Join",                                  &SteamMatchmakingAPI::JoinLobby,
                {{{ "Lobby ID", "The SteamID of the lobby to join." }}})
            ->Method("Steam Lobby Request List",                          &SteamMatchmakingAPI::RequestLobbyList);

        bc->Class<SteamRemotePlayAPI>("Remote Play")
            ->Attribute(AZ::Script::Attributes::Category, "Steam")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Method("Steam Remote Play Get Session Count",          &SteamRemotePlayAPI::GetSessionCount)
            ->Method("Steam Remote Play Get Session ID",             &SteamRemotePlayAPI::GetSessionID,
                {{{ "Index", "Zero-based index into the active Remote Play session list." }}})
            ->Method("Steam Remote Play Get Session Steam ID",       &SteamRemotePlayAPI::GetSessionSteamID,
                {{{ "Session ID", "The Remote Play session ID returned by Get Session ID." }}})
            ->Method("Steam Remote Play Get Session Client Name",    &SteamRemotePlayAPI::GetSessionClientName,
                {{{ "Session ID", "The Remote Play session ID." }}})
            ->Method("Steam Remote Play Get Session Client Form Factor", &SteamRemotePlayAPI::GetSessionClientFormFactor,
                {{{ "Session ID", "The Remote Play session ID. Returns ESteamDeviceFormFactor: 0=Unknown, 1=Phone, 2=Tablet, 3=Computer, 4=TV." }}})
            ->Method("Steam Remote Play Get Session Client Resolution", &SteamRemotePlayAPI::GetSessionClientResolution,
                {{ { "Session ID", "The Remote Play session ID." },
                   { "Out Width",  "Receives the client display width in pixels." },
                   { "Out Height", "Receives the client display height in pixels." } }})
            ->Method("Steam Remote Play Send Invite",                &SteamRemotePlayAPI::SendRemotePlayTogetherInvite,
                {{{ "Friend ID", "The SteamID of the friend to invite to the current Remote Play Together session." }}});

        bc->Class<SteamStorageAPI>("Remote Storage")
            ->Attribute(AZ::Script::Attributes::Category, "Steam")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Method("Steam Cloud File Write",                    &SteamStorageAPI::FileWrite,
                {{ { "File Name", "The name of the cloud file to write (relative path, forward slashes)." },
                   { "Data",      "The binary data to write." } }})
            ->Method("Steam Cloud File Read",                     &SteamStorageAPI::FileRead,
                {{ { "File Name", "The name of the cloud file to read." },
                   { "Out Data",  "Receives the file contents as a byte array." } }})
            ->Method("Steam Cloud File Exists",                   &SteamStorageAPI::FileExists,
                {{{ "File Name", "The name of the cloud file to check." }}})
            ->Method("Steam Cloud File Persisted",                &SteamStorageAPI::FilePersisted,
                {{{ "File Name", "The name of the cloud file to check." }}})
            ->Method("Steam Cloud Get File Size",                 &SteamStorageAPI::GetFileSize,
                {{{ "File Name", "The name of the cloud file to query. Returns -1 if not found." }}})
            ->Method("Steam Cloud Get File Timestamp",            &SteamStorageAPI::GetFileTimestamp,
                {{{ "File Name", "The name of the cloud file to query. Returns a Unix timestamp." }}})
            ->Method("Steam Cloud File Forget",                   &SteamStorageAPI::FileForget,
                {{{ "File Name", "The cloud file to unmap from Steam Cloud sync. Local copy is kept." }}})
            ->Method("Steam Cloud File Delete",                   &SteamStorageAPI::FileDelete,
                {{{ "File Name", "The cloud file to permanently delete from both local storage and Steam Cloud." }}})
            ->Method("Steam Cloud Get File Count",                &SteamStorageAPI::GetFileCount)
            ->Method("Steam Cloud Get File Name And Size",        &SteamStorageAPI::GetFileNameAndSize,
                {{ { "Index",    "Zero-based index into the cloud file list." },
                   { "Out Size", "Receives the file size in bytes." } }})
            ->Method("Steam Cloud Get Quota",                     &SteamStorageAPI::GetQuota,
                {{ { "Out Total Bytes",     "Receives the total cloud storage quota in bytes." },
                   { "Out Available Bytes", "Receives the remaining available cloud storage in bytes." } }})
            ->Method("Steam Cloud Is Enabled For Account",        &SteamStorageAPI::IsCloudEnabledForAccount)
            ->Method("Steam Cloud Is Enabled For App",            &SteamStorageAPI::IsCloudEnabledForApp)
            ->Method("Steam Cloud Set Enabled For App",           &SteamStorageAPI::SetCloudEnabledForApp,
                {{{ "Enabled", "Pass true to enable Steam Cloud sync for this app; false to disable." }}})
            ->Method("Steam Cloud File Share",                    &SteamStorageAPI::FileShare,
                {{{ "File Name", "The cloud file to share as a UGC handle for workshop use." }}})
            ->Method("Steam Cloud File Write Async",              &SteamStorageAPI::FileWriteAsync,
                {{ { "File Name", "The name of the cloud file to write." },
                   { "Data",      "The binary data to write." } }})
            ->Method("Steam Cloud File Read Async",               &SteamStorageAPI::FileReadAsync,
                {{ { "File Name",      "The name of the cloud file to read." },
                   { "Offset",         "Byte offset into the file to start reading from." },
                   { "Bytes To Read",  "Number of bytes to read." } }})
            ->Method("Steam Cloud Subscribe Published File",      &SteamStorageAPI::SubscribePublishedFile,
                {{{ "Published File ID", "The ID of the UGC published file to subscribe to." }}})
            ->Method("Steam Cloud Unsubscribe Published File",    &SteamStorageAPI::UnsubscribePublishedFile,
                {{{ "Published File ID", "The ID of the UGC published file to unsubscribe from." }}});

        bc->Class<SteamScreenshotsAPI>("Screenshots")
            ->Attribute(AZ::Script::Attributes::Category, "Steam")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Method("Steam Screenshots Trigger",                  &SteamScreenshotsAPI::TriggerScreenshot)
            ->Method("Steam Screenshots Write",                    &SteamScreenshotsAPI::WriteScreenshot,
                {{ { "Data",   "Raw RGBA8 pixel buffer (width * height * 4 bytes)." },
                   { "Width",  "Width of the screenshot in pixels." },
                   { "Height", "Height of the screenshot in pixels." } }})
            ->Method("Steam Screenshots Add To Library",           &SteamScreenshotsAPI::AddScreenshotToLibrary,
                {{ { "File Name",           "Absolute path to the JPEG or PNG screenshot file." },
                   { "Thumbnail File Name", "Absolute path to a thumbnail image, or empty string." },
                   { "Width",               "Width of the image in pixels." },
                   { "Height",              "Height of the image in pixels." } }})
            ->Method("Steam Screenshots Set Caption",              &SteamScreenshotsAPI::SetScreenshotCaption,
                {{ { "Screenshot Handle", "The handle of the screenshot to caption." },
                   { "Caption",           "The user-visible caption to attach to the screenshot." } }})
            ->Method("Steam Screenshots Tag User",                 &SteamScreenshotsAPI::TagUser,
                {{ { "Screenshot Handle", "The handle of the screenshot to tag." },
                   { "User ID",           "The SteamID of the user to tag in the screenshot." } }})
            ->Method("Steam Screenshots Tag Published File",       &SteamScreenshotsAPI::TagPublishedFile,
                {{ { "Screenshot Handle",  "The handle of the screenshot to tag." },
                   { "Published File ID",  "The ID of the workshop item to associate with the screenshot." } }})
            ->Method("Steam Screenshots Is Hooked",                &SteamScreenshotsAPI::IsScreenshotsHooked)
            ->Method("Steam Screenshots Hook",                     &SteamScreenshotsAPI::HookScreenshots,
                {{{ "Hook", "If true, disables the built-in screenshot capture so your game can provide its own via On Screenshot Requested." }}});

        bc->Class<SteamTimelineAPI>("Timeline")
            ->Attribute(AZ::Script::Attributes::Category, "Steam")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Method("Steam Timeline Set Tooltip",                     &SteamTimelineAPI::SetTimelineTooltip,
                {{ { "Description", "Localised description shown when the user hovers over the timeline bar." },
                   { "Time Delta",  "Seconds offset from now. Negative values indicate a past moment." } }})
            ->Method("Steam Timeline Clear Tooltip",                   &SteamTimelineAPI::ClearTimelineTooltip,
                {{{ "Time Delta", "Seconds offset from now." }}})
            ->Method("Steam Timeline Set Game Mode",                   &SteamTimelineAPI::SetTimelineGameMode,
                {{{ "Mode", "Controls the colour of the timeline bar: Playing=1, Staging=2, Menus=3, LoadingScreen=4." }}})
            ->Method("Steam Timeline Add Instantaneous Event",         &SteamTimelineAPI::AddInstantaneousTimelineEvent,
                {{ { "Title",               "Localised event title." },
                   { "Description",         "Localised event description." },
                   { "Icon",                "Icon name uploaded to Steamworks, or a built-in \"steam_\" icon." },
                   { "Icon Priority",       "Display priority 0-1000. Higher values appear more prominently." },
                   { "Start Offset Seconds","Seconds offset from now. Negative = past." },
                   { "Clip Priority",       "None=1, Standard=2, Featured=3. Controls whether Steam offers a clip." } }})
            ->Method("Steam Timeline Add Range Event",                 &SteamTimelineAPI::AddRangeTimelineEvent,
                {{ { "Title",               "Localised event title." },
                   { "Description",         "Localised event description." },
                   { "Icon",                "Icon name." },
                   { "Icon Priority",       "Display priority 0-1000." },
                   { "Start Offset Seconds","Seconds offset from now for the start of the range." },
                   { "Duration",            "Length of the range in seconds (max 600)." },
                   { "Clip Priority",       "None=1, Standard=2, Featured=3." } }})
            ->Method("Steam Timeline Start Range Event",               &SteamTimelineAPI::StartRangeTimelineEvent,
                {{ { "Title",               "Localised event title." },
                   { "Description",         "Localised event description." },
                   { "Icon",                "Icon name." },
                   { "Priority",            "Display priority 0-1000." },
                   { "Start Offset Seconds","Seconds offset from now." },
                   { "Clip Priority",       "None=1, Standard=2, Featured=3." } }})
            ->Method("Steam Timeline Update Range Event",              &SteamTimelineAPI::UpdateRangeTimelineEvent,
                {{ { "Event Handle",  "Handle of the open range event to update." },
                   { "Title",        "New localised title." },
                   { "Description",  "New localised description." },
                   { "Icon",         "New icon name." },
                   { "Priority",     "New display priority 0-1000." },
                   { "Clip Priority","None=1, Standard=2, Featured=3." } }})
            ->Method("Steam Timeline End Range Event",                 &SteamTimelineAPI::EndRangeTimelineEvent,
                {{ { "Event Handle",       "Handle of the open range event to close." },
                   { "End Offset Seconds", "Seconds offset from now for the end of the range." } }})
            ->Method("Steam Timeline Remove Event",                    &SteamTimelineAPI::RemoveTimelineEvent,
                {{{ "Event Handle", "Handle of the timeline event to remove." }}})
            ->Method("Steam Timeline Does Event Recording Exist",      &SteamTimelineAPI::DoesEventRecordingExist,
                {{{ "Event Handle", "Handle of the event to query. Result fires On Timeline Event Recording Exists." }}})
            ->Method("Steam Timeline Start Game Phase",                &SteamTimelineAPI::StartGamePhase)
            ->Method("Steam Timeline End Game Phase",                  &SteamTimelineAPI::EndGamePhase)
            ->Method("Steam Timeline Set Game Phase ID",               &SteamTimelineAPI::SetGamePhaseID,
                {{{ "Phase ID", "A persistent identifier for this phase (e.g. a match ID or chapter name)." }}})
            ->Method("Steam Timeline Does Game Phase Recording Exist", &SteamTimelineAPI::DoesGamePhaseRecordingExist,
                {{{ "Phase ID", "The phase ID to query. Result fires On Timeline Game Phase Recording Exists." }}})
            ->Method("Steam Timeline Add Game Phase Tag",              &SteamTimelineAPI::AddGamePhaseTag,
                {{ { "Tag Name",  "Localised name of the tag." },
                   { "Tag Icon",  "Icon name for the tag." },
                   { "Tag Group", "Localised name of the tag group (used for filtering)." },
                   { "Priority",  "Display priority 0-1000." } }})
            ->Method("Steam Timeline Set Game Phase Attribute",        &SteamTimelineAPI::SetGamePhaseAttribute,
                {{ { "Attribute Group", "Localised group name for the attribute." },
                   { "Attribute Value", "Localised current value of the attribute." },
                   { "Priority",        "Display priority 0-1000." } }})
            ->Method("Steam Timeline Open Overlay To Game Phase",      &SteamTimelineAPI::OpenOverlayToGamePhase,
                {{{ "Phase ID", "The phase ID previously set with Set Game Phase ID." }}})
            ->Method("Steam Timeline Open Overlay To Event",           &SteamTimelineAPI::OpenOverlayToTimelineEvent,
                {{{ "Event Handle", "Handle of the timeline event to open the overlay to." }}});

        bc->Class<SteamStatsAPI>("Stats")
            ->Attribute(AZ::Script::Attributes::Category, "Steam")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Method("Steam Stats Request Current Stats",             &SteamStatsAPI::RequestCurrentStats)
            ->Method("Steam Stats Store Stats",                       &SteamStatsAPI::StoreStats)
            ->Method("Steam Stats Get Stat Int",                      &SteamStatsAPI::GetStatInt,
                {{ { "Name",      "The API name of the stat as defined in the Steamworks partner portal." },
                   { "Out Value", "Receives the current integer value of the stat." } }})
            ->Method("Steam Stats Get Stat Float",                    &SteamStatsAPI::GetStatFloat,
                {{ { "Name",      "The API name of the stat as defined in the Steamworks partner portal." },
                   { "Out Value", "Receives the current float value of the stat." } }})
            ->Method("Steam Stats Set Stat Int",                      &SteamStatsAPI::SetStatInt,
                {{ { "Name",  "The API name of the stat." },
                   { "Value", "The new integer value to set. Call Store Stats to persist." } }})
            ->Method("Steam Stats Set Stat Float",                    &SteamStatsAPI::SetStatFloat,
                {{ { "Name",  "The API name of the stat." },
                   { "Value", "The new float value to set. Call Store Stats to persist." } }})
            ->Method("Steam Stats Update Avg Rate Stat",              &SteamStatsAPI::UpdateAvgRateStat,
                {{ { "Name",                "The API name of the AVGRATE stat." },
                   { "Count This Session",  "The numerator amount accumulated this session." },
                   { "Session Length",      "The denominator time in seconds for this session." } }})
            ->Method("Steam Stats Get Achievement",                   &SteamStatsAPI::GetAchievement,
                {{ { "Name",         "The API name of the achievement as defined in the Steamworks partner portal." },
                   { "Out Achieved", "Receives true if the achievement has been unlocked." } }})
            ->Method("Steam Stats Set Achievement",                   &SteamStatsAPI::SetAchievement,
                {{{ "Name", "The API name of the achievement to unlock. Call Store Stats to persist." }}})
            ->Method("Steam Stats Clear Achievement",                 &SteamStatsAPI::ClearAchievement,
                {{{ "Name", "The API name of the achievement to reset (lock). Call Store Stats to persist." }}})
            ->Method("Steam Stats Get Achievement And Unlock Time",   &SteamStatsAPI::GetAchievementAndUnlockTime,
                {{ { "Name",            "The API name of the achievement." },
                   { "Out Achieved",    "Receives true if the achievement has been unlocked." },
                   { "Out Unlock Time", "Receives the Unix timestamp when the achievement was unlocked (0 if locked)." } }})
            ->Method("Steam Stats Indicate Achievement Progress",     &SteamStatsAPI::IndicateAchievementProgress,
                {{ { "Name",         "The API name of the achievement." },
                   { "Cur Progress", "The current progress value to display to the user." },
                   { "Max Progress", "The total required to unlock the achievement." } }})
            ->Method("Steam Stats Reset All Stats",                   &SteamStatsAPI::ResetAllStats,
                {{{ "Achievements Too", "If true, also resets all achievement unlock states." }}})
            ->Method("Steam Stats Get Num Achievements",              &SteamStatsAPI::GetNumAchievements)
            ->Method("Steam Stats Get Achievement Name",              &SteamStatsAPI::GetAchievementName,
                {{{ "Index", "Zero-based index into the achievement list for this app." }}})
            ->Method("Steam Stats Get Achievement Display Attribute",  &SteamStatsAPI::GetAchievementDisplayAttribute,
                {{ { "Name", "The API name of the achievement." },
                   { "Key",  "The attribute to retrieve: \"name\", \"desc\", or \"hidden\"." } }})
            ->Method("Steam Stats Get Achievement Icon",              &SteamStatsAPI::GetAchievementIcon,
                {{{ "Name", "The API name of the achievement. Use Get Image RGBA to decode the returned handle." }}})
            ->Method("Steam Stats Get User Stat Int",                 &SteamStatsAPI::GetUserStatInt,
                {{ { "User ID",   "The SteamID of the user whose stat to retrieve (requires Request User Stats first)." },
                   { "Name",      "The API name of the stat." },
                   { "Out Value", "Receives the integer value of the stat." } }})
            ->Method("Steam Stats Get User Stat Float",               &SteamStatsAPI::GetUserStatFloat,
                {{ { "User ID",   "The SteamID of the user whose stat to retrieve (requires Request User Stats first)." },
                   { "Name",      "The API name of the stat." },
                   { "Out Value", "Receives the float value of the stat." } }})
            ->Method("Steam Stats Get User Achievement",              &SteamStatsAPI::GetUserAchievement,
                {{ { "User ID",      "The SteamID of the user (requires Request User Stats first)." },
                   { "Name",         "The API name of the achievement." },
                   { "Out Achieved", "Receives true if the user has unlocked the achievement." } }})
            ->Method("Steam Stats Get User Achievement And Unlock Time", &SteamStatsAPI::GetUserAchievementAndUnlockTime,
                {{ { "User ID",         "The SteamID of the user (requires Request User Stats first)." },
                   { "Name",            "The API name of the achievement." },
                   { "Out Achieved",    "Receives true if the user has unlocked the achievement." },
                   { "Out Unlock Time", "Receives the Unix timestamp the achievement was unlocked (0 if locked)." } }})
            ->Method("Steam Leaderboard Get Name",                    &SteamStatsAPI::GetLeaderboardName,
                {{{ "Leaderboard", "The leaderboard handle obtained from Find Or Create Leaderboard or Find Leaderboard." }}})
            ->Method("Steam Leaderboard Get Entry Count",             &SteamStatsAPI::GetLeaderboardEntryCount,
                {{{ "Leaderboard", "The leaderboard handle." }}})
            ->Method("Steam Leaderboard Get Sort Method",             &SteamStatsAPI::GetLeaderboardSortMethod,
                {{{ "Leaderboard", "The leaderboard handle. Returns a SteamLeaderboardSortMethod integer value." }}})
            ->Method("Steam Leaderboard Get Display Type",            &SteamStatsAPI::GetLeaderboardDisplayType,
                {{{ "Leaderboard", "The leaderboard handle. Returns a SteamLeaderboardDisplayType integer value." }}})
            ->Method("Steam Stats Request User Stats",                &SteamStatsAPI::RequestUserStats,
                {{{ "User ID", "The SteamID of the user whose stats and achievements to request." }}})
            ->Method("Steam Leaderboard Find Or Create",              &SteamStatsAPI::FindOrCreateLeaderboard,
                {{ { "Name",         "The name of the leaderboard to find or create." },
                   { "Sort Method",  "The sort method (SteamLeaderboardSortMethod): None, Ascending, or Descending." },
                   { "Display Type", "The display type (SteamLeaderboardDisplayType): None, Numeric, TimeSeconds, or TimeMilliSeconds." } }})
            ->Method("Steam Leaderboard Find",                        &SteamStatsAPI::FindLeaderboard,
                {{{ "Name", "The name of the existing leaderboard to find." }}})
            ->Method("Steam Leaderboard Download Entries",            &SteamStatsAPI::DownloadLeaderboardEntries,
                {{ { "Leaderboard",   "The leaderboard handle." },
                   { "Data Request",  "The SteamLeaderboardDataRequest type: Global, GlobalAroundUser, Friends, or Users." },
                   { "Range Start",   "Start of the range to download (1-based for Global)." },
                   { "Range End",     "End of the range to download." } }})
            ->Method("Steam Leaderboard Upload Score",                &SteamStatsAPI::UploadLeaderboardScore,
                {{ { "Leaderboard", "The leaderboard handle." },
                   { "Method",      "The SteamLeaderboardUploadScoreMethod: KeepBest or ForceUpdate." },
                   { "Score",       "The score to upload." } }})
            ->Method("Steam Stats Get Number Of Current Players",     &SteamStatsAPI::GetNumberOfCurrentPlayers)
            ->Method("Steam Stats Request Global Achievement Percentages", &SteamStatsAPI::RequestGlobalAchievementPercentages)
            ->Method("Steam Stats Request Global Stats",              &SteamStatsAPI::RequestGlobalStats,
                {{{ "History Days", "Number of days of history to request (max 60)." }}});

        bc->Class<SteamUserAPI>("User")
            ->Attribute(AZ::Script::Attributes::Category, "Steam")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Method("Steam Is Logged On",                   &SteamUserAPI::IsLoggedOn)
            ->Method("Steam Get Steam ID",                   &SteamUserAPI::GetSteamID)
            ->Method("Steam Get Player Steam Level",         &SteamUserAPI::GetPlayerSteamLevel)
            ->Method("Steam Get Game Badge Level",           &SteamUserAPI::GetGameBadgeLevel,
                {{ { "Series", "Badge series number. 1 for the standard badge, higher values for foil/special editions." },
                   { "Foil",   "Pass true to query the foil badge level." } }})
            ->Method("Steam Get Auth Ticket For Web API",    &SteamUserAPI::GetAuthTicketForWebApi,
                {{{ "Identity", "The service identity string that will consume the ticket, e.g. \"steamcommunity.com\"." }}})
            ->Method("Steam Cancel Auth Ticket",             &SteamUserAPI::CancelAuthTicket,
                {{{ "Ticket Handle", "The auth ticket handle returned by Steam Get Auth Ticket For Web API." }}})
            ->Method("Steam Request Store Auth URL",         &SteamUserAPI::RequestStoreAuthURL,
                {{{ "Redirect URL", "The URL the user will be redirected to after authenticating with Steam." }}})
            ->Method("Steam Get Market Eligibility",         &SteamUserAPI::GetMarketEligibility)
            ->Method("Steam Get Duration Control",           &SteamUserAPI::GetDurationControl)
            ->Method("Steam Request Encrypted App Ticket",   &SteamUserAPI::RequestEncryptedAppTicket,
                {{{ "Data To Include", "Optional binary blob to embed in the ticket for your own game server to read." }}});

        bc->Class<SteamUGCAPI>("User Generated Content")
            ->Attribute(AZ::Script::Attributes::Category, "Steam")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Method("Steam UGC Get Item State",                    &SteamUGCAPI::GetItemState,
                {{{ "Published File ID", "The ID of the workshop item. Returns a bitmask of EItemState flags." }}})
            ->Method("Steam UGC Get Item Download Info",            &SteamUGCAPI::GetItemDownloadInfo,
                {{ { "Published File ID",    "The ID of the workshop item." },
                   { "Out Bytes Downloaded", "Receives the number of bytes downloaded so far." },
                   { "Out Bytes Total",      "Receives the total size of the download in bytes." } }})
            ->Method("Steam UGC Get Item Install Info",             &SteamUGCAPI::GetItemInstallInfo,
                {{ { "Published File ID", "The ID of the installed workshop item." },
                   { "Out Size On Disk",  "Receives the disk size in bytes." },
                   { "Out Folder",        "Receives the absolute path to the installed content folder." },
                   { "Out Timestamp",     "Receives the last-updated Unix timestamp." } }})
            ->Method("Steam UGC Get Num Subscribed Items",          &SteamUGCAPI::GetNumSubscribedItems)
            ->Method("Steam UGC Get Subscribed Items",              &SteamUGCAPI::GetSubscribedItems,
                {{ { "Out IDs",      "Array that receives the subscribed published file IDs." },
                   { "Max Entries",  "The maximum number of IDs to return." } }})
            ->Method("Steam UGC Create Query All",                  &SteamUGCAPI::CreateQueryAllUGCRequest,
                {{ { "Query Type",          "EUGCQuery cast to int, e.g. 0 = RankedByVote." },
                   { "Matching File Type",  "EUGCMatchingUGCType cast to int." },
                   { "Creator App ID",      "The AppID of the app that created the items." },
                   { "Consumer App ID",     "The AppID of the app that will consume the items." },
                   { "Page",                "One-based page number of results." } }})
            ->Method("Steam UGC Create Query User",                 &SteamUGCAPI::CreateQueryUserUGCRequest,
                {{ { "Account ID",         "The SteamID of the user to query items for." },
                   { "List Type",          "EUserUGCList cast to int." },
                   { "Matching File Type", "EUGCMatchingUGCType cast to int." },
                   { "Sort Order",         "EUserUGCListSortOrder cast to int." },
                   { "Creator App ID",     "The AppID of the creator app." },
                   { "Consumer App ID",    "The AppID of the consumer app." },
                   { "Page",               "One-based page number of results." } }})
            ->Method("Steam UGC Create Query Details",              &SteamUGCAPI::CreateQueryUGCDetailsRequest,
                {{{ "Published File IDs", "Array of specific item IDs to query details for." }}})
            ->Method("Steam UGC Query Add Required Tag",            &SteamUGCAPI::AddRequiredTag,
                {{ { "Query Handle", "The query handle to configure." },
                   { "Tag Name",     "The tag that items must have to appear in results." } }})
            ->Method("Steam UGC Query Add Excluded Tag",            &SteamUGCAPI::AddExcludedTag,
                {{ { "Query Handle", "The query handle to configure." },
                   { "Tag Name",     "Items with this tag will be excluded from results." } }})
            ->Method("Steam UGC Query Set Match Any Tag",           &SteamUGCAPI::SetMatchAnyTag,
                {{ { "Query Handle",   "The query handle to configure." },
                   { "Match Any Tag",  "If true, items matching ANY required tag are returned; if false, ALL tags must match." } }})
            ->Method("Steam UGC Query Add Required Key Value",      &SteamUGCAPI::AddRequiredKeyValueTag,
                {{ { "Query Handle", "The query handle to configure." },
                   { "Key",          "The metadata key that must be present." },
                   { "Value",        "The value the key must equal." } }})
            ->Method("Steam UGC Query Set Return Long Description", &SteamUGCAPI::SetReturnLongDescription,
                {{ { "Query Handle",           "The query handle to configure." },
                   { "Return Long Description","If true, the full description text is included in results." } }})
            ->Method("Steam UGC Query Set Return Metadata",         &SteamUGCAPI::SetReturnMetadata,
                {{ { "Query Handle",     "The query handle to configure." },
                   { "Return Metadata",  "If true, metadata strings are included in results." } }})
            ->Method("Steam UGC Query Set Return Children",         &SteamUGCAPI::SetReturnChildren,
                {{ { "Query Handle",    "The query handle to configure." },
                   { "Return Children", "If true, child item IDs are included in results." } }})
            ->Method("Steam UGC Query Set Return Additional Previews", &SteamUGCAPI::SetReturnAdditionalPreviews,
                {{ { "Query Handle",              "The query handle to configure." },
                   { "Return Additional Previews","If true, extra preview images/videos are included in results." } }})
            ->Method("Steam UGC Query Set Return Total Only",       &SteamUGCAPI::SetReturnTotalOnly,
                {{ { "Query Handle",      "The query handle to configure." },
                   { "Return Total Only", "If true, only the total result count is returned (no item data)." } }})
            ->Method("Steam UGC Query Set Language",                &SteamUGCAPI::SetLanguage,
                {{ { "Query Handle", "The query handle to configure." },
                   { "Language",     "The language code for localised strings, e.g. \"english\", \"german\"." } }})
            ->Method("Steam UGC Query Set Allow Cached Response",   &SteamUGCAPI::SetAllowCachedResponse,
                {{ { "Query Handle",    "The query handle to configure." },
                   { "Max Age Seconds", "Maximum age in seconds for a cached result to be considered valid." } }})
            ->Method("Steam UGC Release Query",                     &SteamUGCAPI::ReleaseQueryUGCRequest,
                {{{ "Query Handle", "The query handle to release. Must be called after processing results." }}})
            ->Method("Steam UGC Start Item Update",                 &SteamUGCAPI::StartItemUpdate,
                {{ { "Consumer App ID",   "The AppID of the app consuming the workshop item." },
                   { "Published File ID", "The ID of the workshop item to update." } }})
            ->Method("Steam UGC Set Item Title",                    &SteamUGCAPI::SetItemTitle,
                {{ { "Update Handle", "The update handle from Start Item Update." },
                   { "Title",         "The new title for the item (max 128 bytes)." } }})
            ->Method("Steam UGC Set Item Description",              &SteamUGCAPI::SetItemDescription,
                {{ { "Update Handle", "The update handle from Start Item Update." },
                   { "Description",   "The new description for the item (max 8000 bytes)." } }})
            ->Method("Steam UGC Set Item Metadata",                 &SteamUGCAPI::SetItemMetadata,
                {{ { "Update Handle", "The update handle from Start Item Update." },
                   { "Metadata",      "Developer metadata string for the item (max 5000 bytes)." } }})
            ->Method("Steam UGC Set Item Visibility",               &SteamUGCAPI::SetItemVisibility,
                {{ { "Update Handle", "The update handle from Start Item Update." },
                   { "Visibility",    "The SteamUGCVisibility enum: Public, FriendsOnly, Private, or Unlisted." } }})
            ->Method("Steam UGC Set Item Tags",                     &SteamUGCAPI::SetItemTags,
                {{ { "Update Handle", "The update handle from Start Item Update." },
                   { "Tags",          "Array of tag strings to associate with the item." } }})
            ->Method("Steam UGC Set Item Content",                  &SteamUGCAPI::SetItemContent,
                {{ { "Update Handle",   "The update handle from Start Item Update." },
                   { "Content Folder",  "Absolute path to the folder containing the item content." } }})
            ->Method("Steam UGC Set Item Preview",                  &SteamUGCAPI::SetItemPreview,
                {{ { "Update Handle", "The update handle from Start Item Update." },
                   { "Preview File",  "Absolute path to the preview image (JPG, PNG, or GIF, max 1 MB)." } }})
            ->Method("Steam UGC Download Item",                     &SteamUGCAPI::DownloadItem,
                {{ { "Published File ID", "The ID of the workshop item to download or update." },
                   { "High Priority",     "If true, moves the item to the front of the download queue." } }})
            ->Method("Steam UGC Send Query",                        &SteamUGCAPI::SendQueryUGCRequest,
                {{{ "Query Handle", "The configured query handle to execute." }}})
            ->Method("Steam UGC Request Details",                   &SteamUGCAPI::RequestUGCDetails,
                {{ { "Published File ID", "The ID of the workshop item to get full details for." },
                   { "Max Age Seconds",   "Maximum age in seconds for cached details to be considered valid." } }})
            ->Method("Steam UGC Create Item",                       &SteamUGCAPI::CreateItem,
                {{ { "Consumer App ID", "The AppID of the app the workshop item is for." },
                   { "File Type",       "EWorkshopFileType cast to int, typically 0 (Community)." } }})
            ->Method("Steam UGC Submit Item Update",                &SteamUGCAPI::SubmitItemUpdate,
                {{ { "Update Handle", "The update handle from Start Item Update." },
                   { "Change Note",   "A description of the changes made in this update." } }})
            ->Method("Steam UGC Add Item To Favorites",             &SteamUGCAPI::AddItemToFavorites,
                {{ { "App ID",            "The AppID of the app the item belongs to." },
                   { "Published File ID", "The ID of the workshop item to favourite." } }})
            ->Method("Steam UGC Remove Item From Favorites",        &SteamUGCAPI::RemoveItemFromFavorites,
                {{ { "App ID",            "The AppID of the app the item belongs to." },
                   { "Published File ID", "The ID of the workshop item to unfavourite." } }})
            ->Method("Steam UGC Set User Item Vote",                &SteamUGCAPI::SetUserItemVote,
                {{ { "Published File ID", "The ID of the workshop item to vote on." },
                   { "Vote Up",           "Pass true to vote up, false to vote down." } }})
            ->Method("Steam UGC Get User Item Vote",                &SteamUGCAPI::GetUserItemVote,
                {{{ "Published File ID", "The ID of the workshop item to retrieve the current vote for." }}})
            ->Method("Steam UGC Start Playtime Tracking",           &SteamUGCAPI::StartPlaytimeTracking,
                {{{ "Published File IDs", "Array of workshop item IDs to begin tracking playtime for." }}})
            ->Method("Steam UGC Stop Playtime Tracking",            &SteamUGCAPI::StopPlaytimeTracking,
                {{{ "Published File IDs", "Array of workshop item IDs to stop tracking playtime for." }}})
            ->Method("Steam UGC Stop Playtime Tracking All Items",  &SteamUGCAPI::StopPlaytimeTrackingForAllItems)
            ->Method("Steam UGC Add Dependency",                    &SteamUGCAPI::AddDependency,
                {{ { "Parent ID", "The ID of the parent workshop item." },
                   { "Child ID",  "The ID of the child item that the parent depends on." } }})
            ->Method("Steam UGC Remove Dependency",                 &SteamUGCAPI::RemoveDependency,
                {{ { "Parent ID", "The ID of the parent workshop item." },
                   { "Child ID",  "The ID of the child dependency to remove." } }})
            ->Method("Steam UGC Delete Item",                       &SteamUGCAPI::DeleteItem,
                {{{ "Published File ID", "The ID of the workshop item to permanently delete." }}})
            ->Method("Steam UGC Get Workshop EULA Status",          &SteamUGCAPI::GetWorkshopEULAStatus);

        bc->Class<SteamUtilsAPI>("Utils")
            ->Attribute(AZ::Script::Attributes::Category, "Steam")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Method("Steam Utils Get Server Real Time",              &SteamUtilsAPI::GetServerRealTime)
            ->Method("Steam Utils Get IP Country",                    &SteamUtilsAPI::GetIPCountry)
            ->Method("Steam Utils Get Steam UI Language",             &SteamUtilsAPI::GetSteamUILanguage)
            ->Method("Steam Utils Get Image Size",                    &SteamUtilsAPI::GetImageSize,
                {{ { "Image Handle", "The handle to the image (e.g. from Get Small Friend Avatar)." },
                   { "Out Width",    "Receives the image width in pixels." },
                   { "Out Height",   "Receives the image height in pixels." } }})
            ->Method("Steam Utils Get Image RGBA",                    &SteamUtilsAPI::GetImageRGBA,
                {{ { "Image Handle", "The handle to the image to decode." },
                   { "Out Data",     "Receives the raw RGBA8 pixel data (width * height * 4 bytes)." },
                   { "Width",        "The width of the image in pixels (from Get Image Size)." },
                   { "Height",       "The height of the image in pixels (from Get Image Size)." } }})
            ->Method("Steam Utils Is Overlay Enabled",                &SteamUtilsAPI::IsOverlayEnabled)
            ->Method("Steam Utils Is Steam In Big Picture Mode",      &SteamUtilsAPI::IsSteamInBigPictureMode)
            ->Method("Steam Utils Is Steam Running On Steam Deck",    &SteamUtilsAPI::IsSteamRunningOnSteamDeck)
            ->Method("Steam Utils Is Steam Running In VR",            &SteamUtilsAPI::IsSteamRunningInVR)
            ->Method("Steam Utils Show Floating Gamepad Text Input",  &SteamUtilsAPI::ShowFloatingGamepadTextInput,
                {{ { "Input Mode",        "EFloatingGamepadTextInputMode: 0 = single line, 1 = multiple lines, 2 = email, 3 = numeric." },
                   { "X",                 "Horizontal position of the text field hint rectangle." },
                   { "Y",                 "Vertical position of the text field hint rectangle." },
                   { "Width",             "Width of the text field hint rectangle." },
                   { "Height",            "Height of the text field hint rectangle." } }})
            ->Method("Steam Utils Dismiss Floating Gamepad Text Input", &SteamUtilsAPI::DismissFloatingGamepadTextInput)
            ->Method("Steam Utils Filter Text",                       &SteamUtilsAPI::FilterText,
                {{ { "Context",       "ETextFilteringContext: 0 = Unknown, 1 = GameContent, 2 = Chat, 3 = Name." },
                   { "Source Steam ID","The SteamID of the user who authored the text." },
                   { "Input Message", "The text string to filter." },
                   { "Out Filtered",  "Receives the filtered version of the input text." } }})
            ->Method("Steam Utils Get Current Battery Power",         &SteamUtilsAPI::GetCurrentBatteryPower)
            ->Method("Steam Utils Is Steam China Launcher",           &SteamUtilsAPI::IsSteamChinaLauncher);


        // --- Notification buses ---
        bc->EBus<SteamGameServerNotificationBus>("SteamGameServerNotificationBus")
            ->Handler<BehaviorSteamGameServerNotificationHandler>();
        bc->EBus<SteamGameServerStatsNotificationBus>("SteamGameServerStatsNotificationBus")
            ->Handler<BehaviorSteamGameServerStatsNotificationHandler>();

        // --- Result struct classes ---
        bc->Class<SteamInitResult>("SteamInitResult")
            ->Attribute(AZ::Script::Attributes::Category, "Steam/Results")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Property("success",  BehaviorValueProperty(&SteamInitResult::success))
            ->Property("errorMsg", BehaviorValueProperty(&SteamInitResult::errorMsg));
        bc->Class<SteamStatIntResult>("SteamStatIntResult")
            ->Attribute(AZ::Script::Attributes::Category, "Steam/Results")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Property("success", BehaviorValueProperty(&SteamStatIntResult::success))
            ->Property("value",   BehaviorValueProperty(&SteamStatIntResult::value));
        bc->Class<SteamStatFloatResult>("SteamStatFloatResult")
            ->Attribute(AZ::Script::Attributes::Category, "Steam/Results")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Property("success", BehaviorValueProperty(&SteamStatFloatResult::success))
            ->Property("value",   BehaviorValueProperty(&SteamStatFloatResult::value));
        bc->Class<SteamAchievementResult>("SteamAchievementResult")
            ->Attribute(AZ::Script::Attributes::Category, "Steam/Results")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Property("success",  BehaviorValueProperty(&SteamAchievementResult::success))
            ->Property("achieved", BehaviorValueProperty(&SteamAchievementResult::achieved));
        bc->Class<SteamAchievementAndUnlockTimeResult>("SteamAchievementAndUnlockTimeResult")
            ->Attribute(AZ::Script::Attributes::Category, "Steam/Results")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Property("success",    BehaviorValueProperty(&SteamAchievementAndUnlockTimeResult::success))
            ->Property("achieved",   BehaviorValueProperty(&SteamAchievementAndUnlockTimeResult::achieved))
            ->Property("unlockTime", BehaviorValueProperty(&SteamAchievementAndUnlockTimeResult::unlockTime));
        bc->Class<SteamImageSizeResult>("SteamImageSizeResult")
            ->Attribute(AZ::Script::Attributes::Category, "Steam/Results")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Property("success", BehaviorValueProperty(&SteamImageSizeResult::success))
            ->Property("width",   BehaviorValueProperty(&SteamImageSizeResult::width))
            ->Property("height",  BehaviorValueProperty(&SteamImageSizeResult::height));
        bc->Class<SteamFilterTextResult>("SteamFilterTextResult")
            ->Attribute(AZ::Script::Attributes::Category, "Steam/Results")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Property("success",  BehaviorValueProperty(&SteamFilterTextResult::success))
            ->Property("filtered", BehaviorValueProperty(&SteamFilterTextResult::filtered));
        bc->Class<SteamFileNameAndSizeResult>("SteamFileNameAndSizeResult")
            ->Attribute(AZ::Script::Attributes::Category, "Steam/Results")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Property("fileName", BehaviorValueProperty(&SteamFileNameAndSizeResult::fileName))
            ->Property("size",     BehaviorValueProperty(&SteamFileNameAndSizeResult::size));
        bc->Class<SteamQuotaResult>("SteamQuotaResult")
            ->Attribute(AZ::Script::Attributes::Category, "Steam/Results")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Property("success",        BehaviorValueProperty(&SteamQuotaResult::success))
            ->Property("totalBytes",     BehaviorValueProperty(&SteamQuotaResult::totalBytes))
            ->Property("availableBytes", BehaviorValueProperty(&SteamQuotaResult::availableBytes));
        bc->Class<SteamItemDownloadInfoResult>("SteamItemDownloadInfoResult")
            ->Attribute(AZ::Script::Attributes::Category, "Steam/Results")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Property("success",         BehaviorValueProperty(&SteamItemDownloadInfoResult::success))
            ->Property("bytesDownloaded",  BehaviorValueProperty(&SteamItemDownloadInfoResult::bytesDownloaded))
            ->Property("bytesTotal",       BehaviorValueProperty(&SteamItemDownloadInfoResult::bytesTotal));
        bc->Class<SteamItemInstallInfoResult>("SteamItemInstallInfoResult")
            ->Attribute(AZ::Script::Attributes::Category, "Steam/Results")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Property("success",    BehaviorValueProperty(&SteamItemInstallInfoResult::success))
            ->Property("sizeOnDisk", BehaviorValueProperty(&SteamItemInstallInfoResult::sizeOnDisk))
            ->Property("folder",     BehaviorValueProperty(&SteamItemInstallInfoResult::folder))
            ->Property("timestamp",  BehaviorValueProperty(&SteamItemInstallInfoResult::timestamp));
        bc->Class<SteamSessionClientResolutionResult>("SteamSessionClientResolutionResult")
            ->Attribute(AZ::Script::Attributes::Category, "Steam/Results")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Property("success", BehaviorValueProperty(&SteamSessionClientResolutionResult::success))
            ->Property("width",   BehaviorValueProperty(&SteamSessionClientResolutionResult::width))
            ->Property("height",  BehaviorValueProperty(&SteamSessionClientResolutionResult::height));
        bc->Class<SteamInputDigitalActionData>("SteamInputDigitalActionData")
            ->Attribute(AZ::Script::Attributes::Category, "Steam/Input")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Property("active", BehaviorValueProperty(&SteamInputDigitalActionData::active))
            ->Property("state",  BehaviorValueProperty(&SteamInputDigitalActionData::state));
        bc->Class<SteamInputAnalogActionData>("SteamInputAnalogActionData")
            ->Attribute(AZ::Script::Attributes::Category, "Steam/Input")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Property("mode",   BehaviorValueProperty(&SteamInputAnalogActionData::mode))
            ->Property("x",      BehaviorValueProperty(&SteamInputAnalogActionData::x))
            ->Property("y",      BehaviorValueProperty(&SteamInputAnalogActionData::y))
            ->Property("active", BehaviorValueProperty(&SteamInputAnalogActionData::active));
        bc->Class<SteamGSUserStatIntResult>("SteamGSUserStatIntResult")
            ->Attribute(AZ::Script::Attributes::Category, "Steam/GameServerStats")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Property("success", BehaviorValueProperty(&SteamGSUserStatIntResult::success))
            ->Property("value",   BehaviorValueProperty(&SteamGSUserStatIntResult::value));
        bc->Class<SteamGSUserStatFloatResult>("SteamGSUserStatFloatResult")
            ->Attribute(AZ::Script::Attributes::Category, "Steam/GameServerStats")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Property("success", BehaviorValueProperty(&SteamGSUserStatFloatResult::success))
            ->Property("value",   BehaviorValueProperty(&SteamGSUserStatFloatResult::value));
        bc->Class<SteamGSUserAchievementResult>("SteamGSUserAchievementResult")
            ->Attribute(AZ::Script::Attributes::Category, "Steam/GameServerStats")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Property("success",  BehaviorValueProperty(&SteamGSUserAchievementResult::success))
            ->Property("achieved", BehaviorValueProperty(&SteamGSUserAchievementResult::achieved));

        // --- SC-safe stats methods added to SteamStatsAPI registration ---
        bc->Class<SteamStatsAPI>("Steam Stats API")
            ->Attribute(AZ::Script::Attributes::Category, "Steam/Stats")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Method("Steam Stats SC Get Stat Int",                          &SteamStatsAPI::SC_GetStatInt)
            ->Method("Steam Stats SC Get Stat Float",                        &SteamStatsAPI::SC_GetStatFloat)
            ->Method("Steam Stats SC Get Achievement",                       &SteamStatsAPI::SC_GetAchievement)
            ->Method("Steam Stats SC Get Achievement And Unlock Time",       &SteamStatsAPI::SC_GetAchievementAndUnlockTime)
            ->Method("Steam Stats SC Get User Stat Int",                     &SteamStatsAPI::SC_GetUserStatInt)
            ->Method("Steam Stats SC Get User Stat Float",                   &SteamStatsAPI::SC_GetUserStatFloat)
            ->Method("Steam Stats SC Get User Achievement",                  &SteamStatsAPI::SC_GetUserAchievement)
            ->Method("Steam Stats SC Get User Achievement And Unlock Time",  &SteamStatsAPI::SC_GetUserAchievementAndUnlockTime);

        bc->Class<SteamStorageAPI>("Steam Storage API")
            ->Attribute(AZ::Script::Attributes::Category, "Steam/Storage")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Method("Steam Storage SC Get File Name And Size", &SteamStorageAPI::SC_GetFileNameAndSize)
            ->Method("Steam Storage SC Get Quota",              &SteamStorageAPI::SC_GetQuota);

        bc->Class<SteamUGCAPI>("Steam UGC API")
            ->Attribute(AZ::Script::Attributes::Category, "Steam/UGC")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Method("Steam UGC SC Get Item Download Info", &SteamUGCAPI::SC_GetItemDownloadInfo)
            ->Method("Steam UGC SC Get Item Install Info",  &SteamUGCAPI::SC_GetItemInstallInfo);

        bc->Class<SteamUtilsAPI>("Steam Utils API")
            ->Attribute(AZ::Script::Attributes::Category, "Steam/Utils")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Method("Steam Utils SC Get Image Size", &SteamUtilsAPI::SC_GetImageSize)
            ->Method("Steam Utils SC Filter Text",    &SteamUtilsAPI::SC_FilterText);

        bc->Class<SteamRemotePlayAPI>("Steam Remote Play API SC")
            ->Attribute(AZ::Script::Attributes::Category, "Steam/Remote Play")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Method("Steam Remote Play SC Get Session Client Resolution", &SteamRemotePlayAPI::SC_GetSessionClientResolution);

        // --- Game Server API ---
        bc->Class<SteamGameServerAPI>("Steam Game Server API")
            ->Attribute(AZ::Script::Attributes::Category, "Steam/GameServer")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Method("Steam GS Set Product",               &SteamGameServerAPI::SetProduct)
            ->Method("Steam GS Set Game Description",      &SteamGameServerAPI::SetGameDescription)
            ->Method("Steam GS Set Mod Dir",               &SteamGameServerAPI::SetModDir)
            ->Method("Steam GS Set Dedicated Server",      &SteamGameServerAPI::SetDedicatedServer)
            ->Method("Steam GS Log On",                    &SteamGameServerAPI::LogOn)
            ->Method("Steam GS Log On Anonymous",          &SteamGameServerAPI::LogOnAnonymous)
            ->Method("Steam GS Log Off",                   &SteamGameServerAPI::LogOff)
            ->Method("Steam GS Is Logged On",              &SteamGameServerAPI::GSIsLoggedOn)
            ->Method("Steam GS Is Secure",                 &SteamGameServerAPI::GSIsSecure)
            ->Method("Steam GS Get Steam ID",              &SteamGameServerAPI::GSGetSteamID)
            ->Method("Steam GS Was Restart Requested",     &SteamGameServerAPI::WasRestartRequested)
            ->Method("Steam GS Set Max Player Count",      &SteamGameServerAPI::SetMaxPlayerCount)
            ->Method("Steam GS Set Bot Player Count",      &SteamGameServerAPI::SetBotPlayerCount)
            ->Method("Steam GS Set Server Name",           &SteamGameServerAPI::SetServerName)
            ->Method("Steam GS Set Map Name",              &SteamGameServerAPI::SetMapName)
            ->Method("Steam GS Set Password Protected",    &SteamGameServerAPI::SetPasswordProtected)
            ->Method("Steam GS Set Spectator Port",        &SteamGameServerAPI::SetSpectatorPort)
            ->Method("Steam GS Set Spectator Server Name", &SteamGameServerAPI::SetSpectatorServerName)
            ->Method("Steam GS Clear All Key Values",      &SteamGameServerAPI::ClearAllKeyValues)
            ->Method("Steam GS Set Key Value",             &SteamGameServerAPI::SetKeyValue)
            ->Method("Steam GS Set Game Tags",             &SteamGameServerAPI::SetGameTags)
            ->Method("Steam GS Set Game Data",             &SteamGameServerAPI::SetGameData)
            ->Method("Steam GS Set Region",                &SteamGameServerAPI::SetRegion)
            ->Method("Steam GS Set Advertise Server Active", &SteamGameServerAPI::SetAdvertiseServerActive)
            ->Method("Steam GS Begin Auth Session",        &SteamGameServerAPI::BeginAuthSession)
            ->Method("Steam GS End Auth Session",          &SteamGameServerAPI::EndAuthSession)
            ->Method("Steam GS Cancel Auth Ticket",        &SteamGameServerAPI::GSCancelAuthTicket)
            ->Method("Steam GS User Has License For App",  &SteamGameServerAPI::UserHasLicenseForApp)
            ->Method("Steam GS Request User Group Status", &SteamGameServerAPI::RequestUserGroupStatus)
            ->Method("Steam GS Update User Data",          &SteamGameServerAPI::UpdateUserData)
            ->Method("Steam GS Associate With Clan",       &SteamGameServerAPI::AssociateWithClan)
            ->Method("Steam GS Compute New Player Compatibility", &SteamGameServerAPI::ComputeNewPlayerCompatibility)
            ->Method("Steam GS Get Server Reputation",     &SteamGameServerAPI::GetServerReputation);

        // --- Input API ---
        bc->Class<SteamInputAPI>("Steam Input API")
            ->Attribute(AZ::Script::Attributes::Category, "Steam/Input")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Method("Steam Input Get Connected Controllers",         &SteamInputAPI::GetConnectedControllers)
            ->Method("Steam Input Enable Device Callbacks",           &SteamInputAPI::EnableDeviceCallbacks)
            ->Method("Steam Input Get Action Set Handle",             &SteamInputAPI::GetActionSetHandle)
            ->Method("Steam Input Activate Action Set",               &SteamInputAPI::ActivateActionSet)
            ->Method("Steam Input Get Current Action Set",            &SteamInputAPI::GetCurrentActionSet)
            ->Method("Steam Input Activate Action Set Layer",         &SteamInputAPI::ActivateActionSetLayer)
            ->Method("Steam Input Deactivate Action Set Layer",       &SteamInputAPI::DeactivateActionSetLayer)
            ->Method("Steam Input Deactivate All Action Set Layers",  &SteamInputAPI::DeactivateAllActionSetLayers)
            ->Method("Steam Input Get Active Action Set Layers",      &SteamInputAPI::GetActiveActionSetLayers)
            ->Method("Steam Input Get Digital Action Handle",         &SteamInputAPI::GetDigitalActionHandle)
            ->Method("Steam Input Get Digital Action Data",           &SteamInputAPI::GetDigitalActionData)
            ->Method("Steam Input Get String For Digital Action Name",&SteamInputAPI::GetStringForDigitalActionName)
            ->Method("Steam Input Get Analog Action Handle",          &SteamInputAPI::GetAnalogActionHandle)
            ->Method("Steam Input Get Analog Action Data",            &SteamInputAPI::GetAnalogActionData)
            ->Method("Steam Input Get String For Analog Action Name", &SteamInputAPI::GetStringForAnalogActionName)
            ->Method("Steam Input Trigger Vibration",                 &SteamInputAPI::TriggerVibration)
            ->Method("Steam Input Trigger Vibration Extended",        &SteamInputAPI::TriggerVibrationExtended)
            ->Method("Steam Input Set LED Color",                     &SteamInputAPI::SetLEDColor)
            ->Method("Steam Input Show Binding Panel",                &SteamInputAPI::ShowBindingPanel)
            ->Method("Steam Input Get Input Type For Handle",         &SteamInputAPI::GetInputTypeForHandle)
            ->Method("Steam Input Get Controller For Gamepad Index",  &SteamInputAPI::GetControllerForGamepadIndex)
            ->Method("Steam Input Get Gamepad Index For Controller",  &SteamInputAPI::GetGamepadIndexForController)
            ->Method("Steam Input Get Remote Play Session ID",        &SteamInputAPI::GetRemotePlaySessionID);

        // --- Game Server Stats API ---
        bc->Class<SteamGameServerStatsAPI>("Steam Game Server Stats API")
            ->Attribute(AZ::Script::Attributes::Category, "Steam/GameServerStats")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Constructor<>()
            ->Method("Steam GS Stats Request User Stats",       &SteamGameServerStatsAPI::GSRequestUserStats)
            ->Method("Steam GS Stats Get User Stat Int",        &SteamGameServerStatsAPI::GSGetUserStatInt)
            ->Method("Steam GS Stats Get User Stat Float",      &SteamGameServerStatsAPI::GSGetUserStatFloat)
            ->Method("Steam GS Stats Get User Achievement",     &SteamGameServerStatsAPI::GSGetUserAchievement)
            ->Method("Steam GS Stats Set User Stat Int",        &SteamGameServerStatsAPI::GSSetUserStatInt)
            ->Method("Steam GS Stats Set User Stat Float",      &SteamGameServerStatsAPI::GSSetUserStatFloat)
            ->Method("Steam GS Stats Update User Avg Rate Stat",&SteamGameServerStatsAPI::GSUpdateUserAvgRateStat)
            ->Method("Steam GS Stats Set User Achievement",     &SteamGameServerStatsAPI::GSSetUserAchievement)
            ->Method("Steam GS Stats Clear User Achievement",   &SteamGameServerStatsAPI::GSClearUserAchievement)
            ->Method("Steam GS Stats Store User Stats",         &SteamGameServerStatsAPI::GSStoreUserStats);
    }
} // namespace FoundationSteamworks
