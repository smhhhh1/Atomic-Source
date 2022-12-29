#pragma once


namespace big::menu
{
	class paint_gun_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline paint_gun_menu m_paint_gun_menu;
}

namespace big::weapon::paint_gun::vars {
	struct variables {
		bool m_toggle;
		bool m_rainbow;
		float m_intensity = 250.0f;
		float m_range = 0.25f;
		int red = 255;
		int green = 0;
		int blue = 0;
	};

	extern variables m_vars;
}
