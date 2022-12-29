#include "common.hpp"
#include "gta_util.hpp"
#include "network_selected_player.h"
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
#include "network_selected_spawner.h"
using namespace big::network::selected_player::vars;


namespace big::network::selected_player::vars
{
    variables m_vars;
}

namespace big::menu
{


    void network_selected_player_menu::menu()
    {
        using namespace ui;

        m_renderer.new_sub<PlayerSubmenu>(&selected_player, SubSelectedPlayer, [](PlayerSubmenu* core)
            {
                m_renderer.m_enable_player_info = true;
                core->add_option<submenu>("Friendly", nullptr, SubSelectedFriendly);
                core->add_option<submenu>("Teleport", nullptr, SubSelectedTeleport);
                core->add_option<submenu>("Text Message", nullptr, SubSelectedText);
                core->add_option<submenu>("Abusive", nullptr, SubSelectedAbusive);
                core->add_option<submenu>("Trolling", nullptr, SubSelectedTrolling);
                core->add_option<submenu>("Kicks", nullptr, SubSelectedKicks);
                core->add_option<submenu>("Crashes", nullptr, SubSelectedCrashes);
                core->add_option<submenu>("Spawner", nullptr, SubSelectedSpawner);
                core->add_option<submenu>("Vehicle", nullptr, SubSelectedVehicle);
                core->add_option<submenu>("ESP", nullptr, SubSelectedESP);
               
                core->add_option<toggle_option<bool>>(("Spectate"),
                    nullptr, 
                    &m_vars.m_spectate
                );

                core->add_option<simple_option>(("View Profile"), nullptr, []
                    {
                        if (*g_pointers->m_is_session_started) {
                            if (NETWORK::NETWORK_IS_SESSION_ACTIVE) {
                                auto net_player = (CNetGamePlayer*)g_pointers->m_net_game_player(selected_player);
                                auto rid = net_player->get_net_data()->m_gamer_handle_2.m_rockstar_id;
                                if (rid > 0)
                                {
                                    int netHandle[13];
                                    NETWORK::NETWORK_HANDLE_FROM_MEMBER_ID(std::to_string(rid).c_str(), netHandle, 13);
                                    NETWORK::NETWORK_SHOW_PROFILE_UI(netHandle);
                                }
                            }
                        }
                    });
            });
    }

    void network_selected_player_menu::script_init() {}

    void network_selected_player_menu::script_on_tick()
    {
        const auto target = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player);
        if (m_vars.m_spectate) {

            NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(true, target);
            HUD::SET_MINIMAP_IN_SPECTATOR_MODE(true, target);

            ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), true);
            ENTITY::FREEZE_ENTITY_POSITION(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), true);

            STREAMING::SET_FOCUS_ENTITY(target);
        }
        else {
            NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(false, -1);
            HUD::SET_MINIMAP_IN_SPECTATOR_MODE(false, -1);

            ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), false);
            ENTITY::FREEZE_ENTITY_POSITION(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), false);

            STREAMING::SET_FOCUS_ENTITY(PLAYER::PLAYER_PED_ID());
        }
    }

    void network_selected_player_menu::script_func()
    {
        m_network_selected_player_menu.script_init();
        while (true)
        {
           

            m_network_selected_player_menu.script_on_tick();
            script::get_current()->yield();
        }
    }
}