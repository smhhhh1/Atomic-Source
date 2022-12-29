#include "common.hpp"
#include "gta_util.hpp"
#include "network_spoofing_ip.h"
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

using namespace big::network::spoofing::ip::vars;


namespace big::network::spoofing::ip::vars
{
	variables m_vars;

	bool active;

	void one()
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
		m_vars.ip_address[0] = std::atoi(MISC::GET_ONSCREEN_KEYBOARD_RESULT());
	}
	void two()
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
		m_vars.ip_address[1] = std::atoi(MISC::GET_ONSCREEN_KEYBOARD_RESULT());
	}
	void three()
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
		m_vars.ip_address[2] = std::atoi(MISC::GET_ONSCREEN_KEYBOARD_RESULT());
	}
	void four()
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
		m_vars.ip_address[3] = std::atoi(MISC::GET_ONSCREEN_KEYBOARD_RESULT());
	}
}

namespace big::menu
{



	void network_spoofing_ip_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Ip Address", SubNetworkSpoofingIp, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				core->add_option<keyboard>(std::move(keyboard()
					.SetLeftText("Input Field 1: ").SetRightText(std::to_string(m_vars.ip_address[0]).c_str())
					.SetAction(one))
					);

				core->add_option<keyboard>(std::move(keyboard()
					.SetLeftText("Input Field 2: ").SetRightText(std::to_string(m_vars.ip_address[1]).c_str())
					.SetAction(two))
					);

				core->add_option<keyboard>(std::move(keyboard()
					.SetLeftText("Input Field 3: ").SetRightText(std::to_string(m_vars.ip_address[2]).c_str())
					.SetAction(three))
					);

				core->add_option<keyboard>(std::move(keyboard()
					.SetLeftText("Input Field 4: ").SetRightText(std::to_string(m_vars.ip_address[3]).c_str())
					.SetAction(four))
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

	void network_spoofing_ip_menu::script_init() {}

	void network_spoofing_ip_menu::script_on_tick() {}

	void network_spoofing_ip_menu::script_func()
	{
		m_network_spoofing_ip_menu.script_init();
		while (true)
		{
			m_network_spoofing_ip_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}