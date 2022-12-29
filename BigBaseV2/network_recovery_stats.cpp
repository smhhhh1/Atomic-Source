#include "common.hpp"
#include "gta_util.hpp"
#include "network_recovery_stats.h"
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
#include "../keyboard_option.h"
#include "../submenus.h"
#include "lists.h"
#include "fiber_pool.hpp"
#include "xorstr.h"

namespace big::menu
{
	void network_recovery_stats_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Stats", SubRecoveryStats, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				core->add_option<simple_option>("Stamina", nullptr, [] {
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STAM"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STAM"), 100, 0);
				});
				core->add_option<simple_option>("Strength", nullptr, [] {
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STRN"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STRN"), 100, 0);
				});
				core->add_option<simple_option>("Lungs", nullptr, [] {
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_LUNG"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_LUNG"), 100, 0);
				});
				core->add_option<simple_option>("Driving", nullptr, [] {
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_DRIV"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_DRIV"), 100, 0);
				});
				core->add_option<simple_option>("Flying", nullptr, [] {
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_FLY"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_FLY"), 100, 0);
				});
				core->add_option<simple_option>("Shooting", nullptr, [] {
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_SHO"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_SHO"), 100, 0);
				});
				core->add_option<simple_option>("Stealth", nullptr, [] {
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STL"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STL"), 100, 0);
				});
			});
	}

	void network_recovery_stats_menu::script_init() {}

	void network_recovery_stats_menu::script_on_tick() {}

	void network_recovery_stats_menu::script_func()
	{
		m_network_recovery_stats_menu.script_init();
		while (true)
		{
			m_network_recovery_stats_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}