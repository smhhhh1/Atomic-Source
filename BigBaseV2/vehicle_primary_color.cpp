#include "common.hpp"
#include "gta_util.hpp"
#include "vehicle_primary_color.h"
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
using namespace big::vehicle::color::primary::vars;


namespace big::vehicle::color::primary::vars
{
	variables m_vars;
}

namespace big::menu
{
	void vehicle_primary_color_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Primary Color", SubVehicleColorPrimary, [](sub* core)
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
				

				core->add_option<number_option<int>>("Red",
					nullptr,
					&m_vars.red, 0,
					255, 1,
					2
				);
				core->add_option<number_option<int>>("Green", 
					nullptr,
					&m_vars.green, 0,
					255, 1,
					2
				);
				core->add_option<number_option<int>>("Blue",
					nullptr,
					&m_vars.blue, 0, 
					255, 1,
					2
				);
				core->add_option<simple_option>(("Apply Primary Color"), nullptr, [&]
					{
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, m_vars.red, m_vars.green, m_vars.blue);
					});
			});
	}

	void vehicle_primary_color_menu::script_init() {}

	void vehicle_primary_color_menu::script_on_tick() {}

	void vehicle_primary_color_menu::script_func()
	{
		m_vehicle_primary_color_menu.script_init();
		while (true)
		{
			m_vehicle_primary_color_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}