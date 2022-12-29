#include "hooking.hpp"
#include "gta/player.hpp"
#include "gta_util.hpp"
#include "network_spoofing_name.h"
#include "network_spoofing_ip.h"
#include "network_spoofing_rid.h"
#include "network_toolkit.h"
namespace big
{
	bool hooks::hk_read_bitbuffer_gamer_handle(rage::datBitBuffer* buffer, rage::rlGamerHandle* handle)
	{
		bool result = g_hooking->og_read_bitbuffer_gamer_handle.get_original<decltype(&hooks::hk_read_bitbuffer_gamer_handle)>()(buffer, handle);
		if (network::spoofing::rid::vars::m_vars.should_spoof_rockstar_id && handle->m_rockstar_id == network::spoofing::rid::vars::m_vars.applied_spoof_rockstar_id)
			handle->m_rockstar_id = g_pointers->m_profile_gamer_info->m_gamer_handle_2.m_rockstar_id;
		return result;
	}
	bool hooks::hk_write_bitbuffer_gamer_handle(rage::datBitBuffer* buffer, rage::rlGamerHandle* handle)
	{
		bool restore = false;

		if (network::spoofing::rid::vars::m_vars.should_spoof_rockstar_id && handle->m_rockstar_id == g_pointers->m_profile_gamer_info->m_gamer_handle_2.m_rockstar_id)
		{
			handle->m_rockstar_id = network::spoofing::rid::vars::m_vars.applied_spoof_rockstar_id;
			restore = true;
		}

		bool result = g_hooking->og_write_bitbuffer_gamer_handle.get_original<decltype(&hooks::hk_write_bitbuffer_gamer_handle)>()(buffer, handle);

		if (restore)
			handle->m_rockstar_id = g_pointers->m_profile_gamer_info->m_gamer_handle_2.m_rockstar_id;
		return result;
	}

	bool hooks::hk_send_net_info_to_lobby(rage::netPlayerData* player, int64_t a2, int64_t a3, DWORD* a4)
	{
		if (gta_util::get_local_ped()->m_player_info->m_net_player_data.m_rockstar_id == player->m_rockstar_id)
		{
			if (network::spoofing::name::vars::m_vars.m_spoof) {
				memcpy(player->m_name, network::spoofing::name::vars::m_vars.m_name.c_str(), sizeof(player->m_name));
			}

			if (network::spoofing::ip::vars::m_vars.m_spoof) {
				player->m_external_ip.m_field1 = network::spoofing::ip::vars::m_vars.ip_address[0];
				player->m_external_ip.m_field2 = network::spoofing::ip::vars::m_vars.ip_address[1];
				player->m_external_ip.m_field3 = network::spoofing::ip::vars::m_vars.ip_address[2];
				player->m_external_ip.m_field4 = network::spoofing::ip::vars::m_vars.ip_address[3];
			}

			if (network::spoofing::rid::vars::m_vars.should_spoof_rockstar_id)
			{
				player->m_rockstar_id = network::spoofing::rid::vars::m_vars.applied_spoof_rockstar_id;
				player->m_rockstar_id2 = network::spoofing::rid::vars::m_vars.applied_spoof_rockstar_id;
			}
		}
		else
		{
			std::string name = "~p~atomicmenu.xyz";
			if (network::toolkit::vars::m_vars.m_streamer_mode)
			{
				memcpy(player->m_name, name.c_str(), sizeof(player->m_name));
			}
			else
			{
				memcpy(player->m_name, network::spoofing::name::vars::m_vars.m_name.c_str(), sizeof(player->m_name));
			}
		}

		return g_hooking->og_send_net_info_to_lobby.get_original<decltype(&hooks::hk_send_net_info_to_lobby)>()(player, a2, a3, a4);
	}
}