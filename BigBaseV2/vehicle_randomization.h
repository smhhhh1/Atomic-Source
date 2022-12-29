#pragma once


namespace big::menu
{
	class vehicle_randomization_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline vehicle_randomization_menu m_vehicle_randomization_menu;
}

namespace big::vehicle::randomization::vars {
	struct variables {

		bool m_rainbow_paint;
		bool m_second_rainbow_paint;
		bool m_rainbow_tire_smoke;

	};


	extern variables m_vars;
}
