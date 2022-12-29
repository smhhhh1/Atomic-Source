#pragma once


namespace big::menu
{
	class network_selected_friendly_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline network_selected_friendly_menu m_network_selected_friendly_menu;
}

namespace big::network::selected_player::friendly::vars {
	struct variables {
		bool m_demi_godmode;
		bool m_off_the_radar;
		bool m_disable_police;
		bool m_kill_killers;
		bool m_force_visible;

	};


	extern variables m_vars;
}
