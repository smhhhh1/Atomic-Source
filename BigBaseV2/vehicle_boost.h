#pragma once


namespace big::menu
{
	class vehicle_boost_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline vehicle_boost_menu m_vehicle_boost_menu;
}

namespace big::vehicle::boost::vars {
	struct variables {
		bool m_horn_boost;
		bool m_boost_fx;
		float m_horn_boost_speed{ 50.f };
	};


	extern variables m_vars;
}
