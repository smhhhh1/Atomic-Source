#include "common.hpp"
#include "gta_util.hpp"
#include "hand_trails.h"
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
#include "scroll.h"
#include "lists.h"
using namespace big::player::hand_trails::vars;

namespace big::player::hand_trails::vars
{
	variables m_vars;
	void RGBFade()
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

	void hand_trails_menu::menu()
	{
		using namespace ui;



		m_renderer.new_sub<sub>("Hand Trails", SubHandTrails, [](sub* core)
			{
				core->add_option<toggle_option<bool>>(("Toggle"), nullptr, &m_vars.g_particle_enable);
				core->add_option<toggle_option<bool>>(("Rainbow"), nullptr, &m_vars.g_rainbow);
				core->add_option<number_option<float>>(("Scale"), nullptr, &m_vars.g_scale, 0.00f, 1.0f, 0.01f, 2);
				core->add_option<break_option>(std::move(break_option()
					.SetRightText("Colors")
				));
				core->add_option<number_option<float>>(("Red"), nullptr, &m_vars.red, 0, 255, 5, 1, false);
				core->add_option<number_option<float>>(("Green"), nullptr, &m_vars.green, 0, 255, 5, 1, false);
				core->add_option<number_option<float>>(("Blue"), nullptr, &m_vars.blue, 0, 255, 5, 1, false);
			});
	}

	void hand_trails_menu::script_init() {}

	void hand_trails_menu::script_on_tick()
	{
		if (m_vars.g_particle_enable) {



			if (m_vars.g_rainbow) {
				RGBFade();
				STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_indep_fireworks");
				GRAPHICS::USE_PARTICLE_FX_ASSET("scr_indep_fireworks");
				int handle = GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE("scr_indep_firework_sparkle_spawn", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 28422, m_vars.g_scale, 0, 0, 0);
				GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR(m_vars.red, m_vars.green, m_vars.blue);


				STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_indep_fireworks");
				GRAPHICS::USE_PARTICLE_FX_ASSET("scr_indep_fireworks");
				int handle1 = GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE("scr_indep_firework_sparkle_spawn", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 60309, m_vars.g_scale, 0, 0, 0);



				GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR(m_vars.red, m_vars.green, m_vars.blue);
			}
			else {
				STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_indep_fireworks");
				GRAPHICS::USE_PARTICLE_FX_ASSET("scr_indep_fireworks");
				int handle = GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE("scr_indep_firework_sparkle_spawn", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 28422, m_vars.g_scale, 0, 0, 0);
				GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR(m_vars.red, m_vars.green, m_vars.blue);


				STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_indep_fireworks");
				GRAPHICS::USE_PARTICLE_FX_ASSET("scr_indep_fireworks");
				int handle1 = GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE("scr_indep_firework_sparkle_spawn", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 60309, m_vars.g_scale, 0, 0, 0);



				GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR(m_vars.red, m_vars.green, m_vars.blue);
			}
		}
	}

	void hand_trails_menu::script_func()
	{
		m_hand_trails_menu.script_init();
		while (true)
		{
			m_hand_trails_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}