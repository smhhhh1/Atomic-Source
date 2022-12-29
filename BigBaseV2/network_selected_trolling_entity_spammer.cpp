#include "common.hpp"
#include "gta_util.hpp"
#include "network_selected_trolling_entity_spammer.h"
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
using namespace big::network::selected_player::trolling::entity_spammer::vars;


namespace big::network::selected_player::trolling::entity_spammer::vars
{
    variables m_vars;
	int spawn(std::string_view model)
	{


		if (const Hash hash = rage::joaat(model.data()); hash)
		{
			for (uint8_t i = 0; !STREAMING::HAS_MODEL_LOADED(hash) && i < 100; i++)
			{
				STREAMING::REQUEST_MODEL(hash);

				script::get_current()->yield();
			}
			if (!STREAMING::HAS_MODEL_LOADED(hash))
			{
				LOG(INFO) << "Invalid Vehicle Model";
				return -1;
			}
			bool isFlyingVehicle = VEHICLE::IS_THIS_MODEL_A_PLANE(hash);
			Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
			*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
			Vehicle veh = VEHICLE::CREATE_VEHICLE(hash, pos.x, pos.y, pos.z, 0.0f, true, false, false);
			*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

			script::get_current()->yield();

			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);

			if (*g_pointers->m_is_session_started)
			{
				*script_global(4539659).as<bool*>() = true;
				DECORATOR::DECOR_SET_INT(veh, "MPBitset", 0);
				ENTITY::_SET_ENTITY_SOMETHING(veh, true);
				int networkId = NETWORK::VEH_TO_NET(veh);
				if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(veh))
					NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
				VEHICLE::SET_VEHICLE_IS_STOLEN(veh, false);
			}

			return veh;
		}

		return -1;
	}
}

namespace big::menu
{


    void network_selected_trolling_entity_spammer_menu::menu()
    {
        using namespace ui;

        m_renderer.new_sub<PlayerSubmenu>(&selected_player, SubSelectedTrollingEntitySpammer, [](PlayerSubmenu* core)
            {
                m_renderer.m_enable_player_info = true;
                core->add_option<toggle_option<bool>>(("Clone"),
                    nullptr,
                    &m_vars.g_clone
                );
                core->add_option<toggle_option<bool>>(("Ped"), 
                    nullptr,
                    &m_vars.g_ped
                );
                core->add_option<toggle_option<bool>>(("Vehicle"),
                    nullptr,
                    &m_vars.g_vehicle
                );
            });
    }

    void network_selected_trolling_entity_spammer_menu::script_init() {}

    void network_selected_trolling_entity_spammer_menu::script_on_tick()
    {
        auto vic = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player);
        Vector3 pos = ENTITY::GET_ENTITY_COORDS(vic, 1);

        if (m_vars.g_ped) {


            if (ENTITY::DOES_ENTITY_EXIST(vic)) {
                *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
                PED::CREATE_RANDOM_PED(pos.x + rand() % 1, pos.y + rand() % 1, pos.z + 1);
                *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;
            }

        }
        if (m_vars.g_clone) {
            if (ENTITY::DOES_ENTITY_EXIST(vic)) {
                *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
                PED::CLONE_PED(vic, 1, 1, 1);
                *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;
            }
        }
        if (m_vars.g_vehicle) {

            spawn("adder");
        }
    }

    void network_selected_trolling_entity_spammer_menu::script_func()
    {
        m_network_selected_trolling_entity_spammer_menu.script_init();
        while (true)
        {


            m_network_selected_trolling_entity_spammer_menu.script_on_tick();
            script::get_current()->yield();
        }
    }
}