#pragma once


namespace big::menu
{
	class network_recovery_misc_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline network_recovery_misc_menu m_network_recovery_misc_menu;
}

