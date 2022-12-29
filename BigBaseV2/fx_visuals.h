#pragma once


namespace big::menu
{
	class game_fx_visuals_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline game_fx_visuals_menu m_game_fx_visuals_menu;
}

namespace big::game_fx::visuals::vars
{
	struct variables {
	};

	extern variables m_vars;
}