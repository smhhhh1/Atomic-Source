#include "common.hpp"
#include "gta_util.hpp"
#include "protections_presence.h"
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
#include "scroll.h"
#include "xorstr.h"	
#include "player_service.hpp"
#include "script_global.hpp"
#include <nlohmann/json.hpp>
#include "json.h"
using namespace big::protections::presence::vars;

namespace big::protections::presence::vars {

	
}

namespace big::menu
{

	void protections_presence_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Presence Events", SubProtectionsPresence, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				core->add_option<scroll_option<const char*, std::size_t>>(("Text Message"), nullptr, &lists::text_message, &lists::text_message_pos, true);
				core->add_option<scroll_option<const char*, std::size_t>>(("Crew Message"), nullptr, &lists::crew_message, &lists::crew_message_pos, true);
				core->add_option<scroll_option<const char*, std::size_t>>(("Game Invite"), nullptr, &lists::game_invite, &lists::game_invite_pos, true);
				core->add_option<scroll_option<const char*, std::size_t>>(("Game Server Rewards"), nullptr, &lists::game_server_rewards, &lists::game_server_rewards_pos, true);
				core->add_option<scroll_option<const char*, std::size_t>>(("Admin Invite"), nullptr, &lists::admin_invite, &lists::admin_invite_pos, true);
				core->add_option<scroll_option<const char*, std::size_t>>(("Stat Update"), nullptr, &lists::stat_update, &lists::stat_update_pos, true);
			});
	}

	void protections_presence_menu::script_init() {}

	void protections_presence_menu::script_on_tick()
	{


	}

	void protections_presence_menu::script_func()
	{
		m_protections_presence_menu.script_init();
		while (true)
		{
			m_protections_presence_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}