#pragma once


namespace big::menu
{
	class vehicle_collision_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline vehicle_collision_menu m_vehicle_collision_menu;
}

namespace big::vehicle::collision::vars {
	struct variables {
		bool m_disable_veh_collision;
		bool m_disable_full_collision;
	};


	extern variables m_vars;
}
