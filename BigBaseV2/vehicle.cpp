#include "common.hpp"
#include "gta_util.hpp"
#include "vehicle.h"
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
#include "vehicle_health.h"
#include "vehicle_weapons.h"
#include "vehicle_ptfx.h"
#include "vehicle_movement.h"
#include "vehicle_parachute.h"
#include "vehicle_boost.h"
#include "vehicle_collision.h"
#include "vehicle_gravity.h"
#include "vehicle_multipliers.h"
#include "vehicle_randomization.h"
#include "vehicle_proofs.h"
using namespace big::vehicle::vars;

struct color_rgba {
	int r;
	int g;
	int b;
	int a = 255;

	color_rgba()
		: r(0), g(0), b(0), a(0) {}

	color_rgba(int red, int green, int blue, int alpha = 255)
		: r(red), g(green), b(blue), a(alpha) {}

	color_rgba(uint32_t hex)
		: r(hex >> 24), g(((hex >> 16) & 0x00FF)), b(((hex >> 8) & 0x0000FF)), a(hex & 0xFF) {}

	color_rgba opacity(int opacity) {
		return color_rgba(r, g, b, opacity);
	}

	math::vector3_<int> as_vector() {
		return { r, g, b };
	}

	std::initializer_list<int> as_initializer_list() {
		return std::initializer_list<int> { r, g, b, a };
	}

	uint32_t to_argb() {
		uint8_t val[4];
		val[0] = a;
		val[1] = r;
		val[2] = g;
		val[3] = b;

		return *(uint32_t*)&val;
	}
};


namespace big::vehicle::vars
{
	variables m_vars;

	void request(uint32_t model) {
		int tries = 0;
		while (!STREAMING::HAS_MODEL_LOADED(model) && tries < 25) {
			STREAMING::REQUEST_MODEL(model);
			tries++;
			script::get_current()->yield();
		}
	}

