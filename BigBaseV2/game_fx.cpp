#include "common.hpp"
#include "gta_util.hpp"
#include "game_fx.h"
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

using namespace big::game_fx::vars;


namespace big::game_fx::vars
{
	variables m_vars;
}
namespace big::menu
{
	void game_fx_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Game Fx", SubGameFx, [](sub* core)
			{
				m_sky_open = false;
				m_renderer.m_enable_player_info = false;

				core->add_option<submenu>("Sky",
					nullptr,
					SubGameFxSky
				);

				core->add_option<submenu>("Visuals",
					nullptr,
					SubGameFxVisuals
				);

				core->add_option<submenu>("World Glow",
					nullptr,
					SubGameFxWorldGlow
				);

				core->add_option<number_option<float>>(("Fog On Map"), nullptr, &m_vars.m_fog, 0.f, 2.f, 0.00002, 5, true, "", "", [] {
					*(float*)engine::memory::scan_address(g_base_address + 0x19B1D70, {}) = m_vars.m_fog; }
				);
			});
	}

	void game_fx_menu::script_init() {}

	void game_fx_menu::script_on_tick()
	{
		if (m_vars.m_disable_lights) {
			GRAPHICS::SET_ARTIFICIAL_LIGHTS_STATE(m_vars.m_disable_lights);
		}
	}

	void game_fx_menu::script_func()
	{
		m_game_fx_menu.script_init();
		while (true)
		{
			m_game_fx_menu.script_on_tick();

			script::get_current()->yield();
		}
	}
}