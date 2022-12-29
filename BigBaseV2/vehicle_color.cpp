#include "common.hpp"
#include "gta_util.hpp"
#include "vehicle_color.h"
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
namespace big::menu
{


	void vehicle_color_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Vehicle Color", SubVehicleColor, [](sub* core)
			{
				core->add_option<submenu>("Primary Color", nullptr, SubVehicleColorPrimary);
				core->add_option<submenu>("Secondary Color", nullptr, SubVehicleColorSecondary);
			});
	}

	void vehicle_color_menu::script_init() {}

	void vehicle_color_menu::script_on_tick() {}

	void vehicle_color_menu::script_func()
	{
		m_vehicle_color_menu.script_init();
		while (true)
		{
			m_vehicle_color_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}