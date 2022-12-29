#pragma once


namespace big::menu
{
	class vehicle_gravity_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline vehicle_gravity_menu m_vehicle_gravity_menu;
}

namespace big::vehicle::gravity::vars {
	struct variables {
		bool m_disable_gravity;
		bool m_drive_on_water;
		bool m_stick_to_ground;
		bool m_auto_flip;
		bool m_slippy_wheels;
	
	};


	extern variables m_vars;
}
