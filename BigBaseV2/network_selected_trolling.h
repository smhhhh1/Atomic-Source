#pragma once


namespace big::menu
{
	class network_selected_trolling_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline network_selected_trolling_menu m_network_selected_trolling_menu;
}

namespace big::network::selected_player::trolling::vars {
	struct variables {
		bool m_sound_spam;
	};


	extern variables m_vars;
}
