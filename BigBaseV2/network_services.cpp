#include "common.hpp"
#include "gta_util.hpp"
#include "network_services.h"
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
#include "xorstr.h"
#include "script_global.hpp"
namespace big::menu
{


	void network_services_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Services", SubNetworkServices, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				core->add_option<simple_option>(XOR("Request Ammo Crate"), nullptr, [] { *script_global(2815059).at(874).as<int*>() = 1; });
				core->add_option<simple_option>(XOR("Request Airstrike"), nullptr, [] { *script_global(2815059).at(4455).as<int*>() = 1; });
				core->add_option<simple_option>(XOR("Request Heli Pickup"), nullptr, [] { *script_global(2815059).at(876).as<int*>() = 1; });
				core->add_option<simple_option>(XOR("Request Backup Heli Pickup"), nullptr, [] { *script_global(2815059).at(4454).as<int*>() = 1; });
				core->add_option<simple_option>(XOR("Request Bullshark Testosterone"), nullptr, [] { *script_global(2815059).at(822).as<int*>() = 1; });
				core->add_option<simple_option>(XOR("Request Taxi"), nullptr, [] { *script_global(2815059).at(836).as<int*>() = 1; });
				core->add_option<simple_option>(XOR("Request Mini Tank"), nullptr, [] { *script_global(2815059).at(6752).as<int*>() = 1; });
				core->add_option<simple_option>(XOR("Request Rc Bandito"), nullptr, [] { *script_global(2815059).at(6751).as<int*>() = 1; });
				core->add_option<simple_option>(XOR("Request Dingy"), nullptr, [] { *script_global(2815059).at(945).as<int*>() = 1; });
				core->add_option<simple_option>(XOR("Request Terrorbyte"), nullptr, [] { *script_global(2815059).at(925).as<int*>() = 1; });
				core->add_option<simple_option>(XOR("Request Avenger"), nullptr, [] { *script_global(2815059).at(921).as<int*>() = 1; });
				core->add_option<simple_option>(XOR("Request MOC"), nullptr, [] { *script_global(2815059).at(913).as<int*>() = 1; });
				core->add_option<simple_option>(XOR("Request Locate"), nullptr, [] { *script_global(2703735).at(3673).as<int*>() = 1; });
				core->add_option<simple_option>(XOR("Request Ballistic Armor"), nullptr, [] { *script_global(2815059).at(884).as<int*>() = 1; });
				

			});
	}

	void network_services_menu::script_init() {}

	void network_services_menu::script_on_tick() {}

	void network_services_menu::script_func()
	{
		m_network_services_menu.script_init();
		while (true)
		{
			m_network_services_menu.script_on_tick();
			m_network_spoofing_crew_name_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}