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

#include <AzCore/base.h>
#include <AzCore/std/string/string.h>
#include <AzCore/RTTI/TypeInfo.h>
#include <AzCore/Memory/SystemAllocator.h>

namespace Heathen
{
    // -----------------------------------------------------------------------
    // Core handle types
    // These are O3DE-typed aliases for the underlying Steam handle types.
    // steam_api.h is never included in public headers — all Steam types are
    // normalised here and converted at the implementation boundary.
    // -----------------------------------------------------------------------

    /// Wraps CSteamID (uint64). Represents any Steam account, lobby, or game server.
    using SteamId = AZ::u64;

    /// Wraps SteamAPICall_t (uint64). Handle returned by CallResult-based API calls.
    /// Pass this handle to the corresponding notification bus listener to match
    /// a response to a specific request.
    using SteamCallHandle = AZ::u64;

    /// Wraps AppId_t (uint32).
    using SteamAppId = AZ::u32;

    /// Wraps DepotId_t (uint32).
    using SteamDepotId = AZ::u32;

    /// Wraps SteamItemInstanceID_t (uint64).
    using SteamItemInstanceId = AZ::u64;

    /// Wraps SteamItemDef_t (int32).
    using SteamItemDefId = AZ::s32;

    /// Wraps SteamInventoryResult_t (int32).
    using SteamInventoryResultHandle = AZ::s32;

    /// Wraps UGCHandle_t (uint64).
    using SteamUGCHandle = AZ::u64;

    /// Wraps UGCQueryHandle_t (uint64).
    using SteamUGCQueryHandle = AZ::u64;

    /// Wraps UGCUpdateHandle_t (uint64).
    using SteamUGCUpdateHandle = AZ::u64;

    /// Wraps PublishedFileId_t (uint64).
    using SteamPublishedFileId = AZ::u64;

    /// Wraps SteamLeaderboard_t (uint64).
    using SteamLeaderboardHandle = AZ::u64;

    /// Wraps SteamLeaderboardEntries_t (uint64).
    using SteamLeaderboardEntriesHandle = AZ::u64;

    /// Wraps HAuthTicket (uint32).
    using SteamAuthTicketHandle = AZ::u32;

    /// Invalid/null value for all handle types.
    inline constexpr AZ::u64 InvalidSteamHandle = 0;
    inline constexpr AZ::u32 InvalidSteamHandle32 = 0;

