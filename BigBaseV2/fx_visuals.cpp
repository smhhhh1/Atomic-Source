#include "common.hpp"
#include "gta_util.hpp"
#include "fx_visuals.h"
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
using namespace big::game_fx::visuals::vars;


namespace big::game_fx::visuals::vars
{
	variables m_vars;

}
namespace big::menu
{
	void game_fx_visuals_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Visuals", SubGameFxVisuals, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;

				core->add_option<number_option<float>>("Saturation",
					nullptr,
					&g_pointers->m_visual_settings->m_saturation,
					0.f, 100.f,
					0.1f, 1
				);

				core->add_option<number_option<float>>("Sky Intensity",
					nullptr,
					&g_pointers->m_visual_settings->m_sky_intensity,
					0.f, 100.f,
					0.1f, 1
				);

				core->add_option<number_option<float>>("Blur",
					nullptr,
					&g_pointers->m_visual_settings->m_blur,
					0.f, 100.f,
					0.1f, 1
				);

				core->add_option<number_option<float>>("Blur 2",
					nullptr,
					&g_pointers->m_visual_settings->m_blur2,
					0.f, 100.f,
					0.1f, 1
				);

				core->add_option<number_option<float>>("Gamma",
					nullptr,
					&g_pointers->m_visual_settings->m_gamma,
					0.f, 100.f,
					0.1f, 1
				);

				core->add_option<number_option<float>>("Shadow Light",
					nullptr,
					&g_pointers->m_visual_settings->m_shadow_light,
					0.f, 100.f,
					0.1f, 1
				);

				core->add_option<number_option<float>>("Reflection",
					nullptr,
					&g_pointers->m_visual_settings->m_reflection,
					0.f, 100.f,
					0.1f, 1
				);

			});
	}

	void game_fx_visuals_menu::script_init() {}

	void game_fx_visuals_menu::script_on_tick() {}
	void game_fx_visuals_menu::script_func()
	{
		m_game_fx_visuals_menu.script_init();
		while (true)
		{
			m_game_fx_visuals_menu.script_on_tick();

			script::get_current()->yield();
		}
	}
}