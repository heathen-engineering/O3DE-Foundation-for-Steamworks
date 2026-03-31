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

#include <FoundationSteamworks/FoundationSteamworksBus.h>
#include <FoundationSteamworks/SteamUserRequestBus.h>
#include <FoundationSteamworks/SteamAppsRequestBus.h>
#include <FoundationSteamworks/SteamFriendsRequestBus.h>
#include <FoundationSteamworks/SteamMatchmakingRequestBus.h>
#include <FoundationSteamworks/SteamUserStatsRequestBus.h>
#include <FoundationSteamworks/SteamRemoteStorageRequestBus.h>
#include <FoundationSteamworks/SteamInventoryRequestBus.h>
#include <FoundationSteamworks/SteamUGCRequestBus.h>
#include <FoundationSteamworks/SteamUtilsRequestBus.h>
#include <FoundationSteamworks/SteamScreenshotsRequestBus.h>
#include <FoundationSteamworks/SteamRemotePlayRequestBus.h>
#include <FoundationSteamworks/SteamInputRequestBus.h>
#include <FoundationSteamworks/SteamGameServerRequestBus.h>
#include <FoundationSteamworks/SteamGameServerStatsRequestBus.h>
#include <FoundationSteamworks/SteamTimelineRequestBus.h>

namespace FoundationSteamworks
{
    // -----------------------------------------------------------------------
    // Script Canvas proxy structs — one per ISteam interface.
    // Each is a stateless struct whose static methods forward through the
    // appropriate request bus, making calls discoverable in the SC palette.
    // -----------------------------------------------------------------------

    struct SteamUserAPI
    {
        AZ_TYPE_INFO(SteamUserAPI, "{10A1B2C3-D4E5-4F60-A7B8-C9D0E1F2A3B4}");
        AZ_CLASS_ALLOCATOR(SteamUserAPI, AZ::SystemAllocator);
        static bool              IsLoggedOn()                                         { bool r=false;              SteamUserRequestBus::BroadcastResult(r,&SteamUserRequests::IsLoggedOn); return r; }
        static SteamId           GetSteamID()                                         { SteamId r=0;               SteamUserRequestBus::BroadcastResult(r,&SteamUserRequests::GetSteamID); return r; }
        static AZ::s32           GetPlayerSteamLevel()                                { AZ::s32 r=0;               SteamUserRequestBus::BroadcastResult(r,&SteamUserRequests::GetPlayerSteamLevel); return r; }
        static AZ::s32           GetGameBadgeLevel(AZ::s32 series, bool foil)         { AZ::s32 r=0;               SteamUserRequestBus::BroadcastResult(r,&SteamUserRequests::GetGameBadgeLevel,series,foil); return r; }
        static SteamAuthTicketHandle GetAuthTicketForWebApi(const AZStd::string& identity) { SteamAuthTicketHandle r=0; SteamUserRequestBus::BroadcastResult(r,&SteamUserRequests::GetAuthTicketForWebApi,identity); return r; }
        static void              CancelAuthTicket(SteamAuthTicketHandle handle)        { SteamUserRequestBus::Broadcast(&SteamUserRequests::CancelAuthTicket,handle); }
        static SteamCallHandle   RequestStoreAuthURL(const AZStd::string& redirectURL) { SteamCallHandle r=0;      SteamUserRequestBus::BroadcastResult(r,&SteamUserRequests::RequestStoreAuthURL,redirectURL); return r; }
        static SteamCallHandle   GetMarketEligibility()                               { SteamCallHandle r=0;       SteamUserRequestBus::BroadcastResult(r,&SteamUserRequests::GetMarketEligibility); return r; }
        static SteamCallHandle   GetDurationControl()                                 { SteamCallHandle r=0;       SteamUserRequestBus::BroadcastResult(r,&SteamUserRequests::GetDurationControl); return r; }
        static SteamCallHandle   RequestEncryptedAppTicket(const AZStd::vector<AZ::u8>& data) { SteamCallHandle r=0; SteamUserRequestBus::BroadcastResult(r,&SteamUserRequests::RequestEncryptedAppTicket,data); return r; }
    };

    struct SteamAppsAPI
    {
        AZ_TYPE_INFO(SteamAppsAPI, "{20B2C3D4-E5F6-4071-B8C9-D0E1F2A3B4C5}");
        AZ_CLASS_ALLOCATOR(SteamAppsAPI, AZ::SystemAllocator);
        static bool          IsSubscribed()                                    { bool r=false;        SteamAppsRequestBus::BroadcastResult(r,&SteamAppsRequests::IsSubscribed); return r; }
        static bool          IsSubscribedFromFreeWeekend()                     { bool r=false;        SteamAppsRequestBus::BroadcastResult(r,&SteamAppsRequests::IsSubscribedFromFreeWeekend); return r; }
        static bool          IsSubscribedFromFamilySharing()                   { bool r=false;        SteamAppsRequestBus::BroadcastResult(r,&SteamAppsRequests::IsSubscribedFromFamilySharing); return r; }
        static bool          IsSubscribedApp(SteamAppId appId)                 { bool r=false;        SteamAppsRequestBus::BroadcastResult(r,&SteamAppsRequests::IsSubscribedApp,appId); return r; }
        static bool          IsDlcInstalled(SteamAppId appId)                  { bool r=false;        SteamAppsRequestBus::BroadcastResult(r,&SteamAppsRequests::IsDlcInstalled,appId); return r; }
        static AZ::u32       GetEarliestPurchaseUnixTime(SteamAppId appId)     { AZ::u32 r=0;         SteamAppsRequestBus::BroadcastResult(r,&SteamAppsRequests::GetEarliestPurchaseUnixTime,appId); return r; }
        static bool          IsLowViolence()                                   { bool r=false;        SteamAppsRequestBus::BroadcastResult(r,&SteamAppsRequests::IsLowViolence); return r; }
        static bool          IsCybercafe()                                     { bool r=false;        SteamAppsRequestBus::BroadcastResult(r,&SteamAppsRequests::IsCybercafe); return r; }
        static bool          IsVACBanned()                                     { bool r=false;        SteamAppsRequestBus::BroadcastResult(r,&SteamAppsRequests::IsVACBanned); return r; }
        static AZStd::string GetCurrentGameLanguage()                          { AZStd::string r;     SteamAppsRequestBus::BroadcastResult(r,&SteamAppsRequests::GetCurrentGameLanguage); return r; }
        static AZStd::string GetAvailableGameLanguages()                       { AZStd::string r;     SteamAppsRequestBus::BroadcastResult(r,&SteamAppsRequests::GetAvailableGameLanguages); return r; }
        static SteamAppId    GetAppID()                                        { SteamAppId r=0;      SteamAppsRequestBus::BroadcastResult(r,&SteamAppsRequests::GetAppID); return r; }
        static AZ::s32       GetDLCCount()                                     { AZ::s32 r=0;         SteamAppsRequestBus::BroadcastResult(r,&SteamAppsRequests::GetDLCCount); return r; }
        static void          InstallDLC(SteamAppId appId)                      { SteamAppsRequestBus::Broadcast(&SteamAppsRequests::InstallDLC,appId); }
        static void          UninstallDLC(SteamAppId appId)                    { SteamAppsRequestBus::Broadcast(&SteamAppsRequests::UninstallDLC,appId); }
        static AZStd::string GetCurrentBetaName()                              { AZStd::string r;     SteamAppsRequestBus::BroadcastResult(r,&SteamAppsRequests::GetCurrentBetaName); return r; }
        static AZ::s32       GetAppBuildId()                                   { AZ::s32 r=0;         SteamAppsRequestBus::BroadcastResult(r,&SteamAppsRequests::GetAppBuildId); return r; }
        static bool          MarkContentCorrupt(bool missingFilesOnly)         { bool r=false;        SteamAppsRequestBus::BroadcastResult(r,&SteamAppsRequests::MarkContentCorrupt,missingFilesOnly); return r; }
        static SteamCallHandle GetFileDetails(const AZStd::string& fileName)   { SteamCallHandle r=0; SteamAppsRequestBus::BroadcastResult(r,&SteamAppsRequests::GetFileDetails,fileName); return r; }
    };

