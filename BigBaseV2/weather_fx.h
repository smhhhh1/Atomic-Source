#pragma once


namespace big::menu
{
	class weather_fx_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline weather_fx_menu m_weather_fx_menu;
}

namespace big::world::weather::fx::vars
{
	struct variables {
		float m_rain_red;
		float m_rain_green;
		float m_rain_blue;
		float m_rain_intensity;
	};

	extern variables m_vars;
}