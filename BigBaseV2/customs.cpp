#include "common.hpp"
#include "gta_util.hpp"
#include "customs.h"
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
using namespace big::vehicle::customs::vars;


namespace big::vehicle::customs::vars
{
	variables m_vars;
}

namespace big::menu
{


	void customs_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Customs", SubCustoms, [](sub* core)
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
				VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

				/*core->add_option<number_option<std::int32_t>>(("Spoiler"), nullptr, &m_vars.Spoiler, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_SPOILER), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_SPOILER, m_vars.Spoiler, false); });
				core->add_option<number_option<std::int32_t>>(("Front Bumper"), nullptr, &m_vars.FBumper, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_FRONTBUMPER), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_FRONTBUMPER, m_vars.FBumper, false); });
				core->add_option<number_option<std::int32_t>>(("Rear Bumper"), nullptr, &m_vars.RBumper, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_REARBUMPER), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_REARBUMPER, m_vars.RBumper, false); });
				core->add_option<number_option<std::int32_t>>(("Side Skirt"), nullptr, &m_vars.SSkirt, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_SIDESKIRT), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_SIDESKIRT, m_vars.SSkirt, false); });
				core->add_option<number_option<std::int32_t>>(("Exhaust"), nullptr, &m_vars.Exhaust, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_EXHAUST), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_EXHAUST, m_vars.Exhaust, false); });
				core->add_option<number_option<std::int32_t>>(("Grille"), nullptr, &m_vars.Grille, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_GRILLE), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_GRILLE, m_vars.Grille, false); });
				core->add_option<number_option<std::int32_t>>(("Chassis"), nullptr, &m_vars.Chasis, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_CHASSIS), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_CHASSIS, m_vars.Chasis, false); });
				core->add_option<number_option<std::int32_t>>(("Hood"), nullptr, &m_vars.Hood, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_HOOD), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_HOOD, m_vars.Hood, false); });
				core->add_option<number_option<std::int32_t>>(("Fender"), nullptr, &m_vars.Fender, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_FENDER), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_FENDER, m_vars.Fender, false); });
				core->add_option<number_option<std::int32_t>>(("Right Fender"), nullptr, &m_vars.RFender, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_RIGHTFENDER), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_RIGHTFENDER, m_vars.RFender, false); });
				core->add_option<number_option<std::int32_t>>(("Roof"), nullptr, &m_vars.Roof, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ROOF), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_ROOF, m_vars.Roof, false); });
				core->add_option<number_option<std::int32_t>>(("Engine"), nullptr, &m_vars.Engine, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ENGINE), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_ENGINE, m_vars.Engine, false); });
				core->add_option<number_option<std::int32_t>>(("Brakes"), nullptr, &m_vars.Brakes, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_BRAKES), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_BRAKES, m_vars.Brakes, false); });
				core->add_option<number_option<std::int32_t>>(("Transmission"), nullptr, &m_vars.Transmission, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_TRANSMISSION), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_TRANSMISSION, m_vars.Transmission, false); });
				core->add_option<number_option<std::int32_t>>(("Horns"), nullptr, &m_vars.Horns, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_HORNS), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_HORNS, m_vars.Horns, false); });
				core->add_option<number_option<std::int32_t>>(("Suspension"), nullptr, &m_vars.Suspension, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_SUSPENSION), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_SUSPENSION, m_vars.Suspension, false); });
				core->add_option<number_option<std::int32_t>>(("Armor"), nullptr, &m_vars.Armor, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ARMOR), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_ARMOR, m_vars.Armor, false); });
				core->add_option<number_option<std::int32_t>>(("Turbo"), nullptr, &m_vars.Turbo, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_TURBO), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_TURBO, m_vars.Turbo, false); });
				core->add_option<number_option<std::int32_t>>(("Tire Smoke"), nullptr, &m_vars.TSmoke, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_TIRESMOKE), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_TIRESMOKE, m_vars.TSmoke, false); });
				core->add_option<number_option<std::int32_t>>(("Xenon"), nullptr, &m_vars.Xenon, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_XENONLIGHTS), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_XENONLIGHTS, m_vars.Xenon, false); });
				core->add_option<number_option<std::int32_t>>(("Wheels"), nullptr, &m_vars.Wheels, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_FRONTWHEELS), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_FRONTWHEELS, m_vars.Wheels, false); });
				core->add_option<number_option<std::int32_t>>(("Windows"), nullptr, &m_vars.Windows, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_WINDOWS), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_WINDOWS, m_vars.Windows, false); });
				core->add_option<number_option<std::int32_t>>(("Hydraulics"), nullptr, &m_vars.Hydraulics, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_HYDRAULICS), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_HYDRAULICS, m_vars.Hydraulics, false); });
				core->add_option<number_option<std::int32_t>>(("Engine Block"), nullptr, &m_vars.EngineBlock, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ENGINE_BLOCK), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_ENGINE_BLOCK, m_vars.EngineBlock, false); });
				core->add_option<number_option<std::int32_t>>(("Livery"), nullptr, &m_vars.Livery, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_LIVERY), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_LIVERY, m_vars.Livery, false); });*/
			});
	}

	void customs_menu::script_init() {}

	void customs_menu::script_on_tick() {}

	void customs_menu::script_func()
	{
		m_customs_menu.script_init();
		while (true)
		{
			m_customs_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}