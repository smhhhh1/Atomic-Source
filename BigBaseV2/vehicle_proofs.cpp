#include "common.hpp"
#include "gta_util.hpp"
#include "vehicle_proofs.h"
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
using namespace big::vehicle::proofs::vars;

namespace big::vehicle::proofs::vars
{
	variables m_vars;

}

namespace big::menu
{

	void vehicle_proofs_menu::menu()
	{
		using namespace ui;



		m_renderer.new_sub<sub>("Vehicle Proofs", SubVehicleProofs, [](sub* core)
			{
				core->add_option<toggle_option<bool>>(("Bullet Proof"),
					nullptr,
					&m_vars.g_bullet_proof
					);

				core->add_option<toggle_option<bool>>(("Fire Proof"),
					nullptr,
					&m_vars.g_fire_proof
					);

				core->add_option<toggle_option<bool>>(("Explosion Proof"),
					nullptr,
					&m_vars.g_explosion_proof
					);

				core->add_option<toggle_option<bool>>(("Collision Proof"),
					nullptr,
					&m_vars.g_collision_proof
					);

				core->add_option<toggle_option<bool>>(("Melee Proof"),
					nullptr,
					&m_vars.g_melee_proof
					);

				core->add_option<toggle_option<bool>>(("Drown Proof"),
					nullptr,
					&m_vars.g_drown_proof
					);
			});
	}

	void vehicle_proofs_menu::script_init() {}

	void vehicle_proofs_menu::script_on_tick()
	{
		ENTITY::SET_ENTITY_PROOFS(PLAYER::PLAYER_PED_ID(), m_vars.g_bullet_proof, m_vars.g_fire_proof, m_vars.g_explosion_proof, m_vars.g_collision_proof, m_vars.g_melee_proof, 0, 0, m_vars.g_drown_proof);
	}

	void vehicle_proofs_menu::script_func()
	{
		m_vehicle_proofs_menu.script_init();
		while (true)
		{
			m_vehicle_proofs_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}