#pragma once


namespace big::menu
{
	class network_spoofing_rid_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline network_spoofing_rid_menu m_network_spoofing_rid_menu;
}

namespace big::network::spoofing::rid::vars
{
	struct variables {
		bool m_spoof = false;
		uint64_t rockstar_id = 1337;
		bool should_spoof_rockstar_id = false;
		uint64_t applied_spoof_rockstar_id = 0;
	};
	extern variables m_vars;
}
