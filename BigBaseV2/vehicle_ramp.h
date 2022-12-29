#pragma once


namespace big::menu
{
	class vehicle_ramp_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline vehicle_ramp_menu m_vehicle_ramp_menu;
}

namespace big::vehicle::ramp::vars {
	struct variables {
		
		bool m_front;
		bool m_back;
		bool m_left;
		bool m_right;

	};


	extern variables m_vars;
}
