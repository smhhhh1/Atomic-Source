#pragma once


namespace big::menu
{
	class vehicle_health_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline vehicle_health_menu m_vehicle_health_menu;
}

namespace big::vehicle::health::vars {
	struct variables {
		bool m_auto_repair;
		bool m_auto_wash;
	};


	extern variables m_vars;
}