	Vehicle clone(Vehicle veh) {
		Vehicle spawned_vehicle = 0;

		if (ENTITY::DOES_ENTITY_EXIST(veh)) {
			uint32_t model = ENTITY::GET_ENTITY_MODEL(veh);
			request(model);

			Vector3 coords = ENTITY::GET_ENTITY_COORDS(veh, true);
			Vector3 spawn_coords = coords;
			*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
			spawned_vehicle = VEHICLE::CREATE_VEHICLE(model, spawn_coords.x + 10, spawn_coords.y, spawn_coords.z, ENTITY::GET_ENTITY_HEADING(veh), true, true, 0);
			*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;
			if (ENTITY::DOES_ENTITY_EXIST(spawned_vehicle)) {
				VEHICLE::SET_VEHICLE_DIRT_LEVEL(spawned_vehicle, VEHICLE::GET_VEHICLE_DIRT_LEVEL(veh));
				VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(spawned_vehicle, VEHICLE::GET_VEHICLE_DIRT_LEVEL(veh));
				VEHICLE::SET_VEHICLE_MOD_KIT(spawned_vehicle, 0);

				for (int i = MOD_SPOILER; i <= MOD_ARMOR; i++) {
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, i) > 0) {
						VEHICLE::SET_VEHICLE_MOD(spawned_vehicle, i, VEHICLE::GET_VEHICLE_MOD(veh, i), 0);
					}
				}

				for (int i = MOD_PLATEHOLDER; i <= MOD_LIVERY; i++) {
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, i) > 0) {
						VEHICLE::SET_VEHICLE_MOD(spawned_vehicle, i, VEHICLE::GET_VEHICLE_MOD(veh, i), 0);
					}
				}

				VEHICLE::SET_VEHICLE_WHEEL_TYPE(spawned_vehicle, VEHICLE::GET_VEHICLE_WHEEL_TYPE(veh));
				VEHICLE::SET_VEHICLE_MOD(spawned_vehicle, MOD_FRONTWHEELS, VEHICLE::GET_VEHICLE_MOD(veh, MOD_FRONTWHEELS), VEHICLE::GET_VEHICLE_MOD_VARIATION(veh, MOD_FRONTWHEELS));
				VEHICLE::SET_VEHICLE_MOD(spawned_vehicle, MOD_BACKWHEELS, VEHICLE::GET_VEHICLE_MOD(veh, MOD_BACKWHEELS), VEHICLE::GET_VEHICLE_MOD_VARIATION(veh, MOD_FRONTWHEELS));

				for (int i = MOD_UNK17; i <= MOD_XENONLIGHTS; i++) {
					VEHICLE::TOGGLE_VEHICLE_MOD(spawned_vehicle, VEHICLE::GET_VEHICLE_MOD_VARIATION(veh, i), true);
				}

				int colors[2];
				int extra_colors[2];
				color_rgba tyre_smoke;
				color_rgba custom_primary;
				color_rgba custom_secondary;
				color_rgba neon;

				VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, &custom_primary.r, &custom_primary.g, &custom_primary.b);
				VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, &custom_secondary.r, &custom_secondary.g, &custom_secondary.b);
				VEHICLE::_GET_VEHICLE_NEON_LIGHTS_COLOUR(veh, &neon.r, &neon.g, &neon.b);
				VEHICLE::GET_VEHICLE_TYRE_SMOKE_COLOR(veh, &tyre_smoke.r, &tyre_smoke.g, &tyre_smoke.b);
				VEHICLE::GET_VEHICLE_COLOURS(veh, &colors[0], &colors[1]);
				VEHICLE::GET_VEHICLE_EXTRA_COLOURS(veh, &extra_colors[0], &extra_colors[1]);

				VEHICLE::SET_VEHICLE_COLOURS(spawned_vehicle, colors[0], colors[1]);
				VEHICLE::SET_VEHICLE_EXTRA_COLOURS(spawned_vehicle, extra_colors[0], extra_colors[1]);
				VEHICLE::SET_VEHICLE_WINDOW_TINT(spawned_vehicle, VEHICLE::GET_VEHICLE_WINDOW_TINT(veh));

				VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(spawned_vehicle, tyre_smoke.r, tyre_smoke.g, tyre_smoke.b);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(spawned_vehicle, custom_primary.r, custom_primary.g, custom_primary.b);
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(spawned_vehicle, custom_secondary.r, custom_secondary.g, custom_secondary.b);

				for (int i = 0; i < 4; i++) {
					VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(spawned_vehicle, i, VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(veh, i));
				}

				VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(spawned_vehicle, neon.r, neon.g, neon.b);
				VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(spawned_vehicle, VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(veh));
				VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(spawned_vehicle, VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT(veh));

				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), spawned_vehicle, -1);
			}
		}

		return spawned_vehicle;
	}

	void upgrade()
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		for (int i = 0; i < 50; i++)
		{
			VEHICLE::SET_VEHICLE_MOD(veh, i, VEHICLE::GET_NUM_VEHICLE_MODS(veh, i) - 1, false);
		}
	}
	void downgrade()
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		for (int i = 0; i < 50; i++)
		{
			VEHICLE::REMOVE_VEHICLE_MOD(veh, VEHICLE::GET_NUM_VEHICLE_MODS(veh, i) - 1);

		}
	}
	void Delete()
	{
		Entity veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		take_control_of(veh);
		ENTITY::DELETE_ENTITY(&veh);
	}


}

namespace big::menu
{

