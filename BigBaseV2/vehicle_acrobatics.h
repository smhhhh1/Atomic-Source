#pragma once


namespace big::menu
{
	class vehicle_acrobatics_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline vehicle_acrobatics_menu m_vehicle_acrobatics_menu;
}

