#pragma once


namespace big::menu
{
	class protections_reactions_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline protections_reactions_menu m_protections_reactions_menu;
}

namespace big::protections::reactions::vars
{

	struct variables {
		std::unordered_map<int, std::unordered_map<int, uint32_t>> m_spectate_map;
	};


	extern variables m_vars;
}