#pragma once


namespace big::menu
{
	class network_spoofing_crew_icon_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline network_spoofing_crew_icon_menu m_network_spoofing_crew_icon_menu;
}


namespace big::network::spoofing::crew::icon::vars
{
	struct variables {
		bool m_spoof = false;
		int64_t m_id = 69420;
	};
	extern variables m_vars;
}