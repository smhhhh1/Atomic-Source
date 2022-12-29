#pragma once


namespace big::menu
{
	class particle_gun_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline particle_gun_menu m_particle_gun_menu;
}

namespace big::weapon::particle_gun::vars {
	struct variables {

		bool m_toggle;
		float m_scale{ 1.0f };
	};


	extern variables m_vars;
}
