#include "common.hpp"
#include "gta_util.hpp"
#include "protections_reactions.h"
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
#include "scroll.h"
#include "xorstr.h"	
#include "player_service.hpp"
#include "script_global.hpp"
#include <nlohmann/json.hpp>
#include "json.h"
using namespace big::protections::reactions::vars;

namespace big::protections::reactions::vars {


	variables m_vars;
	
}

namespace big::menu
{

	void protections_reactions_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Reactions", SubProtectionsReactions, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;

				core->add_option<submenu>("Death",
					nullptr,
					SubProtectionsNetworkEvents
				);

				core->add_option<submenu>("Aim",
					nullptr,
					SubProtectionsNetworkEvents
				);

				core->add_option<submenu>("Report",
					nullptr,
					SubProtectionsNetworkEvents
				);

				core->add_option<submenu>("Spoofed Name",
					nullptr,
					SubProtectionsNetworkEvents
				);

				core->add_option<submenu>("Spoofed Rockstar ID",
					nullptr,
					SubProtectionsNetworkEvents
				);

				core->add_option<submenu>("Spoofed Host Token",
					nullptr,
					SubProtectionsNetworkEvents
				);

				core->add_option<submenu>("Crash Attempt",
					nullptr,
					SubProtectionsNetworkEvents
				);

				core->add_option<submenu>("Kick Attempt",
					nullptr,
					SubProtectionsNetworkEvents
				);
				core->add_option<submenu>("Spectate",
					nullptr,
					SubProtectionsNetworkEvents
					);

				core->add_option<submenu>("Money Drop",
					nullptr,
					SubProtectionsNetworkEvents
				);

				core->add_option<submenu>("Arxan",
					nullptr,
					SubProtectionsNetworkEvents
					);

				core->add_option<submenu>("Super Jump",
					nullptr,
					SubProtectionsNetworkEvents
				);

				core->add_option<submenu>("Explosive Ammo",
					nullptr,
					SubProtectionsNetworkEvents
				);

				core->add_option<submenu>("Fire Ammo",
					nullptr,
					SubProtectionsNetworkEvents
				);

				core->add_option<submenu>("Explosive Fist",
					nullptr,
					SubProtectionsNetworkEvents
				);

				core->add_option<submenu>("Invalid Model",
					nullptr,
					SubProtectionsNetworkEvents
				);


				core->add_option<submenu>("Forced Script Host",
					nullptr,
					SubProtectionsNetworkEvents
				);

			});
	}

	void protections_reactions_menu::script_init() {}

	void protections_reactions_menu::script_on_tick()
	{
		static uint32_t last_aim[32];
		for (uint32_t i = 0; i < 32; ++i)
		{

			if (g_pointers->m_net_game_player(i)->m_player_id != PLAYER::PLAYER_ID()) {
				if (!ENTITY::IS_ENTITY_DEAD(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), 0)) {
					if (g_pointers->m_net_game_player(i)->m_player_info->m_ped) {
						if (g_pointers->m_net_game_player(i)->m_player_info->m_ped->m_net_object) {
							if (g_pointers->m_net_game_player(i)->m_player_info->m_ped->m_net_object->m_spectating_network_id) {
								rage::netObject* object = g_pointers->m_get_net_object_for_player(*g_pointers->m_network_object_mgr, g_pointers->m_net_game_player(i)->m_player_info->m_ped->m_net_object->m_spectating_network_id, true);
								if (object->m_owner_id >= 0 && object->m_owner_id < 32) {
									if ((GetTickCount() - m_vars.m_spectate_map[g_pointers->m_net_game_player(i)->m_player_id][object->m_owner_id]) > 5000) {
										m_vars.m_spectate_map[g_pointers->m_net_game_player(i)->m_player_id][object->m_owner_id] = GetTickCount();

										std::string target = g_pointers->m_net_game_player(object->m_owner_id)->get_name();
										if (!target.compare(PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID()))) {
											target = "you";
										}

										LOG(INFO) << g_pointers->m_net_game_player(i)->get_name() << " is spectating " << target;
									}
								}
							}
						}
					}
				}

			}
		}
		
	}

	void protections_reactions_menu::script_func()
	{
		m_protections_reactions_menu.script_init();
		while (true)
		{
			m_protections_reactions_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}