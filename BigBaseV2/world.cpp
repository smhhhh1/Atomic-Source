#include "common.hpp"
#include "gta_util.hpp"
#include "world.h"
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
#include "../game_fx.h"
#include "fx_sky.h"
#include "weather.h"
#include "weather_fx.h"
#include "fx_world_glow.h"
using namespace big::world::vars;


namespace big::world::vars
{
	variables m_vars;
}
namespace big::menu
{
	void world_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("World", SubWorld, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;

				core->add_option<submenu>("Game Fx",
					nullptr,
					SubGameFx
				);

				core->add_option<submenu>("Weather",
					nullptr,
					SubWorldWeather
				);

			});
	}

	void world_menu::script_init() {}

	void world_menu::script_on_tick() {}

	
	void world_menu::script_func()
	{
		m_world_menu.script_init();
		while (true)
		{
			m_world_menu.script_on_tick();
			m_game_fx_menu.script_on_tick();
			m_game_fx_sky_menu.script_on_tick();
			m_game_fx_world_glow_menu.script_on_tick();
			m_weather_menu.script_on_tick();
			m_weather_fx_menu.script_on_tick();			
			script::get_current()->yield();
		}
	}
}