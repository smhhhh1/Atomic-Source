#pragma once


namespace big::menu
{
	class game_fx_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline game_fx_menu m_game_fx_menu;
}

namespace big::game_fx::vars
{
	struct variables {
		float m_fog{ 0.0001f };
		bool m_disable_lights;
	};

	extern variables m_vars;
}