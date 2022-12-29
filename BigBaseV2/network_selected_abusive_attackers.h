#pragma once


namespace big::menu
{
	class network_selected_abusive_attackers_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline network_selected_abusive_attackers_menu m_network_selected_abusive_attackers_menu;
}

namespace big::network::selected_player::abusive::attackers::vars {
	struct variables {

		const char* AttackerWeapon{ NULL };
		const char* AttackerModel{ NULL };

	};
	extern variables m_vars;
}
