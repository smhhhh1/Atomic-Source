#include "hooking.hpp"
#include "player_service.hpp"
#include "network_notifications.h"
#include "notify.h"
namespace big
{
	void hooks::hk_network_player_mgr_init(CNetworkPlayerMgr* _this, std::uint64_t a2, std::uint32_t a3, std::uint32_t a4[4])
	{
		
		LOG(INFO) << "Session | Joining Session";
		
		if (network::notifications::vars::m_vars.m_session_join) {
			ImGui::InsertNotification({ ImGuiToastType_None, 2600, "joining session" });
		}

		g_hooking->og_network_player_mgr_init.get_original<decltype(&hooks::hk_network_player_mgr_init)>()(_this, a2, a3, a4);

		g_player_service->player_join(_this->m_local_net_player);
	}

	void hooks::hk_network_player_mgr_shutdown(CNetworkPlayerMgr* _this)
	{
		g_player_service->do_cleanup();

		if (network::notifications::vars::m_vars.m_session_leave) {
			ImGui::InsertNotification({ ImGuiToastType_None, 2600, "leaving session" });
		}

		LOG(INFO) << "Session | Leaving Session";
		

		g_hooking->og_network_player_mgr_shutdown.get_original<decltype(&hooks::hk_network_player_mgr_shutdown)>()(_this);
	}
}
