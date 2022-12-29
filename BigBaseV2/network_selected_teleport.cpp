#include "common.hpp"
#include "gta_util.hpp"
#include "network_selected_teleport.h"
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
#include "notify.h"
#include "util.h"

namespace big::menu
{


    void network_selected_teleport_menu::menu()
    {
        using namespace ui;

        m_renderer.new_sub<PlayerSubmenu>(&selected_player, SubSelectedTeleport, [](PlayerSubmenu* core)
            {
                m_renderer.m_enable_player_info = true;
				core->add_option<submenu>(("Apartments"), nullptr, SubSelectedTeleportApartments);
				core->add_option<simple_option>(("Teleport To Player"), nullptr, [] {
					Entity handle;
					Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), false);
					PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false) ? handle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()) : handle = PLAYER::PLAYER_PED_ID();
					ENTITY::SET_ENTITY_COORDS(handle, coords.x, coords.y, coords.z, false, false, false, false);
					if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), FALSE))
					{
						Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), false);
						for (int i = -1; i < 16; i++)
						{
							if (VEHICLE::IS_VEHICLE_SEAT_FREE(veh, i, 0))
							{
								PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, i);
								return;
							}
						}
					}
					});

				core->add_option<simple_option>(("Teleport To Me"), nullptr, [] {

					Entity ent = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player);

					if (ENTITY::IS_ENTITY_DEAD(ent, true))
					{
						//g_notification_service->push_warning("Teleport", "Target player is dead.");

						return false;
					}

					if (!PED::IS_PED_IN_ANY_VEHICLE(ent, true))
					{

						ImGui::InsertNotification({ ImGuiToastType_None, 2000, "Player is not in a vehicle" });
						return false;
					}

					ent = PED::GET_VEHICLE_PED_IS_IN(ent, false);
					Vector3 location = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);

					if (take_control_of(ent))
						ENTITY::SET_ENTITY_COORDS(ent, location.x, location.y, location.z, 0, 0, 0, 0);
					else
						ImGui::InsertNotification({ ImGuiToastType_None, 2000, "Failed to take control of players vehicle" });

					});

				core->add_option<simple_option>(("Into Vehicle"), nullptr, [] {

					Entity ent = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player);
					Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(ent, true);
					if (!ENTITY::IS_ENTITY_A_VEHICLE(veh))
					{
						ImGui::InsertNotification({ ImGuiToastType_None, 2000, "Player is not in a vehicle" });

						return false;
					}

					int seat_index = 255;
					if (VEHICLE::IS_VEHICLE_SEAT_FREE(veh, -1, true))
						seat_index = -1;
					else if (VEHICLE::IS_VEHICLE_SEAT_FREE(veh, -2, true))
						seat_index = -2;

					if (seat_index == 255)
					{

						ImGui::InsertNotification({ ImGuiToastType_None, 2000, "There Are No Free Seats" });
						return false;
					}

					Vector3 location = ENTITY::GET_ENTITY_COORDS(veh, true);
					load_ground_at_3dcoord(location);

					Ped ped = PLAYER::PLAYER_PED_ID();

					ENTITY::SET_ENTITY_COORDS(ped, location.x, location.y, location.z, 0, 0, 0, 0);

					script::get_current()->yield();

					PED::SET_PED_INTO_VEHICLE(ped, veh, seat_index);
					});
            });
    }

    void network_selected_teleport_menu::script_init() {}

    void network_selected_teleport_menu::script_on_tick()
    {
       
    }

    void network_selected_teleport_menu::script_func()
    {
        m_network_selected_teleport_menu.script_init();
        while (true)
        {


            m_network_selected_teleport_menu.script_on_tick();
            script::get_current()->yield();
        }
    }
}