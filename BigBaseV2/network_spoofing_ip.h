#pragma once


namespace big::menu
{
	class network_spoofing_ip_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline network_spoofing_ip_menu m_network_spoofing_ip_menu;
}

namespace big::network::spoofing::ip::vars
{
	struct variables {
		bool m_spoof = false;
		int ip_address[4] = { 1, 2, 3, 4 };
	};
	extern variables m_vars;
}
