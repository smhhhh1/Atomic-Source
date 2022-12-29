#include "common.hpp"
#include "gta_util.hpp"
#include "ptfx.h"
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
#include "scroll.h"
#include "lists.h"
using namespace big::player::ptfx::vars;

namespace big::player::ptfx::vars
{
	inline const char* particles[] =
	{
		"Clown", "Alien", "Burst", "Money", "Electricty", "Water"
	};

	inline const char* particleDict[] = {
		"scr_clown_appears", "scr_clown_death", "scr_indep_firework_trailburst", "scr_alien_disintegrate", "ent_amb_elec_crackle_sp", "scr_fbi5_ped_water_splash"


	}; inline std::size_t particle_id = 0;
	variables m_vars;
}

namespace big::menu
{

	void ptfx_menu::menu()
	{
		using namespace ui;



		m_renderer.new_sub<sub>("Particle Fx", SubParticleFx, [](sub* core)
			{
				core->add_option<toggle_option<bool>>(("Toggle"), nullptr, &m_vars.g_particle_man);
				core->add_option<number_option<float>>(("Scale"), nullptr, &m_vars.g_particle_man_scale, 0.00f, 1.0f, 0.01f, 2);
				core->add_option<scroll_option<const char*, std::size_t>>("Particle", nullptr, &particles, &particle_id, false);
				core->add_option<break_option>(std::move(break_option()
					.SetRightText("Bones")
				));
				core->add_option<toggle_option<bool>>(("Head"), nullptr, &m_vars.head);
				core->add_option<toggle_option<bool>>(("Right Hand"), nullptr, &m_vars.right_hand);
				core->add_option<toggle_option<bool>>(("Left Hand"), nullptr, &m_vars.left_hand);
				core->add_option<toggle_option<bool>>(("Right Foot"), nullptr, &m_vars.right_foot);
				core->add_option<toggle_option<bool>>(("Left Foot"), nullptr, &m_vars.left_foot);
			});
	}

	void ptfx_menu::script_init() {}

	void ptfx_menu::script_on_tick()
	{
		if (m_vars.g_particle_man) {


			if (m_vars.head) {
				if (particleDict[0]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(particleDict[particle_id], PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 31086, m_vars.g_particle_man_scale, 0, 0, 0);
				}
				if (particleDict[1]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(particleDict[particle_id], PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 31086, m_vars.g_particle_man_scale, 0, 0, 0);
				}
				if (particleDict[2]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_indep_fireworks");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_indep_fireworks");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(particleDict[particle_id], PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 31086, m_vars.g_particle_man_scale, 0, 0, 0);
				}

				if (particleDict[3]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_alien_disintegrate");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_alien_disintegrate");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(particleDict[particle_id], PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 31086, m_vars.g_particle_man_scale, 0, 0, 0);
				}

				if (particleDict[4]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_agencyheistb");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_agencyheistb");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(particleDict[particle_id], PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 31086, m_vars.g_particle_man_scale, 0, 0, 0);
				}

