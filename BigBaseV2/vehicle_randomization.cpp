#include "common.hpp"
#include "gta_util.hpp"
#include "vehicle_randomization.h"
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
#include "scroll.h"
using namespace big::vehicle::randomization::vars;


namespace big::vehicle::randomization::vars
{
	variables m_vars;
	int r = 255, g = 0, b = 0;
	void RGBFadee()
	{
		if (r > 0 && b == 0) {
			r--;
			g++;
		}
		if (g > 0 && r == 0) {
			g--;
			b++;
		}
		if (b > 0 && g == 0) {
			r++;
			b--;
		}
	}

}

namespace big::menu
{


	void vehicle_randomization_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Vehicle Randomization", SubVehicleRandomization, [](sub* core)
			{
				core->add_option<toggle_option<bool>>(("Rainbow Primary Paint"),
					nullptr, 
					&m_vars.m_rainbow_paint
				);
				core->add_option<toggle_option<bool>>(("Rainbow Secondary Paint"),
					nullptr,
					&m_vars.m_second_rainbow_paint
				);
				core->add_option<toggle_option<bool>>(("Rainbow Tire Smoke"),
					nullptr, 
					&m_vars.m_rainbow_tire_smoke
				);
			});
	}

	void vehicle_randomization_menu::script_init() {}

	void vehicle_randomization_menu::script_on_tick()
	{
		Ped playerPed = PLAYER::PLAYER_PED_ID();
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
		DWORD model = ENTITY::GET_ENTITY_MODEL(veh);

		if (m_vars.m_rainbow_paint) {
			if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
			{
				RGBFadee();
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, r, g, b);

			}
		}
		if (m_vars.m_second_rainbow_paint) {
			if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
			{
				RGBFadee();
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, r, g, b);

			}
		}
		if (m_vars.m_second_rainbow_paint) {
			if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
			{
				RGBFadee();
				VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, r, g, b);

			}
		}
	}

	void vehicle_randomization_menu::script_func()
	{
		m_vehicle_randomization_menu.script_init();
		while (true)
		{
			m_vehicle_randomization_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}