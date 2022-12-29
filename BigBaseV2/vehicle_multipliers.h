#pragma once


namespace big::menu
{
	class vehicle_multiplier_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline vehicle_multiplier_menu m_vehicle_multiplier_menu;
}

namespace big::vehicle::multipliers::vars {
	struct variables {
		float power = 1;
		float torque = 1;
		float downforce = 1;
		float traction = 2.5;
	};


	extern variables m_vars;
}
