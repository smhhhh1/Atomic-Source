#include "hooking.hpp"
#include "lists.h"
#include "notify.h"
#include "network_notifications.h"
namespace big
{
	bool hooks::hk_vehicle_creation_data_node(CVehicleCreationDataNode* node)
	{
		auto result = g_hooking->og_vehicle_creation_data_node.get_original<decltype(&hk_vehicle_creation_data_node)>()(node);

		if (!result)
			return result;

		if (lists::crash_model_check(node->m_model)) {
			ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Invalid Model(Vehicle Creation)" });
			LOG(INFO) << "[Protections] Blocked Invalid Vehicle " << "Model: " << HEX_TO_UPPER(node->m_model);
			return false;
		}

		if (network::notifications::vars::m_vars.m_vehicle_creation) {
			LOG(INFO) << "[Notifications] Vehicle Created " << "Model: " << HEX_TO_UPPER(node->m_model);
			ImGui::InsertNotification({ ImGuiToastType_None, 2600, "vehicle created, model hash: ", node->m_model });
		}

		return result;
	}
}