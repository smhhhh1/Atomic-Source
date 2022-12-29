#include "common.hpp"
#include "gta_util.hpp"
#include "vehicle_parachute.h"
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
#include "memediting.hpp"
using namespace big::vehicle::parachute::vars;


namespace big::vehicle::parachute::vars
{
	variables m_vars;

}

namespace big::menu
{


	void vehicle_parachute_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Vehicle Parachute", SubVehicleParachute, [](sub* core)
			{
				core->add_option<simple_option>(("Deploy"), nullptr, []
					{
						Memory::set_value<int>({ 0x8, 0xD10, 0x20, 0x58C }, static_cast<int>(m_vars.m_auto_deploy));
						VEHICLE::_SET_VEHICLE_PARACHUTE_ACTIVE(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), true);
					});
				core->add_option<toggle_option<bool>>(("Auto Deploy"),
					nullptr,
					&m_vars.m_auto_deploy
					);
			});
	}

	void vehicle_parachute_menu::script_init() {}

	void vehicle_parachute_menu::script_on_tick()
	{
		

		if (m_vars.m_auto_deploy) {
			Memory::set_value<int>({ 0x8, 0xD10, 0x20, 0x58C }, static_cast<int>(m_vars.m_auto_deploy));
			VEHICLE::_SET_VEHICLE_PARACHUTE_ACTIVE(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), true);
		}
	}

	void vehicle_parachute_menu::script_func()
	{
		m_vehicle_parachute_menu.script_init();
		while (true)
		{
			m_vehicle_parachute_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}