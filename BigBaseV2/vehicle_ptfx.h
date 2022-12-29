#pragma once


namespace big::menu
{
	class vehicle_ptfx_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline vehicle_ptfx_menu m_vehicle_ptfx_menu;
}

namespace big::vehicle::ptfx::vars {
	struct variables {
		bool m_toggle;
		bool m_rf_wheel{ false };
		bool m_rl_wheel{ false };
		bool m_rb_wheel{ false };
		bool m_lb_wheel{ false };
		float m_scale{ 0.2f };
	};


	extern variables m_vars;
}
