#pragma once


namespace big::menu
{
	class vehicle_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline vehicle_menu m_vehicle_menu;
}

namespace big::vehicle::vars
{
	struct variables {
		bool m_godmode;
		bool m_invisibility;
		bool m_seatbelt;
		bool m_mute_siren;
		bool m_speedometer;
		bool m_burn_shell;
	};

	extern variables m_vars;
}