    // -----------------------------------------------------------------------
    // SteamResult — normalised EResult
    // Maps the most commonly used EResult values. Values are identical to the
    // Steam SDK so they can be cast directly at the implementation boundary.
    // -----------------------------------------------------------------------
    enum class SteamResult : AZ::s32
    {
        OK                          = 1,
        Fail                        = 2,
        NoConnection                = 3,
        InvalidPassword             = 5,
        LoggedInElsewhere           = 6,
        InvalidProtocolVersion      = 7,
        InvalidParam                = 8,
        FileNotFound                = 9,
        Busy                        = 10,
        InvalidState                = 11,
        InvalidName                 = 12,
        InvalidEmail                = 13,
        DuplicateName               = 14,
        AccessDenied                = 15,
        Timeout                     = 16,
        Banned                      = 17,
        AccountNotFound             = 18,
        InvalidSteamID              = 19,
        ServiceUnavailable          = 20,
        NotLoggedOn                 = 21,
        Pending                     = 22,
        EncryptionFailure           = 23,
        InsufficientPrivilege       = 24,
        LimitExceeded               = 25,
        Revoked                     = 26,
        Expired                     = 27,
        AlreadyRedeemed             = 28,
        DuplicateRequest            = 29,
        AlreadyOwned                = 30,
        IPNotFound                  = 31,
        PersistFailed               = 32,
        LockingFailed               = 33,
        LogonSessionReplaced        = 34,
        ConnectFailed               = 35,
        HandshakeFailed             = 36,
        IOFailure                   = 37,
        RemoteDisconnect            = 38,
        ShoppingCartNotFound        = 39,
        Blocked                     = 40,
        Ignored                     = 41,
        NoMatch                     = 42,
        AccountDisabled             = 43,
        ServiceReadOnly             = 44,
        AccountNotFeatured          = 45,
        AdministratorOK             = 46,
        ContentVersion              = 47,
        TryAnotherCM                = 48,
        PasswordRequiredToKickSession = 49,
        AlreadyLoggedInElsewhere    = 50,
        Suspended                   = 51,
        Cancelled                   = 52,
        DataCorruption              = 53,
        DiskFull                    = 54,
        RemoteCallFailed            = 55,
        PasswordNotSet              = 56,
        ExternalAccountUnlinked     = 57,
        PSNTicketInvalid            = 58,
        ExternalAccountAlreadyLinked = 59,
        RemoteFileConflict          = 60,
        IllegalPassword             = 61,
        SameAsPreviousValue         = 62,
        AccountLogonDenied          = 63,
        CannotUseOldPassword        = 64,
        InvalidLoginAuthCode        = 65,
        AccountLogonDeniedNoMailSent = 66,
        HardwareNotCapableOfIPT     = 67,
        IPTInitError                = 68,
        ParentalControlRestricted   = 69,
        FacebookQueryError          = 70,
        ExpiredLoginAuthCode        = 71,
        IPLoginRestrictionFailed    = 72,
        AccountLocked               = 73,
        AccountLogonDeniedVerifiedEmailRequired = 74,
        NoMatchingURL               = 75,
        BadResponse                 = 76,
        RequirePasswordReEntry      = 77,
        ValueOutOfRange             = 78,
        UnexpectedError             = 79,
        Disabled                    = 80,
        InvalidCEGSubmission        = 81,
        RestrictedDevice            = 82,
        RegionLocked                = 83,
        RateLimitExceeded           = 84,
        AccountLoginDeniedNeedTwoFactor = 85,
        ItemOrEntryDeleted          = 86,
        AccountLoginDeniedThrottle  = 87,
        TwoFactorCodeMismatch       = 88,
        TwoFactorActivationCodeMismatch = 89,
        AccountAssociatedToMultiplePartners = 90,
        NotModified                 = 91,
        NoMobileDeviceAvailable     = 92,
        TimeNotSynced               = 93,
        SmsCodeFailed               = 94,
        AccountLimitExceeded        = 95,
        AccountActivityLimitExceeded = 96,
        PhoneActivityLimitExceeded  = 97,
        RefundToWallet              = 98,
        EmailSendFailure            = 99,
        NotSettled                  = 100,
        NeedCaptcha                 = 101,
        GSLTDenied                  = 102,
        GSOwnerDenied               = 103,
        InvalidItemType             = 104,
        IPBanned                    = 105,
        GSLTExpired                 = 106,
        InsufficientFunds           = 107,
        TooManyPending              = 108,
        NoSiteLicensesFound         = 109,
        WGNetworkSendExceeded       = 110,
        AccountNotFriends           = 111,
        LimitedUserAccount          = 112,
        CantRemoveItem              = 113,
        AccountDeleted              = 114,
        ExistingUserCancelledLicense = 115,
        CommunityCooldown           = 116,
        NoLauncherSpecified         = 117,
        MustAgreeToSSA              = 118,
        LauncherMigrated            = 119,
        SteamRealmMismatch          = 120,
        InvalidSignature            = 121,
        ParseFailure                = 122,
        NoVerifiedPhone             = 123,
        InsufficientBattery         = 124,
        ChargerRequired             = 125,
        CachedCredentialInvalid     = 126,
        PhoneNumberIsVOIP           = 127,
    };

