#pragma once


namespace big::menu
{
	class protections_presence_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline protections_presence_menu m_protections_presence_menu;
}

namespace big::protections::presence::vars
{

	struct variables {

	};


	extern variables m_vars;
}