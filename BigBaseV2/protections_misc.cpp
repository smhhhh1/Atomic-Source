#include "common.hpp"
#include "gta_util.hpp"
#include "protections_misc.h"
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
#include "lists.h"
#include "fiber_pool.hpp"
#include "scroll.h"

using namespace big::protections::misc::vars;

namespace big::protections::misc::vars {

	variables m_vars;

}

namespace big::menu
{

	void protections_misc_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Presence Events", SubProtectionsMisc, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				core->add_option<scroll_option<const char*, std::size_t>>(("Crashing"), nullptr, &lists::crash, &lists::crash_pos, true);
				core->add_option<scroll_option<const char*, std::size_t>>(("Desync Kicks"), nullptr, &lists::desync, &lists::desync_pos, true);

				core->add_option<scroll_option<const char*, std::size_t>>(("Invalid Ip"), nullptr, &lists::invalid_ip, &lists::invalid_ip_pos, true);
				core->add_option<scroll_option<const char*, std::size_t>>(("Invalid Syncs"), nullptr, &lists::invalid_syncs, &lists::invalid_syncs_pos, true);
				core->add_option<scroll_option<const char*, std::size_t>>(("Clone"), nullptr, &lists::clone, &lists::clone_pos, true);
				core->add_option<scroll_option<const char*, std::size_t>>(("Cages"), nullptr, &lists::cage, &lists::cage_pos, true);
				core->add_option<scroll_option<const char*, std::size_t>>(("Attachments"), nullptr, &lists::attach, &lists::attach_pos, true);
				core->add_option<toggle_option<bool>>(("Disable Chat Messages"), nullptr, &m_vars.m_disable_chat_messages);
				core->add_option<toggle_option<bool>>(("Disable Text Messages"), nullptr, &m_vars.m_disable_text_messages);
			});
	}

	void protections_misc_menu::script_init() {}

	void protections_misc_menu::script_on_tick()
	{


	}

	void protections_misc_menu::script_func()
	{
		m_protections_misc_menu.script_init();
		while (true)
		{
			m_protections_misc_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}