    // -----------------------------------------------------------------------
    // SteamAccountType — normalised EAccountType
    // -----------------------------------------------------------------------
    enum class SteamAccountType : AZ::s32
    {
        Invalid        = 0,
        Individual     = 1,
        Multiseat      = 2,
        GameServer     = 3,
        AnonGameServer = 4,
        Pending        = 5,
        ContentServer  = 6,
        Clan           = 7,
        Chat           = 8,
        ConsoleUser    = 9,
        AnonUser       = 10,
    };

    // -----------------------------------------------------------------------
    // SteamUniverse — normalised EUniverse
    // -----------------------------------------------------------------------
    enum class SteamUniverse : AZ::s32
    {
        Invalid  = 0,
        Public   = 1,
        Beta     = 2,
        Internal = 3,
        Dev      = 4,
    };

    // -----------------------------------------------------------------------
    // SteamPersonaState — normalised EPersonaState
    // -----------------------------------------------------------------------
    enum class SteamPersonaState : AZ::s32
    {
        Offline        = 0,
        Online         = 1,
        Busy           = 2,
        Away           = 3,
        Snooze         = 4,
        LookingToTrade = 5,
        LookingToPlay  = 6,
        Invisible      = 7,
    };

    // -----------------------------------------------------------------------
    // SteamLobbyType — normalised ELobbyType
    // -----------------------------------------------------------------------
    enum class SteamLobbyType : AZ::s32
    {
        Private         = 0,
        FriendsOnly     = 1,
        Public          = 2,
        Invisible       = 3,
        PrivateUnique   = 4,
    };

    // -----------------------------------------------------------------------
    // SteamLobbyComparison — normalised ELobbyComparison
    // -----------------------------------------------------------------------
    enum class SteamLobbyComparison : AZ::s32
    {
        EqualToOrLessThan    = -2,
        LessThan             = -1,
        Equal                = 0,
        GreaterThan          = 1,
        EqualToOrGreaterThan = 2,
        NotEqual             = 3,
    };

    // -----------------------------------------------------------------------
    // SteamLobbyDistanceFilter — normalised ELobbyDistanceFilter
    // -----------------------------------------------------------------------
    enum class SteamLobbyDistanceFilter : AZ::s32
    {
        Close     = 0,
        Default   = 1,
        Far       = 2,
        Worldwide = 3,
    };

    // -----------------------------------------------------------------------
    // SteamChatMemberStateChange — normalised EChatMemberStateChange flags
    // -----------------------------------------------------------------------
    enum class SteamChatMemberStateChange : AZ::u32
    {
        Entered      = 0x0001,
        Left         = 0x0002,
        Disconnected = 0x0004,
        Kicked       = 0x0008,
        Banned       = 0x0010,
    };

    // -----------------------------------------------------------------------
    // SteamLeaderboardSortMethod — normalised ELeaderboardSortMethod
    // -----------------------------------------------------------------------
    enum class SteamLeaderboardSortMethod : AZ::s32
    {
        None       = 0,
        Ascending  = 1,
        Descending = 2,
    };

    // -----------------------------------------------------------------------
    // SteamLeaderboardDisplayType — normalised ELeaderboardDisplayType
    // -----------------------------------------------------------------------
    enum class SteamLeaderboardDisplayType : AZ::s32
    {
        None              = 0,
        Numeric           = 1,
        TimeSeconds       = 2,
        TimeMilliSeconds  = 3,
    };

    // -----------------------------------------------------------------------
    // SteamLeaderboardDataRequest — normalised ELeaderboardDataRequest
    // -----------------------------------------------------------------------
    enum class SteamLeaderboardDataRequest : AZ::s32
    {
        Global           = 0,
        GlobalAroundUser = 1,
        Friends          = 2,
        Users            = 3,
    };

    // -----------------------------------------------------------------------
    // SteamLeaderboardUploadScoreMethod — normalised ELeaderboardUploadScoreMethod
    // -----------------------------------------------------------------------
    enum class SteamLeaderboardUploadScoreMethod : AZ::s32
    {
        None        = 0,
        KeepBest    = 1,
        ForceUpdate = 2,
    };

