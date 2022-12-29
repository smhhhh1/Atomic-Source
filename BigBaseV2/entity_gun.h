#pragma once


namespace big::menu
{
	class entity_gun_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline entity_gun_menu m_entity_gun_menu;
}

namespace big::weapon::entity_gun::vars {
	struct variables {
		bool toggle;
	};

	extern variables m_vars;
}
