#include "common.hpp"
#include "gta_util.hpp"
#include "gravity_gun.h"
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
using namespace big::weapon::gravity_gun::vars;

namespace big::weapon::gravity_gun::vars {
	variables m_vars;

	

}

namespace big::menu
{


	void gravity_gun_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Gravity Gun", SubGravityGun, [](sub* core)
			{
				core->add_option<toggle_option<bool>>(("Toggle"), 
					nullptr,
					&m_vars.m_toggle
				);
				core->add_option<number_option<float>>(("Push Force"),
					nullptr,
					&m_vars.m_force, 0,
					500, 10,
					1, false
				);
			});
	}

	void gravity_gun_menu::script_init() {}

	void gravity_gun_menu::script_on_tick()
	{
		if (m_vars.m_toggle) {
			static int zoom = 5;
			static Entity currEnt{ NULL };

			if (IsKeyPressed(VK_RBUTTON))
			{
				if (currEnt == NULL)
					PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &currEnt);
				else
				{
					if (ENTITY::IS_ENTITY_A_PED(currEnt) && PED::IS_PED_IN_ANY_VEHICLE(currEnt, true))
						currEnt = PED::GET_VEHICLE_PED_IS_IN(currEnt, 0);

					take_control_of(currEnt);

					Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
					Vector3 dir = RotationToDirection(rot);
					Vector3 spawnPosition = addVector(CAM::GET_GAMEPLAY_CAM_COORD(), multiplyVector(dir, zoom));

					Vector3 getcoords = ENTITY::GET_ENTITY_COORDS(currEnt, 0);
					float getaimcoordsX = GravityGunGoto(spawnPosition.x, getcoords.x);
					float getaimcoordsY = GravityGunGoto(spawnPosition.y, getcoords.y);
					float getaimcoordsZ = GravityGunGoto(spawnPosition.z, getcoords.z);
					ENTITY::SET_ENTITY_VELOCITY(currEnt, getaimcoordsX * 2.0, getaimcoordsY * 2.0, getaimcoordsZ * 2.0);
					//GRAPHICS::DRAW_MARKER(28, spawnPosition.x, spawnPosition.y, spawnPosition.z, 0, 0, 0, 0, 180, 0, 1, 1, 1, 0, 0, 0, 255, 1, 1, 1, 0, 0, 0, 0);

					if (IsKeyPressed(VK_LBUTTON))
					{
						ENTITY::APPLY_FORCE_TO_ENTITY(currEnt, 1, dir.x * m_vars.m_force, dir.y * m_vars.m_force, dir.z * m_vars.m_force, 0.0f, 0.0f, 0.0f, false, false, true, true, false, true);
						PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_ID(), false);
						currEnt = NULL;
					}

				}

			}
			else
				currEnt = NULL;

		}

	}

	void gravity_gun_menu::script_func()
	{
		m_gravity_gun_menu.script_init();
		while (true)
		{
			m_gravity_gun_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}