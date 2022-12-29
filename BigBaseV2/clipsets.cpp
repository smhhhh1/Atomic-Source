#include "common.hpp"
#include "gta_util.hpp"
#include "clipsets.h"
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

	std::array<const char*, 27> m_styles = { "Generic Male", "Generic Female", "Cop", "Gangster", "Hipster", "Hobo", "Fat", "Lester", "Drunk", "Sexy", "Alien", "Business", "Casual", "Clipboard", "Coward", "On Fire", "Fleeing", "Hiking", "Hurried", "Injured", "Intimidating", "Muscle", "Quick", "Sad", "Shady", "Shocked", "Arrogant" };
	std::array<const char*, 27> m_styleId = { "move_m@generic" ,"move_f@generic","move_cop@action","move_m@gangster@generic", "move_m@hipster@a" ,"move_m@hobo@a","move_m@fat@a","move_lester_CaneUp","move_m@drunk@a","move_f@sexy@a","move_m@alien", "move_m@business@a","move_m@casual@a",	"move_m@clipboard","move_m@coward","move_m@fire", "move_m@flee@a","move_m@hiking","move_m@hurry@a","move_injured_generic","move_m@intimidation@1h", "move_m@muscle@a", "move_m@quick", "move_m@sad@a","move_m@shadyped@a","move_m@shocked@a", "move_f@arrogant@a" };
	void clipsets_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Clipsets", SubClipsets, [](sub* core)
			{
				for (int i = 0; i < m_styles.size(); i++)
				{
					core->add_option<simple_option>(m_styles[i], nullptr, [=]
						{
							g_fiber_pool->queue_job([=] {STREAMING::REQUEST_ANIM_SET(m_styleId[i]); });
							STREAMING::HAS_ANIM_SET_LOADED(m_styleId[i]);
							PED::SET_PED_MOVEMENT_CLIPSET(PLAYER::PLAYER_PED_ID(), m_styleId[i], 1.0f);
						});
				}
			});
	}

	void clipsets_menu::script_init() {}

	void clipsets_menu::script_on_tick() {}

	void clipsets_menu::script_func()
	{
		m_clipsets_menu.script_init();
		while (true)
		{
			m_clipsets_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}