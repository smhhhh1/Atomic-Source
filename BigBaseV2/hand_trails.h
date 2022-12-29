#pragma once
#include "math.h"

namespace big::menu
{
	class hand_trails_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline hand_trails_menu m_hand_trails_menu;
}

namespace big::player::hand_trails::vars
{
	struct variables {


		bool g_particle_enable{ false };
		float g_scale{ 0.5f };
		float red{ 255 };
		float green{ 0 };
		float blue{ 0 };
		bool g_rainbow{ false };
	};
	extern variables m_vars;
}