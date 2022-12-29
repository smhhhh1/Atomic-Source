#pragma once


namespace big::menu
{
	class network_selected_trolling_entity_spammer_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline network_selected_trolling_entity_spammer_menu m_network_selected_trolling_entity_spammer_menu;
}

namespace big::network::selected_player::trolling::entity_spammer::vars {
	struct variables {
		bool g_ped{ false };
		bool g_clone{ false };
		bool g_vehicle{ false };
	};


	extern variables m_vars;
}
