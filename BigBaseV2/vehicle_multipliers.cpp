#include "common.hpp"
#include "gta_util.hpp"
#include "vehicle_multipliers.h"
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
#include "util.h"

using namespace big::vehicle::multipliers::vars;

namespace big::vehicle::multipliers::vars
{
	variables m_vars;
}

namespace big::menu
{


	void vehicle_multiplier_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Vehicle Multipliers", SubVehicleMultipliers, [](sub* core)
			{
				core->add_option<number_option<float>>(("Power (RPM)"),
					nullptr, 
					&m_vars.power, 1.f,
					10000.f,
					10.f, 2
				);
				core->add_option<number_option<float>>(("Torque"), 
					nullptr, 
					&m_vars.torque, 1.f,
					10000.f,
					10.f, 2
				);
				core->add_option<number_option<float>>(("Downforce"),
					nullptr, 
					&m_vars.downforce, 1.f,
					150.f,
					1.f, 2
				);
			});
	}

	void vehicle_multiplier_menu::script_init() {}

	void vehicle_multiplier_menu::script_on_tick()
	{

		
		

	}

	void vehicle_multiplier_menu::script_func()
	{
		m_vehicle_multiplier_menu.script_init();
		while (true)
		{
			m_vehicle_multiplier_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}