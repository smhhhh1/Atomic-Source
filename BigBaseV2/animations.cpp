#include "common.hpp"
#include "gta_util.hpp"
#include "animations.h"
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

	std::array<const char*, 11> m_animations = { "Pole Dance","Crouch Walking","Crazy Dancing","Dirty Dancing","Dog Sit", "Sit ups","Mime","Hands Up","Wave Arms","Meditate","No Way" };
	std::array<const char*, 11> m_animationId = { "mini@strip_club@pole_dance@pole_dance3", "move_weapon@rifle@generic", "misschinese2_crystalmazemcs1_ig", "oddjobs@assassinate@multi@yachttarget@lapdance", "creatures@dog@move", "amb@world_human_sit_ups@male@base","special_ped@mime@monologue_8@monologue_8a", "random@arrests", "random@car_thief@victimpoints_ig_3", "rcmcollect_paperleadinout@", "gestures@m@standing@fat" };
	std::array<const char*, 11> m_animationDict = { "pd_dance_03", "walk_crouch", "dance_loop_tao", "yacht_ld_f", "sit_loop", "base", "08_ig_1_wall_ba_0", "idle_2_hands_up", "arms_waving", "meditiate_idle", "gesture_no_way" };
	void animations_menu::menu()
	{
		using namespace ui;

		

		m_renderer.new_sub<sub>("Animations", SubAnimations, [](sub* core)
			{
				core->add_option<simple_option>(("Stop Animation"),
					nullptr,
					[] {
						TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID()); TASK::CLEAR_PED_TASKS(PLAYER::PLAYER_PED_ID());
				});
				core->add_option<break_option>(std::move(break_option().
					SetRightText("Animations")
				));
				for (int i = 0; i < m_animations.size(); i++)
				{
					core->add_option<simple_option>(m_animations[i],
						nullptr,
						[=] {
							g_fiber_pool->queue_job([=] {
								STREAMING::REQUEST_ANIM_SET(m_animationDict[i]);
								STREAMING::REQUEST_ANIM_DICT(m_animationId[i]);
								});

							TASK::TASK_PLAY_ANIM(PLAYER::PLAYER_PED_ID(), m_animationId[i], m_animationDict[i], 8.f, 8.f, -1, 1, 1, 0, 0, 0);
					});
				}
			});
	}

	void animations_menu::script_init() {}

	void animations_menu::script_on_tick() {}

	void animations_menu::script_func()
	{
		m_animations_menu.script_init();
		while (true)
		{
			m_animations_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}