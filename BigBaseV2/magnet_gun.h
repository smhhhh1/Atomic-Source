#pragma once


namespace big::menu
{
	class magnet_gun_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline magnet_gun_menu m_magnet_gun_menu;
}

namespace big::weapon::magnet_gun::vars {
	struct variables {
		bool m_toggle;
		float m_force{ 250.0f };

	};

	extern variables m_vars;
}
