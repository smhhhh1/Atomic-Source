#pragma once


namespace big::menu
{
	class vehicle_secondary_color_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline vehicle_secondary_color_menu m_vehicle_secondary_color_menu;
}

namespace big::vehicle::color::secondary::vars {
	struct variables {
		int red;
		int green;
		int blue;
	};


	extern variables m_vars;
}
