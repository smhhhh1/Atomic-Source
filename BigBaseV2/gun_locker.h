#pragma once


namespace big::menu
{
	class gun_locker_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline gun_locker_menu m_gun_locker_menu;
}

