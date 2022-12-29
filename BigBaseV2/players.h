#pragma once
#include "common.hpp"
#include "generic_types.h"
#include "gta/player.hpp"
#include <functional>
#include "player_service.hpp"
#include "blacklist_helper.h"
#include "blacklist_manager.h"
#include "reason.h"
class player_manager
{
public:
	std::string name;

	Player id;
	Player player;
	Ped ped;
	Entity entity;
	Vehicle vehicle;

	CNetGamePlayer* net_player;
	rage::netPlayerData* net_data;

	Vector3 position;

	float health;
	float armor;
	float max_health;
	float max_armor;
	float distance;

	bool exists = false;
	bool connected = false;
	bool alive = false;
	bool is_modder = false;

	uint32_t model = 0;

}; 

namespace big::menu::players
{

	inline void mark_modder(player_ptr player, eReason infraction)
	{
		auto plyr = g_player_database_service->get_or_create_player(player);
		plyr->is_modder = true;
		player->is_modder = true;
		plyr->infractions.insert((int)infraction);
		g_player_database_service->save();
	}

	void update();


	inline player_manager m_player_mgr[32]; 
}