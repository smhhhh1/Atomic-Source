#pragma once


namespace big::menu
{
	class network_selected_esp_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline network_selected_esp_menu m_network_selected_esp_menu;
}

namespace big::network::selected_player::esp::vars {
	struct variables {

		bool name;
		bool box;
		bool line;

		int box_red{ 255 };
		int box_green{ 0 };
		int box_blue{ 0 };

		int line_red{ 0 };
		int line_green{ 0 };
		int line_blue{ 255 };

		int name_red{ 255 };
		int name_green{ 255 };
		int name_blue{ 255 };
	};


	extern variables m_vars;
}
