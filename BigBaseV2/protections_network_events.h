#pragma once


namespace big::menu
{
	class protections_network_events_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline protections_network_events_menu m_protections_network_events_menu;
}

namespace big::protections::network_events::vars
{
	struct variables {
		bool m_explosions;
		bool m_ptfx;
		bool m_remove_weapons;
		bool m_remove_all_weapons;
		bool m_request_control;
		bool m_give_control;
		bool m_freeze;
		bool m_reports;
	};

	extern variables m_vars;
}