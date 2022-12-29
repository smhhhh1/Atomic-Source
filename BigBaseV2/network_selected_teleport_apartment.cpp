#include "common.hpp"
#include "gta_util.hpp"
#include "network_selected_teleport_apartment.h"
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
#include "player_submenu.h"
#include "../submenus.h"
#include "on_screen_ped.h"
#include "lists.h"
#include "fiber_pool.hpp"
#include "gta/enums.hpp"
#include "notify.h"
#include "util.h"
#include "scroll.h"
namespace big::menu
{

	const char* Apartments[] =
	{
		"Eclipse Towers", "West Vinewood", "Las Lagunas", "Spanish Ave", "Power St", "Del Perro",
		"Milton Rd", "The Royale", "La Puerta", "Rockford Dr", "Dream Tower", "San Vitas", "Vespucci Blvd",
		"Cougar Ave", "Prosperity St","Weazel Plaza", "Del Perro Office", "Maze Bank West Office",
		"Arcadius Office", "Maze Bank Office"
	};
	int Apartments_Ids[] =
	{
		1, 6, 10, 9, 8, 7, 11, 12, 14, 15, 16, 18, 20, 21, 22, 35, 87, 88, 89, 90
	};
	int Apartments_pos{};
	void network_selected_teleport_apartment_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<PlayerSubmenu>(&selected_player, SubSelectedTeleportApartments, [](PlayerSubmenu* core)
			{
				m_renderer.m_enable_player_info = true;
				core->add_option<scroll_option<const char*, int>>(("Apartments"), nullptr, &Apartments, &Apartments_pos, true);
				core->add_option<simple_option>(("Teleport Player To Apartment"), nullptr, [] {
					int64_t args[9] = { -1390976345, PLAYER::PLAYER_ID(), 1, -1, 1, Apartments_Ids[Apartments_pos], 0,0,0};
					g_pointers->m_trigger_script_event(1, args, 9, 1 << selected_player);
					});
			});
	}

	void network_selected_teleport_apartment_menu::script_init() {}

	void network_selected_teleport_apartment_menu::script_on_tick()
	{

	}

	void network_selected_teleport_apartment_menu::script_func()
	{
		m_network_selected_teleport_apartment_menu.script_init();
		while (true)
		{


			m_network_selected_teleport_apartment_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}