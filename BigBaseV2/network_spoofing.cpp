#include "common.hpp"
#include "gta_util.hpp"
#include "network_spoofing.h"
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
#include "network_spoofing_crew_name.h"

using namespace big::network::spoofing::vars;


namespace big::network::spoofing::vars
{
	variables m_vars;
}

namespace big::menu
{
	void network_spoofing_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Spoofing", SubNetworkSpoofing, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;

				core->add_option<submenu>("Name",
					nullptr,
					SubNetworkSpoofingName
				);

				core->add_option<submenu>("Rockstar Id",
					nullptr,
					SubNetworkSpoofingRid
				);

				core->add_option<submenu>("Ip Address",
					nullptr,
					SubNetworkSpoofingIp
				);

				core->add_option<submenu>("Crew",
					nullptr,
					SubNetworkCrew
				);

				core->add_option<toggle_option<bool>>(("Movement Animation"),
					nullptr,
					&m_vars.m_movement_animation
				);

				core->add_option<toggle_option<bool>>(("Rockstar Developer"),
					"Must Have a Spoofed Scid",
					&m_vars.m_rockstar_dev
				);

			});
	}

	void network_spoofing_menu::script_init() {}

	void network_spoofing_menu::script_on_tick() 
	{
		if (*g_pointers->m_is_session_started) {
			m_vars.m_fake_lag ? *(uint8_t*)g_pointers->m_send_clone_sync = 0xC3
				: *(uint8_t*)g_pointers->m_send_clone_sync = 0x48;
		}	
	}

	void network_spoofing_menu::script_func()
	{
		m_network_spoofing_menu.script_init();
		while (true)
		{
			m_network_spoofing_menu.script_on_tick();
			m_network_spoofing_crew_name_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}