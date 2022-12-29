#include "common.hpp"
#include "gta_util.hpp"
#include "player.h"
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
#include "gta/replay.hpp"
#include "script_global.hpp"
#include "../movement.h"
#include "../appearance.h"
#include "../wardrobe.h"
#include "../ptfx.h"
#include "../hand_trails.h"
#include "../proofs.h"
using namespace big::local::vars;


namespace big::local::vars
{
	variables m_vars;
	void no_ragdoll() {
		PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), !m_vars.m_disable_ragdoll);
		PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER::PLAYER_PED_ID(), !m_vars.m_disable_ragdoll);
		PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), !m_vars.m_disable_ragdoll);
	}
}

namespace big::menu
{
	

	void player_menu::menu()
	{
		using namespace ui;
		m_renderer.new_sub<sub>("Player", SubPlayer, [](sub* core)
			{
				core->add_option<submenu>("Appearance", nullptr, SubAppearance);
				core->add_option<submenu>("Movement", nullptr, SubMovement);
				core->add_option<submenu>("Animation", nullptr, SubAnimation);
				core->add_option<submenu>("Particle Fx", nullptr, SubParticleFx);
				core->add_option<submenu>("Hand Trails", nullptr, SubHandTrails);
				core->add_option<submenu>("Proofs", nullptr, SubProofs);

				core->add_option<toggle_option<bool>>(("Godmode"),
					nullptr,
					&m_vars.m_godmode,
					false, [&] {
						if (!m_vars.m_godmode)
							ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), false);
					});
				
				core->add_option<toggle_option<bool>>(("Disable Police"),
					nullptr,
					&m_vars.m_disable_police
					);

				core->add_option<toggle_option<bool>>(("Disable Ragdoll"),
					nullptr,
					&m_vars.m_disable_ragdoll
					);

				core->add_option<toggle_option<bool>>(("Invisibility"),
					nullptr,
					&m_vars.m_invisibility,
					false, [&] {
						if (!m_vars.m_invisibility) {
							ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true, true);
							NETWORK::SET_LOCAL_PLAYER_INVISIBLE_LOCALLY(false);
						}
					});

				core->add_option<toggle_option<bool>>(("Infinite Stamina"),
					nullptr,
					&m_vars.m_infinite_stamina
					);

				core->add_option<toggle_option<bool>>(("Infinite Ability"),
					nullptr,
					&m_vars.m_infinite_ability
					);

				core->add_option<toggle_option<bool>>(("Reduced Collision"),
					nullptr,
					&m_vars.m_reduced_collision
					);


				core->add_option<toggle_option<bool>>(("Tiny Ped"),
					nullptr,
					&m_vars.m_tiny_ped
					);
				core->add_option<toggle_option<bool>>(("Off Radar"),
					nullptr,
					&m_vars.m_off_the_radar
					);
				core->add_option<toggle_option<bool>>(("Swim Anywhere"),
					nullptr,
					&m_vars.m_swim_anywhere
					);


				core->add_option<toggle_option<bool>>(("Peds Ignore"),
					nullptr,
					&m_vars.m_invisibility,
					false, [&] {
						if (!m_vars.m_peds_ingore_player) {
							PLAYER::SET_POLICE_IGNORE_PLAYER(PLAYER::PLAYER_PED_ID(), true);
							PLAYER::SET_EVERYONE_IGNORE_PLAYER(PLAYER::PLAYER_PED_ID(), true);
							PLAYER::SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(PLAYER::PLAYER_PED_ID(), false);
						}
					});

				core->add_option<toggle_option<bool>>(("Superman"),
					nullptr,
					&m_vars.m_superman
					);

				core->add_option<toggle_option<bool>>(("Breath Fire"),
					nullptr,
					&m_vars.m_breathe_fire
					);

				core->add_option<toggle_option<bool>>(("Heal in Cover"),
					nullptr,
					&m_vars.m_heal_in_cover
					);

				core->add_option<simple_option>(("Health & Armour"),
					nullptr,
					[&] {
						gta_util::get_local_ped()->m_armor = 200;
						gta_util::get_local_ped()->m_health = 400;
					});

