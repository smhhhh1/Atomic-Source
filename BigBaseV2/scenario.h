#pragma once


namespace big::menu
{
	class scenario_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline scenario_menu m_scenario_menu;
}

