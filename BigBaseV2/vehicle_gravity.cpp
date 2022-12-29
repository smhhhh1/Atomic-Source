#include "common.hpp"
#include "gta_util.hpp"
#include "vehicle_gravity.h"
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

using namespace big::vehicle::gravity::vars;

namespace big::vehicle::gravity::vars
{
	variables m_vars;
}

namespace big::menu
{


	void vehicle_gravity_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Vehicle Gravity", SubVehicleGravity, [](sub* core)
			{
                core->add_option<toggle_option<bool>>(("Disable Gravity"), 
                    nullptr, 
                    &m_vars.m_disable_gravity
                );
                core->add_option<toggle_option<bool>>(("Drive on Water"),
                    nullptr,
                    &m_vars.m_drive_on_water
                );
                core->add_option<toggle_option<bool>>(("Slippy Wheels"),
                    nullptr, 
                    &m_vars.m_slippy_wheels
                );
                core->add_option<toggle_option<bool>>(("Stick to Ground"),
                    nullptr, 
                    &m_vars.m_stick_to_ground
                );
                core->add_option<toggle_option<bool>>(("Auto Flip"), 
                    nullptr,
                    &m_vars.m_auto_flip
                );
                core->add_option<simple_option>(("Place on Ground"), nullptr, [=]
                    {
                        Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_PED_ID()));
                        if (ENTITY::IS_ENTITY_UPSIDEDOWN(veh) && (ENTITY::GET_ENTITY_ROLL(veh) > 150 || ENTITY::GET_ENTITY_ROLL(veh) < -150))
                        {
                            if (!ENTITY::IS_ENTITY_IN_AIR(veh) && !ENTITY::IS_ENTITY_IN_WATER(veh) && !VEHICLE::IS_THIS_MODEL_A_HELI(ENTITY::GET_ENTITY_MODEL(veh)) && !VEHICLE::IS_THIS_MODEL_A_PLANE(ENTITY::GET_ENTITY_MODEL(veh)))
                            {
                                take_control_of(veh);
                                ENTITY::SET_ENTITY_ROTATION(veh, 0, 0, ENTITY::GET_ENTITY_ROTATION(veh, 2).z, 2, 1);
                            }
                        }

                    });
			});
	}

	void vehicle_gravity_menu::script_init() {}

	void vehicle_gravity_menu::script_on_tick()
	{
        if (m_vars.m_disable_gravity) {
            if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0));
            else
            {
                take_control_of(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()));
                VEHICLE::SET_VEHICLE_GRAVITY(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 0);

            }

        }
        else {
            if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0));
            else
            {
                take_control_of(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()));
                VEHICLE::SET_VEHICLE_GRAVITY(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 1);

            }
        }
        if (m_vars.m_auto_flip) {
            Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());

            if (ENTITY::IS_ENTITY_UPSIDEDOWN(veh) && (ENTITY::GET_ENTITY_ROLL(veh) > 150 || ENTITY::GET_ENTITY_ROLL(veh) < -150))
            {
                if (!ENTITY::IS_ENTITY_IN_AIR(veh) && !ENTITY::IS_ENTITY_IN_WATER(veh) && !VEHICLE::IS_THIS_MODEL_A_HELI(ENTITY::GET_ENTITY_MODEL(veh)) && !VEHICLE::IS_THIS_MODEL_A_PLANE(ENTITY::GET_ENTITY_MODEL(veh)))
                {
                    take_control_of(veh);
                    ENTITY::SET_ENTITY_ROTATION(veh, 0, 0, ENTITY::GET_ENTITY_ROTATION(veh, 2).z, 2, 1);
                }
            }
        }
        if (m_vars.m_drive_on_water) {
            Player player = PLAYER::PLAYER_ID();
            Ped playerPed = PLAYER::PLAYER_PED_ID();
            Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
            DWORD model = ENTITY::GET_ENTITY_MODEL(veh);
            Vector3 pos = ENTITY::GET_ENTITY_COORDS(playerPed, 0);
            float height = 0;
            WATER::SET_DEEP_OCEAN_SCALER(height);
            if ((!(VEHICLE::IS_THIS_MODEL_A_PLANE(ENTITY::GET_ENTITY_MODEL(veh)))) && WATER::GET_WATER_HEIGHT_NO_WAVES(pos.x, pos.y, pos.z, &height)) {
                Object container = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(pos.x, pos.y, pos.z, 4.0, MISC::GET_HASH_KEY("prop_container_ld2"), 0, 0, 1);
                if (ENTITY::DOES_ENTITY_EXIST(container) && height > -50.0f) {
                    Vector3 pRot = ENTITY::GET_ENTITY_ROTATION(playerPed, 0);
                    if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 1)) pRot = ENTITY::GET_ENTITY_ROTATION(veh, 0);
                    take_control_of(container);
                    ENTITY::SET_ENTITY_COORDS(container, pos.x, pos.y, height - 1.5f, 0, 0, 0, 1);
                    ENTITY::SET_ENTITY_ROTATION(container, 0, 0, pRot.z, 0, 1);
                    Vector3 containerCoords = ENTITY::GET_ENTITY_COORDS(container, 1);
                    if (pos.z < containerCoords.z) {
                        if (!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
                            ENTITY::SET_ENTITY_COORDS(playerPed, pos.x, pos.y, containerCoords.z + 2.0f, 0, 0, 0, 1);
                        }
                        else {
                            take_control_of(veh);
                            Vector3 vehc = ENTITY::GET_ENTITY_COORDS(veh, 1);
                            ENTITY::SET_ENTITY_COORDS(veh, vehc.x, vehc.y, containerCoords.z + 2.0f, 0, 0, 0, 1);
                        }
                    }
                }
                else {
                    Hash model = MISC::GET_HASH_KEY("prop_container_ld2");
                    STREAMING::REQUEST_MODEL(model);

                    container = OBJECT::CREATE_OBJECT(model, pos.x, pos.y, pos.z, 0, 0, 0);
                    take_control_of(container);
                    ENTITY::FREEZE_ENTITY_POSITION(container, 1);
                    ENTITY::SET_ENTITY_ALPHA(container, 0, 1);
                    ENTITY::SET_ENTITY_VISIBLE(container, 0, 0);
                }
            }
            else {
                Object container = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(pos.x, pos.y, pos.z, 4.0, MISC::GET_HASH_KEY("prop_container_ld2"), 0, 0, 1);
                if (ENTITY::DOES_ENTITY_EXIST(container)) {
                    take_control_of(container);
                    ENTITY::SET_ENTITY_COORDS(container, 0, 0, -1000.0f, 0, 0, 0, 1);

                    ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&container);
                    ENTITY::DELETE_ENTITY(&container);
                    WATER::RESET_DEEP_OCEAN_SCALER();
                }
            }
        }
        if (m_vars.m_slippy_wheels) {
            if (GetAsyncKeyState(0x10) || PAD::IS_CONTROL_PRESSED(2, 73))
            {
                VEHICLE::SET_VEHICLE_REDUCE_GRIP(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1), 1);
            }
            else
            {
                VEHICLE::SET_VEHICLE_REDUCE_GRIP(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 0);
            }
        }
        if (m_vars.m_stick_to_ground) {
            VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 0);
        }
		
	}

	void vehicle_gravity_menu::script_func()
	{
		m_vehicle_gravity_menu.script_init();
		while (true)
		{
			m_vehicle_gravity_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}