#pragma once


namespace big::menu
{
	class vehicle_weapons_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline vehicle_weapons_menu m_vehicle_weapons_menu;
}

namespace big::vehicle::weapons::vars {
	struct variables {
		bool m_toggle;
		bool m_aiming_lines;
		int m_bullet_speed{ 2000 };
	};


	extern variables m_vars;
}
