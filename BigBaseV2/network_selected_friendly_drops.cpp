#include "common.hpp"
#include "gta_util.hpp"
#include "network_selected_friendly_drops.h"
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
#include <timeapi.h>
#pragma comment (lib, "winmm.lib")
using namespace big::network::selected_player::friendly::drops::vars;


namespace big::network::selected_player::friendly::drops::vars
{
    variables m_vars;
	const char* drop_type[] = {
	   "Money", "Rp"
	}; std::size_t drop_type_id = 0;
}

namespace big::menu
{


    void network_selected_friendly_drops_menu::menu()
    {
        using namespace ui;

        m_renderer.new_sub<PlayerSubmenu>(&selected_player, SubSelectedFriendlyDrops, [](PlayerSubmenu* core)
            {
                m_renderer.m_enable_player_info = true;

				core->add_option<scroll_option<const char*, std::size_t>>("Drop Type", nullptr, &drop_type, &drop_type_id, false);

				switch (drop_type_id) {
				case 0:
					core->add_option<toggle_option<bool>>(("Drop Money"), nullptr, &m_vars.m_money_drop);
					core->add_option<number_option<int>>(("Drop Delay"), nullptr, &m_vars.m_money_drop_delay, 0, 300, 10, 1, false);
					break;
				case 1:
					core->add_option<toggle_option<bool>>(("Drop Rp"), nullptr, &m_vars.m_rp_drop);
					core->add_option<number_option<int>>(("Drop Delay"), nullptr, &m_vars.m_rp_drop_delay, 0, 300, 10, 1, false);
					break;
				}


            });
    }

    void network_selected_friendly_drops_menu::script_init() {}

    void network_selected_friendly_drops_menu::script_on_tick()
    {
		if (m_vars.m_money_drop) {

			Player p = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player);
			if ((timeGetTime() - m_vars.m_money_delay) > m_vars.m_money_drop_delay) // Time between drops
			{
				float dx = coordsOf(p).x;
				float dy = coordsOf(p).y;
				float dz = coordsOf(p).z;
				float randX = rndInt(-2, 2);
				float randY = rndInt(-2, 2);
				float randZ = rndInt(-2, 2);
				float offsetX = dx + randX;
				float offsetY = dy + randY;
				float offsetZ = dz + randZ;
				STREAMING::REQUEST_MODEL(-1666779307);
				if (!STREAMING::HAS_MODEL_LOADED(-1666779307)) {
					script::get_current()->yield();
				}
				else {
					*g_pointers->should_sync_money_rewards = true;
					*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
					OBJECT::CREATE_AMBIENT_PICKUP(1704231442, coordsOf(p).x, coordsOf(p).y, coordsOf(p).z + 30, 1, 2500, -1666779307, false, true);
					*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;
					*g_pointers->should_sync_money_rewards = false;
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(-1666779307);

					m_vars.m_money_delay = timeGetTime();
				}
			}

		}
		else if (m_vars.m_rp_drop) {
			Player p = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player);
			if ((timeGetTime() - m_vars.m_rp_drop_delay) > 300) // Time between drops
			{
				float dx = coordsOf(p).x;
				float dy = coordsOf(p).y;
				float dz = coordsOf(p).z;
				float randX = rndInt(-2, 2);
				float randY = rndInt(-2, 2);
				float randZ = rndInt(-2, 2);
				float offsetX = dx + randX;
				float offsetY = dy + randY;
				float offsetZ = dz + randZ;
				STREAMING::REQUEST_MODEL($("vw_prop_vw_colle_alien"));
				if (!STREAMING::HAS_MODEL_LOADED($("vw_prop_vw_colle_alien"))) {
					script::get_current()->yield();
				}
				else {
					*g_pointers->should_sync_money_rewards = true;
					*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
					OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coordsOf(p).x, coordsOf(p).y, coordsOf(p).z + 30, 0, 10, $("vw_prop_vw_colle_alien"), false, true);
					*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;
					*g_pointers->should_sync_money_rewards = false;
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED($("vw_prop_vw_colle_alien"));

					m_vars.m_rp_delay = timeGetTime();
				}
			}
		}
    }

    void network_selected_friendly_drops_menu::script_func()
    {
        m_network_selected_friendly_drops_menu.script_init();
        while (true)
        {
            m_network_selected_friendly_drops_menu.script_on_tick();
            script::get_current()->yield();
        }
    }
}