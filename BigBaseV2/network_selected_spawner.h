#pragma once


namespace big::menu
{
	class network_selected_spawner_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline network_selected_spawner_menu m_network_selected_spawner_menu;
}


