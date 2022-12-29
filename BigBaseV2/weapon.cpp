#include "common.hpp"
#include "gta_util.hpp"
#include "weapon.h"
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
#include "math.h"
#include "util.h"
#include "../aimbot.h"
#include "../impacts.h"
#include "../entity_gun.h"
#include "../paint_gun.h"
#include "../gravity_gun.h"
#include "../magnet_gun.h"
#include "../explosion_gun.h"
#include "../particle_gun.h"
using namespace big::weapon::vars;


namespace big::weapon::vars
{
	variables m_vars;
	static std::vector<std::pair<uint32_t, float>> og_recoil_values{};
	static uint32_t prev_weapon_hash{};

	bool is_recoil_value_cached(uint32_t hash)
	{
		return std::find_if(og_recoil_values.begin(), og_recoil_values.end(), [hash](auto const entry)
			{
				return hash == entry.first;
			}) != og_recoil_values.end();
	}

	float get_og_recoil_value(uint32_t hash)
	{
		return std::find_if(og_recoil_values.begin(), og_recoil_values.end(), [hash](auto const entry)
			{
				return hash == entry.first;
			})->second;
	}

	float get_recoil_value(uint32_t hash)
	{
		return m_vars.m_no_recoil
			? 0.f
			: get_og_recoil_value(hash);
	}
	static std::vector<std::pair<uint32_t, float>> og_spread_values{};


	bool is_spread_value_cached(uint32_t hash)
	{
		return std::find_if(og_spread_values.begin(), og_spread_values.end(), [hash](auto const entry)
			{
				return hash == entry.first;
			}) != og_spread_values.end();
	}

	float get_og_spread_value(uint32_t hash)
	{
		return std::find_if(og_spread_values.begin(), og_spread_values.end(), [hash](auto const entry)
			{
				return hash == entry.first;
			})->second;
	}

	float get_spread_value(uint32_t hash)
	{
		return m_vars.m_no_spread
			? 0.f
			: get_og_spread_value(hash);
	}	
}

namespace big::menu
{

	void weapon_menu::menu()
	{
		using namespace ui;
		m_renderer.new_sub<sub>("Weapon", SubWeapon, [](sub* core)
			{
				core->add_option<submenu>("Aimbot", nullptr, SubAimbot);
				core->add_option<submenu>("Impacts", nullptr, SubImpacts);
				core->add_option<submenu>("Entity Gun", nullptr, SubEntityGun);
				core->add_option<submenu>("Paint Gun", nullptr, SubPaintGun);
				core->add_option<submenu>("Gravity Gun", nullptr, SubGravityGun);
				core->add_option<submenu>("Magnet Gun", nullptr, SubMagnetGun);
				core->add_option<submenu>("Explosion Gun", nullptr, SubExplosionGun);
				core->add_option<submenu>("Particle Gun", nullptr, SubParticleGun);
				core->add_option<submenu>("Gun Locker", nullptr, SubGunLocker);

				core->add_option<toggle_option<bool>>(("Infinite Ammo"),
					nullptr,
					&m_vars.m_infinite_ammo
				);
				core->add_option<toggle_option<bool>>(("Rapid Fire"),
					nullptr,
					&m_vars.m_rapid_fire
				);
				core->add_option<toggle_option<bool>>(("Explosive Ammo"),
					nullptr,
					&m_vars.m_explosive_ammo
				);
				core->add_option<toggle_option<bool>>(("Fire Ammo"),
					nullptr,
					&m_vars.m_fire_ammo
				);
				core->add_option<toggle_option<bool>>(("Water Ammo"),
					nullptr,
					&m_vars.m_water_ammo
				);
				core->add_option<toggle_option<bool>>(("Delete Gun"),
					nullptr,
					&m_vars.m_delete_gun
				);
				core->add_option<toggle_option<bool>>(("Teleport Gun"),
					nullptr,
					&m_vars.m_teleport_gun
				);
				core->add_option<toggle_option<bool>>(("Revive Gun"),
					nullptr,
					&m_vars.m_defibrillator_gun
				);
				core->add_option<toggle_option<bool>>(("Shrink Gun"),
					nullptr,
					&m_vars.m_shrink_gun
				);
				core->add_option<toggle_option<bool>>(("Drive Gun"),
					nullptr,
					&m_vars.m_drive_gun
				);
				core->add_option<toggle_option<bool>>(("Repair Gun"),
					nullptr,
					&m_vars.m_repair_gun
				);
				core->add_option<toggle_option<bool>>(("Airstrike Gun"),
					nullptr,
					&m_vars.m_airstrike_gun
				);
				core->add_option<toggle_option<bool>>(("Instant Kill"),
					nullptr,
					&m_vars.m_instant_kill
				);
				core->add_option<toggle_option<bool>>(("Trigger Bot"),
					nullptr,
					&m_vars.m_trigger_bot
					);
				core->add_option<toggle_option<bool>>(("No Recoil"),
					nullptr,
					&m_vars.m_no_recoil
				);
				core->add_option<toggle_option<bool>>(("No Spread"),
					nullptr,
					&m_vars.m_no_spread
				);
				core->add_option<toggle_option<bool>>(("Laser Sight"),
					nullptr,
					&m_vars.m_laser_sight
				);
				core->add_option<toggle_option<bool>>(("Asteriod Gun"),
					nullptr,
					&m_vars.m_asteriod_gun
				);
				core->add_option<toggle_option<bool>>(("Ped Gun"),
					nullptr,
					&m_vars.m_ped_gun
				);
				core->add_option<toggle_option<bool>>(("Valkyrie Gun"),
					nullptr,
					&m_vars.m_valkyrie_gun
				);
			});
	}