    // -----------------------------------------------------------------------
    // SteamRemoteStoragePublishedFileVisibility — normalised ERemoteStoragePublishedFileVisibility
    // -----------------------------------------------------------------------
    enum class SteamUGCVisibility : AZ::s32
    {
        Public      = 0,
        FriendsOnly = 1,
        Private     = 2,
        Unlisted    = 3,
    };

    // -----------------------------------------------------------------------
    // SteamItemState — normalised ESteamItemFlags (bitmask)
    // -----------------------------------------------------------------------
    enum class SteamItemState : AZ::u32
    {
        None                = 0,
        Subscribed          = 1 << 0,
        LegacyItem          = 1 << 1,
        Installed           = 1 << 2,
        UpdatePending       = 1 << 3,
        Downloading         = 1 << 4,
        DownloadPending     = 1 << 5,
    };

    // -----------------------------------------------------------------------
    // SteamOverlayToStoreFlag — normalised EOverlayToStoreFlag
    // -----------------------------------------------------------------------
    enum class SteamOverlayToStoreFlag : AZ::s32
    {
        None            = 0,
        AddToCart       = 1,
        AddToCartAndShow = 2,
    };

    // -----------------------------------------------------------------------
    // SteamActivateGameOverlayToWebPageMode
    // -----------------------------------------------------------------------
    enum class SteamOverlayToWebPageMode : AZ::s32
    {
        Default = 0,
        Modal   = 1,
    };

    // -----------------------------------------------------------------------
    // SteamNotificationPosition — normalised ENotificationPosition
    // -----------------------------------------------------------------------
    enum class SteamNotificationPosition : AZ::s32
    {
        TopLeft     = 0,
        TopRight    = 1,
        BottomLeft  = 2,
        BottomRight = 3,
    };

    // -----------------------------------------------------------------------
    // SteamServerMode — normalised EServerMode
    // Passed to SteamGameServerInitialise to control authentication / VAC.
    // -----------------------------------------------------------------------
    enum class SteamServerMode : AZ::s32
    {
        NoAuthentication        = 1,  ///< Don't authenticate users. No VAC.
        Authentication          = 2,  ///< Authenticate users. No VAC bans enforced.
        AuthenticationAndSecure = 3,  ///< Authenticate users AND enforce VAC bans. Recommended.
    };

    /// Pass this as queryPort to share the game port for server browser traffic.
    inline constexpr AZ::u32 SteamGameServerQueryPortShared = 0xFFFF;

    // -----------------------------------------------------------------------
    // SteamTimeline types
    // -----------------------------------------------------------------------

    /// Wraps TimelineEventHandle_t (uint64). Returned by timeline event creation
    /// calls and required for all subsequent operations on that event.
    using SteamTimelineEventHandle = AZ::u64;

    /// Maximum event/tag priority value accepted by the Timeline API.
    inline constexpr AZ::u32 SteamTimelineMaxPriority = 1000;

    /// Maximum duration in seconds for a ranged timeline event.
    inline constexpr float SteamTimelineMaxEventDuration = 600.f;

    /// Controls the colour of the timeline bar segment.
    /// Maps directly to ETimelineGameMode.
    enum class SteamTimelineGameMode : AZ::s32
    {
        Invalid       = 0,
        Playing       = 1,  ///< Active gameplay is happening.
        Staging       = 2,  ///< Lobby / character-select / pre-match.
        Menus         = 3,  ///< Main menu, pause menu, shop, etc.
        LoadingScreen = 4,  ///< Level or asset loading.
    };

    /// Controls whether Steam should offer this event as a clip suggestion.
    /// Maps directly to ETimelineEventClipPriority.
    enum class SteamTimelineClipPriority : AZ::s32
    {
        Invalid  = 0,
        None     = 1,  ///< Event is recorded but not offered as a clip.
        Standard = 2,  ///< Steam may offer this as a clip.
        Featured = 3,  ///< Steam will preferentially offer this as a clip.
    };

