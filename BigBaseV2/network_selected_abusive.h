#pragma once


namespace big::menu
{
	class network_selected_abusive_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline network_selected_abusive_menu m_network_selected_abusive_menu;
}

namespace big::network::selected_player::abusive::vars {
	struct variables {
		bool m_freeze;
		bool m_explode;
		bool m_kick_from_vehicle;
		bool m_set_on_fire;
		bool m_taze;
		bool m_ragdoll;
		bool m_glitch_physics;
		bool m_blame;
		bool m_rain_rockets;
		bool m_shake_cam;
		bool m_clone;
		bool m_vehicle_ram;
		bool m_always_wanted;
		bool m_hostile_peds;

		int m_kick_from_vehicle_timer;
		int m_taze_timer;
		int m_ragdoll_timer;
		int m_glitch_physics_timer;
		int m_rain_rockets_timer;
		int m_always_wanted_timer;
		int m_set_on_fire_timer;
		int m_hostile_peds_timer;
	};


	extern variables m_vars;
}
