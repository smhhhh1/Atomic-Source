#include "common.hpp"
#include "gta_util.hpp"
#include "network_spoofing_detection_flags.h"
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
#include "gta/replay.hpp"
#include "script_global.hpp"
#include "../movement.h"
#include "../appearance.h"
#include "../wardrobe.h"
#include "../ptfx.h"
#include "../hand_trails.h"
#include "../proofs.h"
using namespace big::network::spoofing::detection_flags::vars;


namespace big::network::spoofing::detection_flags::vars
{
	variables m_vars;
}

namespace big::menu
{


	void network_spoofing_detection_flags_menu::menu()
	{
		using namespace ui;
		m_renderer.new_sub<sub>("Detection Flags", SubNetworkDetectionFlags, [](sub* core)
			{


				core->add_option<toggle_option<bool>>(("Godmode"),
					nullptr,
					&m_vars.m_godmode
				);

				core->add_option<toggle_option<bool>>(("Superjump"),
					nullptr,
					&m_vars.m_super_jump
				);

				core->add_option<toggle_option<bool>>(("Spectate"),
					nullptr,
					&m_vars.m_spectate
				);

				core->add_option<toggle_option<bool>>(("Health"),
					nullptr,
					&m_vars.m_health
				);

				core->add_option<toggle_option<bool>>(("Armor"),
					nullptr,
					&m_vars.m_armor
				);

				core->add_option<toggle_option<bool>>(("Weapon Damage"),
					nullptr,
					&m_vars.m_weapon_damage
				);

				core->add_option<toggle_option<bool>>(("Melee Damage"),
					nullptr,
					&m_vars.m_melee_damage
				);

				core->add_option<toggle_option<bool>>(("Defense Damage"),
					nullptr,
					&m_vars.m_defense_damage
				);

			});
	}

	void network_spoofing_detection_flags_menu::script_init() {}

	void network_spoofing_detection_flags_menu::script_on_tick() {}

	void network_spoofing_detection_flags_menu::script_func()
	{
		m_network_spoofing_detection_flags_menu.script_init();
		while (true)
		{
			m_network_spoofing_detection_flags_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}