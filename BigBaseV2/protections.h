#pragma once


namespace big::menu
{
	class protections_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline protections_menu m_protections_menu;
}

namespace big::protections::vars
{
	struct variables {
		bool m_block_resolves;
		bool m_spoof_resolves;
	};

	extern variables m_vars;
}