#pragma once


namespace big::menu
{
	class player_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline player_menu m_player_menu;
}

namespace big::local::vars
{
	struct variables {
		bool m_godmode;
		bool m_disable_police;
		bool m_disable_ragdoll;
		bool m_off_the_radar;
		bool m_reduced_collision;
		bool m_invisibility;
		bool m_superman;
		bool m_peds_ingore_player;
		bool m_tiny_ped;
		bool m_swim_anywhere;
		bool m_kill_killers;
		bool m_infinite_stamina;
		bool m_infinite_ability;
		bool m_heal_in_cover;
		bool m_breathe_fire;
		bool m_infinite_breath;
		int m_breathe_fire_handle;
	};

	extern variables m_vars;
}