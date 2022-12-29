#pragma once


namespace big::menu
{
	class network_toolkit_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline network_toolkit_menu m_network_toolkit_menu;
}

namespace big::network::toolkit::vars {
	struct variables {
		bool m_streamer_mode;
		bool m_peer_token_correction;
		bool m_peer_token_corruption;
		bool m_force_script_host;
	};

	extern variables m_vars;
}
