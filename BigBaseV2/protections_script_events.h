#pragma once


namespace big::menu
{
	class protections_script_events_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline protections_script_events_menu m_protections_script_events_menu;
}

namespace big::protections::script_events::vars
{
	struct variables {
		
	};

	extern variables m_vars;
}