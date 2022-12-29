#include "common.hpp"
#include "gta_util.hpp"
#include "protections_network_events.h"
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
using namespace big::protections::network_events::vars;

namespace big::protections::network_events::vars {

	variables m_vars;

}

namespace big::menu
{

	void protections_network_events_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Network Events", SubProtectionsNetworkEvents, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;

				core->add_option<simple_option>("Enable All", nullptr, []
					{
						lists::explosion_event_id = 2;
						lists::freeze_event_id = 2;
						lists::ptfx_event_id = 2;
						lists::ragdoll_event_id = 2;
						lists::remove_weapons_event_id = 2;
						lists::remove_all_weapons_event_id = 2;
						lists::request_control_event_id = 2;
						lists::give_control_event_id = 2;
					});

				core->add_option<simple_option>("Disable All", nullptr, []
					{
						lists::explosion_event_id = 0;
						lists::freeze_event_id = 0;
						lists::ptfx_event_id = 0;
						lists::ragdoll_event_id = 0;
						lists::remove_weapons_event_id = 0;
						lists::remove_all_weapons_event_id = 0;
						lists::request_control_event_id = 0;
						lists::give_control_event_id = 0;
					});

				core->add_option<break_option>(std::move(break_option()
					.SetRightText("Events"))
				);

				core->add_option<scroll_option<const char*, std::size_t>>(XOR("Explosions"), nullptr,
					&lists::explosion_event, &lists::explosion_event_id,
					true
				);

				core->add_option<scroll_option<const char*, std::size_t>>(XOR("Freeze"), nullptr,
					&lists::freeze_event, &lists::freeze_event_id,
					true
				);

				core->add_option<scroll_option<const char*, std::size_t>>(XOR("Ptfx"), nullptr,
					&lists::ptfx_event, &lists::ptfx_event_id,
					true
				);

				core->add_option<scroll_option<const char*, std::size_t>>(XOR("Ragdoll"), nullptr,
					&lists::ragdoll_event, &lists::ragdoll_event_id,
					true
				);

				core->add_option<scroll_option<const char*, std::size_t>>(XOR("Remove Weapons"), nullptr,
					&lists::remove_weapons_event, &lists::remove_weapons_event_id,
					true
				);

				core->add_option<scroll_option<const char*, std::size_t>>(XOR("Remove All Weapons"), nullptr,
					&lists::remove_all_weapons_event, &lists::remove_all_weapons_event_id,
					true
				);

				core->add_option<scroll_option<const char*, std::size_t>>(XOR("Request Control"), nullptr,
					&lists::request_control_event, &lists::request_control_event_id,
					true
				);

				core->add_option<scroll_option<const char*, std::size_t>>(XOR("Give Control"), nullptr,
					&lists::give_control_event, &lists::give_control_event_id,
					true
				);
			
			});
	}

	void protections_network_events_menu::script_init() {}

	void protections_network_events_menu::script_on_tick() {}

	void protections_network_events_menu::script_func()
	{
		m_protections_network_events_menu.script_init();
		while (true)
		{
			m_protections_network_events_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}