    struct SteamFriendsAPI
    {
        AZ_TYPE_INFO(SteamFriendsAPI, "{30C3D4E5-F6A7-4182-C9D0-E1F2A3B4C5D6}");
        AZ_CLASS_ALLOCATOR(SteamFriendsAPI, AZ::SystemAllocator);
        static AZStd::string GetPersonaName()                                              { AZStd::string r;              SteamFriendsRequestBus::BroadcastResult(r,&SteamFriendsRequests::GetPersonaName); return r; }
        static AZ::s32       GetPersonaState()                                             { SteamPersonaState r=SteamPersonaState::Offline; SteamFriendsRequestBus::BroadcastResult(r,&SteamFriendsRequests::GetPersonaState); return static_cast<AZ::s32>(r); }
        static AZ::s32       GetFriendCount(AZ::s32 friendFlags)                           { AZ::s32 r=0;                  SteamFriendsRequestBus::BroadcastResult(r,&SteamFriendsRequests::GetFriendCount,friendFlags); return r; }
        static SteamId       GetFriendByIndex(AZ::s32 index, AZ::s32 friendFlags)         { SteamId r=0;                  SteamFriendsRequestBus::BroadcastResult(r,&SteamFriendsRequests::GetFriendByIndex,index,friendFlags); return r; }
        static AZ::s32       GetFriendRelationship(SteamId steamId)                        { AZ::s32 r=0;                  SteamFriendsRequestBus::BroadcastResult(r,&SteamFriendsRequests::GetFriendRelationship,steamId); return r; }
        static AZ::s32       GetFriendPersonaState(SteamId steamId)                        { SteamPersonaState r=SteamPersonaState::Offline; SteamFriendsRequestBus::BroadcastResult(r,&SteamFriendsRequests::GetFriendPersonaState,steamId); return static_cast<AZ::s32>(r); }
        static AZStd::string GetFriendPersonaName(SteamId steamId)                        { AZStd::string r;              SteamFriendsRequestBus::BroadcastResult(r,&SteamFriendsRequests::GetFriendPersonaName,steamId); return r; }
        static AZ::s32       GetFriendSteamLevel(SteamId steamId)                         { AZ::s32 r=0;                  SteamFriendsRequestBus::BroadcastResult(r,&SteamFriendsRequests::GetFriendSteamLevel,steamId); return r; }
        static AZStd::string GetPlayerNickname(SteamId steamId)                            { AZStd::string r;              SteamFriendsRequestBus::BroadcastResult(r,&SteamFriendsRequests::GetPlayerNickname,steamId); return r; }
        static bool          HasFriend(SteamId steamId, AZ::s32 friendFlags)               { bool r=false;                 SteamFriendsRequestBus::BroadcastResult(r,&SteamFriendsRequests::HasFriend,steamId,friendFlags); return r; }
        static AZ::s32       GetSmallFriendAvatar(SteamId steamId)                         { AZ::s32 r=0;                  SteamFriendsRequestBus::BroadcastResult(r,&SteamFriendsRequests::GetSmallFriendAvatar,steamId); return r; }
        static AZ::s32       GetMediumFriendAvatar(SteamId steamId)                        { AZ::s32 r=0;                  SteamFriendsRequestBus::BroadcastResult(r,&SteamFriendsRequests::GetMediumFriendAvatar,steamId); return r; }
        static AZ::s32       GetLargeFriendAvatar(SteamId steamId)                         { AZ::s32 r=0;                  SteamFriendsRequestBus::BroadcastResult(r,&SteamFriendsRequests::GetLargeFriendAvatar,steamId); return r; }
        static bool          RequestUserInformation(SteamId steamId, bool requireNameOnly) { bool r=false;                 SteamFriendsRequestBus::BroadcastResult(r,&SteamFriendsRequests::RequestUserInformation,steamId,requireNameOnly); return r; }
        static bool          SetRichPresence(const AZStd::string& key, const AZStd::string& value) { bool r=false;        SteamFriendsRequestBus::BroadcastResult(r,&SteamFriendsRequests::SetRichPresence,key,value); return r; }
        static void          ClearRichPresence()                                           { SteamFriendsRequestBus::Broadcast(&SteamFriendsRequests::ClearRichPresence); }
        static AZStd::string GetFriendRichPresence(SteamId steamId, const AZStd::string& key) { AZStd::string r;         SteamFriendsRequestBus::BroadcastResult(r,&SteamFriendsRequests::GetFriendRichPresence,steamId,key); return r; }
        static AZ::s32       GetFriendRichPresenceKeyCount(SteamId steamId)                { AZ::s32 r=0;                  SteamFriendsRequestBus::BroadcastResult(r,&SteamFriendsRequests::GetFriendRichPresenceKeyCount,steamId); return r; }
        static AZStd::string GetFriendRichPresenceKeyByIndex(SteamId steamId, AZ::s32 index) { AZStd::string r;           SteamFriendsRequestBus::BroadcastResult(r,&SteamFriendsRequests::GetFriendRichPresenceKeyByIndex,steamId,index); return r; }
        static void          RequestFriendRichPresence(SteamId steamId)                    { SteamFriendsRequestBus::Broadcast(&SteamFriendsRequests::RequestFriendRichPresence,steamId); }
        static void          ActivateGameOverlay(const AZStd::string& dialog)              { SteamFriendsRequestBus::Broadcast(&SteamFriendsRequests::ActivateGameOverlay,dialog); }
        static void          ActivateGameOverlayToUser(const AZStd::string& dialog, SteamId steamId) { SteamFriendsRequestBus::Broadcast(&SteamFriendsRequests::ActivateGameOverlayToUser,dialog,steamId); }
        static void          ActivateGameOverlayToWebPage(const AZStd::string& url, SteamOverlayToWebPageMode mode) { SteamFriendsRequestBus::Broadcast(&SteamFriendsRequests::ActivateGameOverlayToWebPage,url,mode); }
        static void          ActivateGameOverlayToStore(SteamAppId appId, SteamOverlayToStoreFlag flag) { SteamFriendsRequestBus::Broadcast(&SteamFriendsRequests::ActivateGameOverlayToStore,appId,flag); }
        static void          ActivateGameOverlayInviteDialog(SteamId lobbyId)              { SteamFriendsRequestBus::Broadcast(&SteamFriendsRequests::ActivateGameOverlayInviteDialog,lobbyId); }
        static void          SetPlayedWith(SteamId steamId)                                { SteamFriendsRequestBus::Broadcast(&SteamFriendsRequests::SetPlayedWith,steamId); }
        static SteamId       GetClanByIndex(AZ::s32 index)                                 { SteamId r=0;                  SteamFriendsRequestBus::BroadcastResult(r,&SteamFriendsRequests::GetClanByIndex,index); return r; }
        static AZ::s32       GetClanCount()                                                { AZ::s32 r=0;                  SteamFriendsRequestBus::BroadcastResult(r,&SteamFriendsRequests::GetClanCount); return r; }
        static AZStd::string GetClanName(SteamId clanId)                                   { AZStd::string r;              SteamFriendsRequestBus::BroadcastResult(r,&SteamFriendsRequests::GetClanName,clanId); return r; }
        static AZStd::string GetClanTag(SteamId clanId)                                    { AZStd::string r;              SteamFriendsRequestBus::BroadcastResult(r,&SteamFriendsRequests::GetClanTag,clanId); return r; }
        static SteamCallHandle RequestClanOfficerList(SteamId clanId)                      { SteamCallHandle r=0;          SteamFriendsRequestBus::BroadcastResult(r,&SteamFriendsRequests::RequestClanOfficerList,clanId); return r; }
        static SteamCallHandle GetFollowerCount(SteamId steamId)                           { SteamCallHandle r=0;          SteamFriendsRequestBus::BroadcastResult(r,&SteamFriendsRequests::GetFollowerCount,steamId); return r; }
        static SteamCallHandle IsFollowing(SteamId steamId)                                { SteamCallHandle r=0;          SteamFriendsRequestBus::BroadcastResult(r,&SteamFriendsRequests::IsFollowing,steamId); return r; }
        static SteamCallHandle EnumerateFollowingList(AZ::u32 startIndex)                  { SteamCallHandle r=0;          SteamFriendsRequestBus::BroadcastResult(r,&SteamFriendsRequests::EnumerateFollowingList,startIndex); return r; }
    };

    struct SteamMatchmakingAPI
    {
        AZ_TYPE_INFO(SteamMatchmakingAPI, "{40D4E5F6-A7B8-4293-D0E1-F2A3B4C5D6E7}");
        AZ_CLASS_ALLOCATOR(SteamMatchmakingAPI, AZ::SystemAllocator);
        static AZ::s32       GetNumLobbyMembers(SteamId lobbyId)                           { AZ::s32 r=0;      SteamMatchmakingRequestBus::BroadcastResult(r,&SteamMatchmakingRequests::GetNumLobbyMembers,lobbyId); return r; }
        static SteamId       GetLobbyMemberByIndex(SteamId lobbyId, AZ::s32 index)        { SteamId r=0;      SteamMatchmakingRequestBus::BroadcastResult(r,&SteamMatchmakingRequests::GetLobbyMemberByIndex,lobbyId,index); return r; }
        static AZStd::string GetLobbyData(SteamId lobbyId, const AZStd::string& key)      { AZStd::string r;  SteamMatchmakingRequestBus::BroadcastResult(r,&SteamMatchmakingRequests::GetLobbyData,lobbyId,key); return r; }
        static bool          SetLobbyData(SteamId lobbyId, const AZStd::string& key, const AZStd::string& value) { bool r=false; SteamMatchmakingRequestBus::BroadcastResult(r,&SteamMatchmakingRequests::SetLobbyData,lobbyId,key,value); return r; }
        static bool          DeleteLobbyData(SteamId lobbyId, const AZStd::string& key)   { bool r=false;     SteamMatchmakingRequestBus::BroadcastResult(r,&SteamMatchmakingRequests::DeleteLobbyData,lobbyId,key); return r; }
        static AZStd::string GetLobbyMemberData(SteamId lobbyId, SteamId memberId, const AZStd::string& key) { AZStd::string r; SteamMatchmakingRequestBus::BroadcastResult(r,&SteamMatchmakingRequests::GetLobbyMemberData,lobbyId,memberId,key); return r; }
        static void          SetLobbyMemberData(SteamId lobbyId, const AZStd::string& key, const AZStd::string& value) { SteamMatchmakingRequestBus::Broadcast(&SteamMatchmakingRequests::SetLobbyMemberData,lobbyId,key,value); }
        static SteamId       GetLobbyOwner(SteamId lobbyId)                                { SteamId r=0;      SteamMatchmakingRequestBus::BroadcastResult(r,&SteamMatchmakingRequests::GetLobbyOwner,lobbyId); return r; }
        static bool          SetLobbyOwner(SteamId lobbyId, SteamId newOwnerId)            { bool r=false;     SteamMatchmakingRequestBus::BroadcastResult(r,&SteamMatchmakingRequests::SetLobbyOwner,lobbyId,newOwnerId); return r; }
        static bool          RequestLobbyData(SteamId lobbyId)                             { bool r=false;     SteamMatchmakingRequestBus::BroadcastResult(r,&SteamMatchmakingRequests::RequestLobbyData,lobbyId); return r; }
        static bool          SetLobbyJoinable(SteamId lobbyId, bool joinable)              { bool r=false;     SteamMatchmakingRequestBus::BroadcastResult(r,&SteamMatchmakingRequests::SetLobbyJoinable,lobbyId,joinable); return r; }
        static bool          SetLobbyMemberLimit(SteamId lobbyId, AZ::s32 maxMembers)      { bool r=false;     SteamMatchmakingRequestBus::BroadcastResult(r,&SteamMatchmakingRequests::SetLobbyMemberLimit,lobbyId,maxMembers); return r; }
        static AZ::s32       GetLobbyMemberLimit(SteamId lobbyId)                          { AZ::s32 r=0;      SteamMatchmakingRequestBus::BroadcastResult(r,&SteamMatchmakingRequests::GetLobbyMemberLimit,lobbyId); return r; }
        static bool          InviteUserToLobby(SteamId lobbyId, SteamId inviteeId)         { bool r=false;     SteamMatchmakingRequestBus::BroadcastResult(r,&SteamMatchmakingRequests::InviteUserToLobby,lobbyId,inviteeId); return r; }
        static void          LeaveLobby(SteamId lobbyId)                                   { SteamMatchmakingRequestBus::Broadcast(&SteamMatchmakingRequests::LeaveLobby,lobbyId); }
        static void          AddRequestLobbyListStringFilter(const AZStd::string& key, const AZStd::string& value, SteamLobbyComparison comparison) { SteamMatchmakingRequestBus::Broadcast(&SteamMatchmakingRequests::AddRequestLobbyListStringFilter,key,value,comparison); }
        static void          AddRequestLobbyListNumericalFilter(const AZStd::string& key, AZ::s32 value, SteamLobbyComparison comparison) { SteamMatchmakingRequestBus::Broadcast(&SteamMatchmakingRequests::AddRequestLobbyListNumericalFilter,key,value,comparison); }
        static void          AddRequestLobbyListNearValueFilter(const AZStd::string& key, AZ::s32 value) { SteamMatchmakingRequestBus::Broadcast(&SteamMatchmakingRequests::AddRequestLobbyListNearValueFilter,key,value); }
        static void          AddRequestLobbyListFilterSlotsAvailable(AZ::s32 slotsAvailable) { SteamMatchmakingRequestBus::Broadcast(&SteamMatchmakingRequests::AddRequestLobbyListFilterSlotsAvailable,slotsAvailable); }
        static void          AddRequestLobbyListDistanceFilter(SteamLobbyDistanceFilter filter) { SteamMatchmakingRequestBus::Broadcast(&SteamMatchmakingRequests::AddRequestLobbyListDistanceFilter,filter); }
        static void          AddRequestLobbyListResultCountFilter(AZ::s32 maxResults)      { SteamMatchmakingRequestBus::Broadcast(&SteamMatchmakingRequests::AddRequestLobbyListResultCountFilter,maxResults); }
        static SteamCallHandle CreateLobby(SteamLobbyType lobbyType, AZ::s32 maxMembers)   { SteamCallHandle r=0; SteamMatchmakingRequestBus::BroadcastResult(r,&SteamMatchmakingRequests::CreateLobby,lobbyType,maxMembers); return r; }
        static SteamCallHandle JoinLobby(SteamId lobbyId)                                  { SteamCallHandle r=0; SteamMatchmakingRequestBus::BroadcastResult(r,&SteamMatchmakingRequests::JoinLobby,lobbyId); return r; }
        static SteamCallHandle RequestLobbyList()                                           { SteamCallHandle r=0; SteamMatchmakingRequestBus::BroadcastResult(r,&SteamMatchmakingRequests::RequestLobbyList); return r; }
    };

