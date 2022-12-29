#include "common.hpp"
#include "gta_util.hpp"
#include "scenario.h"
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

	std::array<const char*, 11> m_scenariosName = { "WORLD_HUMAN_PAPARAZZI", "WORLD_HUMAN_DRUG_DEALER_HARD", "WORLD_HUMAN_AA_COFFEE", "WORLD_HUMAN_MUSICIAN", "WORLD_HUMAN_MUSCLE_FLEX", "WORLD_HUMAN_JOG_STANDING", "WORLD_HUMAN_BINOCULARS", "WORLD_HUMAN_CLIPBOARD", "PROP_HUMAN_SEAT_MUSCLE_BENCH_PRESS", "PROP_HUMAN_MUSCLE_CHIN_UPS", "PROP_HUMAN_BBQ" };
	std::array<const char*, 11> m_scenarios = { "Paparazzi", "Drug Dealer", "Coffee", "Play Instrument", "Flexing", "Jogging", "Binoculars", "Clipboard", "Bench Press", "Chin ups", "BBQ" };
	void scenario_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Scenarios", SubScenarios, [](sub* core)
			{
				core->add_option<simple_option>(("Stop Scenario"), nullptr, [=] {
					TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
				});
				core->add_option<break_option>(std::move(break_option()
					.SetRightText("Scenarios")
				));
				for (int i = 0; i < m_scenarios.size(); i++)
				{
					core->add_option<simple_option>(m_scenarios[i], nullptr, [=]
						{
							TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), m_scenariosName[i], 0, true);
						});
				}
			});		
	}

	void scenario_menu::script_init() {}

	void scenario_menu::script_on_tick() {}

	void scenario_menu::script_func()
	{
		m_scenario_menu.script_init();
		while (true)
		{
			m_scenario_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}