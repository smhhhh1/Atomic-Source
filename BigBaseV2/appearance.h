#pragma once


namespace big::menu
{
	class appearance_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();


	}; inline appearance_menu m_appearance_menu;
}

namespace big::player::appearance::vars
{
	struct variables {

		
		bool m_width_toggle;
		float m_width{ 1.0f };
		bool m_height_toggle;
		float m_height{ 1.0f };
		bool m_lean_front_toggle;
		float m_lean_front{ 1.0f };
		bool m_lean_left_toggle;
		float m_lean_left{ 1.0f };

	};

	extern variables m_vars;
}