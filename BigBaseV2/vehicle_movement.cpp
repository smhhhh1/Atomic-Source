#include "common.hpp"
#include "gta_util.hpp"
#include "vehicle_movement.h"
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
using namespace big::vehicle::movement::vars;


namespace big::vehicle::movement::vars
{
	variables m_vars;
}

namespace big::menu
{


	void vehicle_movement_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Vehicle Movement", SubVehicleMovement, [](sub* core)
			{
                core->add_option<submenu>("Acrobatics", nullptr, SubVehicleAcrobatics);
                core->add_option<submenu>("Parachute", nullptr, SubVehicleParachute);
                core->add_option<toggle_option<bool>>(("Spin"),
                    nullptr,
                    &m_vars.m_spin
                );
                core->add_option<toggle_option<bool>>(("Bypass Max Speed"), 
                    nullptr, 
                    &m_vars.m_bypass_max_speed
                );
                core->add_option<toggle_number_option<float, bool>>("Limit Max Speed",
                    nullptr, &m_vars.m_limit_max_speed,
                    &m_vars.m_max_speed_limit,
                    1.0f, 100.0f,
                    1.f, 1
                );
                core->add_option<toggle_number_option<float, bool>>(("Vehicle Fly"),
                    nullptr,
                    &m_vars.m_flying_vehicle,
                    &m_vars.m_vehicle_fly_speed,
                    10.0f, 80.0f,
                    1.0f, 1
                );
                if (m_vars.m_flying_vehicle)
                    core->add_option<toggle_option<bool>>(("Flying Vehicle Pause"),
                        nullptr, 
                        &m_vars.m_flying_vehicle_pause
                    );
			});
	}

	void vehicle_movement_menu::script_init() {}

	void vehicle_movement_menu::script_on_tick()
	{
		Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
		if (m_vars.m_spin)
		{

			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(vehicle);
				Vector3 Rot = ENTITY::GET_ENTITY_ROTATION(vehicle, 2);
				Rot.z = Rot.z + 2.0;
				ENTITY::SET_ENTITY_ROTATION(vehicle, 0, 0, Rot.z, 2, 1);
			}
		}
		bool stop_on_exit = false;
		if (m_vars.m_bypass_max_speed) {

			VEHICLE::_SET_VEHICLE_MAX_SPEED(vehicle, 9999.f);
		}
		if (m_vars.m_limit_max_speed) {
			VEHICLE::_SET_VEHICLE_MAX_SPEED(vehicle, m_vars.m_max_speed_limit);
		}
		if (m_vars.m_flying_vehicle)
		{
            Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()), false);
            Vector3 cam_pos = CAM::GET_GAMEPLAY_CAM_ROT(0);
            ENTITY::SET_ENTITY_ROTATION(vehicle, cam_pos.x, cam_pos.y, cam_pos.z, 1, true);
            ENTITY::SET_ENTITY_COLLISION(vehicle, false, true);

            float locspeed = (m_vars.m_vehicle_fly_speed * 10);
            float locspeed2 = m_vars.m_vehicle_fly_speed;

            if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_MOVE_UP_ONLY))
            {
                locspeed *= 2;
                locspeed2 *= 2;
            }


            if (PAD::IS_CONTROL_PRESSED(2, (int)ControllerInputs::INPUT_VEH_ACCELERATE))
            {
                if (m_vars.m_flying_vehicle_pause)
                {
                    ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, 1, 0.0, m_vars.m_vehicle_fly_speed, 0.0, 0.0, 0.0, 0.0, 0, 1, 1, 1, 0, 1);
                }
                else
                {
                    VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle, locspeed);
                }
            }

            if (PAD::IS_CONTROL_PRESSED(2, (int)ControllerInputs::INPUT_VEH_BRAKE))
            {
                float lsp = m_vars.m_vehicle_fly_speed;
                if (!PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_MOVE_UP_ONLY))
                {
                    lsp = (m_vars.m_vehicle_fly_speed * 2);
                }
                if (m_vars.m_flying_vehicle_pause)
                {
                    ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, 1, 0.0, 0 - (lsp), 0.0, 0.0, 0.0, 0.0, 0, 1, 1, 1, 0, 1);
                }
                else
                {
                    VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle, (0 - locspeed));
                }
            }

            if (PAD::IS_CONTROL_PRESSED(2, (int)ControllerInputs::INPUT_VEH_MOVE_LEFT_ONLY))
            {
                float lsp = ((0 - m_vars.m_vehicle_fly_speed) * 2);
                if (!PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_MOVE_UP_ONLY))
                {
                    lsp = (0 - m_vars.m_vehicle_fly_speed);
                }
                if (m_vars.m_flying_vehicle_pause)
                {
                    ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, 1, (lsp), 0.0, 0.0, 0.0, 0.0, 0.0, 0, 1, 1, 1, 0, 1);
                }
                else
                {
                    ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, 1, (0 - (locspeed)), 0.0, 0.0, 0.0, 0.0, 0.0, 0, 1, 1, 1, 0, 1);
                }
            }

            if (PAD::IS_CONTROL_PRESSED(2, (int)ControllerInputs::INPUT_VEH_MOVE_RIGHT_ONLY))
            {
                float lsp = m_vars.m_vehicle_fly_speed;
                if (!PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_MOVE_UP_ONLY))
                {
                    lsp = (m_vars.m_vehicle_fly_speed * 2);
                }
                if (m_vars.m_flying_vehicle_pause)
                {
                    ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, 1, lsp, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 1, 1, 1, 0, 1);
                }
                else
                {
                    ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, 1, locspeed, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 1, 1, 1, 0, 1);
                }
            }

            if (m_vars.m_flying_vehicle_pause && !PAD::IS_CONTROL_PRESSED(2, (int)ControllerInputs::INPUT_VEH_ACCELERATE) && !PAD::IS_CONTROL_PRESSED(2, (int)ControllerInputs::INPUT_VEH_BRAKE))
            {
                VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle, 0.0);
            }

            if (TASK::GET_IS_TASK_ACTIVE(PLAYER::PLAYER_PED_ID(), 2))
            {
                m_vars.m_vehicle_fly_speed = false;
                VEHICLE::SET_VEHICLE_GRAVITY(vehicle, true);
                ENTITY::SET_ENTITY_COLLISION(vehicle, true, true);
                if (stop_on_exit)
                {
                    VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle, 0.0);
                }
            }
		}
        else
        {
            Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()), false);
            ENTITY::SET_ENTITY_COLLISION(vehicle, true, true);
        }
	}

	void vehicle_movement_menu::script_func()
	{
		m_vehicle_movement_menu.script_init();
		while (true)
		{
			m_vehicle_movement_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}