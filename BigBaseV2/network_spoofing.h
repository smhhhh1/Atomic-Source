#pragma once


namespace big::menu
{
	class network_spoofing_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline network_spoofing_menu m_network_spoofing_menu;
}


namespace big::network::spoofing::vars {
	struct variables {
		bool m_movement_animation;
		bool m_fake_lag;
		bool m_rockstar_dev;

		
	};

	extern variables m_vars;
}
