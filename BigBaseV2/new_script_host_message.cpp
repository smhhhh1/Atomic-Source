#include "hooking.hpp"
#include "lists.h"
#include "notify.h"
#include "../caller.hpp"
#include "gta/script_handler.hpp"
#include "natives.hpp"
#include "notify.h"
#include "network_notifications.h"
namespace big
{
	bool hooks::hk_new_script_host_message(uint64_t a1, uint64_t a2)
	{
		uint8_t data[0x50];
		memset(data, 0, 0x50);

		uint64_t script_table = *(uint64_t*)a1;
		*(uint64_t*)&data[0] = call<uint64_t>(*(uint64_t*)(script_table + 0x78), a1);

		if (call<bool>(g_pointers->m_new_script_host_message, data, *(uint64_t*)(a2), *(uint32_t*)(a2 + 0x8), 0)) {
			CNetGamePlayer* new_host = *(CNetGamePlayer**)(a2 + 0x10);

			CGameScriptHandler* script_handler = call<CGameScriptHandler*>(*(uint64_t*)(script_table + 0x48), a1, *(uint64_t*)(&data[0]));
			if (is_valid_ptr(script_handler)) {
				if (is_valid_ptr(script_handler->m_script_thread)) {
					if (!strcmp(script_handler->m_script_thread->m_name, "freemode")) {
						if (new_host->m_player_id != NETWORK::NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0)) {
							LOG(INFO) << new_host->m_player_info->m_net_player_data.m_name << " is Now Script Host";
							if (network::notifications::vars::m_vars.m_new_script_host) {
								ImGui::InsertNotification({ ImGuiToastType_None, 2600, "%s is Now Script Host", new_host->m_player_info->m_net_player_data.m_name });
							}
							
						}
					}
				}
			}
		}


		return g_hooking->og_new_script_host_message.get_original<decltype(&hooks::hk_new_script_host_message)>()(a1, a2);
	}
}