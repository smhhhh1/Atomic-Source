#pragma once


namespace big::menu
{
	class impacts_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline impacts_menu m_impacts_menu;
}

namespace big::weapon::impacts::vars {
	struct variables {
		
		bool toggle;
	};


	extern variables m_vars;
}
