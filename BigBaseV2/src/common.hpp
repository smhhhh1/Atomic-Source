#pragma once

#include <SDKDDKVer.h>
#include <Windows.h>
#include <D3D11.h>
#include <wrl/client.h>

#include <cinttypes>
#include <cstddef>
#include <cstdint>

#include <chrono>
#include <ctime>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <iomanip>

#include <atomic>
#include <mutex>
#include <thread>

#include <memory>
#include <new>

#include <sstream>
#include <string>
#include <string_view>

#include <algorithm>
#include <functional>
#include <utility>

#include <stack>
#include <vector>

#include <typeinfo>
#include <type_traits>

#include <exception>
#include <stdexcept>

#include <any>
#include <optional>
#include <variant>

#include <format>
#include <nlohmann/json.hpp>

#include "logger.hpp"

#include "settings.h"



namespace big
{
	enum eScaleformButtons {
		ARROW_UP,
		ARROW_DOWN,
		ARROW_LEFT,
		ARROW_RIGHT,
		BUTTON_DPAD_UP,
		BUTTON_DPAD_DOWN,
		BUTTON_DPAD_RIGHT,
		BUTTON_DPAD_LEFT,
		BUTTON_DPAD_BLANK,
		BUTTON_DPAD_ALL,
		BUTTON_DPAD_UP_DOWN,
		BUTTON_DPAD_LEFT_RIGHT,
		BUTTON_LSTICK_UP,
		BUTTON_LSTICK_DOWN,
		BUTTON_LSTICK_LEFT,
		BUTTON_LSTICK_RIGHT,
		BUTTON_LSTICK,
		BUTTON_LSTICK_ALL,
		BUTTON_LSTICK_UP_DOWN,
		BUTTON_LSTICK_LEFT_RIGHT,
		BUTTON_LSTICK_ROTATE,
		BUTTON_RSTICK_UP,
		BUTTON_RSTICK_DOWN,
		BUTTON_RSTICK_LEFT,
		BUTTON_RSTICK_RIGHT,
		BUTTON_RSTICK,
		BUTTON_RSTICK_ALL,
		BUTTON_RSTICK_UP_DOWN,
		BUTTON_RSTICK_LEFT_RIGHT,
		BUTTON_RSTICK_ROTATE,
		BUTTON_A,
		BUTTON_B,
		BUTTON_X,
		BUTTON_Y,
		BUTTON_LB,
		BUTTON_LT,
		BUTTON_RB,
		BUTTON_RT,
		BUTTON_START,
		BUTTON_BACK,
		RED_BOX,
		RED_BOX_1,
		RED_BOX_2,
		RED_BOX_3,
		LOADING_HALF_CIRCLE_LEFT,
		ARROW_UP_DOWN,
		ARROW_LEFT_RIGHT,
		ARROW_ALL,
		LOADING_HALF_CIRCLE_LEFT_2,
		SAVE_HALF_CIRCLE_LEFT,
		LOADING_HALF_CIRCLE_RIGHT,
	};

