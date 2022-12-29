#include "common.hpp"
#include "gta_util.hpp"
#include "vehicle_doors.h"
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
namespace big::menu
{


	void vehicle_doors_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Vehicle Doors", SubVehicleDoors, [](sub* core)
			{
				core->add_option<simple_option>(("Open Doors"), nullptr, []
					{
						VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 0, true, false);
						VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 1, true, false);
						VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 2, true, false);
						VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 3, true, false);
						VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 4, true, false);
						VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 5, true, false);
						VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 6, true, false);
						VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 7, true, false);

					});
				core->add_option<simple_option>(("Close Doors"), nullptr, []
					{
						VEHICLE::SET_VEHICLE_DOORS_SHUT(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), true);

					});
				core->add_option<simple_option>(("Front Left Door"), nullptr, []
					{
						VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 0, true, false);

					});
				core->add_option<simple_option>(("Front Right Door"), nullptr, []
					{
						VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 1, true, false);

					});
				core->add_option<simple_option>(("Back Left Door"), nullptr, []
					{
						VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 2, true, false);

					});
				core->add_option<simple_option>(("Front Right Door"), nullptr, []
					{
						VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 3, true, false);

					});
			});
	}

	void vehicle_doors_menu::script_init() {}

	void vehicle_doors_menu::script_on_tick() {}

	void vehicle_doors_menu::script_func()
	{
		m_vehicle_doors_menu.script_init();
		while (true)
		{
			m_vehicle_doors_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}