#pragma once


namespace big::menu
{
	class network_selected_abusive_explosion_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline network_selected_abusive_explosion_menu m_network_selected_abusive_explosion_menu;
}

namespace big::network::selected_player::abusive::explosion::vars {
	struct variables {

		bool g_explosion_loop{ false };
		bool g_visible{ false };
		float g_camera_shake{ 1.0f };
		int g_radius{ 100 };
		bool g_audible{ false };

	};
	extern variables m_vars;
}
