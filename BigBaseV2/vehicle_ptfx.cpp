#include "common.hpp"
#include "gta_util.hpp"
#include "vehicle_ptfx.h"
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
#include "gta/enums.hpp"
#include "scroll.h"
using namespace big::vehicle::ptfx::vars;


namespace big::vehicle::ptfx::vars
{
	variables m_vars;

	const char* particles[] =
	{
		"Clown", "Alien", "Burst", "Money", "Electricty", "Water"
	};

	const char* particleDict[] = {

		"scr_clown_appears", "scr_clown_death", "scr_indep_firework_trailburst", "scr_alien_disintegrate", "ent_amb_elec_crackle_sp", "scr_fbi5_ped_water_splash"

	}; std::size_t particle_id = 0;


}

namespace big::menu
{


	void vehicle_ptfx_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Vehicle Ptfx", SubVehicleParticleFx, [](sub* core)
			{
				core->add_option<toggle_option<bool>>(("Toggle"), nullptr, &m_vars.m_toggle);
				core->add_option<number_option<float>>(("Scale"), nullptr, &m_vars.m_scale, 0.00f, 1.0f, 0.01f, 2);
				core->add_option<scroll_option<const char*, std::size_t>>("Particle", nullptr, &particles, &particle_id, false);
				core->add_option<break_option>(std::move(break_option().
					SetRightText("Wheels"))
					);
				core->add_option<toggle_option<bool>>(("Front Right Wheel"), nullptr, &m_vars.m_rf_wheel);
				core->add_option<toggle_option<bool>>(("Front Left Wheel"), nullptr, &m_vars.m_rl_wheel);
				core->add_option<toggle_option<bool>>(("Back Right Wheel"), nullptr, &m_vars.m_rb_wheel);
				core->add_option<toggle_option<bool>>(("Back Left Wheel"), nullptr, &m_vars.m_lb_wheel);
			});
	}

	void vehicle_ptfx_menu::script_init() {}

	void vehicle_ptfx_menu::script_on_tick()
	{
		int myVeh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);

		if (m_vars.m_toggle) {
			if (m_vars.m_rf_wheel) {
				Vector3 rf = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(myVeh, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(myVeh, "wheel_rf"));
				if (particleDict[0]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particleDict[particle_id], rf.x, rf.y, rf.z, 0.f, 0.f, 0.f, m_vars.m_scale, false, false, false, 0);

				}
				if (particleDict[1]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particleDict[particle_id], rf.x, rf.y, rf.z, 0.f, 0.f, 0.f, m_vars.m_scale, false, false, false, 0);
				}
				if (particleDict[2]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_indep_fireworks");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_indep_fireworks");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particleDict[particle_id], rf.x, rf.y, rf.z, 0.f, 0.f, 0.f, m_vars.m_scale, false, false, false, 0);
				}

				if (particleDict[3]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_alien_disintegrate");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_alien_disintegrate");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particleDict[particle_id], rf.x, rf.y, rf.z, 0.f, 0.f, 0.f, m_vars.m_scale, false, false, false, 0);
				}

				if (particleDict[4]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_agencyheistb");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_agencyheistb");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particleDict[particle_id], rf.x, rf.y, rf.z, 0.f, 0.f, 0.f, m_vars.m_scale, false, false, false, 0);
				}

				if (particleDict[5]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_martin1");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_martin1");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particleDict[particle_id], rf.x, rf.y, rf.z, 0.f, 0.f, 0.f, m_vars.m_scale, false, false, false, 0);
				}
				//GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(Lists::particleDict[Lists::particle_id], PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 31086, g_particle_man_scale, 0, 0, 0);
			}
			if (m_vars.m_rl_wheel) {
				Vector3 rf = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(myVeh, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(myVeh, "wheel_lf"));
				if (particleDict[0]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");

					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particleDict[particle_id], rf.x, rf.y, rf.z, 0.f, 0.f, 0.f, m_vars.m_scale, false, false, false, 0);
				}
				if (particleDict[1]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particleDict[particle_id], rf.x, rf.y, rf.z, 0.f, 0.f, 0.f, m_vars.m_scale, false, false, false, 0);
				}
				if (particleDict[2]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_indep_fireworks");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_indep_fireworks");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particleDict[particle_id], rf.x, rf.y, rf.z, 0.f, 0.f, 0.f, m_vars.m_scale, false, false, false, 0);
				}

				if (particleDict[3]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_alien_disintegrate");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_alien_disintegrate");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particleDict[particle_id], rf.x, rf.y, rf.z, 0.f, 0.f, 0.f, m_vars.m_scale, false, false, false, 0);
				}

				if (particleDict[4]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_agencyheistb");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_agencyheistb");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particleDict[particle_id], rf.x, rf.y, rf.z, 0.f, 0.f, 0.f, m_vars.m_scale, false, false, false, 0);
				}

				if (particleDict[5]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_fbi5a");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_fbi5a");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particleDict[particle_id], rf.x, rf.y, rf.z, 0.f, 0.f, 0.f, m_vars.m_scale, false, false, false, 0);
				}
			}
			if (m_vars.m_rb_wheel) {
				Vector3 rf = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(myVeh, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(myVeh, "wheel_rr"));
				if (particleDict[0]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particleDict[particle_id], rf.x, rf.y, rf.z, 0.f, 0.f, 0.f, m_vars.m_scale, false, false, false, 0);
				}
				if (particleDict[1]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particleDict[particle_id], rf.x, rf.y, rf.z, 0.f, 0.f, 0.f, m_vars.m_scale, false, false, false, 0);
				}
				if (particleDict[2]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_indep_fireworks");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_indep_fireworks");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particleDict[particle_id], rf.x, rf.y, rf.z, 0.f, 0.f, 0.f, m_vars.m_scale, false, false, false, 0);
				}

				if (particleDict[3]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_alien_disintegrate");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_alien_disintegrate");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particleDict[particle_id], rf.x, rf.y, rf.z, 0.f, 0.f, 0.f, m_vars.m_scale, false, false, false, 0);
				}

				if (particleDict[4]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_agencyheistb");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_agencyheistb");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particleDict[particle_id], rf.x, rf.y, rf.z, 0.f, 0.f, 0.f, m_vars.m_scale, false, false, false, 0);
				}

				if (particleDict[5]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_fbi5a");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_fbi5a");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particleDict[particle_id], rf.x, rf.y, rf.z, 0.f, 0.f, 0.f, m_vars.m_scale, false, false, false, 0);
				}
			}
			if (m_vars.m_lb_wheel) {
				Vector3 rf = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(myVeh, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(myVeh, "wheel_lr"));
				if (particleDict[0]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particleDict[particle_id], rf.x, rf.y, rf.z, 0.f, 0.f, 0.f, m_vars.m_scale, false, false, false, 0);
				}
				if (particleDict[1]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particleDict[particle_id], rf.x, rf.y, rf.z, 0.f, 0.f, 0.f, m_vars.m_scale, false, false, false, 0);
				}
				if (particleDict[2]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_indep_fireworks");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_indep_fireworks");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particleDict[particle_id], rf.x, rf.y, rf.z, 0.f, 0.f, 0.f, m_vars.m_scale, false, false, false, 0);
				}

				if (particleDict[3]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_alien_disintegrate");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_alien_disintegrate");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particleDict[particle_id], rf.x, rf.y, rf.z, 0.f, 0.f, 0.f, m_vars.m_scale, false, false, false, 0);
				}

				if (particleDict[4]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_agencyheistb");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_agencyheistb");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particleDict[particle_id], rf.x, rf.y, rf.z, 0.f, 0.f, 0.f, m_vars.m_scale, false, false, false, 0);
				}

				if (particleDict[5]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_fbi5a");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_fbi5a");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particleDict[particle_id], rf.x, rf.y, rf.z, 0.f, 0.f, 0.f, m_vars.m_scale, false, false, false, 0);
				}
			}
		}
	}

	void vehicle_ptfx_menu::script_func()
	{
		m_vehicle_ptfx_menu.script_init();
		while (true)
		{
			m_vehicle_ptfx_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}