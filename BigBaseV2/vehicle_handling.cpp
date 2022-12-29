#include "common.hpp"
#include "gta_util.hpp"
#include "vehicle_handling.h"
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

using namespace big::vehicle::handling::vars;

namespace big::vehicle::handling::vars
{
	variables m_vars;
}

namespace big::menu
{


	void vehicle_handling_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Vehicle Handling", SubVehicleHandling, [](sub* core)
			{
				if (gta_util::get_local_ped() == nullptr) return;
				if (gta_util::get_local_ped()->m_vehicle == nullptr) return;
				if (gta_util::get_local_ped()->m_vehicle->m_handling_data == nullptr) return;
				auto handling = gta_util::get_local_ped()->m_vehicle->m_handling_data;

				core->add_option<number_option<float>>(("Mass"), nullptr, &handling->m_mass, 0.f, 50000.f, 10.f, 2);


				core->add_option<number_option<float>>(("Minimum Traction"), nullptr, &handling->m_traction_curve_min, 0.f, 7.f, 0.1f, 2);
				core->add_option<number_option<float>>(("Maximum Traction"), nullptr, &handling->m_traction_curve_max, 0.f, 7.f, 0.1f, 2);
				core->add_option<number_option<float>>(("Traction Curve"), nullptr, &handling->m_traction_curve_lateral, 0.f, 7.f, 0.1f, 2);
				core->add_option<number_option<float>>(("Burnout Multiplier"), nullptr, &handling->m_low_speed_traction_loss_mult, 0.f, 10.f, 0.1f, 2);
				core->add_option<number_option<float>>(("Suspension Force"), nullptr, &handling->m_low_speed_traction_loss_mult, 0.f, 5.0f, 0.1f, 2);
				core->add_option<number_option<float>>(("Suspension Upper Limit"), nullptr, &handling->m_suspension_upper_limit, -1.f, 1.0f, 0.1f, 2);
				core->add_option<number_option<float>>(("Suspension Lower Limit"), nullptr, &handling->m_suspension_lower_limit, -1.f, 1.0f, 0.1f, 2);
				core->add_option<number_option<float>>(("Suspension Height"), nullptr, &handling->m_suspension_raise, -1.f, 1.0f, 0.1f, 2);
				core->add_option<number_option<float>>(("Steering Lock"), nullptr, &handling->m_steering_lock, -90.f, 90.0f, 1.0f, 2);

				core->add_option<number_option<float>>(("Roll Centre Height Front"), nullptr, &handling->m_roll_centre_height_front, -1.f, 1.0f, 0.1f, 2);
				core->add_option<number_option<float>>(("Roll Centre Height Back"), nullptr, &handling->m_roll_centre_height_rear, -1.f, 1.0f, 0.1f, 2);

				core->add_option<number_option<float>>(("Anti Roll Bar Force"), nullptr, &handling->m_anti_rollbar_force, 0.f, 10.f, 1.00f, 2);
				core->add_option<number_option<float>>(("Buoyancy"), nullptr, &handling->m_buoyancy, .01f, 99, 0.01f, 2);
			});
	}

	void vehicle_handling_menu::script_init() {}

	void vehicle_handling_menu::script_on_tick()
	{

		
	}

	void vehicle_handling_menu::script_func()
	{
		m_vehicle_handling_menu.script_init();
		while (true)
		{
			m_vehicle_handling_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}