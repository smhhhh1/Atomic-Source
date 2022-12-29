#include "common.hpp"
#include "gta_util.hpp"
#include "network_selected_kicks.h"
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
namespace big::menu
{


    void network_selected_kicks_menu::menu()
    {
        using namespace ui;

        m_renderer.new_sub<PlayerSubmenu>(&selected_player, SubSelectedKicks, [](PlayerSubmenu* core)
            {
                m_renderer.m_enable_player_info = true;
                core->add_option<simple_option>(("Session Host Kick"), nullptr, []
                    {
                        NETWORK::NETWORK_SESSION_KICK_PLAYER(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player));
                    });
				core->add_option<simple_option>(("Wade Kick"), nullptr, []
					{
						for (int i = 0; i < 50; ++i) {
							Ped iPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player);
							STREAMING::REQUEST_MODEL(MISC::GET_HASH_KEY("vw_prop_vw_colle_alien"));
							if (!STREAMING::HAS_MODEL_LOADED(MISC::GET_HASH_KEY("vw_prop_vw_colle_alien"))) {
								std::this_thread::sleep_for(0ms);
							}
							else {
								Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(iPed, FALSE);
								OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, playerPosition.x, playerPosition.y, playerPosition.z + 0.5f / 10, 0, 2000, MISC::GET_HASH_KEY("vw_prop_vw_colle_alien"), FALSE, TRUE);
								STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(MISC::GET_HASH_KEY("vw_prop_vw_colle_alien"));
							}
						}
					});
				core->add_option<simple_option>("Network Bail Kick", nullptr, []
					{
						g_fiber_pool->queue_job([]
							{
								const size_t arg_count = 3;
								int64_t args[arg_count] =
								{
									(int64_t)1674887089,
									(int64_t)PLAYER::PLAYER_ID(),
									*script_global(1892703).at(g_pointers->m_net_game_player(selected_player)->m_player_id, 599).at(510).as<int64_t*>()
								};

								g_pointers->m_trigger_script_event(1, args, arg_count, 1 << g_pointers->m_net_game_player(selected_player)->m_player_id);
							});
					});
				core->add_option<simple_option>(("Desync Kick"), nullptr, []
					{
						auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player);// get the ped
						auto player = (CNetGamePlayer*)g_pointers->m_net_game_player(selected_player); //get the players net player via cnetgameplayer

						if (g_pointers->m_network_player_mgr && *g_pointers->m_network_player_mgr && ENTITY::DOES_ENTITY_EXIST(ped), g_pointers->m_net_game_player(selected_player)) // add our checks
						{
							(*g_pointers->m_network_player_mgr)->RemovePlayer(player); //remove him
							WEAPON::REMOVE_ALL_PED_WEAPONS(ped, TRUE);//update him
						}
					});
            });
    }

    void network_selected_kicks_menu::script_init() {}

    void network_selected_kicks_menu::script_on_tick()
    {
        
    }

    void network_selected_kicks_menu::script_func()
    {
        m_network_selected_kicks_menu.script_init();
        while (true)
        {


            m_network_selected_kicks_menu.script_on_tick();
            script::get_current()->yield();
        }
    }
}