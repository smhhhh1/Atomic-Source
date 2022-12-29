#pragma once
#include "math.h"

namespace big::menu
{
	class wardrobe_menu
	{
	public:

		void menu();
		void script_init();
		void script_on_tick();
		static void script_func();

	}; inline wardrobe_menu m_wardrobe_menu;
}

namespace big::player::wardrobe::vars
{
	struct variables {

		int m_element_id{ 0 };
		int m_DrawableId{ 0 };
		int m_TextureId{ 0 };
		int m_PaletteId{ 0 };
		std::size_t m_clothing_id{ 0 };
		int s0{ 0 }, s1{ 0 }, s2{ 0 }, s3{ 0 }, a0{ 0 }, a1{ 0 }, a2{ 0 }, a3{ 0 }, b0{ 0 }, b1{ 0 }, b2{ 0 }, b3{ 0 }, c0{ 0 }, c1{ 0 }, c2{ 0 }, c3{ 0 }, d0{ 0 }, d1{ 0 }, d2{ 0 }, d3{ 0 }, e0{ 0 }, e1{ 0 }, e2{ 0 }, e3{ 0 }, f0{ 0 }, f1{ 0 }, f2{ 0 }, f3{ 0 }, g0{ 0 }, g1{ 0 }, g2{ 0 }, g3{ 0 }, h0{ 0 }, h1{ 0 }, h2{ 0 }, h3{ 0 }, i0{ 0 }, i1{ 0 }, i2{ 0 }, i3{ 0 }, j0{ 0 }, j1{ 0 }, j2{ 0 }, j3{ 0 }, k0{ 0 }, k1{ 0 }, k2{ 0 }, k3{ 0 }, l0{ 0 }, l1{ 0 }, l2{ 0 }, l3{ 0 };


	};
	extern variables m_vars;
}