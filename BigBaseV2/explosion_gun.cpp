#include "common.hpp"
#include "gta_util.hpp"
#include "explosion_gun.h"
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
#include "scroll.h"
#include "util.h"
using namespace big::weapon::explosion_gun::vars;

namespace big::weapon::explosion_gun::vars {
	variables m_vars;

	const char* explosion_gun_type[] = {
		"Grenade", "Grenade Launcher", "Sticky Bomb", "Molotov", "Tank Shell", "Octane", "Car", "Plane", "Petrol Pump", "Bike",
		"Steam", "Flame", "Water", "Gas", "Boat", "Ship", "Truck", "Bullet", "Smoke Launcher", "Smoke Grenade", "BZ Gas", "Flae",
		"Gas Can", "Extinguisher", "Programmable Ar", "Train", "Barrel", "Propane", "Blimp", "Flame Explosion", "Tanker", "Rocket",
		"Vehicle Bullet", "Gas Tank", "Bird Crap", "Snow Ball"
	};
	 int explosion_gun_ids[39] = {
		1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39
	}; int explosion_gun_id = 0;

}

namespace big::menu
{


	void explosion_gun_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Explosion Gun", SubExplosionGun, [](sub* core)
			{
				core->add_option<toggle_option<bool>>(("Toggle"),
					nullptr,
					&m_vars.m_toggle
				);
				core->add_option<scroll_option<const char*, int>>(("Type"),
					nullptr,
					&explosion_gun_type,
					&explosion_gun_id,
					true
				);
				core->add_option<number_option<float>>(("Camera Shake"),
					nullptr,
					&m_vars.m_camera_shake, 1,
					100, 1,
					1, false
				);
				core->add_option<number_option<int>>(("Radius"),
					nullptr,
					&m_vars.m_radius, 100,
					500, 10,
					1, false
				);
				core->add_option<toggle_option<bool>>(("Invisible"),
					nullptr,
					&m_vars.m_invisible
				);
				core->add_option<toggle_option<bool>>(("Audible"),
					nullptr, 
					&m_vars.m_audible
				);
				
			});
	}

	void explosion_gun_menu::script_init() {}

	void explosion_gun_menu::script_on_tick()
	{
		
		if (m_vars.m_toggle) {
			if (__shooting(PLAYER::PLAYER_PED_ID()))
			{
				Vector3 c;
				if (auto last = WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &c))
				{
					if (raycast(&last)) {
						FIRE::ADD_EXPLOSION(c.x, c.y, c.z, explosion_gun_ids[explosion_gun_id], 1000, m_vars.m_audible, m_vars.m_invisible, m_vars.m_camera_shake, false);
					}

				}

			}

		}
	}

	void explosion_gun_menu::script_func()
	{
		m_explosion_gun_menu.script_init();
		while (true)
		{
			m_explosion_gun_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}