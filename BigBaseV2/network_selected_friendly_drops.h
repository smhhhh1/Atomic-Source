#pragma once


namespace big::menu
{
	class network_selected_friendly_drops_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline network_selected_friendly_drops_menu m_network_selected_friendly_drops_menu;
}

namespace big::network::selected_player::friendly::drops::vars {
	struct variables {

		bool m_money_drop;
		bool m_rp_drop;
		int m_money_drop_delay{ 300 };
		int m_rp_drop_delay{ 300 };
		int m_money_delay;
		int m_rp_delay;
	};


	extern variables m_vars;
}
