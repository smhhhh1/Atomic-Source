#include "common.hpp"
#include "gta_util.hpp"
#include "network_toolkit.h"
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
#include "xorstr.h"
#include "network_spoofing_rid.h"
using namespace big::network::toolkit::vars;


namespace big::network::toolkit::vars
{
    variables m_vars;
}

namespace big::menu
{

    void network_toolkit_menu::menu()
    {
        using namespace ui;

        m_renderer.new_sub<sub>("Toolkit", SubNetworkToolkit, [](sub* core)
            {
                m_renderer.m_enable_player_info = false;

                core->add_option<toggle_option<bool>>(XOR("Randomize Player Names"),
                    nullptr,
                    &m_vars.m_streamer_mode
                );

                core->add_option<toggle_option<bool>>(XOR("Peer Token Correction"),
                    nullptr,
                    &m_vars.m_peer_token_correction
                );

                core->add_option<toggle_option<bool>>(XOR("Peer Token Corruption"),
                    nullptr,
                    &m_vars.m_peer_token_corruption
                );

                core->add_option<toggle_option<bool>>(XOR("Force Session Host"),
                    nullptr,
                    &m_vars.m_force_script_host
                );

            });
    }

    void network_toolkit_menu::script_init() {}

    void network_toolkit_menu::script_on_tick()
    {
        static bool bLastForceHost = false;
        if (bLastForceHost != m_vars.m_force_script_host && gta_util::get_network()->m_game_session_state == 0)
        {
            std::uint64_t host_token;
            g_pointers->m_generate_uuid(&host_token);

            host_token = m_vars.m_force_script_host ? (rand() % 10000) : host_token;

            *g_pointers->m_host_token = host_token;

            if (gta_util::get_network()->m_game_session_ptr)
                gta_util::get_network()->m_game_session_ptr->m_local_player.m_player_data.m_host_token = host_token;

            g_pointers->m_profile_gamer_info->m_host_token = host_token;
            g_pointers->m_player_info_gamer_info->m_host_token = host_token;
            (*g_pointers->m_communications)->m_voice.m_connections[0]->m_gamer_info.m_host_token = host_token;

            if (gta_util::get_local_ped() && gta_util::get_local_ped()->m_player_info)
                gta_util::get_local_ped()->m_player_info->m_net_player_data.m_host_token = host_token;

            bLastForceHost = m_vars.m_force_script_host;
        }

        if (network::spoofing::rid::vars::m_vars.rockstar_id != network::spoofing::rid::vars::m_vars.applied_spoof_rockstar_id && gta_util::get_network()->m_game_session_state == 0)
        {
            network::spoofing::rid::vars::m_vars.applied_spoof_rockstar_id = network::spoofing::rid::vars::m_vars.m_spoof;
        }

        if (network::spoofing::rid::vars::m_vars.m_spoof != network::spoofing::rid::vars::m_vars.should_spoof_rockstar_id && gta_util::get_network()->m_game_session_state == 0)
        {
            network::spoofing::rid::vars::m_vars.should_spoof_rockstar_id = network::spoofing::rid::vars::m_vars.m_spoof;
        }
    }

    void network_toolkit_menu::script_func()
    {
        m_network_toolkit_menu.script_init();
        while (true)
        {
            m_network_toolkit_menu.script_on_tick();
            script::get_current()->yield();
        }
    }
}