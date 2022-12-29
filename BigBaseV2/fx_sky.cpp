#include "common.hpp"
#include "gta_util.hpp"
#include "fx_sky.h"
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
#include "vfx_types.h"
#include "scroll.h"
using namespace big::game_fx::sky::vars;


namespace big::game_fx::sky::vars
{
	variables m_vars;

	const char* elements[7] = {
		"Azimuth East", "Azimuth West", "Azimuth Transition", "Zenith", "Zenith Transition", "Cloud Base", "Cloud Mid"
	};
	std::size_t element_id = 0;

}
namespace big::menu
{
	void game_fx_sky_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Sky", SubGameFxSky, [](sub* core)
			{
				m_sky_open = true;
				m_renderer.m_enable_player_info = false;
				core->add_option<scroll_option<const char*, std::size_t>>(("Element"), nullptr, &elements, &element_id);
				switch (element_id) {
				case 0:
					core->add_option<number_option<float>>("Red",
						nullptr,
						&m_vars.m_azimuth_east_red,
						0.f, 255.f,
						1.f, 1, true, "", "", []{ std::fill_n(g_pointers->m_east_azimuth_patch, 4, '\x90'); }
					);
					core->add_option<number_option<float>>("Green",
						nullptr,
						&m_vars.m_azimuth_east_green,
						0.f, 255.f,
						1.f, 1, true, "", "", [] { std::fill_n(g_pointers->m_east_azimuth_patch, 4, '\x90'); }
					);
					core->add_option<number_option<float>>("Blue",
						nullptr,
						&m_vars.m_azimuth_east_blue,
						0.f, 255.f,
						1.f, 1, true, "", "", [] { std::fill_n(g_pointers->m_east_azimuth_patch, 4, '\x90'); }
					);
					core->add_option<toggle_option<bool>>(("Rainbow"),
						nullptr,
						&m_vars.m_azimuth_east_rainbow
						);
					core->add_option<number_option<float>>("Luminance",
						nullptr,
						&m_vars.m_azimuth_east_intensity,
						0.f, 10.f,
						0.1f, 1, true, "", "", [] { std::fill_n(g_pointers->m_east_azimuth_patch, 4, '\x90'); }
					);

					core->add_option<simple_option>(("Reset To Default"),
						nullptr,
						[] {
							std::copy_n("\x0F\x29\x62\x20", 4, g_pointers->m_east_azimuth_patch);				
						}
					);
					break;
				case 1:
					core->add_option<number_option<float>>("Red",
						nullptr,
						&m_vars.m_azimuth_west_red,
						0.f, 255.f,
						1.f, 1, true, "", "", [] { std::fill_n(g_pointers->m_west_azimuth_patch, 4, '\x90'); }
					);
					core->add_option<number_option<float>>("Green",
						nullptr,
						&m_vars.m_azimuth_west_green,
						0.f, 255.f,
						1.f, 1, true, "", "", [] { std::fill_n(g_pointers->m_west_azimuth_patch, 4, '\x90'); }
					);
					core->add_option<number_option<float>>("Blue",
						nullptr,
						&m_vars.m_azimuth_west_blue,
						0.f, 255.f,
						1.f, 1, true, "", "", [] { std::fill_n(g_pointers->m_west_azimuth_patch, 4, '\x90'); }
					);
					core->add_option<toggle_option<bool>>(("Rainbow"),
						nullptr,
						&m_vars.m_azimuth_west_rainbow
						);
					core->add_option<number_option<float>>("Luminance",
						nullptr,
						&m_vars.m_azimuth_west_intensity,
						0.f, 10.f,
						0.1f, 1, true, "", "", [] { std::fill_n(g_pointers->m_west_azimuth_patch, 4, '\x90'); }
					);
					core->add_option<simple_option>(("Reset To Default"),
						nullptr,
						[] {
							std::copy_n("\x0F\x29\x62\x50", 4, g_pointers->m_west_azimuth_patch);
						}
					);
					break;
				case 2:
					core->add_option<number_option<float>>("Red",
						nullptr,
						&m_vars.m_azimuth_transition_red,
						0.f, 255.f,
						1.f, 1, true, "", "", [] { std::fill_n(g_pointers->m_azimuth_transition_patch, 7, '\x90'); }
					);
					core->add_option<number_option<float>>("Green",
						nullptr,
						&m_vars.m_azimuth_transition_green,
						0.f, 255.f,
						1.f, 1, true, "", "", [] { std::fill_n(g_pointers->m_azimuth_transition_patch, 7, '\x90'); }
					);
					core->add_option<number_option<float>>("Blue",
						nullptr,
						&m_vars.m_azimuth_transition_blue,
						0.f, 255.f,
						1.f, 1, true, "", "", [] { std::fill_n(g_pointers->m_azimuth_transition_patch, 7, '\x90'); }
					);
					core->add_option<toggle_option<bool>>(("Rainbow"),
						nullptr,
						&m_vars.m_azimuth_transition_rainbow
						);
					core->add_option<number_option<float>>("Luminance",
						nullptr,
						&m_vars.m_azimuth_transition_intensity,
						0.f, 10.f,
						0.1f, 1, true, "", "", [] { std::fill_n(g_pointers->m_azimuth_transition_patch, 7, '\x90'); }
					);
					core->add_option<simple_option>(("Reset To Default"),
						nullptr,
						[] {
							std::copy_n("\x0F\x29\xA2\x80", 7, g_pointers->m_azimuth_transition_patch);
						}
					);
					break;
				case 3:
					core->add_option<number_option<float>>("Red",
						nullptr,
						&m_vars.m_zenith_red,
						0.f, 255.f,
						1.f, 1, true, "", "", [] { std::fill_n(g_pointers->m_zenith_patch, 7, '\x90'); }
					);
					core->add_option<number_option<float>>("Green",
						nullptr,
						&m_vars.m_zenith_green,
						0.f, 255.f,
						1.f, 1, true, "", "", [] { std::fill_n(g_pointers->m_zenith_patch, 7, '\x90'); }
					);
					core->add_option<number_option<float>>("Blue",
						nullptr,
						&m_vars.m_zenith_blue,
						0.f, 255.f,
						1.f, 1, true, "", "", [] { std::fill_n(g_pointers->m_zenith_patch, 7, '\x90'); }
					);
					core->add_option<toggle_option<bool>>(("Rainbow"),
						nullptr,
						&m_vars.m_zenith_rainbow
					);
					core->add_option<number_option<float>>("Luminance",
						nullptr,
						&m_vars.m_zenith_intensity,
						0.f, 10.f,
						0.1f, 1, true, "", "", [] { std::fill_n(g_pointers->m_zenith_patch, 7, '\x90'); }
					);
					core->add_option<simple_option>(("Reset To Default"),
						nullptr,
						[] {
							std::copy_n("\x0F\x29\xA2\xB0", 7, g_pointers->m_zenith_patch);
						}
					);
					break;
				case 4:
					core->add_option<number_option<float>>("Red",
						nullptr,
						&m_vars.m_zenith_transition_red,
						0.f, 255.f,
						1.f, 1, true, "", "", [] { std::fill_n(g_pointers->m_zenith_transition_patch, 7, '\x90'); }
					);
					core->add_option<number_option<float>>("Green",
						nullptr,
						&m_vars.m_zenith_transition_green,
						0.f, 255.f,
						1.f, 1, true, "", "", [] { std::fill_n(g_pointers->m_zenith_transition_patch, 7, '\x90'); }
					);
					core->add_option<number_option<float>>("Blue",
						nullptr,
						&m_vars.m_zenith_transition_blue,
						0.f, 255.f,
						1.f, 1, true, "", "", [] { std::fill_n(g_pointers->m_zenith_transition_patch, 7, '\x90'); }
					);
					core->add_option<toggle_option<bool>>(("Rainbow"),
						nullptr,
						&m_vars.m_zenith_transition_rainbow
					);
					core->add_option<number_option<float>>("Luminance",
						nullptr,
						&m_vars.m_zenith_transition_intensity,
						0.f, 10.f,
						0.1f, 1, true, "", "", [] { std::fill_n(g_pointers->m_zenith_transition_patch, 7, '\x90'); }
					);
					core->add_option<simple_option>(("Reset To Default"),
						nullptr,
						[] {
							std::copy_n("\x0F\x29\xA2\xE0", 7, g_pointers->m_zenith_transition_patch);
						}
					);
					break;
				case 5:
					core->add_option<number_option<float>>("Red",
						nullptr,
						&m_vars.m_cloud_mid_red,
						0.f, 255.f,
						1.f, 1, true, "", "", [] { std::fill_n(g_pointers->m_cloud_mid_patch, 7, '\x90'); }
					);
					core->add_option<number_option<float>>("Green",
						nullptr,
						&m_vars.m_cloud_mid_green,
						0.f, 255.f,
						1.f, 1, true, "", "", [] { std::fill_n(g_pointers->m_cloud_mid_patch, 7, '\x90'); }
					);
					core->add_option<number_option<float>>("Blue",
						nullptr,
						&m_vars.m_cloud_mid_blue,
						0.f, 255.f,
						1.f, 1, true, "", "", [] { std::fill_n(g_pointers->m_cloud_mid_patch, 7, '\x90'); }
					);
					core->add_option<toggle_option<bool>>(("Rainbow"),
						nullptr,
						&m_vars.m_cloud_mid_rainbow
					);
					core->add_option<number_option<float>>("Luminance",
						nullptr,
						&m_vars.m_cloud_mid_intensity,
						0.f, 10.f,
						0.1f, 1, true, "", "", [] { std::fill_n(g_pointers->m_cloud_mid_patch, 7, '\x90'); }
					);
					core->add_option<simple_option>(("Reset To Default"),
						nullptr,
						[] {
							std::copy_n("\x0F\x29\x8B\x60\x03", 7, g_pointers->m_cloud_mid_patch);
						}
					);
					break;
				case 6:
					core->add_option<number_option<float>>("Red",
						nullptr,
						&m_vars.m_cloud_base_red,
						0.f, 255.f,
						1.f, 1, true, "", "", [] { std::fill_n(g_pointers->m_cloud_base_patch, 7, '\x90'); }
					);
					core->add_option<number_option<float>>("Green",
						nullptr,
						&m_vars.m_cloud_base_green,
						0.f, 255.f,
						1.f, 1, true, "", "", [] { std::fill_n(g_pointers->m_cloud_base_patch, 7, '\x90'); }
					);
					core->add_option<number_option<float>>("Blue",
						nullptr,
						&m_vars.m_cloud_base_blue,
						0.f, 255.f,
						1.f, 1, true, "", "", [] { std::fill_n(g_pointers->m_cloud_base_patch, 7, '\x90'); }
					);
					core->add_option<toggle_option<bool>>(("Rainbow"),
						nullptr,
						&m_vars.m_cloud_base_rainbow
					);
					core->add_option<number_option<float>>("Luminance",
						nullptr,
						&m_vars.m_cloud_base_intensity,
						0.f, 10.f,
						0.1f, 1, true, "", "", [] { std::fill_n(g_pointers->m_cloud_base_patch, 7, '\x90'); }
					);
					core->add_option<simple_option>(("Reset To Default"),
						nullptr,
						[] {
							std::copy_n("\x0F\x29\xA2\x80\x03", 7, g_pointers->m_cloud_base_patch);
						}
					);
					break;
				}
			});
	}

	void game_fx_sky_menu::script_init()
	{
	

	}
	
	void game_fx_sky_menu::script_on_tick() 
	{
		if (m_sky_open) {
			
			//azimuth east
			uintptr_t east_red = engine::memory::scan_address(g_base_address + 0x26BB8D0, {});
			uintptr_t east_green = engine::memory::scan_address(g_base_address + 0x26BB8D4, {});
			uintptr_t east_blue = engine::memory::scan_address(g_base_address + 0x26BB8D8, {});

			*(float*)east_red = (m_vars.m_azimuth_east_red / 255.f) * m_vars.m_azimuth_east_intensity;
			*(float*)east_green = (m_vars.m_azimuth_east_green / 255.f) * m_vars.m_azimuth_east_intensity;
			*(float*)east_blue = (m_vars.m_azimuth_east_blue / 255.f) * m_vars.m_azimuth_east_intensity;

			//azimuth west
			uintptr_t west_red = engine::memory::scan_address(g_base_address + 0x26BB900, {});
			uintptr_t west_green = engine::memory::scan_address(g_base_address + 0x26BB904, {});
			uintptr_t west_blue = engine::memory::scan_address(g_base_address + 0x26BB908, {});

			*(float*)west_red = (m_vars.m_azimuth_west_red / 255.f) * m_vars.m_azimuth_west_intensity;
			*(float*)west_green = (m_vars.m_azimuth_west_green / 255.f) * m_vars.m_azimuth_west_intensity;
			*(float*)west_blue = (m_vars.m_azimuth_west_blue / 255.f) * m_vars.m_azimuth_west_intensity;

			//azimuth transition
			uintptr_t azi_trans_red = engine::memory::scan_address(g_base_address + 0x26BB930, {});
			uintptr_t azi_trans_green = engine::memory::scan_address(g_base_address + 0x26BB934, {});
			uintptr_t azi_trans_blue = engine::memory::scan_address(g_base_address + 0x26BB938, {});

			*(float*)azi_trans_red = (m_vars.m_azimuth_transition_red / 255.f) * m_vars.m_azimuth_transition_intensity;
			*(float*)azi_trans_green = (m_vars.m_azimuth_transition_green / 255.f) * m_vars.m_azimuth_transition_intensity;
			*(float*)azi_trans_blue = (m_vars.m_azimuth_transition_blue / 255.f) * m_vars.m_azimuth_transition_intensity;

			//zenith
			uintptr_t zenith_red = engine::memory::scan_address(g_base_address + 0x26BB960, {});
			uintptr_t zenith_green = engine::memory::scan_address(g_base_address + 0x26BB964, {});
			uintptr_t zenith_blue = engine::memory::scan_address(g_base_address + 0x26BB968, {});

			*(float*)zenith_red = (m_vars.m_zenith_red / 255.f) * m_vars.m_zenith_intensity;
			*(float*)zenith_green = (m_vars.m_zenith_green / 255.f) * m_vars.m_zenith_intensity;
			*(float*)zenith_blue = (m_vars.m_zenith_blue / 255.f) * m_vars.m_zenith_intensity;

			//zenith transition
			uintptr_t zenith_transition_red = engine::memory::scan_address(g_base_address + 0x26BB990, {});
			uintptr_t zenith_transition_green = engine::memory::scan_address(g_base_address + 0x26BB994, {});
			uintptr_t zenith_transition_blue = engine::memory::scan_address(g_base_address + 0x26BB998, {});

			*(float*)zenith_transition_red = (m_vars.m_zenith_transition_red / 255.f) * m_vars.m_zenith_transition_intensity;
			*(float*)zenith_transition_green = (m_vars.m_zenith_transition_green / 255.f) * m_vars.m_zenith_transition_intensity;
			*(float*)zenith_transition_blue = (m_vars.m_zenith_transition_blue / 255.f) * m_vars.m_zenith_transition_intensity;

			//cloud mid
			uintptr_t cloud_mid_red = engine::memory::scan_address(g_base_address + 0x26BBC10, {});
			uintptr_t cloud_mid_green = engine::memory::scan_address(g_base_address + 0x26BBC14, {});
			uintptr_t cloud_mid_blue = engine::memory::scan_address(g_base_address + 0x26BBC18, {});

			*(float*)cloud_mid_red = (m_vars.m_cloud_mid_red / 255.f) * m_vars.m_cloud_mid_intensity;
			*(float*)cloud_mid_green = (m_vars.m_cloud_mid_green / 255.f) * m_vars.m_cloud_mid_intensity;
			*(float*)cloud_mid_blue = (m_vars.m_cloud_mid_blue / 255.f) * m_vars.m_cloud_mid_intensity;

			//cloud base
			uintptr_t cloud_base_red = engine::memory::scan_address(g_base_address + 0x26BBC30, {});
			uintptr_t cloud_base_green = engine::memory::scan_address(g_base_address + 0x26BBC34, {});
			uintptr_t cloud_base_blue = engine::memory::scan_address(g_base_address + 0x26BBC38, {});

			*(float*)cloud_base_red = (m_vars.m_cloud_base_red / 255.f) * m_vars.m_cloud_base_intensity;
			*(float*)cloud_base_green = (m_vars.m_cloud_base_green / 255.f) * m_vars.m_cloud_base_intensity;
			*(float*)cloud_base_blue = (m_vars.m_cloud_base_blue / 255.f) * m_vars.m_cloud_base_intensity;


			if (m_vars.m_azimuth_east_rainbow) {
				if (m_vars.m_azimuth_east_red > 0 && m_vars.m_azimuth_east_blue == 0) {
					m_vars.m_azimuth_east_red--;
					m_vars.m_azimuth_east_green++;
				}
				if (m_vars.m_azimuth_east_green > 0 && m_vars.m_azimuth_east_red == 0) {
					m_vars.m_azimuth_east_green--;
					m_vars.m_azimuth_east_blue++;
				}
				if (m_vars.m_azimuth_east_blue > 0 && m_vars.m_azimuth_east_green == 0) {
					m_vars.m_azimuth_east_red++;
					m_vars.m_azimuth_east_blue--;
				}
			}

			if (m_vars.m_azimuth_west_rainbow) {

				if (m_vars.m_azimuth_west_red > 0 && m_vars.m_azimuth_west_blue == 0) {
					m_vars.m_azimuth_west_red--;
					m_vars.m_azimuth_west_green++;
				}
				if (m_vars.m_azimuth_west_green > 0 && m_vars.m_azimuth_west_red == 0) {
					m_vars.m_azimuth_west_green--;
					m_vars.m_azimuth_west_blue++;
				}
				if (m_vars.m_azimuth_west_blue > 0 && m_vars.m_azimuth_west_green == 0) {
					m_vars.m_azimuth_west_red++;
					m_vars.m_azimuth_west_blue--;
				}
			}

			if (m_vars.m_azimuth_transition_rainbow) {
	
				if (m_vars.m_azimuth_transition_red > 0 && m_vars.m_azimuth_transition_blue == 0) {
					m_vars.m_azimuth_transition_red--;
					m_vars.m_azimuth_transition_green++;
				}
				if (m_vars.m_azimuth_transition_green > 0 && m_vars.m_azimuth_transition_red == 0) {
					m_vars.m_azimuth_transition_green--;
					m_vars.m_azimuth_transition_blue++;
				}
				if (m_vars.m_azimuth_transition_blue > 0 && m_vars.m_azimuth_transition_green == 0) {
					m_vars.m_azimuth_transition_red++;
					m_vars.m_azimuth_transition_blue--;
				}
			}

			if (m_vars.m_zenith_rainbow) {
	
				if (m_vars.m_zenith_red > 0 && m_vars.m_zenith_blue == 0) {
					m_vars.m_zenith_red--;
					m_vars.m_zenith_green++;
				}
				if (m_vars.m_zenith_green > 0 && m_vars.m_zenith_red == 0) {
					m_vars.m_zenith_green--;
					m_vars.m_zenith_blue++;
				}
				if (m_vars.m_zenith_blue > 0 && m_vars.m_zenith_green == 0) {
					m_vars.m_zenith_red++;
					m_vars.m_zenith_blue--;
				}
			}

			if (m_vars.m_zenith_transition_rainbow) {

				if (m_vars.m_zenith_transition_red > 0 && m_vars.m_zenith_transition_blue == 0) {
					m_vars.m_zenith_transition_red--;
					m_vars.m_zenith_transition_green++;
				}
				if (m_vars.m_zenith_transition_green > 0 && m_vars.m_zenith_transition_red == 0) {
					m_vars.m_zenith_transition_green--;
					m_vars.m_zenith_transition_blue++;
				}
				if (m_vars.m_zenith_transition_blue > 0 && m_vars.m_zenith_transition_green == 0) {
					m_vars.m_zenith_transition_red++;
					m_vars.m_zenith_transition_blue--;
				}
			}

			if (m_vars.m_cloud_mid_rainbow) {

				if (m_vars.m_cloud_mid_red > 0 && m_vars.m_cloud_mid_blue == 0) {
					m_vars.m_cloud_mid_red--;
					m_vars.m_cloud_mid_green++;
				}
				if (m_vars.m_cloud_mid_green > 0 && m_vars.m_cloud_mid_red == 0) {
					m_vars.m_cloud_mid_green--;
					m_vars.m_cloud_mid_blue++;
				}
				if (m_vars.m_cloud_mid_blue > 0 && m_vars.m_cloud_mid_green == 0) {
					m_vars.m_cloud_mid_red++;
					m_vars.m_cloud_mid_blue--;
				}
			}

			if (m_vars.m_cloud_base_rainbow) {

				if (m_vars.m_cloud_base_red > 0 && m_vars.m_cloud_base_blue == 0) {
					m_vars.m_cloud_base_red--;
					m_vars.m_cloud_base_green++;
				}
				if (m_vars.m_cloud_base_green > 0 && m_vars.m_cloud_base_red == 0) {
					m_vars.m_cloud_base_green--;
					m_vars.m_cloud_base_blue++;
				}
				if (m_vars.m_cloud_base_blue > 0 && m_vars.m_cloud_base_green == 0) {
					m_vars.m_cloud_base_red++;
					m_vars.m_cloud_base_blue--;
				}
			}
		}
	}
	void game_fx_sky_menu::script_func()
	{
		m_game_fx_sky_menu.script_init();
		while (true)
		{
			m_game_fx_sky_menu.script_on_tick();

			script::get_current()->yield();
		}
	}
}