	void vehicle_menu::menu()
	{
		using namespace ui;
		m_renderer.new_sub<sub>("Vehicle", SubVehicle , [](sub* core)
			{
				core->add_option<toggle_option<bool>>(("Godmode"),
					nullptr,
					&m_vars.m_godmode
				);
				core->add_option<toggle_option<bool>>(("Invisiblity"),
					nullptr,
					&m_vars.m_invisibility
				);
				core->add_option<toggle_option<bool>>(("Seatbelt"),
					nullptr,
					&m_vars.m_seatbelt
				);
				core->add_option<simple_option>(("Upgrade"),
					nullptr, [] { 
						upgrade(); 
				});
				core->add_option<simple_option>(("Downgrade"),
					nullptr, [] {
						downgrade();
				});

				core->add_option<submenu>("Customs", nullptr, SubCustoms);
				core->add_option<submenu>("Color", nullptr, SubVehicleColor);
				core->add_option<submenu>("Health", nullptr, SubHealth);
				core->add_option<submenu>("Weapons", nullptr, SubVehicleWeapons);
				core->add_option<submenu>("Particle Fx", nullptr, SubVehicleParticleFx);
				core->add_option<submenu>("Movement", nullptr, SubVehicleMovement);
				core->add_option<submenu>("Boost", nullptr, SubVehicleBoost);
				core->add_option<submenu>("Collision", nullptr, SubVehicleCollision);
				core->add_option<submenu>("Gravity", nullptr, SubVehicleGravity);
				core->add_option<submenu>("Multipliers", nullptr, SubVehicleMultipliers);
				core->add_option<submenu>("Handling", nullptr, SubVehicleHandling);
				core->add_option<submenu>("Autopilot", nullptr, SubVehicleAutoPilot);
				core->add_option<submenu>("Ramps", nullptr, SubVehicleRamps);
				core->add_option<submenu>("Randomization", nullptr, SubVehicleRandomization);
				core->add_option<submenu>("Doors", nullptr, SubVehicleDoors);
				core->add_option<submenu>("Proofs", nullptr, SubVehicleProofs);

				core->add_option<toggle_option<bool>>(("Burn Shell"),
					nullptr,
					&m_vars.m_burn_shell
				);
				core->add_option<toggle_option<bool>>(("Mute Siren"),
					nullptr,
					&m_vars.m_mute_siren
				);
				core->add_option<simple_option>(("Clone"),
					nullptr,
					[&] {
						clone(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false));
				});
				core->add_option<simple_option>(("~r~Delete"),
					nullptr,
					[&] {
						Delete();
				});

			});
	}

	void vehicle_menu::script_init() {}

	void vehicle_menu::script_on_tick()
	{
		
		if (m_vars.m_godmode) {
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
			{
				Entity veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
				ENTITY::SET_ENTITY_INVINCIBLE(veh, m_vars.m_godmode);

				if (VEHICLE::_IS_VEHICLE_DAMAGED(veh))
				{
					for (int i = 0; i < 10; i++)
					{
						try {
							VEHICLE::SET_VEHICLE_TYRE_FIXED(veh, i);
						}
						catch (...) {
							return;
						}
					}
				}
			}
		}
		if (m_vars.m_invisibility) {
			ENTITY::SET_ENTITY_VISIBLE(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), false, 0);
		}
		else {
			ENTITY::SET_ENTITY_VISIBLE(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), true, 0);
		}
		if (m_vars.m_seatbelt) {
			PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), m_vars.m_seatbelt);
			PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 32, m_vars.m_seatbelt);
		}
		if (m_vars.m_burn_shell) {
			ENTITY::SET_ENTITY_RENDER_SCORCHED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), true), m_vars.m_burn_shell);
		}
		if (m_vars.m_mute_siren) {
			VEHICLE::SET_VEHICLE_HAS_MUTED_SIRENS(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), true);
		}
	}

	void vehicle_menu::script_func()
	{
		m_vehicle_menu.script_init();
		while (true)
		{
			m_vehicle_menu.script_on_tick();
			m_vehicle_health_menu.script_on_tick();
			m_vehicle_weapons_menu.script_on_tick();
			m_vehicle_ptfx_menu.script_on_tick();
			m_vehicle_movement_menu.script_on_tick();
			m_vehicle_parachute_menu.script_on_tick();
			m_vehicle_boost_menu.script_on_tick();
			m_vehicle_collision_menu.script_on_tick();
			m_vehicle_gravity_menu.script_on_tick();
			m_vehicle_multiplier_menu.script_on_tick();
		    m_vehicle_randomization_menu.script_on_tick();
			m_vehicle_proofs_menu.script_on_tick();

			script::get_current()->yield();
		}
	}
}