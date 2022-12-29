#include "common.hpp"
#include "gta_util.hpp"
#include "vehicle_boost.h"
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

using namespace big::vehicle::boost::vars;

namespace big::vehicle::boost::vars
{
	variables m_vars;
}

namespace big::menu
{


	void vehicle_boost_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Vehicle Boost", SubVehicleBoost, [](sub* core)
			{
				core->add_option<toggle_number_option<float, bool>>(("Horn Boost"), nullptr, &m_vars.m_horn_boost, &m_vars.m_horn_boost_speed, 10.0f, 80.0f, 1.0f, 1);
				core->add_option<toggle_option<bool>>(("Boost Fx"), nullptr, &m_vars.m_boost_fx);
				core->add_option<simple_option>(("Boost Forward"), nullptr, [=]
					{
						Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_PED_ID()));
						take_control_of(veh);
						VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 100);
						

					});
			});
	}

	void vehicle_boost_menu::script_init() {}

	void vehicle_boost_menu::script_on_tick()
	{
		if (m_vars.m_horn_boost) {
			if (PLAYER::IS_PLAYER_PRESSING_HORN(PLAYER::PLAYER_ID()))
			{
				Vehicle Veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()), false);
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Veh);

				if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(Veh))
				{

					VEHICLE::SET_VEHICLE_FORWARD_SPEED(Veh, m_vars.m_horn_boost_speed);

					if (m_vars.m_boost_fx)
						GRAPHICS::ANIMPOSTFX_PLAY("RaceTurbo", 0, true);


				}
			}
			else {
				GRAPHICS::ANIMPOSTFX_STOP("RaceTurbo");
			}
		}
	}

	void vehicle_boost_menu::script_func()
	{
		m_vehicle_boost_menu.script_init();
		while (true)
		{
			m_vehicle_boost_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}