    struct SteamStatsAPI
    {
        AZ_TYPE_INFO(SteamStatsAPI, "{50E5F6A7-B8C9-43A4-E1F2-A3B4C5D6E7F8}");
        AZ_CLASS_ALLOCATOR(SteamStatsAPI, AZ::SystemAllocator);
        static bool          RequestCurrentStats()                                                  { bool r=false;        SteamUserStatsRequestBus::BroadcastResult(r,&SteamUserStatsRequests::RequestCurrentStats); return r; }
        static bool          StoreStats()                                                           { bool r=false;        SteamUserStatsRequestBus::BroadcastResult(r,&SteamUserStatsRequests::StoreStats); return r; }
        static bool          GetStatInt(const AZStd::string& name, AZ::s32& outValue)              { bool r=false;        SteamUserStatsRequestBus::BroadcastResult(r,&SteamUserStatsRequests::GetStatInt,name,outValue); return r; }
        static bool          GetStatFloat(const AZStd::string& name, float& outValue)              { bool r=false;        SteamUserStatsRequestBus::BroadcastResult(r,&SteamUserStatsRequests::GetStatFloat,name,outValue); return r; }
        static bool          SetStatInt(const AZStd::string& name, AZ::s32 value)                  { bool r=false;        SteamUserStatsRequestBus::BroadcastResult(r,&SteamUserStatsRequests::SetStatInt,name,value); return r; }
        static bool          SetStatFloat(const AZStd::string& name, float value)                  { bool r=false;        SteamUserStatsRequestBus::BroadcastResult(r,&SteamUserStatsRequests::SetStatFloat,name,value); return r; }
        static bool          UpdateAvgRateStat(const AZStd::string& name, float countThisSession, double sessionLength) { bool r=false; SteamUserStatsRequestBus::BroadcastResult(r,&SteamUserStatsRequests::UpdateAvgRateStat,name,countThisSession,sessionLength); return r; }
        static bool          GetAchievement(const AZStd::string& name, bool& outAchieved)          { bool r=false;        SteamUserStatsRequestBus::BroadcastResult(r,&SteamUserStatsRequests::GetAchievement,name,outAchieved); return r; }
        static bool          SetAchievement(const AZStd::string& name)                             { bool r=false;        SteamUserStatsRequestBus::BroadcastResult(r,&SteamUserStatsRequests::SetAchievement,name); return r; }
        static bool          ClearAchievement(const AZStd::string& name)                           { bool r=false;        SteamUserStatsRequestBus::BroadcastResult(r,&SteamUserStatsRequests::ClearAchievement,name); return r; }
        static bool          GetAchievementAndUnlockTime(const AZStd::string& name, bool& outAchieved, AZ::u32& outUnlockTime) { bool r=false; SteamUserStatsRequestBus::BroadcastResult(r,&SteamUserStatsRequests::GetAchievementAndUnlockTime,name,outAchieved,outUnlockTime); return r; }
        static bool          IndicateAchievementProgress(const AZStd::string& name, AZ::u32 curProgress, AZ::u32 maxProgress) { bool r=false; SteamUserStatsRequestBus::BroadcastResult(r,&SteamUserStatsRequests::IndicateAchievementProgress,name,curProgress,maxProgress); return r; }
        static bool          ResetAllStats(bool achievementsToo)                                    { bool r=false;        SteamUserStatsRequestBus::BroadcastResult(r,&SteamUserStatsRequests::ResetAllStats,achievementsToo); return r; }
        static AZ::u32       GetNumAchievements()                                                   { AZ::u32 r=0;         SteamUserStatsRequestBus::BroadcastResult(r,&SteamUserStatsRequests::GetNumAchievements); return r; }
        static AZStd::string GetAchievementName(AZ::u32 index)                                     { AZStd::string r;     SteamUserStatsRequestBus::BroadcastResult(r,&SteamUserStatsRequests::GetAchievementName,index); return r; }
        static AZStd::string GetAchievementDisplayAttribute(const AZStd::string& name, const AZStd::string& key) { AZStd::string r; SteamUserStatsRequestBus::BroadcastResult(r,&SteamUserStatsRequests::GetAchievementDisplayAttribute,name,key); return r; }
        static AZ::s32       GetAchievementIcon(const AZStd::string& name)                         { AZ::s32 r=0;         SteamUserStatsRequestBus::BroadcastResult(r,&SteamUserStatsRequests::GetAchievementIcon,name); return r; }
        static bool          GetUserStatInt(SteamId userId, const AZStd::string& name, AZ::s32& outValue)   { bool r=false; SteamUserStatsRequestBus::BroadcastResult(r,&SteamUserStatsRequests::GetUserStatInt,userId,name,outValue); return r; }
        static bool          GetUserStatFloat(SteamId userId, const AZStd::string& name, float& outValue)   { bool r=false; SteamUserStatsRequestBus::BroadcastResult(r,&SteamUserStatsRequests::GetUserStatFloat,userId,name,outValue); return r; }
        static bool          GetUserAchievement(SteamId userId, const AZStd::string& name, bool& outAchieved) { bool r=false; SteamUserStatsRequestBus::BroadcastResult(r,&SteamUserStatsRequests::GetUserAchievement,userId,name,outAchieved); return r; }
        static bool          GetUserAchievementAndUnlockTime(SteamId userId, const AZStd::string& name, bool& outAchieved, AZ::u32& outUnlockTime) { bool r=false; SteamUserStatsRequestBus::BroadcastResult(r,&SteamUserStatsRequests::GetUserAchievementAndUnlockTime,userId,name,outAchieved,outUnlockTime); return r; }
        // SC-safe variants returning result structs
        static SteamStatIntResult          SC_GetStatInt(const AZStd::string& name)                 { SteamStatIntResult out; SteamUserStatsRequestBus::BroadcastResult(out.success,&SteamUserStatsRequests::GetStatInt,name,out.value); return out; }
        static SteamStatFloatResult        SC_GetStatFloat(const AZStd::string& name)               { SteamStatFloatResult out; SteamUserStatsRequestBus::BroadcastResult(out.success,&SteamUserStatsRequests::GetStatFloat,name,out.value); return out; }
        static SteamAchievementResult      SC_GetAchievement(const AZStd::string& name)             { SteamAchievementResult out; SteamUserStatsRequestBus::BroadcastResult(out.success,&SteamUserStatsRequests::GetAchievement,name,out.achieved); return out; }
        static SteamAchievementAndUnlockTimeResult SC_GetAchievementAndUnlockTime(const AZStd::string& name) { SteamAchievementAndUnlockTimeResult out; SteamUserStatsRequestBus::BroadcastResult(out.success,&SteamUserStatsRequests::GetAchievementAndUnlockTime,name,out.achieved,out.unlockTime); return out; }
        static SteamStatIntResult          SC_GetUserStatInt(SteamId userId, const AZStd::string& name)   { SteamStatIntResult out; SteamUserStatsRequestBus::BroadcastResult(out.success,&SteamUserStatsRequests::GetUserStatInt,userId,name,out.value); return out; }
        static SteamStatFloatResult        SC_GetUserStatFloat(SteamId userId, const AZStd::string& name) { SteamStatFloatResult out; SteamUserStatsRequestBus::BroadcastResult(out.success,&SteamUserStatsRequests::GetUserStatFloat,userId,name,out.value); return out; }
        static SteamAchievementResult      SC_GetUserAchievement(SteamId userId, const AZStd::string& name) { SteamAchievementResult out; SteamUserStatsRequestBus::BroadcastResult(out.success,&SteamUserStatsRequests::GetUserAchievement,userId,name,out.achieved); return out; }
        static SteamAchievementAndUnlockTimeResult SC_GetUserAchievementAndUnlockTime(SteamId userId, const AZStd::string& name) { SteamAchievementAndUnlockTimeResult out; SteamUserStatsRequestBus::BroadcastResult(out.success,&SteamUserStatsRequests::GetUserAchievementAndUnlockTime,userId,name,out.achieved,out.unlockTime); return out; }
        static AZStd::string GetLeaderboardName(SteamLeaderboardHandle leaderboard)                { AZStd::string r;     SteamUserStatsRequestBus::BroadcastResult(r,&SteamUserStatsRequests::GetLeaderboardName,leaderboard); return r; }
        static AZ::s32       GetLeaderboardEntryCount(SteamLeaderboardHandle leaderboard)          { AZ::s32 r=0;         SteamUserStatsRequestBus::BroadcastResult(r,&SteamUserStatsRequests::GetLeaderboardEntryCount,leaderboard); return r; }
        static AZ::s32       GetLeaderboardSortMethod(SteamLeaderboardHandle leaderboard)          { SteamLeaderboardSortMethod r=SteamLeaderboardSortMethod::None; SteamUserStatsRequestBus::BroadcastResult(r,&SteamUserStatsRequests::GetLeaderboardSortMethod,leaderboard); return static_cast<AZ::s32>(r); }
        static AZ::s32       GetLeaderboardDisplayType(SteamLeaderboardHandle leaderboard)         { SteamLeaderboardDisplayType r=SteamLeaderboardDisplayType::None; SteamUserStatsRequestBus::BroadcastResult(r,&SteamUserStatsRequests::GetLeaderboardDisplayType,leaderboard); return static_cast<AZ::s32>(r); }
        static SteamCallHandle RequestUserStats(SteamId userId)                                     { SteamCallHandle r=0; SteamUserStatsRequestBus::BroadcastResult(r,&SteamUserStatsRequests::RequestUserStats,userId); return r; }
        static SteamCallHandle FindOrCreateLeaderboard(const AZStd::string& name, SteamLeaderboardSortMethod sortMethod, SteamLeaderboardDisplayType displayType) { SteamCallHandle r=0; SteamUserStatsRequestBus::BroadcastResult(r,&SteamUserStatsRequests::FindOrCreateLeaderboard,name,sortMethod,displayType); return r; }
        static SteamCallHandle FindLeaderboard(const AZStd::string& name)                           { SteamCallHandle r=0; SteamUserStatsRequestBus::BroadcastResult(r,&SteamUserStatsRequests::FindLeaderboard,name); return r; }
        static SteamCallHandle DownloadLeaderboardEntries(SteamLeaderboardHandle leaderboard, SteamLeaderboardDataRequest dataRequest, AZ::s32 rangeStart, AZ::s32 rangeEnd) { SteamCallHandle r=0; SteamUserStatsRequestBus::BroadcastResult(r,&SteamUserStatsRequests::DownloadLeaderboardEntries,leaderboard,dataRequest,rangeStart,rangeEnd); return r; }
        static SteamCallHandle UploadLeaderboardScore(SteamLeaderboardHandle leaderboard, SteamLeaderboardUploadScoreMethod method, AZ::s32 score) { SteamCallHandle r=0; SteamUserStatsRequestBus::BroadcastResult(r,&SteamUserStatsRequests::UploadLeaderboardScore,leaderboard,method,score); return r; }
        static SteamCallHandle GetNumberOfCurrentPlayers()                                          { SteamCallHandle r=0; SteamUserStatsRequestBus::BroadcastResult(r,&SteamUserStatsRequests::GetNumberOfCurrentPlayers); return r; }
        static SteamCallHandle RequestGlobalAchievementPercentages()                                { SteamCallHandle r=0; SteamUserStatsRequestBus::BroadcastResult(r,&SteamUserStatsRequests::RequestGlobalAchievementPercentages); return r; }
        static SteamCallHandle RequestGlobalStats(AZ::s32 historyDays)                             { SteamCallHandle r=0; SteamUserStatsRequestBus::BroadcastResult(r,&SteamUserStatsRequests::RequestGlobalStats,historyDays); return r; }
    };

