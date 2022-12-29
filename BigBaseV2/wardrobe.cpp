#include "common.hpp"
#include "gta_util.hpp"
#include "wardrobe.h"
#include "natives.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "../render.h"
#include "../abstract_submenu.h"
#include "../break_option.h"
#include "../toggle_option.h"
#include "../number.h"
#include "../option.h"
#include "../submenu_option.h"
#include "../simple_option.h"
#include "../simple_submenu.h"
#include "../bool_and_number.h"
#include "../submenu_option.h"
#include "../submenus.h"
#include "../scroll.h"

using namespace big::player::wardrobe::vars;

namespace big::player::wardrobe::vars {
	variables m_vars;

	std::array<const char*, 12> m_elements{ "None", "Mask", "Hair", "Gloves", "Pants", "Bags", "Shoes", "Accessories", "Shirts", "Bulletproof Vests", "Emblems", "Jackets" };


	void SetPlayerVariation(int componentId, int drawableId, int textureId, int paletteId)
	{
		PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), componentId, drawableId, textureId, paletteId);
	}

	void ResetPedVariation()
	{
		for (int i = 0; i < 12; i++)
		{
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), i, 0, 0, 0);
		}
	}

}

namespace big::menu
{
	void wardrobe_menu::menu()
	{
		using namespace ui;
		m_renderer.new_sub<sub>("Wardrobe", SubWardrobe, [](sub* core)
			{
				core->add_option<scroll_option<const char*, std::size_t>>(("Element"), nullptr, &m_elements, &m_vars.m_clothing_id);
				switch (m_vars.m_clothing_id)
				{
				case 0:
				{

				}
				break;
				case 1:
				{
					core->add_option<number_option<int>>(("Drawable"),
						nullptr,
						&m_vars.s1,
						0,
						200,
						1,
						1,
						true,
						"", "", [] {
							SetPlayerVariation(m_vars.m_clothing_id, m_vars.s1, m_vars.s2, m_vars.s3);
						});
					core->add_option<number_option<int>>(("Texture"),
						nullptr,
						&m_vars.s2,
						0,
						500,
						1,
						1,
						true,
						"", "", [] {
							SetPlayerVariation(m_vars.m_clothing_id, m_vars.s1, m_vars.s2, m_vars.s3);
						});
				}
				break;
				case 2:
				{
					core->add_option<number_option<int>>(("Drawable"),
						nullptr,
						&m_vars.a1,
						0,
						500,
						1,
						1,
						true, "", "", [] {
							SetPlayerVariation(m_vars.m_clothing_id, m_vars.a1, m_vars.a2, m_vars.a3);
						});
					core->add_option<number_option<int>>(("Texture"),
						nullptr,
						&m_vars.a2,
						0,
						500,
						1,
						1,
						true,
						"", "", [] {
							SetPlayerVariation(m_vars.m_clothing_id, m_vars.a1, m_vars.a2, m_vars.a3);
						});
				}
				break;
				case 3:
				{
					core->add_option<number_option<int>>(("Drawable"), nullptr, &m_vars.b1, 0, 500, 1, 1, true, "", "", [] {SetPlayerVariation(m_vars.m_clothing_id, m_vars.b1, m_vars.b2, m_vars.b3); });
					core->add_option<number_option<int>>(("Texture"), nullptr, &m_vars.b2, 0, 500, 1, 1, true, "", "", [] { SetPlayerVariation(m_vars.m_clothing_id, m_vars.b1, m_vars.b2, m_vars.b3); });
				}
				break;
				case 4:
				{
					core->add_option<number_option<int>>(("Drawable"), nullptr, &m_vars.c1, 0, 500, 1, 1, true, "", "", [] {SetPlayerVariation(m_vars.m_clothing_id, m_vars.c1, m_vars.c2, m_vars.c3); });
					core->add_option<number_option<int>>(("Texture"), nullptr, &m_vars.c2, 0, 500, 1, 1, true, "", "", [] { SetPlayerVariation(m_vars.m_clothing_id, m_vars.c1, m_vars.c2, m_vars.c3); });
				}
				break;
				case 5:
				{
					core->add_option<number_option<int>>(("Drawable"), nullptr, &m_vars.d1, 0, 500, 1, 1, true, "", "", [] {SetPlayerVariation(m_vars.m_clothing_id, m_vars.d1, m_vars.d2, m_vars.d3); });
					core->add_option<number_option<int>>(("Texture"), nullptr, &m_vars.d2, 0, 500, 1, 1, true, "", "", [] { SetPlayerVariation(m_vars.m_clothing_id, m_vars.d1, m_vars.d2, m_vars.d3); });
				}
				break;
				case 6:
				{
					core->add_option<number_option<int>>(("Drawable"), nullptr, &m_vars.e1, 0, 500, 1, 1, true, "", "", [] {SetPlayerVariation(m_vars.m_clothing_id, m_vars.e1, m_vars.e2, m_vars.e3); });
					core->add_option<number_option<int>>(("Texture"), nullptr, &m_vars.e2, 0, 500, 1, 1, true, "", "", [] { SetPlayerVariation(m_vars.m_clothing_id, m_vars.e1, m_vars.e2, m_vars.e3); });
				}
				break;
				case 7:
				{
					core->add_option<number_option<int>>(("Drawable"), nullptr, &m_vars.f1, 0, 500, 1, 1, true, "", "", [] {SetPlayerVariation(m_vars.m_clothing_id, m_vars.f1, m_vars.f2, m_vars.f3); });
					core->add_option<number_option<int>>(("Texture"), nullptr, &m_vars.f2, 0, 500, 1, 1, true, "", "", [] { SetPlayerVariation(m_vars.m_clothing_id, m_vars.f1, m_vars.f2, m_vars.f3); });
				}
				break;
				case 8:
				{
					core->add_option<number_option<int>>(("Drawable"), nullptr, &m_vars.g1, 0, 500, 1, 1, true, "", "", [] {SetPlayerVariation(m_vars.m_clothing_id, m_vars.g1, m_vars.g2, m_vars.g3); });
					core->add_option<number_option<int>>(("Texture"), nullptr, &m_vars.g2, 0, 500, 1, 1, true, "", "", [] { SetPlayerVariation(m_vars.m_clothing_id, m_vars.g1, m_vars.g2, m_vars.g3); });
				}
				break;
				case 9:
				{
					core->add_option<number_option<int>>(("Drawable"), nullptr, &m_vars.h1, 0, 500, 1, 1, true, "", "", [] {SetPlayerVariation(m_vars.m_clothing_id, m_vars.h1, m_vars.h2, m_vars.h3); });
					core->add_option<number_option<int>>(("Texture"), nullptr, &m_vars.h2, 0, 500, 1, 1, true, "", "", [] { SetPlayerVariation(m_vars.m_clothing_id, m_vars.h1, m_vars.h2, m_vars.h3); });
				}
				break;
				case 10:
				{
					core->add_option<number_option<int>>(("Drawable"),
						nullptr,
						&m_vars.i1,
						0,
						500,
						1,
						1,
						true,
						"", "", [] {
							SetPlayerVariation(m_vars.m_clothing_id, m_vars.i1, m_vars.i2, m_vars.i3);
						});
					core->add_option<number_option<int>>(("Texture"),
						nullptr,
						&m_vars.i2,
						0,
						500,
						1,
						1,
						true,
						"", "", [] {
							SetPlayerVariation(m_vars.m_clothing_id, m_vars.i1, m_vars.i2, m_vars.i3);
						});
				}
				break;
				case 11:
				{
					core->add_option<number_option<int>>(("Drawable"),
						nullptr,
						&m_vars.j1,
						0,
						500,
						1,
						1,
						true,
						"", "", [] {
							SetPlayerVariation(m_vars.m_clothing_id, m_vars.j1, m_vars.j2, m_vars.j3);
						});
					core->add_option<number_option<int>>(("Texture"),
						nullptr,
						&m_vars.j2,
						0,
						500,
						1,
						1,
						true,
						"", "", [] {
							SetPlayerVariation(m_vars.m_clothing_id, m_vars.j1, m_vars.j2, m_vars.j3);
						});
				}
				break;
				case 12:
				{
					core->add_option<number_option<int>>(("Drawable"),
						nullptr,
						&m_vars.k1,
						0,
						500,
						1,
						1,
						true,
						"", "", [] {
							SetPlayerVariation(m_vars.m_clothing_id, m_vars.k1, m_vars.k2, m_vars.k3);
						});
					core->add_option<number_option<int>>(("Texture"),
						nullptr,
						&m_vars.k2,
						0,
						500,
						1,
						1,
						true,
						"", "", [] {
							SetPlayerVariation(m_vars.m_clothing_id, m_vars.k1, m_vars.k2, m_vars.k3);
						});
				}
				break;
				}
				core->add_option<simple_option>(("Reset"), nullptr, [] { ResetPedVariation(); });
			});
	}

	void wardrobe_menu::script_init() {}

	void wardrobe_menu::script_on_tick()
	{

	}

	void wardrobe_menu::script_func()
	{
		m_wardrobe_menu.script_init();
		while (true)
		{
			m_wardrobe_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}