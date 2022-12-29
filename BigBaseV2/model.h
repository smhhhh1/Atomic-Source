#pragma once


namespace big::menu
{
	class model_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline model_menu m_model_menu;
}

