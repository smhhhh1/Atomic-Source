#include "common.hpp"
#include "features.hpp"
#include "logger.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "../impacts.h"
#include "../entity_gun.h"
#include "../paint_gun.h"
#include "../players.h"
#include "pointers.hpp"
#include "../security_types.h"
namespace big
{
	void features::run_tick()
	{
		menu::m_impacts_menu.script_func();
		menu::m_entity_gun_menu.script_func();
		menu::m_paint_gun_menu.script_func();

		
	}

	void features::script_func()
	{
		while (true)
		{
			TRY_CLAUSE
			{
				run_tick();
			}
			EXCEPT_CLAUSE
			script::get_current()->yield();
		}
	}
}
