#include "common.hpp"
#include "gta_util.hpp"
#include "network_selected_abusive_attackers.h"
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
#include "script_global.hpp"
#include "scroll.h"
#include "util.h"
using namespace big::network::selected_player::abusive::attackers::vars;


namespace big::network::selected_player::abusive::attackers::vars
{
	variables m_vars;
	void spawnAttacker(Player victim, const char* model, const char* weapon) {
		Player vic = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(victim);
		int enemyarray[1000];
		int enemyindex = 1;
		if (!ENTITY::DOES_ENTITY_EXIST(vic)) return;
		Hash gun = rage::joaat(m_vars.AttackerWeapon);
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(vic, 1);
		Hash pedm = rage::joaat(m_vars.AttackerModel);
		STREAMING::REQUEST_MODEL(pedm);
		while (!STREAMING::HAS_MODEL_LOADED(pedm))
			script::get_current()->yield();
		*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
		enemyarray[enemyindex] = PED::CREATE_PED(26, pedm, pos.x + rand() % 1, pos.y + rand() % 1, pos.z + 1, 0, 1, 1);
		*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;
		ENTITY::SET_ENTITY_INVINCIBLE(enemyarray[enemyindex], false);
		PED::SET_PED_COMBAT_ABILITY(enemyarray[enemyindex], 100);
		WEAPON::GIVE_WEAPON_TO_PED(enemyarray[enemyindex], gun, gun, 9999, 9999);
		PED::SET_PED_CAN_SWITCH_WEAPON(enemyarray[enemyindex], true);
		TASK::TASK_COMBAT_PED(enemyarray[enemyindex], vic, 1, 1);
		PED::SET_PED_ALERTNESS(enemyarray[enemyindex], 1000);
		PED::SET_PED_COMBAT_RANGE(enemyarray[enemyindex], 1000);
		enemyindex++;
	}
}

namespace big::menu
{


	void network_selected_abusive_attackers_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<PlayerSubmenu>(&selected_player, SubSelectedAbusiveAttackers, [](PlayerSubmenu* core)
			{
				m_renderer.m_enable_player_info = true;

				core->add_option<submenu>(("Model"), nullptr, Remote_AttackerModel);
				core->add_option<submenu>(("Weapon"), nullptr, Remote_AttackWeapon);
				core->add_option<simple_option>(("Spawn Attacker"), nullptr, [=]
					{

						if (m_vars.AttackerModel != NULL) {
							spawnAttacker(selected_player, m_vars.AttackerModel, m_vars.AttackerWeapon);
						}
					});

			});

		m_renderer.new_sub<PlayerSubmenu>(&selected_player, Remote_AttackerModel, [](PlayerSubmenu* sub)
			{

				m_renderer.m_enable_player_info = true;
				for (auto i : lists::g_ped_model_popular) {
					sub->add_option<simple_option>(i, nullptr, [=]
						{

							m_vars.AttackerModel = i;
						});
				}

			});
		m_renderer.new_sub<PlayerSubmenu>(&selected_player, Remote_AttackWeapon, [](PlayerSubmenu* sub)
			{

				m_renderer.m_enable_player_info = true;

				sub->add_option<simple_option>(("Railgun"), nullptr, [=]
					{

						m_vars.AttackerWeapon = "WEAPON_RAILGUN";
					});
				sub->add_option<simple_option>(("Heavy Sniper"), nullptr, [=]
					{

						m_vars.AttackerWeapon = "WEAPON_HEAVYSNIPER";
					});
				sub->add_option<simple_option>(("Assault Rifle"), nullptr, [=]
					{

						m_vars.AttackerWeapon = "WEAPON_CARBINERIFLE";
					});
				sub->add_option<simple_option>(("Shotgun"), nullptr, [=]
					{

						m_vars.AttackerWeapon = "WEAPON_PUMPSHOTGUN";
					});
				sub->add_option<simple_option>(("Machine Gun"), nullptr, [=]
					{

						m_vars.AttackerWeapon = "WEAPON_MG";
					});
			});
	}

	void network_selected_abusive_attackers_menu::script_init() {}

	void network_selected_abusive_attackers_menu::script_on_tick()
	{
		
	}

	void network_selected_abusive_attackers_menu::script_func()
	{
		m_network_selected_abusive_attackers_menu.script_init();
		while (true)
		{
			m_network_selected_abusive_attackers_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}