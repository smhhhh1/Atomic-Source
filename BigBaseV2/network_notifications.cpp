#include "common.hpp"
#include "gta_util.hpp"
#include "network_notifications.h"
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
#include "xorstr.h"
using namespace big::network::notifications::vars;


namespace big::network::notifications::vars
{
	variables m_vars;
}

namespace big::menu
{
	void network_notifications_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Notifications", SubNetworkNotifications, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;

				core->add_option<toggle_option<bool>>(("Player Join"),
					nullptr,
					&m_vars.m_player_join
				);

				core->add_option<toggle_option<bool>>(("Player Leave"),
					nullptr,
					&m_vars.m_player_leave
				);

				core->add_option<toggle_option<bool>>(("Session Join"),
					nullptr,
					&m_vars.m_session_join
				);

				core->add_option<toggle_option<bool>>(("Session Leave"),
					nullptr,
					&m_vars.m_session_leave
				);

				core->add_option<toggle_option<bool>>(XOR("Script Host Mitigation"),
					nullptr,
					&m_vars.m_new_script_host
				);

				core->add_option<toggle_option<bool>>(XOR("Player Spawn"),
					nullptr,
					&m_vars.m_player_spawn
				);

				core->add_option<toggle_option<bool>>(XOR("Pickup Processing"),
					nullptr,
					&m_vars.m_pickup_processing
				);

				core->add_option<toggle_option<bool>>(XOR("Desync Kicks"),
					nullptr,
					&m_vars.m_desync_kicks
				);

				core->add_option<toggle_option<bool>>(XOR("Breakup Kicks"),
					nullptr,
					&m_vars.m_breakup_kicks
				);

				core->add_option<toggle_option<bool>>(XOR("Object Created"),
					nullptr,
					&m_vars.m_object_creation
				);

				core->add_option<toggle_option<bool>>(XOR("Ped Created"),
					nullptr,
					&m_vars.m_ped_creation
				);

				core->add_option<toggle_option<bool>>(XOR("Vehicle Created"),
					nullptr,
					&m_vars.m_vehicle_creation
				);

				core->add_option<toggle_option<bool>>(XOR("Pickup Created"),
					nullptr,
					&m_vars.m_pickup_creation
				);

			});
	}

	void network_notifications_menu::script_init() {}

	void network_notifications_menu::script_on_tick()
	{
		
	}

	void network_notifications_menu::script_func()
	{
		m_network_notifications_menu.script_init();
		while (true)
		{
			m_network_notifications_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}