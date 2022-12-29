#pragma once


namespace big::menu
{
	class network_selected_player_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline network_selected_player_menu m_network_selected_player_menu;
}

namespace big::network::selected_player::vars {
	struct variables {
		bool m_spectate;
	};


	extern variables m_vars;
}
