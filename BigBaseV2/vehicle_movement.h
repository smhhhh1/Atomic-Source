#pragma once


namespace big::menu
{
	class vehicle_movement_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline vehicle_movement_menu m_vehicle_movement_menu;
}

namespace big::vehicle::movement::vars {
	struct variables {
		bool m_parachute;
		bool m_spin;
		bool m_bypass_max_speed;
		bool m_limit_max_speed;
		bool m_flying_vehicle;
		bool m_flying_vehicle_pause;
		float m_vehicle_fly_speed{ 1 };
		float m_max_speed_limit{ 0 };
	};


	extern variables m_vars;
}
