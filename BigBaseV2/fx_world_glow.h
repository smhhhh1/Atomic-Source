#pragma once


namespace big::menu
{
	class game_fx_world_glow_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline game_fx_world_glow_menu m_game_fx_world_glow_menu;
}

namespace big::game_fx::world_glow::vars
{
	struct variables {
		bool m_toggle;
		int red = 255;
		int green;
		int blue;
		float m_intensity = 25.0f;
		bool m_rainbow;
	};

	extern variables m_vars;
}