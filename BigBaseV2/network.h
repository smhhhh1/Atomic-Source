#pragma once


namespace big::menu
{
	class network_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline network_menu m_network_menu;
}
