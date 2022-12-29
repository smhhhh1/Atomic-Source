#include "common.hpp"
#include "gta_util.hpp"
#include "network_recovery_misc.h"
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
	void network_recovery_misc_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Misc", SubRecoveryMisc, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				core->add_option<simple_option>(XOR("2 Billion Snacks"), nullptr, []
					{
						STATS::STAT_SET_INT(rage::joaat("MP0_NO_BOUGHT_YUM_SNACKS"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP0_NO_BOUGHT_HEALTH_SNACKS"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP0_NO_BOUGHT_EPIC_SNACKS"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP0_NUMBER_OF_ORANGE_BOUGHT"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP0_CIGARETTES_BOUGHT"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP1_NO_BOUGHT_YUM_SNACKS"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP1_NO_BOUGHT_HEALTH_SNACKS"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP1_NO_BOUGHT_EPIC_SNACKS"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP1_NUMBER_OF_ORANGE_BOUGHT"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP1_CIGARETTES_BOUGHT"), 2000000000, 1);
					});
				core->add_option<simple_option>(XOR("2 Billion Armor"), nullptr, []
					{
						STATS::STAT_SET_INT(rage::joaat("MP0_MP_CHAR_ARMOUR_1_COUNT"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP0_MP_CHAR_ARMOUR_2_COUNT"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP0_MP_CHAR_ARMOUR_3_COUNT"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP0_MP_CHAR_ARMOUR_4_COUNT"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP0_MP_CHAR_ARMOUR_5_COUNT"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP1_MP_CHAR_ARMOUR_1_COUNT"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP1_MP_CHAR_ARMOUR_2_COUNT"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP1_MP_CHAR_ARMOUR_3_COUNT"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP1_MP_CHAR_ARMOUR_4_COUNT"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP1_MP_CHAR_ARMOUR_5_COUNT"), 2000000000, 1);
					});
				core->add_option<simple_option>(XOR("2 Billion Fireworks"), nullptr, []
					{
						STATS::STAT_SET_INT(rage::joaat("MP0_FIREWORK_TYPE_1_WHITE"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP0_FIREWORK_TYPE_1_RED"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP0_FIREWORK_TYPE_1_BLUE"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP0_FIREWORK_TYPE_2_WHITE"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP0_FIREWORK_TYPE_2_RED"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP0_FIREWORK_TYPE_2_BLUE"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP0_FIREWORK_TYPE_3_WHITE"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP0_FIREWORK_TYPE_3_RED"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP0_FIREWORK_TYPE_3_BLUE"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP0_FIREWORK_TYPE_4_WHITE"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP0_FIREWORK_TYPE_4_RED"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP0_FIREWORK_TYPE_4_BLUE"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP1_FIREWORK_TYPE_1_WHITE"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP1_FIREWORK_TYPE_1_RED"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP1_FIREWORK_TYPE_1_BLUE"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP1_FIREWORK_TYPE_2_WHITE"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP1_FIREWORK_TYPE_2_RED"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP1_FIREWORK_TYPE_2_BLUE"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP1_FIREWORK_TYPE_3_WHITE"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP1_FIREWORK_TYPE_3_RED"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP1_FIREWORK_TYPE_3_BLUE"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP1_FIREWORK_TYPE_4_WHITE"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP1_FIREWORK_TYPE_4_RED"), 2000000000, 1);
						STATS::STAT_SET_INT(rage::joaat("MP1_FIREWORK_TYPE_4_BLUE"), 2000000000, 1);
					});
				core->add_option<simple_option>(XOR("Increase Play Time"), nullptr, []
					{
						for (int i = 0; i <= 115; i++) {
							STATS::STAT_INCREMENT(RAGE_JOAAT("MP0_TOTAL_PLAYING_TIME"), INT_MAX);
							STATS::STAT_INCREMENT(RAGE_JOAAT("MP_PLAYING_TIME_NEW"), INT_MAX);
							STATS::STAT_INCREMENT(RAGE_JOAAT("MP_PLAYING_TIME"), INT_MAX);
							STATS::STAT_INCREMENT(RAGE_JOAAT("LEADERBOARD_PLAYING_TIME"), INT_MAX);
							STATS::STAT_SAVE(0, 0, 3);
							STATS::STAT_INCREMENT(RAGE_JOAAT("MP1_TOTAL_PLAYING_TIME"), INT_MAX);
							STATS::STAT_INCREMENT(RAGE_JOAAT("MP_PLAYING_TIME_NEW"), INT_MAX);
							STATS::STAT_INCREMENT(RAGE_JOAAT("MP_PLAYING_TIME"), INT_MAX);
							STATS::STAT_INCREMENT(RAGE_JOAAT("LEADERBOARD_PLAYING_TIME"), INT_MAX);
							STATS::STAT_SAVE(0, 0, 3);
						}
					});
				core->add_option<simple_option>(XOR("Max Singleplayer Money"), nullptr, []
					{
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("SP0_TOTAL_CASH"), INT_MAX, true);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("SP1_TOTAL_CASH"), INT_MAX, true);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("SP2_TOTAL_CASH"), INT_MAX, true);
					});
			});
	}

	void network_recovery_misc_menu::script_init() {}

	void network_recovery_misc_menu::script_on_tick() {}

	void network_recovery_misc_menu::script_func()
	{
		m_network_recovery_misc_menu.script_init();
		while (true)
		{
			m_network_recovery_misc_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}