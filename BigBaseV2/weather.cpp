#include "common.hpp"
#include "gta_util.hpp"
#include "weather.h"
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
#include "scroll.h"
using namespace big::world::weather::vars;


namespace big::world::weather::vars
{
	variables m_vars;

	const char* weather_type[] = {
		"clear", "clearing", "clouds", "extrasunny", "foggy", "halloween", "neutral", "overcast", "rain", "smog", "snow", "snowlight", "Blizzard", "thunder"
	}; std::size_t weather_id = 0;

	const char* cloud_type[] = {

		"shower", "Snowy 01", "Stormy 01", "Stratoscumulus", "Stripey", "Wispy", "Altostratus", "Cirrocumulus", "Altostratus", "Clear 01", "Cloudy 01" ,"Contrails", "NoClouds", "Puffs", "Rain", "Snow"
	}; std::size_t cloud_id = 0;

	void set_clouds(const char* texture)
	{
		MISC::LOAD_CLOUD_HAT(texture, 3.f);
	}
}
namespace big::menu
{
	void weather_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Weather", SubWorldWeather, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;

				core->add_option<submenu>("Weather Fx",
					nullptr,
					SubWorldWeatherFx
				);

				core->add_option<scroll_option<const char*, std::size_t>>("Modify Weather",
					nullptr, 
					&weather_type, &weather_id,
					true, [] {
					MISC::SET_WEATHER_TYPE_NOW_PERSIST(weather_type[weather_id]);
				});

				core->add_option<scroll_option<const char*, std::size_t>>("Modify Clouds",
					nullptr,
					&cloud_type, &cloud_id,
					true, [] {
					set_clouds(cloud_type[cloud_id]);
				});

				static int rain_intenisty;

				core->add_option<number_option<int>>(("Rain Intensity"),
					nullptr,
					&rain_intenisty,
					0, 100, 1, 1,
					true, "", "",
					[=] {
						MISC::_SET_RAIN_FX_INTENSITY(rain_intenisty); 
				});

				core->add_option<number_option<float>>(("Wind Speed"),
					nullptr, 
					&m_vars.m_wind_speed, 0, 100,
					1, 1
				);



				core->add_option<toggle_option<bool>>(("Thunder and Lightning"), 
					nullptr,
					&m_vars.m_thunder_and_lightning
				);

				core->add_option<simple_option>(("Flash Lightning"),
					nullptr,
					[&] {
						MISC::FORCE_LIGHTNING_FLASH();
					});
			});
	}

	void weather_menu::script_init() {}

	void weather_menu::script_on_tick()
	{
		

		if (m_vars.m_thunder_and_lightning) {
			MISC::FORCE_LIGHTNING_FLASH();
		}
	}

	void weather_menu::script_func()
	{
		m_weather_menu.script_init();
		while (true)
		{
			m_weather_menu.script_on_tick();

			script::get_current()->yield();
		}
	}
}