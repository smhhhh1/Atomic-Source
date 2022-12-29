#pragma once


namespace big::menu
{
	class network_selected_vehicle_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline network_selected_vehicle_menu m_network_selected_vehicle_menu;
}

namespace big::network::selected_player::vehicle::vars {
	struct variables {
		bool m_godmode;
		bool m_disable_collision;
		bool m_slippy_wheels;
		bool m_freeze;
		

	};


	extern variables m_vars;
}
