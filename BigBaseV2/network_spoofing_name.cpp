#include "common.hpp"
#include "gta_util.hpp"
#include "network_spoofing_name.h"
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
#include "keyboard_option.h"

using namespace big::network::spoofing::name::vars;


namespace big::network::spoofing::name::vars
{
	variables m_vars;

	bool active;

	void spoof()
	{

		MISC::DISPLAY_ONSCREEN_KEYBOARD(true, (char*)"Input", (char*)"", (char*)"", (char*)"", (char*)"", (char*)"", 20);
		while (MISC::UPDATE_ONSCREEN_KEYBOARD() == 0)
		{
			active = true;
			m_renderer.ResetInput();
			script::get_current()->yield();
		}
		active = false;
		if (!MISC::GET_ONSCREEN_KEYBOARD_RESULT())
			return;
		m_vars.m_name = MISC::GET_ONSCREEN_KEYBOARD_RESULT();
	}
}

namespace big::menu
{



	void network_spoofing_name_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Name", SubNetworkSpoofingName, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				core->add_option<keyboard>(std::move(keyboard()
					.SetLeftText("Input Name: ").SetRightText(m_vars.m_name.c_str())
					.SetAction(spoof))
					);

				core->add_option<simple_option>(("Reset to Default"), nullptr, [=]
					{
						m_vars.m_spoof = false;
					});

				core->add_option<simple_option>(("Apply"), nullptr, [=]
					{
						m_vars.m_spoof = true;
					});
			});
	}

	void network_spoofing_name_menu::script_init() {}

	void network_spoofing_name_menu::script_on_tick() {}

	void network_spoofing_name_menu::script_func()
	{
		m_network_spoofing_name_menu.script_init();
		while (true)
		{
			m_network_spoofing_name_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}