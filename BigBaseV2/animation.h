#pragma once


namespace big::menu
{
	class animation_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline animation_menu m_animation_menu;
}

