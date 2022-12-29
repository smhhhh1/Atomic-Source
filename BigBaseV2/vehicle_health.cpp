#include "common.hpp"
#include "gta_util.hpp"
#include "vehicle_health.h"
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
using namespace big::vehicle::health::vars;


namespace big::vehicle::health::vars
{
	variables m_vars;
}

namespace big::menu
{


	void vehicle_health_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Vehicle Health", SubHealth, [](sub* core)
			{
				core->add_option<simple_option>(("Repair Vehicle"), nullptr, []
					{
						Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
						VEHICLE::SET_VEHICLE_FIXED(veh);
						VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(veh);
						VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, 0);
					});
				core->add_option<simple_option>(("Wash Vehicle"), nullptr, []
					{
						Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
						VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, 0);
					});
				core->add_option<simple_option>(("Dirty Vehicle"), nullptr, []
					{
						Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
						VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, 100);
					});
				core->add_option<toggle_option<bool>>(("Auto Repair"),
					nullptr,
					&m_vars.m_auto_repair
				);
				core->add_option<toggle_option<bool>>(("Auto Wash"),
					nullptr,
					&m_vars.m_auto_wash
				);
			});
	}

	void vehicle_health_menu::script_init() {}

	void vehicle_health_menu::script_on_tick()
	{
		Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
		if (m_vars.m_auto_repair) {
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
			{
				VEHICLE::SET_VEHICLE_FIXED(vehicle);
				VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(vehicle);
				VEHICLE::SET_VEHICLE_DIRT_LEVEL(vehicle, 0);

			}
		}
		if (m_vars.m_auto_wash) {
			VEHICLE::SET_VEHICLE_DIRT_LEVEL(vehicle, 0);
		}
	}

	void vehicle_health_menu::script_func()
	{
		m_vehicle_health_menu.script_init();
		while (true)
		{
			m_vehicle_health_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}