	enum eControls {
		ControlNextCamera = 0,
		ControlLookLeftRight = 1,
		ControlLookUpDown = 2,
		ControlLookUpOnly = 3,
		ControlLookDownOnly = 4,
		ControlLookLeftOnly = 5,
		ControlLookRightOnly = 6,
		ControlCinematicSlowMo = 7,
		ControlFlyUpDown = 8,
		ControlFlyLeftRight = 9,
		ControlScriptedFlyZUp = 10,
		ControlScriptedFlyZDown = 11,
		ControlWeaponWheelUpDown = 12,
		ControlWeaponWheelLeftRight = 13,
		ControlWeaponWheelNext = 14,
		ControlWeaponWheelPrev = 15,
		ControlSelectNextWeapon = 16,
		ControlSelectPrevWeapon = 17,
		ControlSkipCutscene = 18,
		ControlCharacterWheel = 19,
		ControlMultiplayerInfo = 20,
		ControlSprint = 21,
		ControlJump = 22,
		ControlEnter = 23,
		ControlAttack = 24,
		ControlAim = 25,
		ControlLookBehind = 26,
		ControlPhone = 27,
		ControlSpecialAbility = 28,
		ControlSpecialAbilitySecondary = 29,
		ControlMoveLeftRight = 30,
		ControlMoveUpDown = 31,
		ControlMoveUpOnly = 32,
		ControlMoveDownOnly = 33,
		ControlMoveLeftOnly = 34,
		ControlMoveRightOnly = 35,
		ControlDuck = 36,
		ControlSelectWeapon = 37,
		ControlPickup = 38,
		ControlSniperZoom = 39,
		ControlSniperZoomInOnly = 40,
		ControlSniperZoomOutOnly = 41,
		ControlSniperZoomInSecondary = 42,
		ControlSniperZoomOutSecondary = 43,
		ControlCover = 44,
		ControlReload = 45,
		ControlTalk = 46,
		ControlDetonate = 47,
		ControlHUDSpecial = 48,
		ControlArrest = 49,
		ControlAccurateAim = 50,
		ControlContext = 51,
		ControlContextSecondary = 52,
		ControlWeaponSpecial = 53,
		ControlWeaponSpecial2 = 54,
		ControlDive = 55,
		ControlDropWeapon = 56,
		ControlDropAmmo = 57,
		ControlThrowGrenade = 58,
		ControlVehicleMoveLeftRight = 59,
		ControlVehicleMoveUpDown = 60,
		ControlVehicleMoveUpOnly = 61,
		ControlVehicleMoveDownOnly = 62,
		ControlVehicleMoveLeftOnly = 63,
		ControlVehicleMoveRightOnly = 64,
		ControlVehicleSpecial = 65,
		ControlVehicleGunLeftRight = 66,
		ControlVehicleGunUpDown = 67,
		ControlVehicleAim = 68,
		ControlVehicleAttack = 69,
		ControlVehicleAttack2 = 70,
		ControlVehicleAccelerate = 71,
		ControlVehicleBrake = 72,
		ControlVehicleDuck = 73,
		ControlVehicleHeadlight = 74,
		ControlVehicleExit = 75,
		ControlVehicleHandbrake = 76,
		ControlVehicleHotwireLeft = 77,
		ControlVehicleHotwireRight = 78,
		ControlVehicleLookBehind = 79,
		ControlVehicleCinCam = 80,
		ControlVehicleNextRadio = 81,
		ControlVehiclePrevRadio = 82,
		ControlVehicleNextRadioTrack = 83,
		ControlVehiclePrevRadioTrack = 84,
		ControlVehicleRadioWheel = 85,
		ControlVehicleHorn = 86,
		ControlVehicleFlyThrottleUp = 87,
		ControlVehicleFlyThrottleDown = 88,
		ControlVehicleFlyYawLeft = 89,
		ControlVehicleFlyYawRight = 90,
		ControlVehiclePassengerAim = 91,
		ControlVehiclePassengerAttack = 92,
		ControlVehicleSpecialAbilityFranklin = 93,
		ControlVehicleStuntUpDown = 94,
		ControlVehicleCinematicUpDown = 95,
		ControlVehicleCinematicUpOnly = 96,
		ControlVehicleCinematicDownOnly = 97,
		ControlVehicleCinematicLeftRight = 98,
		ControlVehicleSelectNextWeapon = 99,
		ControlVehicleSelectPrevWeapon = 100,
		ControlVehicleRoof = 101,
		ControlVehicleJump = 102,
		ControlVehicleGrapplingHook = 103,
		ControlVehicleShuffle = 104,
		ControlVehicleDropProjectile = 105,
		ControlVehicleMouseControlOverride = 106,
		ControlVehicleFlyRollLeftRight = 107,
		ControlVehicleFlyRollLeftOnly = 108,
		ControlVehicleFlyRollRightOnly = 109,
		ControlVehicleFlyPitchUpDown = 110,
		ControlVehicleFlyPitchUpOnly = 111,
		ControlVehicleFlyPitchDownOnly = 112,
		ControlVehicleFlyUnderCarriage = 113,
		ControlVehicleFlyAttack = 114,
		ControlVehicleFlySelectNextWeapon = 115,
		ControlVehicleFlySelectPrevWeapon = 116,
		ControlVehicleFlySelectTargetLeft = 117,
		ControlVehicleFlySelectTargetRight = 118,
		ControlVehicleFlyVerticalFlightMode = 119,
		ControlVehicleFlyDuck = 120,
		ControlVehicleFlyAttackCamera = 121,
		ControlVehicleFlyMouseControlOverride = 122,
		ControlVehicleSubTurnLeftRight = 123,
		ControlVehicleSubTurnLeftOnly = 124,
		ControlVehicleSubTurnRightOnly = 125,
		ControlVehicleSubPitchUpDown = 126,
		ControlVehicleSubPitchUpOnly = 127,
		ControlVehicleSubPitchDownOnly = 128,
		ControlVehicleSubThrottleUp = 129,
		ControlVehicleSubThrottleDown = 130,
		ControlVehicleSubAscend = 131,
		ControlVehicleSubDescend = 132,
		ControlVehicleSubTurnHardLeft = 133,
		ControlVehicleSubTurnHardRight = 134,
		ControlVehicleSubMouseControlOverride = 135,
		ControlVehiclePushbikePedal = 136,
		ControlVehiclePushbikeSprint = 137,
		ControlVehiclePushbikeFrontBrake = 138,
		ControlVehiclePushbikeRearBrake = 139,
		ControlMeleeAttackLight = 140,
		ControlMeleeAttackHeavy = 141,
		ControlMeleeAttackAlternate = 142,
		ControlMeleeBlock = 143,
		ControlParachuteDeploy = 144,
		ControlParachuteDetach = 145,
		ControlParachuteTurnLeftRight = 146,
		ControlParachuteTurnLeftOnly = 147,
		ControlParachuteTurnRightOnly = 148,
		ControlParachutePitchUpDown = 149,
		ControlParachutePitchUpOnly = 150,
		ControlParachutePitchDownOnly = 151,
		ControlParachuteBrakeLeft = 152,
		ControlParachuteBrakeRight = 153,
		ControlParachuteSmoke = 154,
		ControlParachutePrecisionLanding = 155,
		ControlMap = 156,
		ControlSelectWeaponUnarmed = 157,
		ControlSelectWeaponMelee = 158,
		ControlSelectWeaponHandgun = 159,
		ControlSelectWeaponShotgun = 160,
		ControlSelectWeaponSmg = 161,
		ControlSelectWeaponAutoRifle = 162,
		ControlSelectWeaponSniper = 163,
		ControlSelectWeaponHeavy = 164,
		ControlSelectWeaponSpecial = 165,
		ControlSelectCharacterMichael = 166,
		ControlSelectCharacterFranklin = 167,
		ControlSelectCharacterTrevor = 168,
		ControlSelectCharacterMultiplayer = 169,
		ControlSaveReplayClip = 170,
		ControlSpecialAbilityPC = 171,
		ControlPhoneUp = 172,
		ControlPhoneDown = 173,
		ControlPhoneLeft = 174,
		ControlPhoneRight = 175,
		ControlPhoneSelect = 176,
		ControlPhoneCancel = 177,
		ControlPhoneOption = 178,
		ControlPhoneExtraOption = 179,
		ControlPhoneScrollForward = 180,
		ControlPhoneScrollBackward = 181,
		ControlPhoneCameraFocusLock = 182,
		ControlPhoneCameraGrid = 183,
		ControlPhoneCameraSelfie = 184,
		ControlPhoneCameraDOF = 185,
		ControlPhoneCameraExpression = 186,
		ControlFrontendDown = 187,
		ControlFrontendUp = 188,
		ControlFrontendLeft = 189,
		ControlFrontendRight = 190,
		ControlFrontendRdown = 191,
		ControlFrontendRup = 192,
		ControlFrontendRleft = 193,
		ControlFrontendRright = 194,
		ControlFrontendAxisX = 195,
		ControlFrontendAxisY = 196,
		ControlFrontendRightAxisX = 197,
		ControlFrontendRightAxisY = 198,
		ControlFrontendPause = 199,
		ControlFrontendPauseAlternate = 200,
		ControlFrontendAccept = 201,
		ControlFrontendCancel = 202,
		ControlFrontendX = 203,
		ControlFrontendY = 204,
		ControlFrontendLb = 205,
		ControlFrontendRb = 206,
		ControlFrontendLt = 207,
		ControlFrontendRt = 208,
		ControlFrontendLs = 209,
		ControlFrontendRs = 210,
		ControlFrontendLeaderboard = 211,
		ControlFrontendSocialClub = 212,
		ControlFrontendSocialClubSecondary = 213,
		ControlFrontendDelete = 214,
		ControlFrontendEndscreenAccept = 215,
		ControlFrontendEndscreenExpand = 216,
		ControlFrontendSelect = 217,
		ControlScriptLeftAxisX = 218,
		ControlScriptLeftAxisY = 219,
		ControlScriptRightAxisX = 220,
		ControlScriptRightAxisY = 221,
		ControlScriptRUp = 222,
		ControlScriptRDown = 223,
		ControlScriptRLeft = 224,
		ControlScriptRRight = 225,
		ControlScriptLB = 226,
		ControlScriptRB = 227,
		ControlScriptLT = 228,
		ControlScriptRT = 229,
		ControlScriptLS = 230,
		ControlScriptRS = 231,
		ControlScriptPadUp = 232,
		ControlScriptPadDown = 233,
		ControlScriptPadLeft = 234,
		ControlScriptPadRight = 235,
		ControlScriptSelect = 236,
		ControlCursorAccept = 237,
		ControlCursorCancel = 238,
		ControlCursorX = 239,
		ControlCursorY = 240,
		ControlCursorScrollUp = 241,
		ControlCursorScrollDown = 242,
		ControlEnterCheatCode = 243,
		ControlInteractionMenu = 244,
		ControlMpTextChatAll = 245,
		ControlMpTextChatTeam = 246,
		ControlMpTextChatFriends = 247,
		ControlMpTextChatCrew = 248,
		ControlPushToTalk = 249,
		ControlCreatorLS = 250,
		ControlCreatorRS = 251,
		ControlCreatorLT = 252,
		ControlCreatorRT = 253,
		ControlCreatorMenuToggle = 254,
		ControlCreatorAccept = 255,
		ControlCreatorDelete = 256,
		ControlAttack2 = 257,
		ControlRappelJump = 258,
		ControlRappelLongJump = 259,
		ControlRappelSmashWindow = 260,
		ControlPrevWeapon = 261,
		ControlNextWeapon = 262,
		ControlMeleeAttack1 = 263,
		ControlMeleeAttack2 = 264,
		ControlWhistle = 265,
		ControlMoveLeft = 266,
		ControlMoveRight = 267,
		ControlMoveUp = 268,
		ControlMoveDown = 269,
		ControlLookLeft = 270,
		ControlLookRight = 271,
		ControlLookUp = 272,
		ControlLookDown = 273,
		ControlSniperZoomIn = 274,
		ControlSniperZoomOut = 275,
		ControlSniperZoomInAlternate = 276,
		ControlSniperZoomOutAlternate = 277,
		ControlVehicleMoveLeft = 278,
		ControlVehicleMoveRight = 279,
		ControlVehicleMoveUp = 280,
		ControlVehicleMoveDown = 281,
		ControlVehicleGunLeft = 282,
		ControlVehicleGunRight = 283,
		ControlVehicleGunUp = 284,
		ControlVehicleGunDown = 285,
		ControlVehicleLookLeft = 286,
		ControlVehicleLookRight = 287,
		ControlReplayStartStopRecording = 288,
		ControlReplayStartStopRecordingSecondary = 289,
		ControlScaledLookLeftRight = 290,
		ControlScaledLookUpDown = 291,
		ControlScaledLookUpOnly = 292,
		ControlScaledLookDownOnly = 293,
		ControlScaledLookLeftOnly = 294,
		ControlScaledLookRightOnly = 295,
		ControlReplayMarkerDelete = 296,
		ControlReplayClipDelete = 297,
		ControlReplayPause = 298,
		ControlReplayRewind = 299,
		ControlReplayFfwd = 300,
		ControlReplayNewmarker = 301,
		ControlReplayRecord = 302,
		ControlReplayScreenshot = 303,
		ControlReplayHidehud = 304,
		ControlReplayStartpoint = 305,
		ControlReplayEndpoint = 306,
		ControlReplayAdvance = 307,
		ControlReplayBack = 308,
		ControlReplayTools = 309,
		ControlReplayRestart = 310,
		ControlReplayShowhotkey = 311,
		ControlReplayCycleMarkerLeft = 312,
		ControlReplayCycleMarkerRight = 313,
		ControlReplayFOVIncrease = 314,
		ControlReplayFOVDecrease = 315,
		ControlReplayCameraUp = 316,
		ControlReplayCameraDown = 317,
		ControlReplaySave = 318,
		ControlReplayToggletime = 319,
		ControlReplayToggletips = 320,
		ControlReplayPreview = 321,
		ControlReplayToggleTimeline = 322,
		ControlReplayTimelinePickupClip = 323,
		ControlReplayTimelineDuplicateClip = 324,
		ControlReplayTimelinePlaceClip = 325,
		ControlReplayCtrl = 326,
		ControlReplayTimelineSave = 327,
		ControlReplayPreviewAudio = 328,
		ControlVehicleDriveLook = 329,
		ControlVehicleDriveLook2 = 330,
		ControlVehicleFlyAttack2 = 331,
		ControlRadioWheelUpDown = 332,
		ControlRadioWheelLeftRight = 333,
		ControlVehicleSlowMoUpDown = 334,
		ControlVehicleSlowMoUpOnly = 335,
		ControlVehicleSlowMoDownOnly = 336,
		ControlMapPointOfInterest = 337,
	};
	using namespace std::chrono_literals;
	
