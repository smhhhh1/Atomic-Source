#include "common.hpp"
#include "gta_util.hpp"
#include "appearance.h"
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
using namespace big::player::appearance::vars;

namespace big::player::appearance::vars
{
	variables m_vars;
}

namespace big::menu
{
	
	void appearance_menu::menu()
	{
		using namespace ui;


		
		m_renderer.new_sub<sub>("Appearance", SubAppearance, [](sub* core)
			{
				core->add_option<submenu>("Wardrobe", nullptr, SubWardrobe);
				core->add_option<submenu>("Model Changer", nullptr, SubModel);

				core->add_option<break_option>(std::move(break_option()
					.SetRightText("Modifiers")
				));
	
				core->add_option<toggle_number_option<float, bool>>("Width", nullptr, &m_vars.m_width_toggle, &m_vars.m_width, 1.0f, 10.0f, 0.1f, 1);
				core->add_option<toggle_number_option<float, bool>>("Height", nullptr, &m_vars.m_height_toggle, &m_vars.m_height, 1.0f, 10.0f, 0.1f, 1);
				core->add_option<toggle_number_option<float, bool>>("Lean (F/B)", nullptr, &m_vars.m_lean_front_toggle, &m_vars.m_lean_front, 1.0f, 10.0f, 0.1f, 1);
				core->add_option<toggle_number_option<float, bool>>("Lean (L/R)", nullptr, &m_vars.m_lean_left_toggle, &m_vars.m_lean_left, 1.0f, 10.0f, 0.1f, 1);

			});
	}

	void appearance_menu::script_init() {}

	void appearance_menu::script_on_tick()
	{
		if (m_vars.m_height_toggle)
			gta_util::get_local_ped()->m_up.z = m_vars.m_height;

		if (m_vars.m_width_toggle)
			gta_util::get_local_ped()->m_right.x = m_vars.m_width;

		if (m_vars.m_lean_front_toggle)
			gta_util::get_local_ped()->m_up.y = m_vars.m_lean_front;

		if (m_vars.m_lean_left_toggle)
			gta_util::get_local_ped()->m_right.z = m_vars.m_lean_left;
	}

	void appearance_menu::script_func()
	{
		m_appearance_menu.script_init();
		while (true)
		{
			m_appearance_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}