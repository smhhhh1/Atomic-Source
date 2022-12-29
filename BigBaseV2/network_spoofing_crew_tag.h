#pragma once


namespace big::menu
{
	class network_spoofing_crew_tag_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline network_spoofing_crew_tag_menu m_network_spoofing_crew_tag_menu;
}


namespace big::network::spoofing::crew::tag::vars
{
	struct variables {
		bool m_spoof = false;
		std::string m_tag = "Atomic";
	};
	extern variables m_vars;
}