#include "hooking.hpp"
#include "player_service.hpp"
#include "network_toolkit.h"
#include "notify.h"
#include "network_notifications.h"
namespace big
{
	void* hooks::hk_assign_physical_index(CNetworkPlayerMgr* netPlayerMgr, CNetGamePlayer* player, uint8_t new_index)
	{
		const auto result = g_hooking->og_assign_physical_index.get_original<decltype(&hooks::hk_assign_physical_index)>()(netPlayerMgr, player, new_index);
		const auto* net_player_data = player->get_net_data();

		if (new_index == static_cast<uint8_t>(-1))
		{
			g_player_service->player_leave(player);

			if (net_player_data)
			{			
				LOG(INFO) << "Session | " << net_player_data->m_name << " is leaving the session";
				
				if (network::notifications::vars::m_vars.m_player_leave) {
					ImGui::InsertNotification({ ImGuiToastType_None, 2600, "% is leaving the session", net_player_data->m_name });
				}
			}

			return result;
		}

		g_player_service->player_join(player);
		if (net_player_data)
		{
	
			LOG(INFO) << "Session | " << net_player_data->m_name << " is joining the session";

			if (network::notifications::vars::m_vars.m_player_join) {
				ImGui::InsertNotification({ ImGuiToastType_None, 2600, "% is joining the session", net_player_data->m_name });
			}
		}
		return result;
	}
}