    // -----------------------------------------------------------------------
    // Script Canvas result structs
    // Returned by value from SC-facing proxy methods so Script Canvas can
    // receive multiple outputs without reference-parameter workarounds.
    // Each struct carries a success flag plus the real payload fields.
    // -----------------------------------------------------------------------

    struct SteamInitResult
    {
        AZ_TYPE_INFO(SteamInitResult, "{R1S2T3U4-V5W6-4X7Y-Z8A9-B0C1D2E3F4G5}");
        AZ_CLASS_ALLOCATOR(SteamInitResult, AZ::SystemAllocator);
        bool          success  = false;
        AZStd::string errorMsg;
    };

    struct SteamStatIntResult
    {
        AZ_TYPE_INFO(SteamStatIntResult, "{S2T3U4V5-W6X7-4Y8Z-A9B0-C1D2E3F4G5H6}");
        AZ_CLASS_ALLOCATOR(SteamStatIntResult, AZ::SystemAllocator);
        bool    success = false;
        AZ::s32 value   = 0;
    };

    struct SteamStatFloatResult
    {
        AZ_TYPE_INFO(SteamStatFloatResult, "{T3U4V5W6-X7Y8-4Z9A-B0C1-D2E3F4G5H6I7}");
        AZ_CLASS_ALLOCATOR(SteamStatFloatResult, AZ::SystemAllocator);
        bool  success = false;
        float value   = 0.0f;
    };

    struct SteamAchievementResult
    {
        AZ_TYPE_INFO(SteamAchievementResult, "{U4V5W6X7-Y8Z9-4A0B-C1D2-E3F4G5H6I7J8}");
        AZ_CLASS_ALLOCATOR(SteamAchievementResult, AZ::SystemAllocator);
        bool success  = false;
        bool achieved = false;
    };

    struct SteamAchievementAndUnlockTimeResult
    {
        AZ_TYPE_INFO(SteamAchievementAndUnlockTimeResult, "{V5W6X7Y8-Z9A0-4B1C-D2E3-F4G5H6I7J8K9}");
        AZ_CLASS_ALLOCATOR(SteamAchievementAndUnlockTimeResult, AZ::SystemAllocator);
        bool      success    = false;
        bool      achieved   = false;
        AZ::u32   unlockTime = 0;
    };

    struct SteamImageSizeResult
    {
        AZ_TYPE_INFO(SteamImageSizeResult, "{W6X7Y8Z9-A0B1-4C2D-E3F4-G5H6I7J8K9L0}");
        AZ_CLASS_ALLOCATOR(SteamImageSizeResult, AZ::SystemAllocator);
        bool    success = false;
        AZ::u32 width   = 0;
        AZ::u32 height  = 0;
    };

    struct SteamFilterTextResult
    {
        AZ_TYPE_INFO(SteamFilterTextResult, "{X7Y8Z9A0-B1C2-4D3E-F4G5-H6I7J8K9L0M1}");
        AZ_CLASS_ALLOCATOR(SteamFilterTextResult, AZ::SystemAllocator);
        bool          success = false;
        AZStd::string filtered;
    };

    struct SteamFileNameAndSizeResult
    {
        AZ_TYPE_INFO(SteamFileNameAndSizeResult, "{Y8Z9A0B1-C2D3-4E4F-G5H6-I7J8K9L0M1N2}");
        AZ_CLASS_ALLOCATOR(SteamFileNameAndSizeResult, AZ::SystemAllocator);
        AZStd::string fileName;
        AZ::s32       size = 0;
    };

    struct SteamQuotaResult
    {
        AZ_TYPE_INFO(SteamQuotaResult, "{Z9A0B1C2-D3E4-4F5G-H6I7-J8K9L0M1N2O3}");
        AZ_CLASS_ALLOCATOR(SteamQuotaResult, AZ::SystemAllocator);
        bool    success        = false;
        AZ::u64 totalBytes     = 0;
        AZ::u64 availableBytes = 0;
    };

