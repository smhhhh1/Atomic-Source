#include "common.hpp"
#include "gta_util.hpp"
#include "protections_entity.h"
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
#include "scroll.h"
#include "../bool_and_number.h"
#include "../submenu_option.h"
#include "../submenus.h"
#include "lists.h"
#include "fiber_pool.hpp"
using namespace big::protections::entity::vars;

namespace big::protections::entity::vars {

	variables m_vars;

}

namespace big::menu
{

	void protections_entity_menu::menu()
	{
		using namespace ui;


		m_renderer.new_sub<sub>("Entity", SubProtectionsEntity, [](sub* core)
			{
				core->add_option<scroll_option<const char*, std::size_t>>(("Type"), nullptr, &lists::entity_type, &lists::entity_type_pos, true);

				switch (lists::entity_type_pos) {
				case 0:
					core->add_option<toggle_option<bool>>(("Automobile"), nullptr, &m_vars.m_sync_car);
					core->add_option<toggle_option<bool>>(("Bike"), nullptr, &m_vars.m_sync_bike);
					core->add_option<toggle_option<bool>>(("Boat"), nullptr, &m_vars.m_sync_boat);
					core->add_option<toggle_option<bool>>(("Door"), nullptr, &m_vars.m_sync_door);
					core->add_option<toggle_option<bool>>(("Heli"), nullptr, &m_vars.m_sync_heli);
					core->add_option<toggle_option<bool>>(("Object"), nullptr, &m_vars.m_sync_object);
					core->add_option<toggle_option<bool>>(("Ped"), nullptr, &m_vars.m_sync_ped);
					core->add_option<toggle_option<bool>>(("Pickup"), nullptr, &m_vars.m_sync_pickup);
					core->add_option<toggle_option<bool>>(("Pickup Placement"), nullptr, &m_vars.m_sync_pickup_placement);
					core->add_option<toggle_option<bool>>(("Plane"), nullptr, &m_vars.m_sync_plane);
					core->add_option<toggle_option<bool>>(("Submarine"), nullptr, &m_vars.m_sync_sub);
					core->add_option<toggle_option<bool>>(("Player"), nullptr, &m_vars.m_sync_player);
					core->add_option<toggle_option<bool>>(("Trailer"), nullptr, &m_vars.m_sync_trailer);
					core->add_option<toggle_option<bool>>(("Train"), nullptr, &m_vars.m_sync_train);
					break;
				case 1:
					core->add_option<toggle_option<bool>>(("Automobile"), nullptr, &m_vars.m_car);
					core->add_option<toggle_option<bool>>(("Bike"), nullptr, &m_vars.m_bike);
					core->add_option<toggle_option<bool>>(("Boat"), nullptr, &m_vars.m_boat);
					core->add_option<toggle_option<bool>>(("Door"), nullptr, &m_vars.m_door);
					core->add_option<toggle_option<bool>>(("Heli"), nullptr, &m_vars.m_heli);
					core->add_option<toggle_option<bool>>(("Object"), nullptr, &m_vars.m_object);
					core->add_option<toggle_option<bool>>(("Ped"), nullptr, &m_vars.m_ped);
					core->add_option<toggle_option<bool>>(("Pickup"), nullptr, &m_vars.m_pickup);
					core->add_option<toggle_option<bool>>(("Pickup Placement"), nullptr, &m_vars.m_pickup_placement);
					core->add_option<toggle_option<bool>>(("Plane"), nullptr, &m_vars.m_plane);
					core->add_option<toggle_option<bool>>(("Submarine"), nullptr, &m_vars.m_sub);
					core->add_option<toggle_option<bool>>(("Player"), nullptr, &m_vars.m_player);
					core->add_option<toggle_option<bool>>(("Trailer"), nullptr, &m_vars.m_trailer);
					core->add_option<toggle_option<bool>>(("Train"), nullptr, &m_vars.m_train);
					break;
				}

			});

	}

	void protections_entity_menu::script_init() {}

	void protections_entity_menu::script_on_tick() {}

	void protections_entity_menu::script_func()
	{
		m_protections_entity_menu.script_init();
		while (true)
		{
			m_protections_entity_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}