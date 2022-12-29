#include "common.hpp"
#include "gta_util.hpp"
#include "network_recovery_rank.h"
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
#include "levels.h"
#include "xorstr.h"

namespace
{
	int rank_value;
	bool active = false;

	void SetRank(int rpvalue)
	{
		if (rpvalue < 0 && rpvalue > 8000)
		{
			rpvalue = 8000;
		}
		STATS::STAT_SET_INT(rage::joaat("MP0_CHAR_SET_RP_GIFT_ADMIN"), big::menu::Levels[rpvalue], 0);
		STATS::STAT_SET_INT(rage::joaat("MP1_CHAR_SET_RP_GIFT_ADMIN"), big::menu::Levels[rpvalue], 0);

	}
	void set_rank()
	{

		MISC::DISPLAY_ONSCREEN_KEYBOARD(true, (char*)"Input", (char*)"", (char*)"", (char*)"", (char*)"", (char*)"", 20);
		while (MISC::UPDATE_ONSCREEN_KEYBOARD() == 0)
		{
			active = true;
			big::m_renderer.ResetInput();
			big::script::get_current()->yield();
		}
		active = false;
		if (!MISC::GET_ONSCREEN_KEYBOARD_RESULT())
			return;

		rank_value = std::atoi(MISC::GET_ONSCREEN_KEYBOARD_RESULT());
		SetRank(rank_value);
	}
}

namespace big::menu
{
	void network_recovery_rank_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Rank", SubRecoveryRank, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				core->add_option<keyboard>(std::move(keyboard()
					.SetLeftText("Input Rank: ").SetRightText(std::to_string(rank_value).c_str())
					.SetAction(set_rank)));
				core->add_option<break_option>(std::move(break_option().
					SetRightText("Presets"))
				);
				core->add_option<simple_option>(XOR("100"), "100 kids in my garage", [] {
					SetRank(100);
					});
				core->add_option<simple_option>(XOR("120"), "120 hoes in my basement", [] {
					SetRank(120);
					});
				core->add_option<simple_option>(XOR("420"), "dank memer", [] {
					SetRank(420);
					});
				core->add_option<simple_option>(XOR("666"), "sex sex sex", [] {
					SetRank(666);
					});
				core->add_option<simple_option>(XOR("1000"), "1000 bitches that i dont have", [] {
					SetRank(1000);
					});
				core->add_option<simple_option>(XOR("1337"), "haxxer man", [] {
					SetRank(1337);
					});
				core->add_option<simple_option>(XOR("6666"), "devil man", [] {
					SetRank(6666);
					});
				core->add_option<simple_option>(XOR("8000"), "modder man", [] {
					SetRank(8000);
					});
			});
	}

	void network_recovery_rank_menu::script_init() {}

	void network_recovery_rank_menu::script_on_tick() {}

	void network_recovery_rank_menu::script_func()
	{
		m_network_recovery_rank_menu.script_init();
		while (true)
		{
			m_network_recovery_rank_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}