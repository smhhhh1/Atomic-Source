#include "common.hpp"
#include "gta_util.hpp"
#include "network_selected_abusive_explosion.h"
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
using namespace big::network::selected_player::abusive::explosion::vars;


namespace big::network::selected_player::abusive::explosion::vars
{
	variables m_vars;
	const char* explosion_type[] = {
   "Grenade", "Grenade Launcher", "Sticky Bomb", "Molotov", "Tank Shell", "Octane", "Car", "Plane", "Petrol Pump", "Bike",
   "Steam", "Flame", "Water", "Gas", "Boat", "Ship", "Truck", "Bullet", "Smoke Launcher", "Smoke Grenade", "BZ Gas", "Flae",
   "Gas Can", "Extinguisher", "Programmable Ar", "Train", "Barrel", "Propane", "Blimp", "Flame Explosion", "Tanker", "Rocket",
   "Vehicle Bullet", "Gas Tank", "Bird Crap", "Snow Ball"
	};
	int explosion_ids[39] = {
		1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39
	}; int explosion_id = 0;
}

namespace big::menu
{


	void network_selected_abusive_explosion_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<PlayerSubmenu>(&selected_player, SubSelectedAbusiveExplosions, [](PlayerSubmenu* core)
			{
				m_renderer.m_enable_player_info = true;

				core->add_option<scroll_option<const char*, int>>(("Type"), nullptr, &explosion_type, &explosion_id, true);
				core->add_option<number_option<float>>(("Camera Shake"), nullptr, &m_vars.g_camera_shake, 1, 100, 1, 1, false);
				core->add_option<number_option<int>>(("Radius"), nullptr, &m_vars.g_radius, 100, 500, 10, 1, false);
				core->add_option<toggle_option<bool>>(("Invisible"), nullptr, &m_vars.g_visible);
				core->add_option<toggle_option<bool>>(("Audible"), nullptr, &m_vars.g_audible);
				core->add_option<toggle_option<bool>>(("Loop"), nullptr, &m_vars.g_explosion_loop);
				core->add_option<simple_option>(("Explode"), nullptr, []
					{
						Vector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), 0);
						FIRE::ADD_EXPLOSION(c.x, c.y, c.z, explosion_ids[explosion_id], 1000, m_vars.g_audible, m_vars.g_visible, m_vars.g_camera_shake, false);
					});
		
			});

	

	}

	void network_selected_abusive_explosion_menu::script_init() {}

	void network_selected_abusive_explosion_menu::script_on_tick()
	{
		if (m_vars.g_explosion_loop) {
			Vector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), 0);
			FIRE::ADD_EXPLOSION(c.x, c.y, c.z, explosion_ids[explosion_id], 1000, m_vars.g_audible, m_vars.g_visible, m_vars.g_camera_shake, false);
		}
	}

	void network_selected_abusive_explosion_menu::script_func()
	{
		m_network_selected_abusive_explosion_menu.script_init();
		while (true)
		{
			m_network_selected_abusive_explosion_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}