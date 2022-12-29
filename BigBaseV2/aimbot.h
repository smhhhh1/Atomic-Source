#pragma once


namespace big::menu
{
	class aimbot_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline aimbot_menu m_aimbot_menu;
}

namespace big::weapon::aimbot::vars {
	struct variables {
		bool m_toggle;
		bool m_multi_bullet;
		int shoot_delay{ 20 };
	};

	
	extern variables m_vars;
}
