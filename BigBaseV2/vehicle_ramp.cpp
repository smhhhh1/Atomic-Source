#include "common.hpp"
#include "gta_util.hpp"
#include "vehicle_ramp.h"
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
using namespace big::vehicle::ramp::vars;


namespace big::vehicle::ramp::vars
{
	variables m_vars;
	void spawn(bool front, bool back, bool left, bool right)
	{
		Entity veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
		Hash ramp = MISC::GET_HASH_KEY("lts_prop_lts_ramp_01");
		STREAMING::REQUEST_MODEL(ramp);
		if (STREAMING::HAS_MODEL_LOADED(ramp))
		{
			if (ENTITY::DOES_ENTITY_EXIST(veh))
			{
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(veh);

				if (front)
				{
					std::int32_t Object = OBJECT::CREATE_OBJECT(ramp, 0.f, 0.f, 0.f, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 1, 0);
					if (ENTITY::DOES_ENTITY_EXIST(Object))
					{
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, veh, 0, 0, 5, 0.3f, 0, 0, 180, 0, 0, 0, 0, 2, 1);
						ENTITY::SET_ENTITY_COLLISION(Object, 1, 0);
					}
				}

				if (back)
				{
					std::int32_t Object = OBJECT::CREATE_OBJECT(ramp, 0.f, 0.f, 0.f, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 1, 0);
					if (ENTITY::DOES_ENTITY_EXIST(Object))
					{
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, veh, 0, 0, -5, 0.3f, 0, 0, 360, 0, 0, 0, 0, 2, 1);
						ENTITY::SET_ENTITY_COLLISION(Object, 1, 0);
					}
				}

				if (left)
				{
					std::int32_t Object = OBJECT::CREATE_OBJECT(ramp, 0.f, 0.f, 0.f, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 1, 0);
					if (ENTITY::DOES_ENTITY_EXIST(Object))
					{
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, veh, 0, -5, 0, 0.3f, 0, 0, -90, 0, 0, 0, 0, 2, 1);
						ENTITY::SET_ENTITY_COLLISION(Object, 1, 0);
					}
				}

				if (right)
				{
					std::int32_t Object = OBJECT::CREATE_OBJECT(ramp, 0.f, 0.f, 0.f, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 1, 0);
					if (ENTITY::DOES_ENTITY_EXIST(Object))
					{
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, veh, 0, 5, 0, 0.3f, 0, 0, 90, 0, 0, 0, 0, 2, 1);
						ENTITY::SET_ENTITY_COLLISION(Object, 1, 0);
					}
				}

			}
		}
	}

}

namespace big::menu
{


	void vehicle_ramp_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Vehicle Ramps", SubVehicleRamps, [](sub* core)
			{
				core->add_option<toggle_option<bool>>(("Front"), nullptr, &m_vars.m_front);
				core->add_option<toggle_option<bool>>(("Back"), nullptr, &m_vars.m_back);
				core->add_option<toggle_option<bool>>(("Left"), nullptr, &m_vars.m_left);
				core->add_option<toggle_option<bool>>(("Right"), nullptr, &m_vars.m_right);
				core->add_option<simple_option>(("Create"), nullptr, [] { spawn(m_vars.m_front, m_vars.m_back, m_vars.m_left, m_vars.m_right); });
				core->add_option<simple_option>(("Delete"), nullptr, [] {
					for (int i = 0; i < 4; i++)
					{
						static Hash ramp = MISC::GET_HASH_KEY("lts_prop_lts_ramp_01");
						Vector3 pedpos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);
						Object ObjToDelete = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(pedpos.x, pedpos.y, pedpos.z, 10.f, ramp, 0, 1, 1);
						OBJECT::DELETE_OBJECT(&ObjToDelete);
					}
					});
			});
	}

	void vehicle_ramp_menu::script_init() {}

	void vehicle_ramp_menu::script_on_tick()
	{

	}

	void vehicle_ramp_menu::script_func()
	{
		m_vehicle_ramp_menu.script_init();
		while (true)
		{
			m_vehicle_ramp_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}