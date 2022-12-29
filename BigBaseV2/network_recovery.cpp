#include "common.hpp"
#include "gta_util.hpp"
#include "network_recovery.h"
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


	void network_recovery_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Recovery", SubNetworkRecovery, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				core->add_option<submenu>(("Rank"), nullptr, SubRecoveryRank);
				core->add_option<submenu>(("Unlocks"), nullptr, SubRecoveryUnlocks);
				core->add_option<submenu>(("Stats"), nullptr, SubRecoveryStats);
				//core->add_option<submenu>(("Casino Heist"), nullptr, SubRecoveryCasinoHeist);
				core->add_option<submenu>(("Miscellaneous"), nullptr, SubRecoveryMisc);
				core->add_option<simple_option>(("Redesign Character"), nullptr, []
					{

						STATS::STAT_SET_BOOL(rage::joaat("MP0_FM_CHANGECHAR_ASKED"), 0, true);
					});
				core->add_option<simple_option>(("Reset Mental State"), nullptr, []
					{

						STATS::STAT_SET_FLOAT(rage::joaat("PLAYER_MENTAL_STATE"), 0.0f, true);
					});
			});
	}

	void network_recovery_menu::script_init() {}

	void network_recovery_menu::script_on_tick() {}

	void network_recovery_menu::script_func()
	{
		m_network_recovery_menu.script_init();
		while (true)
		{
			m_network_recovery_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}