    struct SteamItemDownloadInfoResult
    {
        AZ_TYPE_INFO(SteamItemDownloadInfoResult, "{A0B1C2D3-E4F5-4G6H-I7J8-K9L0M1N2O3P4}");
        AZ_CLASS_ALLOCATOR(SteamItemDownloadInfoResult, AZ::SystemAllocator);
        bool    success          = false;
        AZ::u64 bytesDownloaded  = 0;
        AZ::u64 bytesTotal       = 0;
    };

    struct SteamItemInstallInfoResult
    {
        AZ_TYPE_INFO(SteamItemInstallInfoResult, "{B1C2D3E4-F5G6-4H7I-J8K9-L0M1N2O3P4Q5}");
        AZ_CLASS_ALLOCATOR(SteamItemInstallInfoResult, AZ::SystemAllocator);
        bool          success    = false;
        AZ::u64       sizeOnDisk = 0;
        AZStd::string folder;
        AZ::u32       timestamp  = 0;
    };

    struct SteamSessionClientResolutionResult
    {
        AZ_TYPE_INFO(SteamSessionClientResolutionResult, "{C2D3E4F5-G6H7-4I8J-K9L0-M1N2O3P4Q5R6}");
        AZ_CLASS_ALLOCATOR(SteamSessionClientResolutionResult, AZ::SystemAllocator);
        bool    success = false;
        AZ::s32 width   = 0;
        AZ::s32 height  = 0;
    };

    // -----------------------------------------------------------------------
    // Input data types (for ISteamInput)
    // -----------------------------------------------------------------------

    struct SteamInputDigitalActionData
    {
        AZ_TYPE_INFO(SteamInputDigitalActionData, "{D3E4F5G6-H7I8-4J9K-L0M1-N2O3P4Q5R6S7}");
        AZ_CLASS_ALLOCATOR(SteamInputDigitalActionData, AZ::SystemAllocator);
        bool active = false;  ///< True if the device bound to this action is currently connected.
        bool state  = false;  ///< True if the digital action is currently pressed.
    };

    struct SteamInputAnalogActionData
    {
        AZ_TYPE_INFO(SteamInputAnalogActionData, "{E4F5G6H7-I8J9-4K0L-M1N2-O3P4Q5R6S7T8}");
        AZ_CLASS_ALLOCATOR(SteamInputAnalogActionData, AZ::SystemAllocator);
        AZ::s32 mode   = 0;     ///< EInputSourceMode cast to s32.
        float   x      = 0.0f;
        float   y      = 0.0f;
        bool    active = false; ///< True if the device bound to this action is connected.
    };

    // -----------------------------------------------------------------------
    // GS stats result types (for ISteamGameServerStats)
    // -----------------------------------------------------------------------

    struct SteamGSUserStatIntResult
    {
        AZ_TYPE_INFO(SteamGSUserStatIntResult, "{F5G6H7I8-J9K0-4L1M-N2O3-P4Q5R6S7T8U9}");
        AZ_CLASS_ALLOCATOR(SteamGSUserStatIntResult, AZ::SystemAllocator);
        bool    success = false;
        AZ::s32 value   = 0;
    };

    struct SteamGSUserStatFloatResult
    {
        AZ_TYPE_INFO(SteamGSUserStatFloatResult, "{G6H7I8J9-K0L1-4M2N-O3P4-Q5R6S7T8U9V0}");
        AZ_CLASS_ALLOCATOR(SteamGSUserStatFloatResult, AZ::SystemAllocator);
        bool  success = false;
        float value   = 0.0f;
    };

    struct SteamGSUserAchievementResult
    {
        AZ_TYPE_INFO(SteamGSUserAchievementResult, "{H7I8J9K0-L1M2-4N3O-P4Q5-R6S7T8U9V0W1}");
        AZ_CLASS_ALLOCATOR(SteamGSUserAchievementResult, AZ::SystemAllocator);
        bool success  = false;
        bool achieved = false;
    };

} // namespace Heathen