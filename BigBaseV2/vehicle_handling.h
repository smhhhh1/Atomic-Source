#pragma once


namespace big::menu
{
	class vehicle_handling_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline vehicle_handling_menu m_vehicle_handling_menu;
}

namespace big::vehicle::handling::vars {
	struct variables {
		
	};


	extern variables m_vars;
}
