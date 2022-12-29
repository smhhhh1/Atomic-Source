#pragma once


namespace big::menu
{
	class network_spoofing_name_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline network_spoofing_name_menu m_network_spoofing_name_menu;
}

namespace big::network::spoofing::name::vars
{
	struct variables {
		bool m_spoof = false;
		std::string m_name = "Atomic";
	};
	extern variables m_vars;
}