				core->add_option<simple_option>(("Clone"),
					nullptr, 
					[&] {
						*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
						PED::CLONE_PED(PLAYER::PLAYER_PED_ID(), 0, 1, 0);
						*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;
					});

				core->add_option<simple_option>(("Clean"),
					nullptr,
					[&] {
						Ped player_ped = PLAYER::PLAYER_PED_ID();

						PED::CLEAR_PED_BLOOD_DAMAGE(player_ped);
						PED::CLEAR_PED_WETNESS(player_ped);
						PED::CLEAR_PED_ENV_DIRT(player_ped);
						PED::RESET_PED_VISIBLE_DAMAGE(player_ped);
					});

				core->add_option<simple_option>(("Skydive"),
					nullptr,
					[&] {
						TASK::TASK_SKY_DIVE(PLAYER::PLAYER_PED_ID(), 0);
						auto c = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);
						ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), c.x, c.y, c.z + 700, 0, 0, 0, 0);
					});

				core->add_option<simple_option>(("Suicide"),
					nullptr, 
					[&] {
						gta_util::get_local_ped()->m_health = 0;	
					});
			});
	}

	void player_menu::script_init() {}

	void player_menu::script_on_tick() 
	{

		if (m_vars.m_godmode) {
			ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), true);
		}
		if (m_vars.m_disable_police) {
			gta_util::get_local_ped()->m_player_info->m_wanted_level = 0;
			g_pointers->m_max_wanted_level->apply();
			g_pointers->m_max_wanted_level_2->apply();
		}
		else {
			g_pointers->m_max_wanted_level->restore();
			g_pointers->m_max_wanted_level_2->restore();
		}
		if (m_vars.m_disable_ragdoll) {
			no_ragdoll();
		}
		
		if (m_vars.m_infinite_stamina) {
			gta_util::get_local_ped()->m_player_info->m_stamina = 100;
		}
		static bool bLastNoCollsion = false;
		
		bool bNoCollsion = m_vars.m_reduced_collision;

		if (bNoCollsion)
		{
			((rage::phBoundComposite*)gta_util::get_local_ped()->m_navigation->m_damp->m_bound)->m_bounds[0]->m_bounding_box_max_xyz_margin_w.w = -1;
			bLastNoCollsion = bNoCollsion;
		}
		else if (bNoCollsion != bLastNoCollsion)
		{
			((rage::phBoundComposite*)gta_util::get_local_ped()->m_navigation->m_damp->m_bound)->m_bounds[0]->m_bounding_box_max_xyz_margin_w.w = 0.25;
			bLastNoCollsion = bNoCollsion;
		}

		PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 223, m_vars.m_tiny_ped);
		PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 65, m_vars.m_swim_anywhere);
		
		if (m_vars.m_peds_ingore_player) {
			PLAYER::SET_POLICE_IGNORE_PLAYER(PLAYER::PLAYER_PED_ID(), false);
			PLAYER::SET_EVERYONE_IGNORE_PLAYER(PLAYER::PLAYER_PED_ID(), false);
			PLAYER::SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(PLAYER::PLAYER_PED_ID(), true);
		}

		if (m_vars.m_invisibility) {
			ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), false, false);
			NETWORK::SET_LOCAL_PLAYER_INVISIBLE_LOCALLY(true);
		}
		if (m_vars.m_heal_in_cover) {
			Ped playerPed = PLAYER::PLAYER_PED_ID();
			int health = ENTITY::GET_ENTITY_HEALTH(playerPed);
			if (PED::IS_PED_IN_COVER(playerPed, false) && !PED::IS_PED_AIMING_FROM_COVER(playerPed) && health < ENTITY::GET_ENTITY_MAX_HEALTH(playerPed))
			{
				static int timer;
				if ((GetTickCount() - timer) > 200)
				{
					static int healincoverint{ 3 };
					ENTITY::SET_ENTITY_HEALTH(playerPed, health + healincoverint, 0);
					timer = GetTickCount();
				}
			}
		}
		if (m_vars.m_breathe_fire) {
			if (STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("core")) {
				GRAPHICS::USE_PARTICLE_FX_ASSET("core");
				if (!GRAPHICS::DOES_PARTICLE_FX_LOOPED_EXIST(m_vars.m_breathe_fire_handle)) {
					m_vars.m_breathe_fire_handle = GRAPHICS::START_PARTICLE_FX_LOOPED_ON_ENTITY("ent_sht_flame", PLAYER::PLAYER_PED_ID(), -0.02f, 0.2f, 0.0f, 90.0f, 100.0f, 90.0f, PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), 31086), 1.0f, false, false);
				}
			}
			else {
				STREAMING::REQUEST_NAMED_PTFX_ASSET("core");
			}
		}
		if (m_vars.m_infinite_ability) {
			if (!PLAYER::IS_SPECIAL_ABILITY_ENABLED(PLAYER::PLAYER_ID()))
				PLAYER::ENABLE_SPECIAL_ABILITY(PLAYER::PLAYER_ID(), true);
			PLAYER::SET_SPECIAL_ABILITY_MULTIPLIER(m_vars.m_infinite_ability ? FLT_MAX : 1);
			PLAYER::SPECIAL_ABILITY_FILL_METER(PLAYER::PLAYER_ID(), m_vars.m_infinite_ability);
		}
		
		if (m_vars.m_off_the_radar) {
			*script_global(2657589).at(PLAYER::GET_PLAYER_INDEX(), 466).at(210).as<int*>() = m_vars.m_off_the_radar;
			*script_global(2672505).at(56).as<int*>() = NETWORK::GET_NETWORK_TIME() + 1;
		}
		if (m_vars.m_superman) {
			int left_right = PAD::GET_CONTROL_VALUE(2, 188);
			int up_down = PAD::GET_CONTROL_VALUE(2, 189);

			if (ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(PLAYER::PLAYER_PED_ID()) < 3.f) {
				WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, -1, true, true);

				Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				coords.z += 100.f;
				ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), coords.x, coords.y, coords.z, false, false, false, false);
			}
			else {
				if (up_down == 254 || GetAsyncKeyState(0x53)) {
					ENTITY::APPLY_FORCE_TO_ENTITY(PLAYER::PLAYER_PED_ID(), 1, 0.f, 3.f, 10.f, 0.f, 0.f, 0.f, false, true, true, true, false, true);
				}

				if (up_down == 0 || GetAsyncKeyState(0x57)) {
					ENTITY::APPLY_FORCE_TO_ENTITY(PLAYER::PLAYER_PED_ID(), 1, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, false, true, true, true, false, true);
				}

				if (GetAsyncKeyState(VK_SHIFT)) {
					ENTITY::APPLY_FORCE_TO_ENTITY(PLAYER::PLAYER_PED_ID(), 1, 0.f, 15.f, .3f, 0.f, 0.f, 0.f, false, true, true, true, false, true);
				}

				if (left_right == 254 || GetAsyncKeyState(0x44)) {
					ENTITY::APPLY_FORCE_TO_ENTITY(PLAYER::PLAYER_PED_ID(), 1, 1.20f, 0.f, 0.f, 0.f, 0.1f, 0.f, false, true, true, true, false, true);
				}

				if (left_right == 0 || GetAsyncKeyState(0x41)) {
					ENTITY::APPLY_FORCE_TO_ENTITY(PLAYER::PLAYER_PED_ID(), 1, -1.20f, 0.f, 0.f, 0.f, 0.1f, 0.f, false, true, true, true, false, true);
				}
			}
		}

	}

	void player_menu::script_func()
	{
		m_player_menu.script_init();
		while (true)
		{
			m_player_menu.script_on_tick();
			m_movement_menu.script_on_tick();
			m_appearance_menu.script_on_tick();
			m_hand_trails_menu.script_on_tick();
			m_proofs_menu.script_on_tick();
			m_ptfx_menu.script_on_tick();
			m_wardrobe_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}