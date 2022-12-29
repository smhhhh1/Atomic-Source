#pragma once


namespace big::menu
{
	class network_friends_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline network_friends_menu m_network_friends_menu;
}


namespace big::network::friends::vars {
	struct variables {
		bool join_queued;
		rage::rlSessionInfo info;
	};


	extern variables m_vars;
}

