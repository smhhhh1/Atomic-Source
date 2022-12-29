#pragma once


namespace big::menu
{
	class protections_misc_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline protections_misc_menu m_protections_misc_menu;
}

namespace big::protections::misc::vars
{
	struct variables {
		bool m_disable_chat_messages{ false };
		bool m_disable_text_messages{ false };
	};

	extern variables m_vars;
}