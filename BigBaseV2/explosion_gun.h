#pragma once


namespace big::menu
{
	class explosion_gun_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline explosion_gun_menu m_explosion_gun_menu;
}

namespace big::weapon::explosion_gun::vars {
	struct variables {

		bool m_toggle;
		bool m_audible;
		int m_radius{ 100 };
		float m_camera_shake{ 1.0f };
		bool m_invisible;
	};


	extern variables m_vars;
}
