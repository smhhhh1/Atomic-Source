#pragma once


namespace big::menu
{
	class network_notifications_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline network_notifications_menu m_network_notifications_menu;
}


namespace big::network::notifications::vars {
	struct variables {
		bool m_player_join;
		bool m_player_leave;
		bool m_session_join;
		bool m_session_leave;
		bool m_new_script_host;
		bool m_object_creation;
		bool m_ped_creation;
		bool m_pickup_creation;
		bool m_pickup_processing;
		bool m_player_creation;
		bool m_player_spawn;
		bool m_vehicle_creation;
		bool m_desync_kicks;
		bool m_breakup_kicks;
	};

	extern variables m_vars;
}
