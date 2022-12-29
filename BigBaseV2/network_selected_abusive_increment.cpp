#include "common.hpp"
#include "gta_util.hpp"
#include "network_selected_abusive_increment.h"
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
#include "player_submenu.h"
#include "../submenus.h"
#include "on_screen_ped.h"
#include "lists.h"
#include "fiber_pool.hpp"
#include "gta/enums.hpp"
#include "script_global.hpp"
#include "scroll.h"
#include "util.h"
using namespace big::network::selected_player::abusive::increment::vars;


namespace big::network::selected_player::abusive::increment::vars
{
	variables m_vars;
	const char* stats[] = {
		"Griefing", "Game Exploits", "Exploits", "Punished", "Cheat", "Bad Sport", "Bad Crew Name", "Bad Crew Motto", "Bad Crew Status", "Bad Crew Emblem"
	}; std::size_t stats_id;
}

namespace big::menu
{


	void network_selected_abusive_increment_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<PlayerSubmenu>(&selected_player, SubSelectedAbusiveIncrements, [](PlayerSubmenu* core)
			{
				m_renderer.m_enable_player_info = true;

				static int timer = 0;
				static int strength = 100;
				static bool g_spam;
				core->add_option<scroll_option<const char*, std::size_t>>(("Type"), nullptr, &stats, &stats_id, true);
				core->add_option<number_option<int>>(("Strength"), nullptr, &strength, 1, 100, 10, 1, false);
				core->add_option<number_option<int>>(("Delay"), nullptr, &m_vars.increment_delay, 0, 300, 10, 1, false);
				core->add_option<simple_option>(("Increment"), nullptr, [] {
					g_pointers->m_remote_increment(*(Hash*)stats[stats_id], strength, g_pointers->m_net_game_player(selected_player));
					});
				core->add_option<toggle_option<bool>>(("Loop"), nullptr, &g_spam);
				if (g_spam) {
					if (GetTickCount() - timer >= m_vars.increment_delay)
					{
						g_pointers->m_remote_increment(*(Hash*)stats[stats_id], strength, g_pointers->m_net_game_player(selected_player));
						timer = GetTickCount();
					}
				}

			});



	}

	void network_selected_abusive_increment_menu::script_init() {}

	void network_selected_abusive_increment_menu::script_on_tick()
	{
		
	}

	void network_selected_abusive_increment_menu::script_func()
	{
		m_network_selected_abusive_increment_menu.script_init();
		while (true)
		{
			m_network_selected_abusive_increment_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}