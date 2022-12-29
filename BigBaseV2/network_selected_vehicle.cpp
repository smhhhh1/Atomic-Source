#include "common.hpp"
#include "gta_util.hpp"
#include "network_selected_vehicle.h"
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
#include "player_submenu.h"
#include "../submenus.h"
#include "on_screen_ped.h"
#include "lists.h"
#include "fiber_pool.hpp"
#include "gta/enums.hpp"
#include "script_global.hpp"
#include "scroll.h"
#include "util.h"
using namespace big::network::selected_player::vehicle::vars;


namespace big::network::selected_player::vehicle::vars
{
    variables m_vars;

}

namespace big::menu
{


    void network_selected_vehicle_menu::menu()
    {
        using namespace ui;

        m_renderer.new_sub<PlayerSubmenu>(&selected_player, SubSelectedVehicle, [](PlayerSubmenu* core)
            {
                m_renderer.m_enable_player_info = true;

				Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player));
				bool isPedInVeh = PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), false);
				core->add_option<submenu>(("Acrobatics"), nullptr, Remote_Acro);
                core->add_option<toggle_option<bool>>(("Godmode"),
                    nullptr,
                    &m_vars.m_godmode
                );

                core->add_option<toggle_option<bool>>(("Disable Collision"),
                    nullptr,
                    &m_vars.m_disable_collision
                );

                core->add_option<toggle_option<bool>>(("Slippy Wheels"),
                    nullptr,
                    &m_vars.m_slippy_wheels
                );

                core->add_option<toggle_option<bool>>(("Freeze"),
                    nullptr,
                    &m_vars.m_freeze
                );
				core->add_option<simple_option>(("Slingshot"), nullptr, [=]
					{

						ENTITY::APPLY_FORCE_TO_ENTITY(veh, 1, 0, 0, 20, 0, 0, 0, 1, false, true, true, true, true);
					});
				core->add_option<simple_option>(("Boost Forward"), nullptr, [=]
					{
						if (take_control_of(veh)) {
							ENTITY::APPLY_FORCE_TO_ENTITY(veh, true, 0, 300 / 10, 0, 0, 0, 0, true, true, true, true, false, true);
						}

					});
				core->add_option<simple_option>(("Pop Tyres"), nullptr, [=]
					{
						if (isPedInVeh) {
							if (take_control_of(veh)) {

								VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, true);
								for (int i = 5; i--;)
									VEHICLE::SET_VEHICLE_TYRE_BURST(veh, i, true, 1000.f);
							}

						}

					});
				core->add_option<simple_option>(("Max Vehicle"), nullptr, [=]
					{
						if (take_control_of(veh)) {
							VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
							for (int i = 0; i < 50; i++)
							{
								VEHICLE::SET_VEHICLE_MOD(veh, i, VEHICLE::GET_NUM_VEHICLE_MODS(veh, i) - 1, false);
							}
							VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, "Atomic");
						}

					});
				core->add_option<simple_option>(("Repair Vehicle"), nullptr, [=]
					{
						if (take_control_of(veh)) {

							VEHICLE::SET_VEHICLE_FIXED(veh);
							VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(veh);
							VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, 0);
						}

					});
				core->add_option<simple_option>(("Clone"), nullptr, [] {
					Vehicle pedVeh = NULL;
					Ped playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player);
					if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, FALSE))
					{
						pedVeh = PED::GET_VEHICLE_PED_IS_IN(playerPed, FALSE);
						if (ENTITY::DOES_ENTITY_EXIST(pedVeh))
						{
							Hash vehicleModelHash = ENTITY::GET_ENTITY_MODEL(pedVeh);


							Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(playerPed, FALSE);
							*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
							Vehicle playerVeh = VEHICLE::CREATE_VEHICLE(vehicleModelHash, playerPosition.x, playerPosition.y, playerPosition.z, 0.f, true, false, false);
							*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;
							PED::SET_PED_INTO_VEHICLE(playerPed, playerVeh, -1);
							int primaryColor, secondaryColor;
							VEHICLE::GET_VEHICLE_COLOURS(pedVeh, &primaryColor, &secondaryColor);
							VEHICLE::SET_VEHICLE_COLOURS(playerVeh, primaryColor, secondaryColor);
							if (VEHICLE::GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(pedVeh))
							{
								int r, g, b;
								VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(pedVeh, &r, &g, &b);
								VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(playerVeh, r, g, b);
							}
							if (VEHICLE::GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(pedVeh))
							{
								int r, g, b;
								VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(pedVeh, &r, &g, &b);
								VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(playerVeh, r, g, b);
							}
							if (VEHICLE::IS_THIS_MODEL_A_CAR(vehicleModelHash) || VEHICLE::IS_THIS_MODEL_A_BIKE(vehicleModelHash))
							{
								VEHICLE::SET_VEHICLE_MOD_KIT(playerVeh, 0);
								VEHICLE::SET_VEHICLE_WHEEL_TYPE(playerVeh, VEHICLE::GET_VEHICLE_WHEEL_TYPE(pedVeh));
								for (int i = 0; i <= 24; i++)
								{
									if (i > 16 && i < 23)
										VEHICLE::TOGGLE_VEHICLE_MOD(playerVeh, i, VEHICLE::IS_TOGGLE_MOD_ON(pedVeh, i));
									else
										VEHICLE::SET_VEHICLE_MOD(playerVeh, i, VEHICLE::GET_VEHICLE_MOD(pedVeh, i), VEHICLE::GET_VEHICLE_MOD_VARIATION(pedVeh, i));
								}
								int tireSmokeColor[3], pearlescentColor, wheelColor;
								VEHICLE::GET_VEHICLE_TYRE_SMOKE_COLOR(pedVeh, &tireSmokeColor[0], &tireSmokeColor[1], &tireSmokeColor[2]);
								VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(playerVeh, tireSmokeColor[0], tireSmokeColor[1], tireSmokeColor[2]);
								VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(playerVeh, VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(pedVeh));
								VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(playerVeh, VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT(pedVeh));
								VEHICLE::GET_VEHICLE_EXTRA_COLOURS(pedVeh, &pearlescentColor, &wheelColor);
								VEHICLE::SET_VEHICLE_EXTRA_COLOURS(playerVeh, pearlescentColor, wheelColor);
								if (VEHICLE::IS_VEHICLE_A_CONVERTIBLE(pedVeh, 0))
								{
									int convertableState = VEHICLE::GET_CONVERTIBLE_ROOF_STATE(pedVeh);
									if (convertableState == 0 || convertableState == 3 || convertableState == 5)
										VEHICLE::RAISE_CONVERTIBLE_ROOF(playerVeh, 1);
									else
										VEHICLE::LOWER_CONVERTIBLE_ROOF(playerVeh, 1);
								}
								for (int i = 0; i <= 3; i++)
								{
									VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(playerVeh, i, VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(pedVeh, i));
								}
								for (int i = 0; i <= 11; i++)
								{
									if (VEHICLE::DOES_EXTRA_EXIST(pedVeh, i))
										VEHICLE::SET_VEHICLE_EXTRA(playerVeh, i, !VEHICLE::IS_VEHICLE_EXTRA_TURNED_ON(pedVeh, i));
								}
								if ((VEHICLE::GET_VEHICLE_LIVERY_COUNT(pedVeh) > 1) && VEHICLE::GET_VEHICLE_LIVERY(pedVeh) >= 0)
								{
									VEHICLE::SET_VEHICLE_LIVERY(playerVeh, VEHICLE::GET_VEHICLE_LIVERY(pedVeh));
								}
								int neonColor[3];
								VEHICLE::_GET_VEHICLE_NEON_LIGHTS_COLOUR(pedVeh, &neonColor[0], &neonColor[1], &neonColor[2]);
								VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(playerVeh, neonColor[0], neonColor[1], neonColor[2]);
								VEHICLE::SET_VEHICLE_WINDOW_TINT(playerVeh, VEHICLE::GET_VEHICLE_WINDOW_TINT(pedVeh));
								VEHICLE::SET_VEHICLE_DIRT_LEVEL(playerVeh, VEHICLE::GET_VEHICLE_DIRT_LEVEL(pedVeh));
							}
							STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(vehicleModelHash);

							if (*g_pointers->m_is_session_started)
							{
								DECORATOR::DECOR_SET_INT(vehicleModelHash, "MPBitset", 0);
								ENTITY::_SET_ENTITY_SOMETHING(vehicleModelHash, true);
								int networkId = NETWORK::VEH_TO_NET(vehicleModelHash);
								if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(vehicleModelHash))
									NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
								VEHICLE::SET_VEHICLE_IS_STOLEN(vehicleModelHash, false);
							}
						}
					}
					});

            });
			m_renderer.new_sub<PlayerSubmenu>(&selected_player, Remote_Acro, [](PlayerSubmenu* core)
				{
					m_renderer.m_enable_player_info = true;
					core->add_option<simple_option>(("Front Flip"), nullptr, [] {
						Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), false);

						if (take_control_of(vehicle)) {
							ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, true, 0, 0, 6.0f, 0, -2.0f, 0, true, true, true, true, false, true);
						}

						});
					core->add_option<simple_option>(("Side Flip"), nullptr, [] {
						Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), false);
						if (take_control_of(vehicle)) {
							ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, true, 0, 0, 6.0f, 5.0f, 2.0f, 0, true, true, true, true, false, true);
						}

						});
					core->add_option<simple_option>(("Back Flip"), nullptr, [] {
						Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), false);
						//take_control_of(vehicle); 
						if (take_control_of(vehicle)) {
							ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, true, 0, 0, 6.0f, 0, 2.0f, 0, true, true, true, true, false, true);
						}

						});
					core->add_option<simple_option>(("Kick Flip"), nullptr, [] {
						Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), false);
						//take_control_of(vehicle); 
						if (take_control_of(vehicle)) {
							ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, true, 0, 0, 5.0f, 2.0f, 0, 0, true, true, true, true, false, true);
						}

						});
					core->add_option<simple_option>(("Bunny Hop"), nullptr, [] {
						Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), false);
						if (take_control_of(vehicle)) {
							ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, true, 0, 0, 7.0f, 0, 0, 0, true, true, true, true, false, true);
						}

						});
					core->add_option<simple_option>(("Double Front Flip"), nullptr, [] {
						Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), false);
						if (take_control_of(vehicle)) {
							ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, true, 0, 0, 12.0f, 0, -4.0f, 0, true, true, true, true, false, true);
						}

						});
					core->add_option<simple_option>(("Double Back Flip"), nullptr, [] {
						Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), false);
						//take_control_of(vehicle); 
						if (take_control_of(vehicle)) {
							ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, true, 0, 0, 12.0f, 0, 4.0f, 0, true, true, true, true, false, true);
						}

						});

				});
    }

    void network_selected_vehicle_menu::script_init() {}

    void network_selected_vehicle_menu::script_on_tick()
    {
        if (m_vars.m_godmode) {
            ENTITY::SET_ENTITY_INVINCIBLE(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), true), true);
        }
        else {
            ENTITY::SET_ENTITY_INVINCIBLE(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), true), false);
        }
        if (m_vars.m_disable_collision) {
            ENTITY::SET_ENTITY_COLLISION(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), true), false, true);
        }
        else {
            ENTITY::SET_ENTITY_COLLISION(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), true), true, true);
        }
        if (m_vars.m_slippy_wheels) {
            VEHICLE::SET_VEHICLE_REDUCE_GRIP(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), true), true);
        }
        else {
            VEHICLE::SET_VEHICLE_REDUCE_GRIP(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), true), false);
        }
        if (m_vars.m_freeze) {
            ENTITY::FREEZE_ENTITY_POSITION(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), true), true);
        }
        else {
            ENTITY::FREEZE_ENTITY_POSITION(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), true), false);
        }
    }

    void network_selected_vehicle_menu::script_func()
    {
        m_network_selected_vehicle_menu.script_init();
        while (true)
        {
            m_network_selected_vehicle_menu .script_on_tick();
            script::get_current()->yield();
        }
    }
}