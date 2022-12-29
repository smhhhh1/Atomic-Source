#pragma once


namespace big::menu
{
	class network_spoofing_detection_flags_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline network_spoofing_detection_flags_menu m_network_spoofing_detection_flags_menu;
}

namespace big::network::spoofing::detection_flags::vars {
	struct variables {
		bool m_godmode = true;
		bool m_super_jump = true;
		bool m_health = true;
		bool m_armor = true;
		bool m_proofs = true;
		bool m_spectate = true;
		bool m_weapon_damage = true;
		bool m_melee_damage = true;
		bool m_defense_damage = true;
	};


	extern variables m_vars;
}