				if (particleDict[5]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_martin1");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_martin1");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(particleDict[particle_id], PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 31086, m_vars.g_particle_man_scale, 0, 0, 0);
				}
				//GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(Lists::particleDict[Lists::particle_id], PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 31086, g_particle_man_scale, 0, 0, 0);
			}
			if (m_vars.right_hand) {
				if (particleDict[0]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(particleDict[particle_id], PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 28422, m_vars.g_particle_man_scale, 0, 0, 0);
				}
				if (particleDict[1]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(particleDict[particle_id], PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 28422, m_vars.g_particle_man_scale, 0, 0, 0);
				}
				if (particleDict[2]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_indep_fireworks");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_indep_fireworks");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(particleDict[particle_id], PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 28422, m_vars.g_particle_man_scale, 0, 0, 0);
				}

				if (particleDict[3]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_alien_disintegrate");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_alien_disintegrate");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(particleDict[particle_id], PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 28422, m_vars.g_particle_man_scale, 0, 0, 0);
				}

				if (particleDict[4]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_agencyheistb");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_agencyheistb");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(particleDict[particle_id], PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 28422, m_vars.g_particle_man_scale, 0, 0, 0);
				}

				if (particleDict[5]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_fbi5a");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_fbi5a");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(particleDict[particle_id], PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 28422, m_vars.g_particle_man_scale, 0, 0, 0);
				}
			}
			if (m_vars.left_hand) {
				if (particleDict[0]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(particleDict[particle_id], PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 60309, m_vars.g_particle_man_scale, 0, 0, 0);
				}
				if (particleDict[1]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(particleDict[particle_id], PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 60309, m_vars.g_particle_man_scale, 0, 0, 0);
				}
				if (particleDict[2]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_indep_fireworks");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_indep_fireworks");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(particleDict[particle_id], PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 60309, m_vars.g_particle_man_scale, 0, 0, 0);
				}

				if (particleDict[3]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_alien_disintegrate");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_alien_disintegrate");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(particleDict[particle_id], PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 60309, m_vars.g_particle_man_scale, 0, 0, 0);
				}

				if (particleDict[4]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_agencyheistb");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_agencyheistb");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(particleDict[particle_id], PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 60309, m_vars.g_particle_man_scale, 0, 0, 0);
				}

				if (particleDict[5]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_fbi5a");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_fbi5a");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(particleDict[particle_id], PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 60309, m_vars.g_particle_man_scale, 0, 0, 0);
				}
			}
			if (m_vars.left_foot) {
				if (particleDict[0]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(particleDict[particle_id], PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 65245, m_vars.g_particle_man_scale, 0, 0, 0);
				}
				if (particleDict[1]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(particleDict[particle_id], PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 65245, m_vars.g_particle_man_scale, 0, 0, 0);
				}
				if (particleDict[2]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_indep_fireworks");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_indep_fireworks");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(particleDict[particle_id], PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 65245, m_vars.g_particle_man_scale, 0, 0, 0);
				}

				if (particleDict[3]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_alien_disintegrate");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_alien_disintegrate");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(particleDict[particle_id], PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 65245, m_vars.g_particle_man_scale, 0, 0, 0);
				}

				if (particleDict[4]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_agencyheistb");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_agencyheistb");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(particleDict[particle_id], PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 65245, m_vars.g_particle_man_scale, 0, 0, 0);
				}

				if (particleDict[5]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_fbi5a");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_fbi5a");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(particleDict[particle_id], PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 65245, m_vars.g_particle_man_scale, 0, 0, 0);
				}
			}
			if (m_vars.right_foot) {
				if (particleDict[0]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(particleDict[particle_id], PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 35502, m_vars.g_particle_man_scale, 0, 0, 0);
				}
				if (particleDict[1]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(particleDict[particle_id], PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 35502, m_vars.g_particle_man_scale, 0, 0, 0);
				}
				if (particleDict[2]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_indep_fireworks");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_indep_fireworks");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(particleDict[particle_id], PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 35502, m_vars.g_particle_man_scale, 0, 0, 0);
				}

				if (particleDict[3]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_alien_disintegrate");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_alien_disintegrate");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(particleDict[particle_id], PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 35502, m_vars.g_particle_man_scale, 0, 0, 0);
				}

				if (particleDict[4]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_agencyheistb");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_agencyheistb");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(particleDict[particle_id], PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 35502, m_vars.g_particle_man_scale, 0, 0, 0);
				}

				if (particleDict[5]) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_fbi5a");
					GRAPHICS::USE_PARTICLE_FX_ASSET("scr_fbi5a");
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(particleDict[particle_id], PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 65245, m_vars.g_particle_man_scale, 0, 0, 0);
				}
			}
			//GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(Lists::particleDict[Lists::particle_id], PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 31086, g_particle_man_scale, 0, 0, 0);
		}
	}

	void ptfx_menu::script_func()
	{
		m_ptfx_menu.script_init();
		while (true)
		{
			m_ptfx_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}