    struct SteamStorageAPI
    {
        AZ_TYPE_INFO(SteamStorageAPI, "{60F6A7B8-C9D0-44B5-F2A3-B4C5D6E7F8A9}");
        AZ_CLASS_ALLOCATOR(SteamStorageAPI, AZ::SystemAllocator);
        static bool          FileWrite(const AZStd::string& fileName, const AZStd::vector<AZ::u8>& data) { bool r=false;        SteamRemoteStorageRequestBus::BroadcastResult(r,&SteamRemoteStorageRequests::FileWrite,fileName,data); return r; }
        static bool          FileRead(const AZStd::string& fileName, AZStd::vector<AZ::u8>& outData)     { bool r=false;        SteamRemoteStorageRequestBus::BroadcastResult(r,&SteamRemoteStorageRequests::FileRead,fileName,outData); return r; }
        static bool          FileExists(const AZStd::string& fileName)                                   { bool r=false;        SteamRemoteStorageRequestBus::BroadcastResult(r,&SteamRemoteStorageRequests::FileExists,fileName); return r; }
        static bool          FilePersisted(const AZStd::string& fileName)                                { bool r=false;        SteamRemoteStorageRequestBus::BroadcastResult(r,&SteamRemoteStorageRequests::FilePersisted,fileName); return r; }
        static AZ::s32       GetFileSize(const AZStd::string& fileName)                                  { AZ::s32 r=-1;        SteamRemoteStorageRequestBus::BroadcastResult(r,&SteamRemoteStorageRequests::GetFileSize,fileName); return r; }
        static AZ::s64       GetFileTimestamp(const AZStd::string& fileName)                             { AZ::s64 r=0;         SteamRemoteStorageRequestBus::BroadcastResult(r,&SteamRemoteStorageRequests::GetFileTimestamp,fileName); return r; }
        static bool          FileForget(const AZStd::string& fileName)                                   { bool r=false;        SteamRemoteStorageRequestBus::BroadcastResult(r,&SteamRemoteStorageRequests::FileForget,fileName); return r; }
        static bool          FileDelete(const AZStd::string& fileName)                                   { bool r=false;        SteamRemoteStorageRequestBus::BroadcastResult(r,&SteamRemoteStorageRequests::FileDelete,fileName); return r; }
        static AZ::s32       GetFileCount()                                                              { AZ::s32 r=0;         SteamRemoteStorageRequestBus::BroadcastResult(r,&SteamRemoteStorageRequests::GetFileCount); return r; }
        static AZStd::string GetFileNameAndSize(AZ::s32 index, AZ::s32& outSize)                         { AZStd::string r;     SteamRemoteStorageRequestBus::BroadcastResult(r,&SteamRemoteStorageRequests::GetFileNameAndSize,index,outSize); return r; }
        static bool          GetQuota(AZ::u64& outTotalBytes, AZ::u64& outAvailableBytes)                { bool r=false;        SteamRemoteStorageRequestBus::BroadcastResult(r,&SteamRemoteStorageRequests::GetQuota,outTotalBytes,outAvailableBytes); return r; }
        static bool          IsCloudEnabledForAccount()                                                  { bool r=false;        SteamRemoteStorageRequestBus::BroadcastResult(r,&SteamRemoteStorageRequests::IsCloudEnabledForAccount); return r; }
        static bool          IsCloudEnabledForApp()                                                      { bool r=false;        SteamRemoteStorageRequestBus::BroadcastResult(r,&SteamRemoteStorageRequests::IsCloudEnabledForApp); return r; }
        static void          SetCloudEnabledForApp(bool enabled)                                         { SteamRemoteStorageRequestBus::Broadcast(&SteamRemoteStorageRequests::SetCloudEnabledForApp,enabled); }
        static SteamCallHandle FileShare(const AZStd::string& fileName)                                  { SteamCallHandle r=0; SteamRemoteStorageRequestBus::BroadcastResult(r,&SteamRemoteStorageRequests::FileShare,fileName); return r; }
        static SteamCallHandle FileWriteAsync(const AZStd::string& fileName, const AZStd::vector<AZ::u8>& data) { SteamCallHandle r=0; SteamRemoteStorageRequestBus::BroadcastResult(r,&SteamRemoteStorageRequests::FileWriteAsync,fileName,data); return r; }
        static SteamCallHandle FileReadAsync(const AZStd::string& fileName, AZ::u32 offset, AZ::u32 bytesToRead) { SteamCallHandle r=0; SteamRemoteStorageRequestBus::BroadcastResult(r,&SteamRemoteStorageRequests::FileReadAsync,fileName,offset,bytesToRead); return r; }
        static SteamCallHandle SubscribePublishedFile(SteamPublishedFileId fileId)                       { SteamCallHandle r=0; SteamRemoteStorageRequestBus::BroadcastResult(r,&SteamRemoteStorageRequests::SubscribePublishedFile,fileId); return r; }
        static SteamCallHandle UnsubscribePublishedFile(SteamPublishedFileId fileId)                     { SteamCallHandle r=0; SteamRemoteStorageRequestBus::BroadcastResult(r,&SteamRemoteStorageRequests::UnsubscribePublishedFile,fileId); return r; }
        static SteamFileNameAndSizeResult  SC_GetFileNameAndSize(AZ::s32 index)               { SteamFileNameAndSizeResult out; out.fileName = SteamStorageAPI::GetFileNameAndSize(index,out.size); return out; }
        static SteamQuotaResult            SC_GetQuota()                                        { SteamQuotaResult out; SteamRemoteStorageRequestBus::BroadcastResult(out.success,&SteamRemoteStorageRequests::GetQuota,out.totalBytes,out.availableBytes); return out; }
    };

    struct SteamInventoryAPI
    {
        AZ_TYPE_INFO(SteamInventoryAPI, "{70A7B8C9-D0E1-45C6-A3B4-C5D6E7F8A9B0}");
        AZ_CLASS_ALLOCATOR(SteamInventoryAPI, AZ::SystemAllocator);
        static void                   DestroyResult(SteamInventoryResultHandle resultHandle)              { SteamInventoryRequestBus::Broadcast(&SteamInventoryRequests::DestroyResult,resultHandle); }
        static AZ::s32                GetResultStatus(SteamInventoryResultHandle resultHandle)             { SteamResult r=SteamResult::Fail; SteamInventoryRequestBus::BroadcastResult(r,&SteamInventoryRequests::GetResultStatus,resultHandle); return static_cast<AZ::s32>(r); }
        static AZ::u32                GetResultTimestamp(SteamInventoryResultHandle resultHandle)          { AZ::u32 r=0;         SteamInventoryRequestBus::BroadcastResult(r,&SteamInventoryRequests::GetResultTimestamp,resultHandle); return r; }
        static SteamInventoryResultHandle GetAllItems()                                                   { SteamInventoryResultHandle r=-1; SteamInventoryRequestBus::BroadcastResult(r,&SteamInventoryRequests::GetAllItems); return r; }
        static SteamInventoryResultHandle GetItemsByID(const AZStd::vector<SteamItemInstanceId>& instanceIds) { SteamInventoryResultHandle r=-1; SteamInventoryRequestBus::BroadcastResult(r,&SteamInventoryRequests::GetItemsByID,instanceIds); return r; }
        static SteamInventoryResultHandle AddPromoItem(SteamItemDefId itemDefId)                          { SteamInventoryResultHandle r=-1; SteamInventoryRequestBus::BroadcastResult(r,&SteamInventoryRequests::AddPromoItem,itemDefId); return r; }
        static SteamInventoryResultHandle AddPromoItems(const AZStd::vector<SteamItemDefId>& itemDefIds)  { SteamInventoryResultHandle r=-1; SteamInventoryRequestBus::BroadcastResult(r,&SteamInventoryRequests::AddPromoItems,itemDefIds); return r; }
        static SteamInventoryResultHandle ConsumeItem(SteamItemInstanceId instanceId, AZ::u32 quantity)   { SteamInventoryResultHandle r=-1; SteamInventoryRequestBus::BroadcastResult(r,&SteamInventoryRequests::ConsumeItem,instanceId,quantity); return r; }
        static SteamInventoryResultHandle TransferItemQuantity(SteamItemInstanceId sourceId, AZ::u32 quantity, SteamItemInstanceId destId) { SteamInventoryResultHandle r=-1; SteamInventoryRequestBus::BroadcastResult(r,&SteamInventoryRequests::TransferItemQuantity,sourceId,quantity,destId); return r; }
        static SteamInventoryResultHandle GetAllItemsServer()                                              { SteamInventoryResultHandle r=-1; SteamInventoryRequestBus::BroadcastResult(r,&SteamInventoryRequests::GetAllItemsServer); return r; }
        static AZ::u32                GetNumItemDefinitions()                                              { AZ::u32 r=0;         SteamInventoryRequestBus::BroadcastResult(r,&SteamInventoryRequests::GetNumItemDefinitions); return r; }
        static AZStd::string          GetItemDefinitionProperty(SteamItemDefId defId, const AZStd::string& propertyName) { AZStd::string r; SteamInventoryRequestBus::BroadcastResult(r,&SteamInventoryRequests::GetItemDefinitionProperty,defId,propertyName); return r; }
        static bool                   LoadItemDefinitions()                                                { bool r=false;        SteamInventoryRequestBus::BroadcastResult(r,&SteamInventoryRequests::LoadItemDefinitions); return r; }
        static SteamCallHandle        StartPurchase(const AZStd::vector<SteamItemDefId>& itemDefIds, const AZStd::vector<AZ::u32>& quantities) { SteamCallHandle r=0; SteamInventoryRequestBus::BroadcastResult(r,&SteamInventoryRequests::StartPurchase,itemDefIds,quantities); return r; }
        static SteamCallHandle        RequestPrices()                                                      { SteamCallHandle r=0; SteamInventoryRequestBus::BroadcastResult(r,&SteamInventoryRequests::RequestPrices); return r; }
    };

