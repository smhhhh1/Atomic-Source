#pragma once


namespace big::menu
{
	class weather_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline weather_menu m_weather_menu;
}

namespace big::world::weather::vars
{
	struct variables {
	
		bool m_thunder_and_lightning;
		float m_wind_speed = 100000.f;
	};

	extern variables m_vars;
}