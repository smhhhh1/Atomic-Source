#include "common.hpp"
#include "gta_util.hpp"
#include "weather_fx.h"
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
#include "on_screen_ped.h"
#include "lists.h"
#include "fiber_pool.hpp"

using namespace big::world::weather::fx::vars;


namespace big::world::weather::fx::vars
{
	variables m_vars;

}
namespace big::menu
{
	void weather_fx_menu::menu()
	{
		using namespace ui;


		m_renderer.new_sub<sub>("Weaher Fx", SubWorldWeatherFx, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
			//ONLY RAIN ATM CUZ LAZY	
				core->add_option<number_option<float>>("Red",
					nullptr,
					&m_vars.m_rain_red,
					0.f, 255.f,
					0.1f, 1, true, "", "", [] {
				});

				core->add_option<number_option<float>>("Green",
					nullptr,
					&m_vars.m_rain_green,
					0.f, 255.f,
					0.1f, 1, true, "", "", [] {
				});

				core->add_option<number_option<float>>("Blue",
					nullptr,
					&m_vars.m_rain_blue,
					0.f, 255.f,
					0.1f, 1, true, "", "", [] {
				});

				core->add_option<number_option<float>>("Luminance",
					nullptr,
					&m_vars.m_rain_intensity,
					0.f, 10.f,
					0.1f, 1, true, "", "", [] {  }
				);

				core->add_option<number_option<float>>("Gravity",
					nullptr,
					&*(float*)engine::memory::scan_address(g_base_address + 0x26E60FC, {}),
					-20.f, 10.f,
					0.1f, 1, true, "", "", [] {}
				);

				core->add_option<number_option<float>>("Box Centre X",
					nullptr,
					&*(float*)engine::memory::scan_address(g_base_address + 0x26E6110, {}),
					-10.f, 10.f,
					0.1f, 1, true, "", "", [] {}
				);

				core->add_option<number_option<float>>("Box Centre Y",
					nullptr,
					&*(float*)engine::memory::scan_address(g_base_address + 0x26E6114, {}),
					-10.f, 10.f,
					0.1f, 1, true, "", "", [] {}
				);

				core->add_option<number_option<float>>("Box Centre Z",
					nullptr,
					&*(float*)engine::memory::scan_address(g_base_address + 0x26E6118, {}),
					-10.f, 10.f,
					0.1f, 1, true, "", "", [] {}
				);

				core->add_option<number_option<float>>("Box Size X",
					nullptr,
					&*(float*)engine::memory::scan_address(g_base_address + 0x26E6120, {}),
					0.f, 50.f,
					0.1f, 1, true, "", "", [] {}
				);

				core->add_option<number_option<float>>("Box Size Y",
					nullptr,
					&*(float*)engine::memory::scan_address(g_base_address + 0x26E6124, {}),
					0.f, 50.f,
					0.1f, 1, true, "", "", [] {}
				);

				core->add_option<number_option<float>>("Box Size Z",
					nullptr,
					&*(float*)engine::memory::scan_address(g_base_address + 0x26E6128, {}),
					0.f, 50.f,
					0.1f, 1, true, "", "", [] {}
				);

				core->add_option<number_option<float>>("Life Min",
					nullptr,
					&*(float*)engine::memory::scan_address(g_base_address + 0x26E6130, {}),
					0.f, 12.f,
					0.1f, 1, true, "", "", [] {}
				);

				core->add_option<number_option<float>>("Life Max",
					nullptr,
					&*(float*)engine::memory::scan_address(g_base_address + 0x26E6134, {}),
					0.f, 12.f,
					0.1f, 1, true, "", "", [] {}
				);

				core->add_option<number_option<float>>("Velocity Min X",
					nullptr,
					&*(float*)engine::memory::scan_address(g_base_address + 0x26E6140, {}),
					0.f, 50.f,
					0.1f, 1, true, "", "", [] {}
				);

				core->add_option<number_option<float>>("Velocity Min Y",
					nullptr,
					&*(float*)engine::memory::scan_address(g_base_address + 0x26E6144, {}),
					0.f, 50.f,
					0.1f, 1, true, "", "", [] {}
				);

				core->add_option<number_option<float>>("Velocity Min Z",
					nullptr,
					&*(float*)engine::memory::scan_address(g_base_address + 0x26E6148, {}),
					0.f, 50.f,
					0.1f, 1, true, "", "", [] {}
				);

				core->add_option<number_option<float>>("Size X",
					nullptr,
					&*(float*)engine::memory::scan_address(g_base_address + 0x26E61B0, {}),
					0.f, 50.f,
					0.1f, 1, true, "", "", [] {}
				);

				core->add_option<number_option<float>>("Size Y",
					nullptr,
					&*(float*)engine::memory::scan_address(g_base_address + 0x26E61B4, {}),
					0.f, 50.f,
					0.1f, 1, true, "", "", [] {}
				);

				core->add_option<number_option<float>>("Size Z",
					nullptr,
					&*(float*)engine::memory::scan_address(g_base_address + 0x26E61B8, {}),
					0.f, 50.f,
					0.1f, 1, true, "", "", [] {}
				);

				core->add_option<number_option<float>>("Size W",
					nullptr,
					&*(float*)engine::memory::scan_address(g_base_address + 0x26E61BC, {}),
					0.f, 50.f,
					0.1f, 1, true, "", "", [] {}
				);

				core->add_option<number_option<float>>("Rot Speed Min",
					nullptr,
					&*(float*)engine::memory::scan_address(g_base_address + 0x26E61F0, {}),
					0.f, 50.f,
					0.1f, 1, true, "", "", [] {}
				);

				core->add_option<number_option<float>>("Rot Speed Max",
					nullptr,
					&*(float*)engine::memory::scan_address(g_base_address + 0x26E61F4, {}),
					0.f, 50.f,
					0.1f, 1, true, "", "", [] {}
				);

				core->add_option<number_option<float>>("Directional Z Offset X",
					nullptr,
					&*(float*)engine::memory::scan_address(g_base_address + 0x26E6200, {}),
					0.f, 50.f,
					0.1f, 1, true, "", "", [] {}
				);

				core->add_option<number_option<float>>("Directional Z Offset Y",
					nullptr,
					&*(float*)engine::memory::scan_address(g_base_address + 0x26E6204, {}),
					0.f, 50.f,
					0.1f, 1, true, "", "", [] {}
				);

				core->add_option<number_option<float>>("Directional Z Offset Z",
					nullptr,
					&*(float*)engine::memory::scan_address(g_base_address + 0x26E6208, {}),
					0.f, 50.f,
					0.1f, 1, true, "", "", [] {}
				);

				core->add_option<number_option<float>>("Edge Softness",
					nullptr,
					&*(float*)engine::memory::scan_address(g_base_address +  0x26E6220, {}),
					0.f, 50.f,
					0.1f, 1, true, "", "", [] {}
				);
			});
	}

	void weather_fx_menu::script_init() {}

	void weather_fx_menu::script_on_tick()
	{
		uintptr_t rain_red = engine::memory::scan_address(g_base_address + 0x26E61C0, {});
		uintptr_t rain_green = engine::memory::scan_address(g_base_address + 0x26E61C4, {});
		uintptr_t rain_blue = engine::memory::scan_address(g_base_address + 0x26E61C8, {});

		*(float*)rain_red = (m_vars.m_rain_red / 255.f) * m_vars.m_rain_intensity;
		*(float*)rain_green = (m_vars.m_rain_green / 255.f) * m_vars.m_rain_intensity;
		*(float*)rain_blue = (m_vars.m_rain_blue / 255.f) * m_vars.m_rain_intensity;

	}

	void weather_fx_menu::script_func()
	{
		m_weather_fx_menu.script_init();
		while (true)
		{
			m_weather_fx_menu.script_on_tick();

			script::get_current()->yield();
		}
	}
}