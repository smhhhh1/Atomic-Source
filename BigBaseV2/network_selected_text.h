#pragma once


namespace big::menu
{
	class network_selected_text_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

		const char* message = "atomicmenu.xyz";
		bool active;

	}; inline network_selected_text_menu m_network_selected_text_menu;
}

