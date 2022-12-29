#include "common.hpp"
#include "gta_util.hpp"
#include "network.h"
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
#include "network_selected_player.h"
#include "network_selected_friendly.h"
#include "network_selected_friendly_drops.h"
#include "network_selected_abusive.h"
#include "network_selected_abusive_increment.h"
#include "network_selected_trolling.h"
#include "network_selected_trolling_entity_spammer.h"
#include "network_selected_esp.h"
#include "network_selected_vehicle.h"
#include "network_recent_players.h"
#include "network_spoofing.h"
#include "network_toolkit.h"
#include "players.h"
#include "script_patcher_service.hpp"
namespace big::menu
{


	void network_menu::menu()
	{
		using namespace ui;
		
		m_renderer.new_sub<sub>("Network", SubNetwork, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;

				core->add_option<submenu>("Players",
					nullptr,
					SubPlayers
				);

				core->add_option<submenu>("Friends",
					nullptr,
					SubNetworkFriends
				);

				core->add_option<submenu>("Spoofing",
					nullptr,
					SubNetworkSpoofing
				);

				core->add_option<submenu>("Recent Players",
					nullptr,
					SubNetworkRecentPlayers
				);

				/*core->add_option<submenu>("Player Search",
					nullptr,
					SubNetworkPlayerSearch
				);*/

				core->add_option<submenu>("Services",
					nullptr,
					SubNetworkServices
				);

				core->add_option<submenu>("Toolkit",
					nullptr,
					SubNetworkToolkit
				);

				core->add_option<submenu>("Notifications",
					nullptr,
					SubNetworkNotifications
				);
			});
	}

	void network_menu::script_init() {
		//std::copy_n("\x0F\x29\x62\x20", 4, g_pointers->m_east_bypass); //restore
	}

	void network_menu::script_on_tick() {}

	
	void network_menu::script_func()
	{
		m_network_menu.script_init();
		while (true)
		{
			m_network_menu.script_on_tick();
			m_network_selected_player_menu.script_on_tick();
			m_network_selected_friendly_menu.script_on_tick();
			m_network_selected_friendly_drops_menu.script_on_tick();
			m_network_selected_abusive_menu.script_on_tick();
			m_network_selected_trolling_menu.script_on_tick();
			m_network_selected_trolling_entity_spammer_menu.script_on_tick();
			m_network_selected_esp_menu.script_on_tick();
			m_network_selected_vehicle_menu.script_on_tick();
			m_network_recent_players_menu.script_on_tick();
			m_network_spoofing_menu.script_on_tick();
			m_network_toolkit_menu.script_on_tick();
			players::update();
			


			script::get_current()->yield();
		}
	}
}