	void weapon_menu::script_init() {}

	void weapon_menu::script_on_tick()
	{
		uint32_t m_weapon_hash = 0;
		Entity cur_weapon_hash = WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &m_weapon_hash, 0);
		if (m_vars.m_infinite_ammo) {
			WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(), true);
		}
		if (m_vars.m_rapid_fire) {
			
			Player playerPed = PLAYER::PLAYER_PED_ID();
			if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
				PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_PED_ID(), 1);
				Vector3 gameplayCam = CAM::GET_GAMEPLAY_CAM_COORD();
				Vector3 gameplayCamRot = CAM::GET_GAMEPLAY_CAM_ROT(0);
				Vector3 gameplayCamDirection = RotationToDirection(gameplayCamRot);
				Vector3 startCoords = addVector(gameplayCam, (multiplyVector(gameplayCamDirection, 1.0f)));
				Vector3 endCoords = addVector(startCoords, multiplyVector(gameplayCamDirection, 500.0f));
				Hash weaponhash;
				WEAPON::GET_CURRENT_PED_WEAPON(playerPed, &weaponhash, 1);
				if (PAD::IS_CONTROL_PRESSED(2, 208) || (GetKeyState(VK_LBUTTON) & 0x8000)) {
					MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(startCoords.x, startCoords.y, startCoords.z, endCoords.x, endCoords.y, endCoords.z, 50, 1, weaponhash, playerPed, 1, 1, 0xbf800000);
				}
			}	
		}
		if (m_vars.m_explosive_ammo) {
			if (__shooting(PLAYER::PLAYER_PED_ID()))
			{
				Vector3 c;
				if (auto last = WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &c))
				{
					if (raycast(&last))
					{
						FIRE::ADD_EXPLOSION(c.x, c.y, c.z, 45, 1000, true, false, true, false);
					}
					
				}
			}
		}
		if (m_vars.m_fire_ammo) {
			if (__shooting(PLAYER::PLAYER_PED_ID()))
			{
				Vector3 c;
				if (auto last = WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &c))
				{
					if (raycast(&last))
					{
						FIRE::ADD_EXPLOSION(c.x, c.y, c.z, 12, 1000, true, false, true, false);
					}
					
				}
			}
		}
		if (m_vars.m_trigger_bot) {
			Entity PlayerTarget;
			if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &PlayerTarget))
			{
				//	Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_ID(), 1);

				if (ENTITY::IS_ENTITY_A_PED(PlayerTarget) && !ENTITY::IS_ENTITY_DEAD(PlayerTarget, 0) && ENTITY::GET_ENTITY_ALPHA(PlayerTarget) == 255)
				{
					//if (PED::IS_PED_SHOOTING_IN_AREA(PLAYER::PLAYER_ID(), coords.x, coords.y, coords.z, coords.x, coords.y, coords.z, true, true))
					if (__shooting)
					{
						Vector3 Head = PED::GET_PED_BONE_COORDS(PlayerTarget, 0x796E, 0.1f, 0.0f, 0.0f);
						PED::SET_PED_SHOOTS_AT_COORD(PLAYER::PLAYER_PED_ID(), Head.x, Head.y, Head.z, true);
					}

				}
			}
		}
		if (m_vars.m_water_ammo) {
			if (__shooting(PLAYER::PLAYER_PED_ID()))
			{
				Vector3 c;
				if (auto last = WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &c))
				{
					if (raycast(&last))
					{
						FIRE::ADD_EXPLOSION(c.x, c.y, c.z, 13, 1000, true, false, true, false);
					}
					
				}
			}
		}
		if (m_vars.m_no_recoil) {
			if (!gta_util::get_local_ped())
			{
				return;
			}

			auto* const weapon_mgr = gta_util::get_local_ped()->m_weapon_manager;
			if (weapon_mgr)
			{
				auto const cur_weapon_hash = weapon_mgr->m_selected_weapon_hash;
				if (prev_weapon_hash != cur_weapon_hash)
				{
					if (!is_recoil_value_cached(cur_weapon_hash))
					{
						og_recoil_values.push_back({ cur_weapon_hash, weapon_mgr->m_weapon_info->m_explosion_shake_amplitude });
					}

					weapon_mgr->m_weapon_info->m_explosion_shake_amplitude = get_recoil_value(cur_weapon_hash); // m_explosion_shake_amplitude is the right offset in https://github.com/Yimura/GTAV-Classes
				}
			}
		}
		if (m_vars.m_no_spread) {
			if (!gta_util::get_local_ped())
			{
				return;
			}

			auto* const weapon_mgr = gta_util::get_local_ped()->m_weapon_manager;
			if (weapon_mgr)
			{
				auto const cur_weapon_hash = weapon_mgr->m_selected_weapon_hash;
				if (prev_weapon_hash != cur_weapon_hash)
				{
					if (!is_spread_value_cached(cur_weapon_hash))
					{
						og_spread_values.push_back({ cur_weapon_hash, weapon_mgr->m_weapon_info->m_accuracy_spread });
					}

					weapon_mgr->m_weapon_info->m_accuracy_spread = get_spread_value(cur_weapon_hash);
				}
			}
		}
		if (m_vars.m_delete_gun) {
			Entity entity;
			if (__shooting(PLAYER::PLAYER_PED_ID())) {
				if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &entity)) {
					if (ENTITY::IS_ENTITY_A_PED(entity)) {
						entity = PED::IS_PED_IN_ANY_VEHICLE(entity, true) ? PED::GET_VEHICLE_PED_IS_IN(entity, false) : entity;
					}

					if (ENTITY::DOES_ENTITY_EXIST(entity)) {
						if (take_control_of(entity)) {
							ENTITY::SET_ENTITY_AS_MISSION_ENTITY(entity, true, true);
							ENTITY::DELETE_ENTITY(&entity);
						}
							
					}
				}
			}
		}
		if (m_vars.m_teleport_gun) {
			Ped playerPed = PLAYER::PLAYER_PED_ID();
			if (__shooting(playerPed))
			{
				Vector3 coords;
				if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(playerPed, &coords))
				{
					ENTITY::SET_ENTITY_COORDS(playerPed, coords.x, coords.y, coords.z, true, false, true, false);
				}
			}
		}
		if (m_vars.m_defibrillator_gun) {
			if (m_weapon_hash == 0x3656c8c1) {
				Entity aimed;
				if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &aimed)) {
					if (ENTITY::IS_ENTITY_A_PED(aimed) && ENTITY::IS_ENTITY_DEAD(aimed, 0)) {
						PED::RESURRECT_PED(aimed);
						PED::REVIVE_INJURED_PED(aimed);
						ENTITY::SET_ENTITY_HEALTH(aimed, 100, 0);
					}
				}
			}
		}
		if (m_vars.m_shrink_gun) {
			Entity aimed;
			if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &aimed)) {
				if (ENTITY::IS_ENTITY_A_PED(aimed)) {
					PED::SET_PED_CONFIG_FLAG(aimed, 223, true);
				}
			}
		}
		if (m_vars.m_instant_kill) {
			PLAYER::SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER(PLAYER::PLAYER_PED_ID(), 99999.f, 1);
			PLAYER::SET_PLAYER_WEAPON_DAMAGE_MODIFIER(PLAYER::PLAYER_PED_ID(), 99999.f);
		}
		if (m_vars.m_drive_gun) {
			Entity ent;
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
			{
				if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_ATTACK))
				{
					if (raycast(&ent))
					{
						if (ENTITY::IS_ENTITY_A_VEHICLE(ent))
						{
							for (size_t i = 0; i < 8 && !VEHICLE::IS_VEHICLE_SEAT_FREE(ent, -1, 0); i++)
							{
								const auto ped = VEHICLE::GET_PED_IN_VEHICLE_SEAT(ent, -1, 0);
								TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);

								script::get_current()->yield(100ms);
							}

							PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), ent, -1);
						}
					}
				}
			}
		}
		if (m_vars.m_laser_sight) {
			Ped playerPed = PLAYER::PLAYER_PED_ID();
			float startDistance = must_Distance(CAM::GET_GAMEPLAY_CAM_COORD(), ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true));
			float endDistance = must_Distance(CAM::GET_GAMEPLAY_CAM_COORD(), ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true));
			startDistance += 5.25;
			endDistance += 1000.0;

			if (PED::IS_PED_ON_FOOT(playerPed) && PED::GET_PED_CONFIG_FLAG(playerPed, 78, 1))
			{

				GRAPHICS::DRAW_LINE(add(CAM::GET_GAMEPLAY_CAM_COORD(), multiply(rot_to_direction(CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).x,
					add(CAM::GET_GAMEPLAY_CAM_COORD(), multiply(rot_to_direction(CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).y,
					add(CAM::GET_GAMEPLAY_CAM_COORD(), multiply(rot_to_direction(CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).z,
					add(CAM::GET_GAMEPLAY_CAM_COORD(), multiply(rot_to_direction(CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).x,
					add(CAM::GET_GAMEPLAY_CAM_COORD(), multiply(rot_to_direction(CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).y,
					add(CAM::GET_GAMEPLAY_CAM_COORD(), multiply(rot_to_direction(CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).z,
					255, 0, 0, 255
				);
			}
		}
		if (m_vars.m_ped_gun) {
			if (__shooting(PLAYER::PLAYER_PED_ID()))
			{
				Vector3 coords;
				if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &coords))
				{
					PED::CREATE_RANDOM_PED(coords.x, coords.y, coords.z);
				}

			}
		}
		if (m_vars.m_asteriod_gun)
		{
			if (__shooting(PLAYER::PLAYER_PED_ID()))
			{
				Vector3 Rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
				Vector3 Dir = RotationToDirection(Rot);
				Vector3 CPosition = CAM::GET_GAMEPLAY_CAM_COORD();
				Vector3 PlayerPosition = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				float spawnDistance = get_distance(CPosition, PlayerPosition);
				spawnDistance += 2;
				Vector3 SPosition = addVector(CPosition, multiplyVector(Dir, spawnDistance));
				DWORD Model = MISC::GET_HASH_KEY("prop_asteroid_01");
				Object ObJect = OBJECT::CREATE_OBJECT(Model, SPosition.x, SPosition.y, SPosition.z, 1, 1, 1);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(Model);
				if (ENTITY::DOES_ENTITY_EXIST(ObJect))
				{
					ENTITY::SET_ENTITY_RECORDS_COLLISIONS(ObJect, true);
					for (float f = 0.0f; f < 75.0f; f++) {
						if (ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(ObJect))break;
						ENTITY::APPLY_FORCE_TO_ENTITY(ObJect, 1, Dir.x * 10.0f, Dir.y * 10.0f, Dir.z * 10.0f, 0.0f, 0.0f, 0.0f, 0, 0, 1, 1, 0, 1);
						std::this_thread::yield();
					}
					Vector3 Coordinates = ENTITY::GET_ENTITY_COORDS(ObJect, 1);
					FIRE::ADD_EXPLOSION(Coordinates.x, Coordinates.y, Coordinates.z, 9, 25.0f, 1, 1, 0.5f, true);
				}
			}
		}
		if (m_vars.m_repair_gun)
		{
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
			{
				if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_ATTACK))
				{
					Entity entity;

					if (raycast(&entity))
					{
						if (ENTITY::IS_ENTITY_A_VEHICLE(entity))
						{
							if (!ENTITY::IS_ENTITY_A_VEHICLE(entity) || !take_control_of(entity))
							{
								return;
							}

							VEHICLE::SET_VEHICLE_FIXED(entity);
							VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(entity);
							VEHICLE::SET_VEHICLE_DIRT_LEVEL(entity, 0.f);
						}
					}
				}
			}
		}
		static std::int32_t rocket, cam;
		static std::uint8_t y;
		static float bar;
		static bool init;
		if (m_vars.m_valkyrie_gun) {
			if (__shooting(PLAYER::PLAYER_PED_ID())) {
				if (!init) init = true;
			}
			if (init) {
				if (!ENTITY::DOES_ENTITY_EXIST(rocket)) {
					auto weapon = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(PLAYER::PLAYER_PED_ID());
					auto c = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(weapon, 0.f, 1.f, 0.f);
					rocket = OBJECT::CREATE_OBJECT($("w_lr_rpg_rocket"), c.x, c.y, c.z, 1, 1, 0);
					CAM::DESTROY_ALL_CAMS(true);
					cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
					CAM::ATTACH_CAM_TO_ENTITY(cam, rocket, 0.f, 0.f, 0.f, 1);
					CAM::RENDER_SCRIPT_CAMS(1, true, 700, 1, 1, 0);
					CAM::SET_CAM_ACTIVE(cam, 1);
					ENTITY::SET_ENTITY_VISIBLE(rocket, 0, 0);
					bar = .5f; y = 255;
				}
				else {
					CAM::SET_CAM_ROT(cam, CAM::GET_GAMEPLAY_CAM_ROT(0).x, CAM::GET_GAMEPLAY_CAM_ROT(0).y, CAM::GET_GAMEPLAY_CAM_ROT(0).z, 0);
					ENTITY::SET_ENTITY_ROTATION(rocket, CAM::GET_GAMEPLAY_CAM_ROT(0).x, CAM::GET_GAMEPLAY_CAM_ROT(0).y, CAM::GET_GAMEPLAY_CAM_ROT(0).z, 0, 1);

					auto c = add(ENTITY::GET_ENTITY_COORDS(rocket, 1), multiply(rot_to_direction(CAM::GET_GAMEPLAY_CAM_ROT(0)), .8f));
					ENTITY::SET_ENTITY_COORDS_NO_OFFSET(rocket, c.x, c.y, c.z, 0, 0, 0);

					HUD::HIDE_HUD_AND_RADAR_THIS_FRAME();
					PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_PED_ID(), 1);
					ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), 1);
					

					GRAPHICS::DRAW_RECT(0.5f, 0.5f - 0.025f, 0.050f, 0.002f, 255, 255, 255, 255, 0);
					GRAPHICS::DRAW_RECT(0.5f, 0.5f + 0.025f, 0.050f, 0.002f, 255, 255, 255, 255, 0);
					GRAPHICS::DRAW_RECT(0.5f - 0.025f, 0.5f, 0.002f, 0.050f, 255, 255, 255, 255, 0);
					GRAPHICS::DRAW_RECT(0.5f + 0.025f, 0.5f, 0.002f, 0.050f, 255, 255, 255, 255, 0);
					GRAPHICS::DRAW_RECT(0.5f + 0.05f, 0.5f, 0.050f, 0.002f, 255, 255, 255, 255, 0);
					GRAPHICS::DRAW_RECT(0.5f - 0.05f, 0.5f, 0.050f, 0.002f, 255, 255, 255, 255, 0);
					GRAPHICS::DRAW_RECT(0.5f, 0.5f + 0.05f, 0.002f, 0.050f, 255, 255, 255, 255, 0);
					GRAPHICS::DRAW_RECT(0.5f, 0.5f - 0.05f, 0.002f, 0.050f, 255, 255, 255, 255, 0);
					GRAPHICS::SET_TIMECYCLE_MODIFIER("CAMERA_secuirity");

					GRAPHICS::DRAW_RECT(0.25f, 0.5f, 0.03f, 0.5f, 255, 255, 255, 255, 0);
					static auto ticker = GetTickCount();
					if (GetTickCount() - ticker >= 200) {
						bar -= .01f; y -= 4; ticker = GetTickCount();
					}
					GRAPHICS::DRAW_RECT(0.25f, 0.75f - (bar / 2), 0.03f, bar, 255, y, 0, 255, 0);

					float groundZ;
					MISC::GET_GROUND_Z_FOR_3D_COORD(ENTITY::GET_ENTITY_COORDS(rocket, 1).x, ENTITY::GET_ENTITY_COORDS(rocket, 1).y, ENTITY::GET_ENTITY_COORDS(rocket, 1).z, &groundZ, 0, 0);
					if (ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(rocket) ||
						(std::abs(ENTITY::GET_ENTITY_COORDS(rocket, 1).z - groundZ) < .5f) ||
						bar <= 0.01) {
						auto impact_coord = ENTITY::GET_ENTITY_COORDS(rocket, 1); ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), 0);
						FIRE::ADD_EXPLOSION(impact_coord.x, impact_coord.y, impact_coord.z, 0, 10.f, 1, 0, .4f, 0);
						ENTITY::DELETE_ENTITY(&rocket);
						rocket = 0;
						PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_PED_ID(), 0);
						CAM::RENDER_SCRIPT_CAMS(0, true, 700, 1, 1, 0);
						CAM::DESTROY_CAM(cam, 1);
						GRAPHICS::SET_TIMECYCLE_MODIFIER("DEFAULT");
						init = false;
					}
				}
			}
		}

		else {
			CAM::DESTROY_CAM(cam, 1);
			ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), false);
			rocket = 0;
			bar = .5f;
			y = 255;
		}

		if (m_vars.m_airstrike_gun) {
			Vector3 iCoord;
			if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &iCoord))
			{
				MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(iCoord.x, iCoord.y, iCoord.z + 5, iCoord.x, iCoord.y, iCoord.z, 100, 1, MISC::GET_HASH_KEY("WEAPON_AIRSTRIKE_ROCKET"), PLAYER::PLAYER_PED_ID(), 1, 1, 100);
				MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(iCoord.x, iCoord.y + 5, iCoord.z + 5, iCoord.x, iCoord.y, iCoord.z, 100, 1, MISC::GET_HASH_KEY("WEAPON_AIRSTRIKE_ROCKET"), PLAYER::PLAYER_PED_ID(), 1, 1, 130);
				MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(iCoord.x + 3, iCoord.y, iCoord.z + 5, iCoord.x, iCoord.y, iCoord.z, 100, 1, MISC::GET_HASH_KEY("WEAPON_AIRSTRIKE_ROCKET"), PLAYER::PLAYER_PED_ID(), 1, 1, 80);
				MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(iCoord.x - 5, iCoord.y, iCoord.z + 5, iCoord.x, iCoord.y, iCoord.z, 100, 1, MISC::GET_HASH_KEY("WEAPON_AIRSTRIKE_ROCKET"), PLAYER::PLAYER_PED_ID(), 1, 1, 110);
				MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(iCoord.x, iCoord.y - 2, iCoord.z + 5, iCoord.x, iCoord.y, iCoord.z, 100, 1, MISC::GET_HASH_KEY("WEAPON_AIRSTRIKE_ROCKET"), PLAYER::PLAYER_PED_ID(), 1, 1, 150);
			}
		}

	}

	void weapon_menu::script_func()
	{
		m_weapon_menu.script_init();
		while (true)
		{
			m_weapon_menu.script_on_tick();
			m_aimbot_menu.script_on_tick();
			m_entity_gun_menu.script_on_tick();
			m_explosion_gun_menu.script_on_tick();
			m_gravity_gun_menu.script_on_tick();
			m_impacts_menu.script_on_tick();
			m_magnet_gun_menu.script_on_tick();
			m_paint_gun_menu.script_on_tick();
			m_particle_gun_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}