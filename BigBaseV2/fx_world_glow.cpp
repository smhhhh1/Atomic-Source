#include "common.hpp"
#include "gta_util.hpp"
#include "fx_world_glow.h"
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
#include "vfx_types.h"
using namespace big::game_fx::world_glow::vars;


namespace big::game_fx::world_glow::vars
{
	variables m_vars;

	void rgb()
	{
		if (m_vars.red > 0 && m_vars.blue == 0) {
			m_vars.red--;
			m_vars.green++;
		}
		if (m_vars.green > 0 && m_vars.red == 0) {
			m_vars.green--;
			m_vars.blue++;
		}
		if (m_vars.blue > 0 && m_vars.green == 0) {
			m_vars.red++;
			m_vars.blue--;
		}
	}
}
namespace big::menu
{
	void game_fx_world_glow_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("World Glow", SubGameFxWorldGlow, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				core->add_option<toggle_option<bool>>("Toggle",
					nullptr, 
					& m_vars.m_toggle
				);
				core->add_option<toggle_option<bool>>(("Rainbow"),
					nullptr, 
					&m_vars.m_rainbow
				);
				core->add_option<break_option>(std::move(break_option()
					.SetRightText("Colors"))
				);

				core->add_option<number_option<int>>(("Red"),
					nullptr,
					&m_vars.red, 1, 255,
					5, 1, false
				);
				core->add_option<number_option<int>>(("Green"),
					nullptr, 
					&m_vars.green, 1, 255,
					5, 1, false
				);
				core->add_option<number_option<int>>(("Blue"),
					nullptr, 
					&m_vars.blue, 1, 255,
					5, 1, false
				);
				core->add_option<number_option<float>>(("Luminance"),
					nullptr,
					&m_vars.m_intensity, 1, 100,
					1, 1, false
					);
			});
	}

	void game_fx_world_glow_menu::script_init() {}

	void game_fx_world_glow_menu::script_on_tick()
	{
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), FALSE);
		if (m_vars.m_toggle) {
			if (m_vars.m_rainbow) {
				rgb();
				GRAPHICS::DRAW_LIGHT_WITH_RANGE(coords.x, coords.y, coords.z, m_vars.red, m_vars.green, m_vars.blue, 1000, m_vars.m_intensity);
			}
			else {
				GRAPHICS::DRAW_LIGHT_WITH_RANGE(coords.x, coords.y, coords.z, m_vars.red, m_vars.green, m_vars.blue, 1000, m_vars.m_intensity);
			}

		}
	}

	void game_fx_world_glow_menu::script_func()
	{
		m_game_fx_world_glow_menu.script_init();
		while (true)
		{
			m_game_fx_world_glow_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}