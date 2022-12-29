#include "hooking.hpp"
#include "lists.h"
#include "notify.h"
#include "network_notifications.h"

namespace big
{
	bool hooks::hk_player_creation_data_node(CPlayerCreationDataNode* node)
	{
		auto result = g_hooking->og_player_creation_data_node.get_original<decltype(&hk_player_creation_data_node)>()(node);

		if (lists::crash_model_check(node->m_model)) {
			ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Invalid Model(Player Creation)" });
			LOG(INFO) << "[Protections] Blocked Invalid Player " << "Model: " << HEX_TO_UPPER(node->m_model);
			return false;
		}

		if (network::notifications::vars::m_vars.m_player_creation) {
			LOG(INFO) << "[Notifications] Player Created " << "Model: " << HEX_TO_UPPER(node->m_model);
			ImGui::InsertNotification({ ImGuiToastType_None, 2600, "player created, model hash: ", node->m_model });
		}

		return result;
	}
}