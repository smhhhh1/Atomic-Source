#pragma once


namespace big::menu
{
	class network_selected_abusive_increment_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline network_selected_abusive_increment_menu m_network_selected_abusive_increment_menu;
}

namespace big::network::selected_player::abusive::increment::vars {
	struct variables {

		int increment_delay{ 300 };

	};
	extern variables m_vars;
}
