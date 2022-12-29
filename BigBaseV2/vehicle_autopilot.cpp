#include "common.hpp"
#include "gta_util.hpp"
#include "vehicle_autopilot.h"
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
#include "util.h"
namespace big::menu
{


	void vehicle_autopilot_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Vehicle Autopilot", SubVehicleAutoPilot, [](sub* core)
			{
				static bool autopilotstart = false;
				core->add_option<simple_option>(("Start Auto Pilot"), nullptr, []
					{
						Vector3 coords = get_blip_marker();
						Player playerPed = PLAYER::PLAYER_PED_ID();
						if (coords.x != 0 && coords.y != 0)
						{
							if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, false))
							{
								Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
								if (!PED::IS_PED_IN_ANY_BOAT(playerPed) && !PED::IS_PED_IN_ANY_HELI(playerPed) && !PED::IS_PED_IN_ANY_PLANE(playerPed) && !PED::IS_PED_IN_ANY_TAXI(playerPed) && !PED::IS_PED_IN_ANY_SUB(playerPed) && !PED::IS_PED_IN_ANY_TRAIN(playerPed) && !PED::IS_PED_ON_ANY_BIKE(playerPed))
								{
									TASK::TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(playerPed, veh, coords.x, coords.y, 0, 150.0f, 1074528293, 1.0f);
									autopilotstart = true;
								}
							}
						}
					});
				core->add_option<simple_option>(("Stop Auto Pilot"), nullptr, []
					{
						if (autopilotstart)
						{
							Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
							TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
							PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
							autopilotstart = false;
						}
					});
			});
	}

	void vehicle_autopilot_menu::script_init() {}

	void vehicle_autopilot_menu::script_on_tick() {}

	void vehicle_autopilot_menu::script_func()
	{
		m_vehicle_autopilot_menu.script_init();
		while (true)
		{
			m_vehicle_autopilot_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}