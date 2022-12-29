#include "common.hpp"
#include "gta_util.hpp"
#include "vehicle_acrobatics.h"
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
#include "util.h"
namespace big::menu
{


	void vehicle_acrobatics_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Vehicle Acrobatics", SubVehicleAcrobatics, [](sub* core)
			{
				core->add_option<simple_option>(("Front Flip"), nullptr, [] {
					Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
					if (take_control_of(vehicle)) {
						ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, true, 0, 0, 6.0f, 0, -2.0f, 0, true, true, true, true, false, true);
					}

					});
				core->add_option<simple_option>(("Side Flip"), nullptr, [] {
					Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
					if (take_control_of(vehicle)) {
						ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, true, 0, 0, 6.0f, 5.0f, 2.0f, 0, true, true, true, true, false, true);
					}

					});
				core->add_option<simple_option>(("Back Flip"), nullptr, [] {
					Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
					//take_control_of(vehicle); 
					if (take_control_of(vehicle)) {
						ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, true, 0, 0, 6.0f, 0, 2.0f, 0, true, true, true, true, false, true);
					}

					});
				core->add_option<simple_option>(("Kick Flip"), nullptr, [] {
					Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
					//take_control_of(vehicle); 
					if (take_control_of(vehicle)) {
						ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, true, 0, 0, 5.0f, 2.0f, 0, 0, true, true, true, true, false, true);
					}

					});
				core->add_option<simple_option>(("Bunny Hop"), nullptr, [] {
					Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
					if (take_control_of(vehicle)) {
						ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, true, 0, 0, 7.0f, 0, 0, 0, true, true, true, true, false, true);
					}

					});
				core->add_option<simple_option>(("Double Front Flip"), nullptr, [] {
					Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
					if (take_control_of(vehicle)) {
						ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, true, 0, 0, 12.0f, 0, -4.0f, 0, true, true, true, true, false, true);
					}

					});
				core->add_option<simple_option>(("Double Back Flip"), nullptr, [] {
					Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
					if (take_control_of(vehicle)) {
						ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, true, 0, 0, 12.0f, 0, 4.0f, 0, true, true, true, true, false, true);
					}

					});
			});
	}

	void vehicle_acrobatics_menu::script_init() {}

	void vehicle_acrobatics_menu::script_on_tick() {}

	void vehicle_acrobatics_menu::script_func()
	{
		m_vehicle_acrobatics_menu.script_init();
		while (true)
		{
			m_vehicle_acrobatics_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}