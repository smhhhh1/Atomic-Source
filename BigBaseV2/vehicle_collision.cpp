#include "common.hpp"
#include "gta_util.hpp"
#include "vehicle_collision.h"
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
#include "gta/enums.hpp"
using namespace big::vehicle::collision::vars;


namespace big::vehicle::collision::vars
{
	variables m_vars;
}

namespace big::menu
{


	void vehicle_collision_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Vehicle Collision", SubVehicleCollision, [](sub* core)
			{
				
				core->add_option<toggle_option<bool>>(("Disable Full Collision"),
					nullptr,
					&m_vars.m_disable_veh_collision
				);
				core->add_option<toggle_option<bool>>(("Disable Vehicle Collision"),
					nullptr, 
					&m_vars.m_disable_full_collision
				);

			});
	}

	void vehicle_collision_menu::script_init() {}

	void vehicle_collision_menu::script_on_tick()
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()), false);

		if (m_vars.m_disable_full_collision) {
			ENTITY::SET_ENTITY_COMPLETELY_DISABLE_COLLISION(veh, 1, 1);
		}
		if (m_vars.m_disable_veh_collision) {
			ENTITY::SET_ENTITY_COLLISION(veh, m_vars.m_disable_full_collision, false);
		}
	}

	void vehicle_collision_menu::script_func()
	{
		m_vehicle_collision_menu.script_init();
		while (true)
		{
			m_vehicle_collision_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}