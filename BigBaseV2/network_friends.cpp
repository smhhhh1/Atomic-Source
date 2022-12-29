#include "common.hpp"
#include "gta_util.hpp"
#include "network_friends.h"
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
#include "script_global.hpp"

using namespace big::network::friends::vars;


namespace big::network::friends::vars
{
	variables m_vars;

	enum class eSessionType
	{
		JOIN_PUBLIC,
		NEW_PUBLIC,
		CLOSED_CREW,
		CREW,
		CLOSED_FRIENDS = 6,
		FIND_FRIEND = 9,
		SOLO,
		INVITE_ONLY,
		JOIN_CREW,
		SC_TV,
		LEAVE_ONLINE = -1
	};
	void join_type(eSessionType session)
	{
		*script_global(2726795).as<int*>() = (session == eSessionType::SC_TV ? 1 : 0);

		if (session == eSessionType::LEAVE_ONLINE)
			*script_global(1574589).at(2).as<int*>() = -1;
		else
			*script_global(1575015).as<int*>() = (int)session;

		*script_global(1574589).as<int*>() = 1;
		script::get_current()->yield(200ms);
		*script_global(1574589).as<int*>() = 0;
	}
	void join_by_rockstar_id(uint64_t rid)
	{
		if (SCRIPT::_GET_NUMBER_OF_REFERENCES_OF_SCRIPT_WITH_NAME_HASH(RAGE_JOAAT("maintransition")) != 0 ||
			STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS())
		{
			return;
		}

		rage::rlGamerHandle player_handle(rid);
		rage::rlSessionByGamerTaskResult result;
		bool success = false;
		int state = 0;
		if (g_pointers->m_start_get_session_by_gamer_handle(0, &player_handle, 1, &result, 1, &success, &state))
		{
			while (state == 1)
				script::get_current()->yield();

			if (state == 3 && success)
			{
				m_vars.join_queued = true;
				m_vars.info = result.m_session_info;
				join_type({ eSessionType::NEW_PUBLIC });
				if (SCRIPT::_GET_NUMBER_OF_REFERENCES_OF_SCRIPT_WITH_NAME_HASH(RAGE_JOAAT("maintransition")) == 0)
				{
					m_vars.join_queued = false;
				}
				return;
			}
		}
	}

}



namespace big::menu
{


	void network_friends_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Friends", SubNetworkFriends, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				for (std::uint32_t i = 0; i < g_pointers->m_friend_registry->m_friend_count; ++i)
				{
					core->add_option<simple_option>(g_pointers->m_friend_registry->get(i)->m_name, nullptr, [=]
						{
							selected_friend = i;

							join_by_rockstar_id(g_pointers->m_friend_registry->get(selected_friend)->m_rockstar_id);
						});
				}

			});
	}

	void network_friends_menu::script_init() {}

	void network_friends_menu::script_on_tick() {}

	void network_friends_menu::script_func()
	{
		m_network_friends_menu.script_init();
		while (true)
		{
			m_network_friends_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}