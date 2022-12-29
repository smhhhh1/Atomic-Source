#pragma once
#include "math.h"

namespace big::menu
{
	class proofs_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline proofs_menu m_proofs_menu;
}

namespace big::player::proofs::vars
{
	struct variables {

		bool g_bullet_proof;
		bool g_fire_proof;
		bool g_explosion_proof;
		bool g_collision_proof;
		bool g_melee_proof;
		bool g_drown_proof;

	};
	extern variables m_vars;
}