    struct SteamUGCAPI
    {
        AZ_TYPE_INFO(SteamUGCAPI, "{80B8C9D0-E1F2-46D7-B4C5-D6E7F8A9B0C1}");
        AZ_CLASS_ALLOCATOR(SteamUGCAPI, AZ::SystemAllocator);
        static AZ::u32         GetItemState(SteamPublishedFileId fileId)                              { AZ::u32 r=0;         SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::GetItemState,fileId); return r; }
        static bool            GetItemDownloadInfo(SteamPublishedFileId fileId, AZ::u64& outBytesDownloaded, AZ::u64& outBytesTotal) { bool r=false; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::GetItemDownloadInfo,fileId,outBytesDownloaded,outBytesTotal); return r; }
        static bool            GetItemInstallInfo(SteamPublishedFileId fileId, AZ::u64& outSizeOnDisk, AZStd::string& outFolder, AZ::u32& outTimestamp) { bool r=false; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::GetItemInstallInfo,fileId,outSizeOnDisk,outFolder,outTimestamp); return r; }
        static AZ::u32         GetNumSubscribedItems()                                                { AZ::u32 r=0;         SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::GetNumSubscribedItems); return r; }
        static AZ::u32         GetSubscribedItems(AZStd::vector<SteamPublishedFileId>& outIds, AZ::u32 maxEntries) { AZ::u32 r=0; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::GetSubscribedItems,outIds,maxEntries); return r; }
        static SteamUGCQueryHandle CreateQueryAllUGCRequest(AZ::s32 queryType, AZ::s32 matchingFileType, SteamAppId creatorAppId, SteamAppId consumerAppId, AZ::u32 page) { SteamUGCQueryHandle r=0; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::CreateQueryAllUGCRequest,queryType,matchingFileType,creatorAppId,consumerAppId,page); return r; }
        static SteamUGCQueryHandle CreateQueryUserUGCRequest(SteamId accountId, AZ::s32 listType, AZ::s32 matchingFileType, AZ::s32 sortOrder, SteamAppId creatorAppId, SteamAppId consumerAppId, AZ::u32 page) { SteamUGCQueryHandle r=0; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::CreateQueryUserUGCRequest,accountId,listType,matchingFileType,sortOrder,creatorAppId,consumerAppId,page); return r; }
        static SteamUGCQueryHandle CreateQueryUGCDetailsRequest(const AZStd::vector<SteamPublishedFileId>& fileIds) { SteamUGCQueryHandle r=0; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::CreateQueryUGCDetailsRequest,fileIds); return r; }
        static bool            AddRequiredTag(SteamUGCQueryHandle queryHandle, const AZStd::string& tagName)           { bool r=false; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::AddRequiredTag,queryHandle,tagName); return r; }
        static bool            AddExcludedTag(SteamUGCQueryHandle queryHandle, const AZStd::string& tagName)           { bool r=false; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::AddExcludedTag,queryHandle,tagName); return r; }
        static bool            SetMatchAnyTag(SteamUGCQueryHandle queryHandle, bool matchAnyTag)                       { bool r=false; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::SetMatchAnyTag,queryHandle,matchAnyTag); return r; }
        static bool            AddRequiredKeyValueTag(SteamUGCQueryHandle queryHandle, const AZStd::string& key, const AZStd::string& value) { bool r=false; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::AddRequiredKeyValueTag,queryHandle,key,value); return r; }
        static bool            SetReturnLongDescription(SteamUGCQueryHandle queryHandle, bool returnLongDescription)   { bool r=false; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::SetReturnLongDescription,queryHandle,returnLongDescription); return r; }
        static bool            SetReturnMetadata(SteamUGCQueryHandle queryHandle, bool returnMetadata)                 { bool r=false; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::SetReturnMetadata,queryHandle,returnMetadata); return r; }
        static bool            SetReturnChildren(SteamUGCQueryHandle queryHandle, bool returnChildren)                 { bool r=false; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::SetReturnChildren,queryHandle,returnChildren); return r; }
        static bool            SetReturnAdditionalPreviews(SteamUGCQueryHandle queryHandle, bool returnAdditionalPreviews) { bool r=false; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::SetReturnAdditionalPreviews,queryHandle,returnAdditionalPreviews); return r; }
        static bool            SetReturnTotalOnly(SteamUGCQueryHandle queryHandle, bool returnTotalOnly)               { bool r=false; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::SetReturnTotalOnly,queryHandle,returnTotalOnly); return r; }
        static bool            SetLanguage(SteamUGCQueryHandle queryHandle, const AZStd::string& language)             { bool r=false; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::SetLanguage,queryHandle,language); return r; }
        static bool            SetAllowCachedResponse(SteamUGCQueryHandle queryHandle, AZ::u32 maxAgeSeconds)          { bool r=false; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::SetAllowCachedResponse,queryHandle,maxAgeSeconds); return r; }
        static void            ReleaseQueryUGCRequest(SteamUGCQueryHandle queryHandle)                                 { SteamUGCRequestBus::Broadcast(&SteamUGCRequests::ReleaseQueryUGCRequest,queryHandle); }
        static SteamUGCUpdateHandle StartItemUpdate(SteamAppId consumerAppId, SteamPublishedFileId fileId)             { SteamUGCUpdateHandle r=0; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::StartItemUpdate,consumerAppId,fileId); return r; }
        static bool            SetItemTitle(SteamUGCUpdateHandle updateHandle, const AZStd::string& title)             { bool r=false; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::SetItemTitle,updateHandle,title); return r; }
        static bool            SetItemDescription(SteamUGCUpdateHandle updateHandle, const AZStd::string& description) { bool r=false; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::SetItemDescription,updateHandle,description); return r; }
        static bool            SetItemMetadata(SteamUGCUpdateHandle updateHandle, const AZStd::string& metadata)       { bool r=false; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::SetItemMetadata,updateHandle,metadata); return r; }
        static bool            SetItemVisibility(SteamUGCUpdateHandle updateHandle, SteamUGCVisibility visibility)      { bool r=false; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::SetItemVisibility,updateHandle,visibility); return r; }
        static bool            SetItemTags(SteamUGCUpdateHandle updateHandle, const AZStd::vector<AZStd::string>& tags) { bool r=false; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::SetItemTags,updateHandle,tags); return r; }
        static bool            SetItemContent(SteamUGCUpdateHandle updateHandle, const AZStd::string& contentFolder)   { bool r=false; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::SetItemContent,updateHandle,contentFolder); return r; }
        static bool            SetItemPreview(SteamUGCUpdateHandle updateHandle, const AZStd::string& previewFile)     { bool r=false; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::SetItemPreview,updateHandle,previewFile); return r; }
        static bool            DownloadItem(SteamPublishedFileId fileId, bool highPriority)                            { bool r=false; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::DownloadItem,fileId,highPriority); return r; }
        static SteamCallHandle SendQueryUGCRequest(SteamUGCQueryHandle queryHandle)                                    { SteamCallHandle r=0; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::SendQueryUGCRequest,queryHandle); return r; }
        static SteamCallHandle RequestUGCDetails(SteamPublishedFileId fileId, AZ::u32 maxAgeSeconds)                   { SteamCallHandle r=0; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::RequestUGCDetails,fileId,maxAgeSeconds); return r; }
        static SteamCallHandle CreateItem(SteamAppId consumerAppId, AZ::s32 fileType)                                  { SteamCallHandle r=0; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::CreateItem,consumerAppId,fileType); return r; }
        static SteamCallHandle SubmitItemUpdate(SteamUGCUpdateHandle updateHandle, const AZStd::string& changeNote)    { SteamCallHandle r=0; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::SubmitItemUpdate,updateHandle,changeNote); return r; }
        static SteamCallHandle AddItemToFavorites(SteamAppId appId, SteamPublishedFileId fileId)                       { SteamCallHandle r=0; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::AddItemToFavorites,appId,fileId); return r; }
        static SteamCallHandle RemoveItemFromFavorites(SteamAppId appId, SteamPublishedFileId fileId)                  { SteamCallHandle r=0; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::RemoveItemFromFavorites,appId,fileId); return r; }
        static SteamCallHandle SetUserItemVote(SteamPublishedFileId fileId, bool voteUp)                               { SteamCallHandle r=0; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::SetUserItemVote,fileId,voteUp); return r; }
        static SteamCallHandle GetUserItemVote(SteamPublishedFileId fileId)                                            { SteamCallHandle r=0; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::GetUserItemVote,fileId); return r; }
        static SteamCallHandle StartPlaytimeTracking(const AZStd::vector<SteamPublishedFileId>& fileIds)               { SteamCallHandle r=0; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::StartPlaytimeTracking,fileIds); return r; }
        static SteamCallHandle StopPlaytimeTracking(const AZStd::vector<SteamPublishedFileId>& fileIds)                { SteamCallHandle r=0; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::StopPlaytimeTracking,fileIds); return r; }
        static SteamCallHandle StopPlaytimeTrackingForAllItems()                                                        { SteamCallHandle r=0; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::StopPlaytimeTrackingForAllItems); return r; }
        static SteamCallHandle AddDependency(SteamPublishedFileId parentId, SteamPublishedFileId childId)              { SteamCallHandle r=0; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::AddDependency,parentId,childId); return r; }
        static SteamCallHandle RemoveDependency(SteamPublishedFileId parentId, SteamPublishedFileId childId)           { SteamCallHandle r=0; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::RemoveDependency,parentId,childId); return r; }
        static SteamCallHandle DeleteItem(SteamPublishedFileId fileId)                                                  { SteamCallHandle r=0; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::DeleteItem,fileId); return r; }
        static SteamCallHandle GetWorkshopEULAStatus()                                                                  { SteamCallHandle r=0; SteamUGCRequestBus::BroadcastResult(r,&SteamUGCRequests::GetWorkshopEULAStatus); return r; }
        static SteamItemDownloadInfoResult SC_GetItemDownloadInfo(SteamPublishedFileId fileId)  { SteamItemDownloadInfoResult out; SteamUGCRequestBus::BroadcastResult(out.success,&SteamUGCRequests::GetItemDownloadInfo,fileId,out.bytesDownloaded,out.bytesTotal); return out; }
        static SteamItemInstallInfoResult  SC_GetItemInstallInfo(SteamPublishedFileId fileId)   { SteamItemInstallInfoResult out; SteamUGCRequestBus::BroadcastResult(out.success,&SteamUGCRequests::GetItemInstallInfo,fileId,out.sizeOnDisk,out.folder,out.timestamp); return out; }
    };

    struct SteamUtilsAPI
    {
        AZ_TYPE_INFO(SteamUtilsAPI, "{90C9D0E1-F2A3-47E8-C5D6-E7F8A9B0C1D2}");
        AZ_CLASS_ALLOCATOR(SteamUtilsAPI, AZ::SystemAllocator);
        static AZ::u32       GetServerRealTime()                                                           { AZ::u32 r=0;     SteamUtilsRequestBus::BroadcastResult(r,&SteamUtilsRequests::GetServerRealTime); return r; }
        static AZStd::string GetIPCountry()                                                                { AZStd::string r; SteamUtilsRequestBus::BroadcastResult(r,&SteamUtilsRequests::GetIPCountry); return r; }
        static AZStd::string GetSteamUILanguage()                                                          { AZStd::string r; SteamUtilsRequestBus::BroadcastResult(r,&SteamUtilsRequests::GetSteamUILanguage); return r; }
        static bool          GetImageSize(AZ::s32 imageHandle, AZ::u32& outWidth, AZ::u32& outHeight)     { bool r=false;    SteamUtilsRequestBus::BroadcastResult(r,&SteamUtilsRequests::GetImageSize,imageHandle,outWidth,outHeight); return r; }
        static bool          GetImageRGBA(AZ::s32 imageHandle, AZStd::vector<AZ::u8>& outData, AZ::u32 width, AZ::u32 height) { bool r=false; SteamUtilsRequestBus::BroadcastResult(r,&SteamUtilsRequests::GetImageRGBA,imageHandle,outData,width,height); return r; }
        static bool          IsOverlayEnabled()                                                            { bool r=false;    SteamUtilsRequestBus::BroadcastResult(r,&SteamUtilsRequests::IsOverlayEnabled); return r; }
        static bool          IsSteamInBigPictureMode()                                                     { bool r=false;    SteamUtilsRequestBus::BroadcastResult(r,&SteamUtilsRequests::IsSteamInBigPictureMode); return r; }
        static bool          IsSteamRunningOnSteamDeck()                                                   { bool r=false;    SteamUtilsRequestBus::BroadcastResult(r,&SteamUtilsRequests::IsSteamRunningOnSteamDeck); return r; }
        static bool          IsSteamRunningInVR()                                                          { bool r=false;    SteamUtilsRequestBus::BroadcastResult(r,&SteamUtilsRequests::IsSteamRunningInVR); return r; }
        static bool          ShowFloatingGamepadTextInput(AZ::s32 inputMode, AZ::s32 x, AZ::s32 y, AZ::s32 width, AZ::s32 height) { bool r=false; SteamUtilsRequestBus::BroadcastResult(r,&SteamUtilsRequests::ShowFloatingGamepadTextInput,inputMode,x,y,width,height); return r; }
        static bool          DismissFloatingGamepadTextInput()                                              { bool r=false;    SteamUtilsRequestBus::BroadcastResult(r,&SteamUtilsRequests::DismissFloatingGamepadTextInput); return r; }
        static bool          FilterText(AZ::s32 context, SteamId sourceSteamId, const AZStd::string& inputMessage, AZStd::string& outFiltered) { bool r=false; SteamUtilsRequestBus::BroadcastResult(r,&SteamUtilsRequests::FilterText,context,sourceSteamId,inputMessage,outFiltered); return r; }
        static AZ::u8        GetCurrentBatteryPower()                                                      { AZ::u8 r=255;    SteamUtilsRequestBus::BroadcastResult(r,&SteamUtilsRequests::GetCurrentBatteryPower); return r; }
        static bool          IsSteamChinaLauncher()                                                        { bool r=false;    SteamUtilsRequestBus::BroadcastResult(r,&SteamUtilsRequests::IsSteamChinaLauncher); return r; }
        static SteamImageSizeResult        SC_GetImageSize(AZ::s32 imageHandle)                { SteamImageSizeResult out; SteamUtilsRequestBus::BroadcastResult(out.success,&SteamUtilsRequests::GetImageSize,imageHandle,out.width,out.height); return out; }
        static SteamFilterTextResult       SC_FilterText(AZ::s32 context, SteamId sourceSteamId, const AZStd::string& inputMessage) { SteamFilterTextResult out; SteamUtilsRequestBus::BroadcastResult(out.success,&SteamUtilsRequests::FilterText,context,sourceSteamId,inputMessage,out.filtered); return out; }
    };

    struct SteamScreenshotsAPI
    {
        AZ_TYPE_INFO(SteamScreenshotsAPI, "{A0D0E1F2-A3B4-48F9-D6E7-F8A9B0C1D2E3}");
        AZ_CLASS_ALLOCATOR(SteamScreenshotsAPI, AZ::SystemAllocator);
        static void    TriggerScreenshot()                                                                           { SteamScreenshotsRequestBus::Broadcast(&SteamScreenshotsRequests::TriggerScreenshot); }
        static AZ::u32 WriteScreenshot(const AZStd::vector<AZ::u8>& data, AZ::u32 width, AZ::u32 height)            { AZ::u32 r=0; SteamScreenshotsRequestBus::BroadcastResult(r,&SteamScreenshotsRequests::WriteScreenshot,data,width,height); return r; }
        static AZ::u32 AddScreenshotToLibrary(const AZStd::string& fileName, const AZStd::string& thumbnailFileName, AZ::u32 width, AZ::u32 height) { AZ::u32 r=0; SteamScreenshotsRequestBus::BroadcastResult(r,&SteamScreenshotsRequests::AddScreenshotToLibrary,fileName,thumbnailFileName,width,height); return r; }
        static bool    SetScreenshotCaption(AZ::u32 screenshotHandle, const AZStd::string& caption)                 { bool r=false; SteamScreenshotsRequestBus::BroadcastResult(r,&SteamScreenshotsRequests::SetScreenshotCaption,screenshotHandle,caption); return r; }
        static bool    TagUser(AZ::u32 screenshotHandle, SteamId userId)                                            { bool r=false; SteamScreenshotsRequestBus::BroadcastResult(r,&SteamScreenshotsRequests::TagUser,screenshotHandle,userId); return r; }
        static bool    TagPublishedFile(AZ::u32 screenshotHandle, SteamPublishedFileId fileId)                      { bool r=false; SteamScreenshotsRequestBus::BroadcastResult(r,&SteamScreenshotsRequests::TagPublishedFile,screenshotHandle,fileId); return r; }
        static bool    IsScreenshotsHooked()                                                                        { bool r=false; SteamScreenshotsRequestBus::BroadcastResult(r,&SteamScreenshotsRequests::IsScreenshotsHooked); return r; }
        static void    HookScreenshots(bool hook)                                                                    { SteamScreenshotsRequestBus::Broadcast(&SteamScreenshotsRequests::HookScreenshots,hook); }
    };

    struct SteamRemotePlayAPI
    {
        AZ_TYPE_INFO(SteamRemotePlayAPI, "{B0E1F2A3-B4C5-490A-E7F8-A9B0C1D2E3F4}");
        AZ_CLASS_ALLOCATOR(SteamRemotePlayAPI, AZ::SystemAllocator);
        static AZ::u32       GetSessionCount()                                                             { AZ::u32 r=0;     SteamRemotePlayRequestBus::BroadcastResult(r,&SteamRemotePlayRequests::GetSessionCount); return r; }
        static AZ::u32       GetSessionID(AZ::u32 index)                                                   { AZ::u32 r=0;     SteamRemotePlayRequestBus::BroadcastResult(r,&SteamRemotePlayRequests::GetSessionID,index); return r; }
        static SteamId       GetSessionSteamID(AZ::u32 sessionId)                                         { SteamId r=0;     SteamRemotePlayRequestBus::BroadcastResult(r,&SteamRemotePlayRequests::GetSessionSteamID,sessionId); return r; }
        static AZStd::string GetSessionClientName(AZ::u32 sessionId)                                      { AZStd::string r; SteamRemotePlayRequestBus::BroadcastResult(r,&SteamRemotePlayRequests::GetSessionClientName,sessionId); return r; }
        static AZ::s32       GetSessionClientFormFactor(AZ::u32 sessionId)                                 { AZ::s32 r=0;     SteamRemotePlayRequestBus::BroadcastResult(r,&SteamRemotePlayRequests::GetSessionClientFormFactor,sessionId); return r; }
        static bool          GetSessionClientResolution(AZ::u32 sessionId, AZ::s32& outWidth, AZ::s32& outHeight) { bool r=false; SteamRemotePlayRequestBus::BroadcastResult(r,&SteamRemotePlayRequests::GetSessionClientResolution,sessionId,outWidth,outHeight); return r; }
        static bool          SendRemotePlayTogetherInvite(SteamId friendId)                                { bool r=false;    SteamRemotePlayRequestBus::BroadcastResult(r,&SteamRemotePlayRequests::SendRemotePlayTogetherInvite,friendId); return r; }
        static SteamSessionClientResolutionResult SC_GetSessionClientResolution(AZ::u32 sessionId) { SteamSessionClientResolutionResult out; SteamRemotePlayRequestBus::BroadcastResult(out.success,&SteamRemotePlayRequests::GetSessionClientResolution,sessionId,out.width,out.height); return out; }
    };

    // -----------------------------------------------------------------------
    // SteamCoreAPI — lifecycle proxy (init / shutdown / status)
    // Exposes Initialise, Shutdown, IsInitialised, GameServerInitialise,
    // GameServerShutdown, IsGameServerInitialised, InputInitialise,
    // InputShutdown, and IsInputInitialised to Script Canvas / Lua.
    // -----------------------------------------------------------------------
    struct SteamCoreAPI
    {
        AZ_TYPE_INFO(SteamCoreAPI, "{A1B2C3D4-E5F6-4A7B-8C9D-E0F1A2B3C4D5}");
        AZ_CLASS_ALLOCATOR(SteamCoreAPI, AZ::SystemAllocator);

        static void Shutdown()                { FoundationSteamworksRequestBus::Broadcast(&FoundationSteamworksRequests::Shutdown); }
        static bool IsInitialised()           { bool r=false; FoundationSteamworksRequestBus::BroadcastResult(r,&FoundationSteamworksRequests::IsInitialised); return r; }

        static void GameServerShutdown()       { FoundationSteamworksRequestBus::Broadcast(&FoundationSteamworksRequests::GameServerShutdown); }
        static bool IsGameServerInitialised()  { bool r=false; FoundationSteamworksRequestBus::BroadcastResult(r,&FoundationSteamworksRequests::IsGameServerInitialised); return r; }

        static bool InputInitialise()          { bool r=false; FoundationSteamworksRequestBus::BroadcastResult(r,&FoundationSteamworksRequests::InputInitialise); return r; }
        static void InputShutdown()            { FoundationSteamworksRequestBus::Broadcast(&FoundationSteamworksRequests::InputShutdown); }
        static bool IsInputInitialised()       { bool r=false; FoundationSteamworksRequestBus::BroadcastResult(r,&FoundationSteamworksRequests::IsInputInitialised); return r; }

        static SteamInitResult Initialise(AZ::u32 appId)
        {
            SteamInitResult out;
            FoundationSteamworksRequestBus::BroadcastResult(out.success, &FoundationSteamworksRequests::Initialise, appId, out.errorMsg);
            return out;
        }

        static SteamInitResult GameServerInitialise(
            AZ::u32 appId,
            const AZStd::string& localIP, AZ::u16 gamePort, AZ::u16 queryPort,
            SteamServerMode serverMode, const AZStd::string& versionString)
        {
            SteamInitResult out;
            FoundationSteamworksRequestBus::BroadcastResult(out.success, &FoundationSteamworksRequests::GameServerInitialise,
                appId, localIP, gamePort, queryPort, serverMode, versionString, out.errorMsg);
            return out;
        }
    };

    struct SteamGameServerAPI
    {
        AZ_TYPE_INFO(SteamGameServerAPI, "{D5E6F7A8-B9C0-4D1E-F2A3-B4C5D6E7F8A9}");
        AZ_CLASS_ALLOCATOR(SteamGameServerAPI, AZ::SystemAllocator);
        static void          SetProduct(const AZStd::string& product)                       { SteamGameServerRequestBus::Broadcast(&SteamGameServerRequests::SetProduct,product); }
        static void          SetGameDescription(const AZStd::string& desc)                  { SteamGameServerRequestBus::Broadcast(&SteamGameServerRequests::SetGameDescription,desc); }
        static void          SetModDir(const AZStd::string& modDir)                         { SteamGameServerRequestBus::Broadcast(&SteamGameServerRequests::SetModDir,modDir); }
        static void          SetDedicatedServer(bool dedicated)                              { SteamGameServerRequestBus::Broadcast(&SteamGameServerRequests::SetDedicatedServer,dedicated); }
        static void          LogOn(const AZStd::string& token)                              { SteamGameServerRequestBus::Broadcast(&SteamGameServerRequests::LogOn,token); }
        static void          LogOnAnonymous()                                                { SteamGameServerRequestBus::Broadcast(&SteamGameServerRequests::LogOnAnonymous); }
        static void          LogOff()                                                        { SteamGameServerRequestBus::Broadcast(&SteamGameServerRequests::LogOff); }
        static bool          GSIsLoggedOn()                                                  { bool r=false; SteamGameServerRequestBus::BroadcastResult(r,&SteamGameServerRequests::GSIsLoggedOn); return r; }
        static bool          GSIsSecure()                                                    { bool r=false; SteamGameServerRequestBus::BroadcastResult(r,&SteamGameServerRequests::GSIsSecure); return r; }
        static SteamId       GSGetSteamID()                                                  { SteamId r=0;  SteamGameServerRequestBus::BroadcastResult(r,&SteamGameServerRequests::GSGetSteamID); return r; }
        static bool          WasRestartRequested()                                           { bool r=false; SteamGameServerRequestBus::BroadcastResult(r,&SteamGameServerRequests::WasRestartRequested); return r; }
        static void          SetMaxPlayerCount(AZ::s32 maxPlayers)                          { SteamGameServerRequestBus::Broadcast(&SteamGameServerRequests::SetMaxPlayerCount,maxPlayers); }
        static void          SetBotPlayerCount(AZ::s32 botPlayers)                          { SteamGameServerRequestBus::Broadcast(&SteamGameServerRequests::SetBotPlayerCount,botPlayers); }
        static void          SetServerName(const AZStd::string& name)                       { SteamGameServerRequestBus::Broadcast(&SteamGameServerRequests::SetServerName,name); }
        static void          SetMapName(const AZStd::string& name)                          { SteamGameServerRequestBus::Broadcast(&SteamGameServerRequests::SetMapName,name); }
        static void          SetPasswordProtected(bool pw)                                   { SteamGameServerRequestBus::Broadcast(&SteamGameServerRequests::SetPasswordProtected,pw); }
        static void          SetSpectatorPort(AZ::u16 port)                                 { SteamGameServerRequestBus::Broadcast(&SteamGameServerRequests::SetSpectatorPort,port); }
        static void          SetSpectatorServerName(const AZStd::string& name)              { SteamGameServerRequestBus::Broadcast(&SteamGameServerRequests::SetSpectatorServerName,name); }
        static void          ClearAllKeyValues()                                             { SteamGameServerRequestBus::Broadcast(&SteamGameServerRequests::ClearAllKeyValues); }
        static void          SetKeyValue(const AZStd::string& key, const AZStd::string& val) { SteamGameServerRequestBus::Broadcast(&SteamGameServerRequests::SetKeyValue,key,val); }
        static void          SetGameTags(const AZStd::string& tags)                         { SteamGameServerRequestBus::Broadcast(&SteamGameServerRequests::SetGameTags,tags); }
        static void          SetGameData(const AZStd::string& data)                         { SteamGameServerRequestBus::Broadcast(&SteamGameServerRequests::SetGameData,data); }
        static void          SetRegion(const AZStd::string& region)                         { SteamGameServerRequestBus::Broadcast(&SteamGameServerRequests::SetRegion,region); }
        static void          SetAdvertiseServerActive(bool active)                           { SteamGameServerRequestBus::Broadcast(&SteamGameServerRequests::SetAdvertiseServerActive,active); }
        static AZ::s32       BeginAuthSession(const AZStd::vector<AZ::u8>& ticket, SteamId steamId) { AZ::s32 r=-1; SteamGameServerRequestBus::BroadcastResult(r,&SteamGameServerRequests::BeginAuthSession,ticket,steamId); return r; }
        static void          EndAuthSession(SteamId steamId)                                { SteamGameServerRequestBus::Broadcast(&SteamGameServerRequests::EndAuthSession,steamId); }
        static void          GSCancelAuthTicket(SteamAuthTicketHandle handle)               { SteamGameServerRequestBus::Broadcast(&SteamGameServerRequests::GSCancelAuthTicket,handle); }
        static AZ::s32       UserHasLicenseForApp(SteamId steamId, SteamAppId appId)        { AZ::s32 r=0;  SteamGameServerRequestBus::BroadcastResult(r,&SteamGameServerRequests::UserHasLicenseForApp,steamId,appId); return r; }
        static bool          RequestUserGroupStatus(SteamId userId, SteamId groupId)        { bool r=false; SteamGameServerRequestBus::BroadcastResult(r,&SteamGameServerRequests::RequestUserGroupStatus,userId,groupId); return r; }
        static bool          UpdateUserData(SteamId userId, const AZStd::string& name, AZ::u32 score) { bool r=false; SteamGameServerRequestBus::BroadcastResult(r,&SteamGameServerRequests::UpdateUserData,userId,name,score); return r; }
        static SteamCallHandle AssociateWithClan(SteamId clanId)                            { SteamCallHandle r=0; SteamGameServerRequestBus::BroadcastResult(r,&SteamGameServerRequests::AssociateWithClan,clanId); return r; }
        static SteamCallHandle ComputeNewPlayerCompatibility(SteamId newPlayerId)           { SteamCallHandle r=0; SteamGameServerRequestBus::BroadcastResult(r,&SteamGameServerRequests::ComputeNewPlayerCompatibility,newPlayerId); return r; }
        static SteamCallHandle GetServerReputation()                                         { SteamCallHandle r=0; SteamGameServerRequestBus::BroadcastResult(r,&SteamGameServerRequests::GetServerReputation); return r; }
    };

    struct SteamInputAPI
    {
        AZ_TYPE_INFO(SteamInputAPI, "{E6F7A8B9-C0D1-4E2F-A3B4-C5D6E7F8A9B0}");
        AZ_CLASS_ALLOCATOR(SteamInputAPI, AZ::SystemAllocator);
        static AZStd::vector<AZ::u64> GetConnectedControllers()                                          { AZStd::vector<AZ::u64> r; SteamInputRequestBus::BroadcastResult(r,&SteamInputRequests::GetConnectedControllers); return r; }
        static void                   EnableDeviceCallbacks()                                             { SteamInputRequestBus::Broadcast(&SteamInputRequests::EnableDeviceCallbacks); }
        static AZ::u64                GetActionSetHandle(const AZStd::string& name)                       { AZ::u64 r=0; SteamInputRequestBus::BroadcastResult(r,&SteamInputRequests::GetActionSetHandle,name); return r; }
        static void                   ActivateActionSet(AZ::u64 inputHandle, AZ::u64 actionSetHandle)    { SteamInputRequestBus::Broadcast(&SteamInputRequests::ActivateActionSet,inputHandle,actionSetHandle); }
        static AZ::u64                GetCurrentActionSet(AZ::u64 inputHandle)                            { AZ::u64 r=0; SteamInputRequestBus::BroadcastResult(r,&SteamInputRequests::GetCurrentActionSet,inputHandle); return r; }
        static void                   ActivateActionSetLayer(AZ::u64 inputHandle, AZ::u64 layerHandle)   { SteamInputRequestBus::Broadcast(&SteamInputRequests::ActivateActionSetLayer,inputHandle,layerHandle); }
        static void                   DeactivateActionSetLayer(AZ::u64 inputHandle, AZ::u64 layerHandle) { SteamInputRequestBus::Broadcast(&SteamInputRequests::DeactivateActionSetLayer,inputHandle,layerHandle); }
        static void                   DeactivateAllActionSetLayers(AZ::u64 inputHandle)                   { SteamInputRequestBus::Broadcast(&SteamInputRequests::DeactivateAllActionSetLayers,inputHandle); }
        static AZStd::vector<AZ::u64> GetActiveActionSetLayers(AZ::u64 inputHandle)                      { AZStd::vector<AZ::u64> r; SteamInputRequestBus::BroadcastResult(r,&SteamInputRequests::GetActiveActionSetLayers,inputHandle); return r; }
        static AZ::u64                GetDigitalActionHandle(const AZStd::string& name)                   { AZ::u64 r=0; SteamInputRequestBus::BroadcastResult(r,&SteamInputRequests::GetDigitalActionHandle,name); return r; }
        static SteamInputDigitalActionData GetDigitalActionData(AZ::u64 inputHandle, AZ::u64 actionHandle) { SteamInputDigitalActionData r; SteamInputRequestBus::BroadcastResult(r,&SteamInputRequests::GetDigitalActionData,inputHandle,actionHandle); return r; }
        static AZStd::string          GetStringForDigitalActionName(AZ::u64 handle)                       { AZStd::string r; SteamInputRequestBus::BroadcastResult(r,&SteamInputRequests::GetStringForDigitalActionName,handle); return r; }
        static AZ::u64                GetAnalogActionHandle(const AZStd::string& name)                    { AZ::u64 r=0; SteamInputRequestBus::BroadcastResult(r,&SteamInputRequests::GetAnalogActionHandle,name); return r; }
        static SteamInputAnalogActionData GetAnalogActionData(AZ::u64 inputHandle, AZ::u64 actionHandle)  { SteamInputAnalogActionData r; SteamInputRequestBus::BroadcastResult(r,&SteamInputRequests::GetAnalogActionData,inputHandle,actionHandle); return r; }
        static AZStd::string          GetStringForAnalogActionName(AZ::u64 handle)                        { AZStd::string r; SteamInputRequestBus::BroadcastResult(r,&SteamInputRequests::GetStringForAnalogActionName,handle); return r; }
        static void                   TriggerVibration(AZ::u64 inputHandle, AZ::u16 leftSpeed, AZ::u16 rightSpeed) { SteamInputRequestBus::Broadcast(&SteamInputRequests::TriggerVibration,inputHandle,leftSpeed,rightSpeed); }
        static void                   TriggerVibrationExtended(AZ::u64 inputHandle, AZ::u16 leftSpeed, AZ::u16 rightSpeed, AZ::u16 leftTriggerSpeed, AZ::u16 rightTriggerSpeed) { SteamInputRequestBus::Broadcast(&SteamInputRequests::TriggerVibrationExtended,inputHandle,leftSpeed,rightSpeed,leftTriggerSpeed,rightTriggerSpeed); }
        static void                   SetLEDColor(AZ::u64 inputHandle, AZ::u8 r, AZ::u8 g, AZ::u8 b, AZ::u32 flags) { SteamInputRequestBus::Broadcast(&SteamInputRequests::SetLEDColor,inputHandle,r,g,b,flags); }
        static bool                   ShowBindingPanel(AZ::u64 inputHandle)                               { bool r=false; SteamInputRequestBus::BroadcastResult(r,&SteamInputRequests::ShowBindingPanel,inputHandle); return r; }
        static AZ::s32                GetInputTypeForHandle(AZ::u64 inputHandle)                          { AZ::s32 r=0; SteamInputRequestBus::BroadcastResult(r,&SteamInputRequests::GetInputTypeForHandle,inputHandle); return r; }
        static AZ::u64                GetControllerForGamepadIndex(AZ::s32 index)                         { AZ::u64 r=0; SteamInputRequestBus::BroadcastResult(r,&SteamInputRequests::GetControllerForGamepadIndex,index); return r; }
        static AZ::s32                GetGamepadIndexForController(AZ::u64 inputHandle)                   { AZ::s32 r=-1; SteamInputRequestBus::BroadcastResult(r,&SteamInputRequests::GetGamepadIndexForController,inputHandle); return r; }
        static AZ::u32                GetRemotePlaySessionID(AZ::u64 inputHandle)                         { AZ::u32 r=0; SteamInputRequestBus::BroadcastResult(r,&SteamInputRequests::GetRemotePlaySessionID,inputHandle); return r; }
    };

    struct SteamGameServerStatsAPI
    {
        AZ_TYPE_INFO(SteamGameServerStatsAPI, "{F7A8B9C0-D1E2-4F3A-B4C5-D6E7F8A9B0C1}");
        AZ_CLASS_ALLOCATOR(SteamGameServerStatsAPI, AZ::SystemAllocator);
        static SteamCallHandle          GSRequestUserStats(SteamId steamId)                                    { SteamCallHandle r=0; SteamGameServerStatsRequestBus::BroadcastResult(r,&SteamGameServerStatsRequests::GSRequestUserStats,steamId); return r; }
        static SteamGSUserStatIntResult GSGetUserStatInt(SteamId steamId, const AZStd::string& name)           { SteamGSUserStatIntResult r; SteamGameServerStatsRequestBus::BroadcastResult(r,&SteamGameServerStatsRequests::GSGetUserStatInt,steamId,name); return r; }
        static SteamGSUserStatFloatResult GSGetUserStatFloat(SteamId steamId, const AZStd::string& name)       { SteamGSUserStatFloatResult r; SteamGameServerStatsRequestBus::BroadcastResult(r,&SteamGameServerStatsRequests::GSGetUserStatFloat,steamId,name); return r; }
        static SteamGSUserAchievementResult GSGetUserAchievement(SteamId steamId, const AZStd::string& name)   { SteamGSUserAchievementResult r; SteamGameServerStatsRequestBus::BroadcastResult(r,&SteamGameServerStatsRequests::GSGetUserAchievement,steamId,name); return r; }
        static bool GSSetUserStatInt(SteamId steamId, const AZStd::string& name, AZ::s32 value)                { bool r=false; SteamGameServerStatsRequestBus::BroadcastResult(r,&SteamGameServerStatsRequests::GSSetUserStatInt,steamId,name,value); return r; }
        static bool GSSetUserStatFloat(SteamId steamId, const AZStd::string& name, float value)                { bool r=false; SteamGameServerStatsRequestBus::BroadcastResult(r,&SteamGameServerStatsRequests::GSSetUserStatFloat,steamId,name,value); return r; }
        static bool GSUpdateUserAvgRateStat(SteamId steamId, const AZStd::string& name, float count, double len) { bool r=false; SteamGameServerStatsRequestBus::BroadcastResult(r,&SteamGameServerStatsRequests::GSUpdateUserAvgRateStat,steamId,name,count,len); return r; }
        static bool GSSetUserAchievement(SteamId steamId, const AZStd::string& name)                           { bool r=false; SteamGameServerStatsRequestBus::BroadcastResult(r,&SteamGameServerStatsRequests::GSSetUserAchievement,steamId,name); return r; }
        static bool GSClearUserAchievement(SteamId steamId, const AZStd::string& name)                        { bool r=false; SteamGameServerStatsRequestBus::BroadcastResult(r,&SteamGameServerStatsRequests::GSClearUserAchievement,steamId,name); return r; }
        static SteamCallHandle GSStoreUserStats(SteamId steamId)                                               { SteamCallHandle r=0; SteamGameServerStatsRequestBus::BroadcastResult(r,&SteamGameServerStatsRequests::GSStoreUserStats,steamId); return r; }
    };

    // -----------------------------------------------------------------------
    // SteamTimelineAPI — timeline event / phase / overlay proxy
    // -----------------------------------------------------------------------
    struct SteamTimelineAPI
    {
        AZ_TYPE_INFO(SteamTimelineAPI, "{E6F7A8B9-C0D1-4E2F-3A4B-C5D6E7F8A9B0}");
        AZ_CLASS_ALLOCATOR(SteamTimelineAPI, AZ::SystemAllocator);

        static void                    SetTimelineTooltip(const AZStd::string& description, float timeDelta)              { SteamTimelineRequestBus::Broadcast(&SteamTimelineRequests::SetTimelineTooltip,description,timeDelta); }
        static void                    ClearTimelineTooltip(float timeDelta)                                               { SteamTimelineRequestBus::Broadcast(&SteamTimelineRequests::ClearTimelineTooltip,timeDelta); }
        static void                    SetTimelineGameMode(SteamTimelineGameMode mode)                                     { SteamTimelineRequestBus::Broadcast(&SteamTimelineRequests::SetTimelineGameMode,mode); }

        static SteamTimelineEventHandle AddInstantaneousTimelineEvent(const AZStd::string& title, const AZStd::string& description, const AZStd::string& icon, AZ::u32 iconPriority, float startOffsetSeconds, SteamTimelineClipPriority clipPriority)
        {
            SteamTimelineEventHandle r=0;
            SteamTimelineRequestBus::BroadcastResult(r,&SteamTimelineRequests::AddInstantaneousTimelineEvent,title,description,icon,iconPriority,startOffsetSeconds,clipPriority);
            return r;
        }

        static SteamTimelineEventHandle AddRangeTimelineEvent(const AZStd::string& title, const AZStd::string& description, const AZStd::string& icon, AZ::u32 iconPriority, float startOffsetSeconds, float duration, SteamTimelineClipPriority clipPriority)
        {
            SteamTimelineEventHandle r=0;
            SteamTimelineRequestBus::BroadcastResult(r,&SteamTimelineRequests::AddRangeTimelineEvent,title,description,icon,iconPriority,startOffsetSeconds,duration,clipPriority);
            return r;
        }

        static SteamTimelineEventHandle StartRangeTimelineEvent(const AZStd::string& title, const AZStd::string& description, const AZStd::string& icon, AZ::u32 priority, float startOffsetSeconds, SteamTimelineClipPriority clipPriority)
        {
            SteamTimelineEventHandle r=0;
            SteamTimelineRequestBus::BroadcastResult(r,&SteamTimelineRequests::StartRangeTimelineEvent,title,description,icon,priority,startOffsetSeconds,clipPriority);
            return r;
        }

        static void                    UpdateRangeTimelineEvent(SteamTimelineEventHandle eventHandle, const AZStd::string& title, const AZStd::string& description, const AZStd::string& icon, AZ::u32 priority, SteamTimelineClipPriority clipPriority) { SteamTimelineRequestBus::Broadcast(&SteamTimelineRequests::UpdateRangeTimelineEvent,eventHandle,title,description,icon,priority,clipPriority); }
        static void                    EndRangeTimelineEvent(SteamTimelineEventHandle eventHandle, float endOffsetSeconds)  { SteamTimelineRequestBus::Broadcast(&SteamTimelineRequests::EndRangeTimelineEvent,eventHandle,endOffsetSeconds); }
        static void                    RemoveTimelineEvent(SteamTimelineEventHandle eventHandle)                            { SteamTimelineRequestBus::Broadcast(&SteamTimelineRequests::RemoveTimelineEvent,eventHandle); }
        static SteamCallHandle         DoesEventRecordingExist(SteamTimelineEventHandle eventHandle)                       { SteamCallHandle r=0; SteamTimelineRequestBus::BroadcastResult(r,&SteamTimelineRequests::DoesEventRecordingExist,eventHandle); return r; }

        static void                    StartGamePhase()                                                                    { SteamTimelineRequestBus::Broadcast(&SteamTimelineRequests::StartGamePhase); }
        static void                    EndGamePhase()                                                                      { SteamTimelineRequestBus::Broadcast(&SteamTimelineRequests::EndGamePhase); }
        static void                    SetGamePhaseID(const AZStd::string& phaseId)                                        { SteamTimelineRequestBus::Broadcast(&SteamTimelineRequests::SetGamePhaseID,phaseId); }
        static SteamCallHandle         DoesGamePhaseRecordingExist(const AZStd::string& phaseId)                          { SteamCallHandle r=0; SteamTimelineRequestBus::BroadcastResult(r,&SteamTimelineRequests::DoesGamePhaseRecordingExist,phaseId); return r; }
        static void                    AddGamePhaseTag(const AZStd::string& tagName, const AZStd::string& tagIcon, const AZStd::string& tagGroup, AZ::u32 priority) { SteamTimelineRequestBus::Broadcast(&SteamTimelineRequests::AddGamePhaseTag,tagName,tagIcon,tagGroup,priority); }
        static void                    SetGamePhaseAttribute(const AZStd::string& attributeGroup, const AZStd::string& attributeValue, AZ::u32 priority) { SteamTimelineRequestBus::Broadcast(&SteamTimelineRequests::SetGamePhaseAttribute,attributeGroup,attributeValue,priority); }

        static void                    OpenOverlayToGamePhase(const AZStd::string& phaseId)                               { SteamTimelineRequestBus::Broadcast(&SteamTimelineRequests::OpenOverlayToGamePhase,phaseId); }
        static void                    OpenOverlayToTimelineEvent(SteamTimelineEventHandle eventHandle)                    { SteamTimelineRequestBus::Broadcast(&SteamTimelineRequests::OpenOverlayToTimelineEvent,eventHandle); }
    };
} // namespace FoundationSteamworks
