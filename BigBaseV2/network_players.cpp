#include "common.hpp"
#include "gta_util.hpp"
#include "network_players.h"
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


namespace big::menu
{


    void network_players_menu::menu()
    {
        using namespace ui;

		m_renderer.new_sub<sub>(("Players"), SubPlayers, [](sub* core)
			{
                m_renderer.m_enable_player_info = false;
				for (std::uint32_t i = 0; i < 32; ++i)
				{
					if (auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))
					{
                        core->add_option<submenu>(PLAYER::GET_PLAYER_NAME(i), nullptr, SubSelectedPlayer, [=]
							{
								selected_player = i;
							});
					}
				}
			});
    }

    void network_players_menu::script_init() {}

    void network_players_menu::script_on_tick()
    {

    }

    void network_players_menu::script_func()
    {
        m_network_players_menu.script_init();
        while (true)
        {
            m_network_players_menu.script_on_tick();
            script::get_current()->yield();
        }
    }
}