#pragma once


namespace big::menu
{
	class world_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline world_menu m_world_menu;
}

namespace big::world::vars
{
	struct variables {
		
	};

	extern variables m_vars;
}