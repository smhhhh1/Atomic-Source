#include "common.hpp"
#include "gta_util.hpp"
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
#include "network_spoofing_crew.h"
namespace big::menu
{


	void network_spoofing_crew_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Crew", SubNetworkCrew, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;

				core->add_option<submenu>("Crew Name",
					nullptr,
					SubNetworkCrewName
				);

				core->add_option<submenu>("Crew Tag",
					nullptr,
					SubNetworkCrewTag
				);

				core->add_option<submenu>("Crew Icon",
					nullptr,
					SubNetworkCrewIcon
				);
			});
	}

	void network_spoofing_crew_menu::script_init() {}

	void network_spoofing_crew_menu::script_on_tick() {}

	void network_spoofing_crew_menu::script_func()
	{
		m_network_spoofing_crew_menu.script_init();
		while (true)
		{
			m_network_spoofing_crew_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}