#pragma once
#include "math.h"

namespace big::menu
{
	class ptfx_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline ptfx_menu m_ptfx_menu;
}

namespace big::player::ptfx::vars
{
	struct variables {

		
		float red{ 255 };
		float green{ 0 };
		float blue{ 0 };
		bool g_rainbow;
		bool head;
		bool right_hand;
		bool left_hand;
		bool right_foot;
		bool left_foot;
		bool g_particle_man;
		float g_particle_man_scale{ 0.2 };

	};
	extern variables m_vars;
}