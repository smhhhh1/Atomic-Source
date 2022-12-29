#pragma once
#include "native_hooks.h"
#include "natives.hpp"
#include "pointers.hpp"
#include "network_friends.h"

namespace big
{
	namespace network
	{
		inline void NETWORK_SESSION_HOST(rage::scrNativeCallContext* src)
		{
			if (friends::vars::m_vars.join_queued)
			{
				g_pointers->m_join_session_by_info(*g_pointers->m_network, &friends::vars::m_vars.info, 0, 0, nullptr, 0);
				friends::vars::m_vars.join_queued = false;
				src->set_return_value<BOOL>(TRUE);
			}
			else
			{
				src->set_return_value<BOOL>(NETWORK::NETWORK_SESSION_HOST(src->get_arg<int>(0), src->get_arg<int>(1), src->get_arg<BOOL>(2)));
			}
		}
	}
}
