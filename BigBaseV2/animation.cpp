#include "common.hpp"
#include "gta_util.hpp"
#include "animation.h"
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
namespace big::menu
{


	void animation_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Animation", SubAnimation, [](sub* core)
			{	
				core->add_option<submenu>("Animations", nullptr, SubAnimations);
				core->add_option<submenu>("Scenarios", nullptr, SubScenarios);
				core->add_option<submenu>("Clipsets", nullptr, SubClipsets);
			});
	}

	void animation_menu::script_init() {}

	void animation_menu::script_on_tick() {}

	void animation_menu::script_func()
	{
		m_animation_menu.script_init();
		while (true)
		{
			m_animation_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}