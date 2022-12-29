#pragma once


namespace big::menu
{
	class movement_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline movement_menu m_movement_menu;
}

namespace big::player::movement::vars
{
	struct variables {

		bool m_no_clip;//ill add later or u can add
		float m_no_clip_speed{ 1.0f };

		bool m_no_clip_notify = true;
		bool m_no_clip_bind;

		bool m_super_run{ false };
		float m_run_speed{ 1.0f };
		bool m_super_swim{ false };
		float m_swim_speed{ 1.0f };

		bool m_super_jump;


	};

	extern variables m_vars;
}