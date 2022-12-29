#include "common.hpp"
#include "gta_util.hpp"
#include "particle_gun.h"
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
#include "util.h"
using namespace big::weapon::particle_gun::vars;

namespace big::weapon::particle_gun::vars {
	variables m_vars;
	const char* paricle_gun_dict[] = {
		"scr_clown_appears", "scr_clown_death", "scr_indep_firework_trailburst", "scr_alien_disintegrate", "ent_amb_elec_crackle_sp", "scr_fbi5_ped_water_splash"


	}; std::size_t particle_gun_id = 0;
	const char* gun_particles[] =
	{
		"Clown", "Alien", "Burst", "Money", "Electricty", "Water"
	};
}

namespace big::menu
{


	void particle_gun_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Particle Gun", SubParticleGun, [](sub* core)
			{
				core->add_option<scroll_option<const char*, std::size_t>>(("Particle"),
					nullptr,
					&gun_particles,
					&particle_gun_id,
					true
				);
				core->add_option<toggle_option<bool>>(("Toggle"),
					nullptr,
					&m_vars.m_toggle
				);
				core->add_option<number_option<float>>(("Scale"),
					nullptr,
					&m_vars.m_scale, 1.0f,
					10.0f, 0.1f,
					1, false
				);
				
			});
	}

	void particle_gun_menu::script_init() {}

	void particle_gun_menu::script_on_tick() {


		if (m_vars.m_toggle) {
			if (__shooting(PLAYER::PLAYER_PED_ID()))
			{

				Vector3 c;
				if (auto last = WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &c))
				{
					if (raycast(&last)) {
						if (paricle_gun_dict[0]) {
							STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
							GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");
							GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(paricle_gun_dict[particle_gun_id], c.x, c.y, c.z, 0, 0, 0, m_vars.m_scale, 0, 0, 0, 0);
						}
						if (paricle_gun_dict[1]) {
							STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
							GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");
							GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(paricle_gun_dict[particle_gun_id], c.x, c.y, c.z, 0, 0, 0, m_vars.m_scale, 0, 0, 0, 0);
						}
						if (paricle_gun_dict[2]) {
							STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_indep_fireworks");
							GRAPHICS::USE_PARTICLE_FX_ASSET("scr_indep_fireworks");
							GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(paricle_gun_dict[particle_gun_id], c.x, c.y, c.z, 0, 0, 0, m_vars.m_scale, 0, 0, 0, 0);
						}

						if (paricle_gun_dict[3]) {
							STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_alien_disintegrate");
							GRAPHICS::USE_PARTICLE_FX_ASSET("scr_alien_disintegrate");
							GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(paricle_gun_dict[particle_gun_id], c.x, c.y, c.z, 0, 0, 0, m_vars.m_scale, 0, 0, 0, 0);
						}

						if (paricle_gun_dict[4]) {
							STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_agencyheistb");
							GRAPHICS::USE_PARTICLE_FX_ASSET("scr_agencyheistb");
							GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(paricle_gun_dict[particle_gun_id], c.x, c.y, c.z, 0, 0, 0, m_vars.m_scale, 0, 0, 0, 0);
						}

						if (paricle_gun_dict[5]) {
							STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_martin1");
							GRAPHICS::USE_PARTICLE_FX_ASSET("scr_martin1");
							GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(paricle_gun_dict[particle_gun_id], c.x, c.y, c.z, 0, 0, 0, m_vars.m_scale, 0, 0, 0, 0);
						}
					}

				}

			}
		}

	}

	void particle_gun_menu::script_func()
	{
		m_particle_gun_menu.script_init();
		while (true)
		{
			m_particle_gun_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}