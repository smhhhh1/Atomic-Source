#pragma once


namespace big::menu
{
	class vehicle_parachute_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline vehicle_parachute_menu m_vehicle_parachute_menu;
}

namespace big::vehicle::parachute::vars {
	struct variables {
		
		bool m_auto_deploy;
	};


	extern variables m_vars;
}
