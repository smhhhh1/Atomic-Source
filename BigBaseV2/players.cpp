#include "players.h"
#include "pointers.hpp"
#include "natives.hpp"
#include "notify.h"

namespace big::menu::players
{

	void update()
	{
		for (int i = 0; i < 32; i++)
		{
			m_player_mgr[i].id = i;
			m_player_mgr[i].name = PLAYER::GET_PLAYER_NAME(i);
			m_player_mgr[i].player = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);

			if (i == PLAYER::PLAYER_ID()) {
				m_player_mgr[i].ped = PLAYER::PLAYER_PED_ID();
			}

			m_player_mgr[i].exists = ENTITY::DOES_ENTITY_EXIST(m_player_mgr[i].player);

			m_player_mgr[i].net_player = g_pointers->m_net_game_player(i);

			m_player_mgr[i].connected = m_player_mgr[i].net_player != nullptr;

			if (*g_pointers->m_is_session_started) {
				
			}



		}
	}

}
