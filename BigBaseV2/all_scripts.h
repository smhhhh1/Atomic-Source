#pragma once
#include "native_hooks.h"
#include "natives.hpp"
#include "pointers.hpp"
#include "network_spoofing_name.h"
#include "network_toolkit.h"
#include "hooking.hpp"
namespace big
{
		
		
    namespace all_scripts
    {

        

        void GET_PLAYER_NAME(rage::scrNativeCallContext* src)
        {
			std::string name = "~h~~p~atomicmenu.xyz";
            const auto playerId = src->get_arg<Player>(0);
            src->set_return_value(PLAYER::GET_PLAYER_NAME(playerId));
            if (network::toolkit::vars::m_vars.m_streamer_mode)
            {
				switch (playerId) {
				case 0: return src->set_return_value(name.c_str());
				case 1: return src->set_return_value(name.c_str());
				case 2: return src->set_return_value(name.c_str());
				case 3: return src->set_return_value(name.c_str());
				case 4: return src->set_return_value(name.c_str());
				case 5: return src->set_return_value(name.c_str());
				case 6: return src->set_return_value(name.c_str());
				case 7: return src->set_return_value(name.c_str());
				case 8: return src->set_return_value(name.c_str());
				case 9: return src->set_return_value(name.c_str());
				case 10: return src->set_return_value(name.c_str());
				case 11: return src->set_return_value(name.c_str());
				case 12: return src->set_return_value(name.c_str());
				case 13: return src->set_return_value(name.c_str());
				case 14: return src->set_return_value(name.c_str());
				case 15: return src->set_return_value(name.c_str());
				case 16: return src->set_return_value(name.c_str());
				case 17: return src->set_return_value(name.c_str());
				case 18: return src->set_return_value(name.c_str());
				case 19: return src->set_return_value(name.c_str());
				case 20: return src->set_return_value(name.c_str());
				case 21: return src->set_return_value(name.c_str());
				case 22: return src->set_return_value(name.c_str());
				case 23: return src->set_return_value(name.c_str());
				case 24: return src->set_return_value(name.c_str());
				case 25: return src->set_return_value(name.c_str());
				case 26: return src->set_return_value(name.c_str());
				case 27: return src->set_return_value(name.c_str());
				case 28: return src->set_return_value(name.c_str());
				case 29: return src->set_return_value(name.c_str());
				case 30: return src->set_return_value(name.c_str());
				case 31: return src->set_return_value(name.c_str());
				case 32: return src->set_return_value(name.c_str());
				}
            }
            if (network::spoofing::name::vars::m_vars.m_spoof)
            {
                const auto network_player_mgr = (*g_pointers->m_network_player_mgr);
                if (network_player_mgr && network_player_mgr->m_local_net_player && playerId == network_player_mgr->m_local_net_player->m_player_id)
                {
                    src->set_return_value(network::spoofing::name::vars::m_vars.m_name.c_str());
                }
            }
        }
    }
  
}