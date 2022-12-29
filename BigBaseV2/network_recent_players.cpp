#include "common.hpp"
#include "gta_util.hpp"
#include "network_recent_players.h"
#include "natives.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "../render.h"
#include "../abstract_submenu.h"
#include "../break_option.h"
#include "../toggle_option.h"
#include "../number.h"
#include "../option.h"
#include "../submenu_option.h"
#include "../simple_option.h"
#include "../simple_submenu.h"
#include "../bool_and_number.h"
#include "../submenu_option.h"
#include "../submenus.h"
#include "on_screen_ped.h"
#include "lists.h"
#include "fiber_pool.hpp"
#include "script_global.hpp"



namespace {
	std::vector<std::string> m_joined;
}

namespace big::menu
{


	void network_recent_players_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Recent Players", SubNetworkRecentPlayers, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				
				for (auto recent_player : m_joined)
				{
					core->add_option<simple_option>(recent_player.c_str(), nullptr, [=] {});
				}

			});
	}

	void network_recent_players_menu::script_init() {}

	void network_recent_players_menu::script_on_tick()
	{
		for (std::int32_t i = 0; i < 32; ++i)
		{		
			CNetGamePlayer* net_player = g_pointers->m_net_game_player(i);

			std::string name = PLAYER::GET_PLAYER_NAME(i);

			if (name == "**Invalid**" || name == PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())) {}
			else
			{
				if (std::find(m_joined.begin(), m_joined.end(), name) != m_joined.end()) {}
				else
				{
					m_joined.push_back(name);
				}
			}
		}
	}

	void network_recent_players_menu::script_func()
	{
		m_network_recent_players_menu.script_init();
		while (true)
		{

			m_network_recent_players_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}