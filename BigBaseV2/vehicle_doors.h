#pragma once


namespace big::menu
{
	class vehicle_doors_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline vehicle_doors_menu m_vehicle_doors_menu;
}