	template <typename T>
	using comptr = Microsoft::WRL::ComPtr<T>;

	inline HMODULE g_hmodule{};
	inline HANDLE g_main_thread{};
	inline DWORD g_main_thread_id{};
	inline std::atomic_bool g_running{ true };
	inline std::uint32_t selected_player;
	inline std::uint32_t selected_friend;

	inline CNetGamePlayer* sync_sender;

	inline bool m_sky_open = false;

	inline uintptr_t g_base_address = (uintptr_t)GetModuleHandle(NULL);

	constexpr uint64_t operator ""_fnv1a(char const* str, std::size_t len)
	{
		auto const fnv_offset_basis = 14695981039346656037ULL;
		auto const fnv_prime = 1099511628211ULL;

		auto value = fnv_offset_basis;
		for (auto i = 0; i < len; i++)
		{
			value ^= static_cast<size_t>(str[i]);
			value *= fnv_prime;
		}
		value ^= value >> 32;

		return value;
	}

	template<typename T>
	inline bool is_valid_ptr(T ptr) {
		uint64_t address = (uint64_t)ptr;
		if (address < 0x5000) return false;
		if ((address & 0xFFFFFFFF) == 0xFFFFFFFF) return false;
		if ((address & 0xFFFFFFFF) <= 0xFF) return false;

		if (*(uint8_t*)((uint64_t)&address + 6) != 0 || *(uint8_t*)((uint64_t)&address + 7) != 0) return false;

		return true;
	}
#define is_valid_vtable(address) \
	[=]() -> bool { \
		if (!is_valid_ptr<uint64_t>(address)) return false; \
		return address > g_pointers->g_game_address.first && address < (g_pointers->g_game_address.first + g_pointers->g_game_address.second); \
	}()
}


namespace big::engine::memory
{
	inline void nop(uint64_t address, uint32_t size) {
		uint32_t old;
		VirtualProtect((void*)address, size, PAGE_EXECUTE_READWRITE, (DWORD*)&old);
		memset((void*)address, 0x90, size);
		VirtualProtect((void*)address, size, old, (DWORD*)&old);
	}

	inline uintptr_t scan_address(uintptr_t ptr, std::vector<unsigned int> offsets)
	{
		uintptr_t addr = ptr;
		for (unsigned int i = 0; i < offsets.size(); ++i)
		{
			addr = *(uintptr_t*)addr;
			addr += offsets[i];
		}
		return addr;
	}
}