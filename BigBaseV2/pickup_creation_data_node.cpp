#include "hooking.hpp"
#include "lists.h"
#include "notify.h"
#include "network_notifications.h"
namespace big
{
	bool hooks::hk_pickup_creation_data_node(CPickupCreationDataNode* node, rage::netObject* obj)
	{
		auto result = g_hooking->og_pickup_creation_data_node.get_original<decltype(&hk_pickup_creation_data_node)>()(node, obj);

		if (lists::crash_model_check(node->m_custom_model) || lists::crash_model_check(node->m_pickup_hash)) {
			ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Invalid Model(Pickup Creation)" });
			LOG(INFO) << "[Protections] Blocked Invalid Pickup " << "Model: " << HEX_TO_UPPER(node->m_custom_model);
			return true;
		}

		if (network::notifications::vars::m_vars.m_pickup_creation) {
			LOG(INFO) << "[Notifications] Pickup Created " << "Model: " << HEX_TO_UPPER(node->m_pickup_hash);
			ImGui::InsertNotification({ ImGuiToastType_None, 2600, "pickup created, model hash: ", node->m_pickup_hash });
		}

		return result;
	}
}