#pragma once
#include "gta/joaat.hpp"

namespace big
{
	enum class eReason
	{		
		SPOOFED_ROCKSTAR_ID,
		SPOOFED_NAME,
		SPOOFED_IP,
		ARXAN,
		CRASH,
		KICK,
		MODEL_CHANGE,
		SPECTATING,
		SUPER_JUMP,
		FIRE_AMMO,
		EXPLOSIVE_AMMO

	};

	inline std::unordered_map<eReason, const char*> reason_desc =
	{
		{eReason::SPOOFED_ROCKSTAR_ID, "Spoofed Rid"},
		{eReason::SPOOFED_NAME, "Spoofed Name"},
		{eReason::SPOOFED_IP, "Spoofed Ip"},
		{eReason::ARXAN, "Arxan"},
		{eReason::CRASH, "Crash"},
		{eReason::KICK, "Kick"},
		{eReason::MODEL_CHANGE, "Model Change"},
		{eReason::SPECTATING, "Spectate"},
		{eReason::SUPER_JUMP, "Super Jump"},
		{eReason::FIRE_AMMO, "Fire Ammo"},
		{eReason::EXPLOSIVE_AMMO, "Explosive Ammo"}
		
	};
}