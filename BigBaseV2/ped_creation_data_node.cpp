#include "hooking.hpp"
#include "lists.h"
#include "notify.h"
#include "network_notifications.h"
namespace big
{
	bool hooks::hk_ped_creation_data_node(CPedCreationDataNode* node)
	{
		auto result = g_hooking->og_ped_creation_data_node.get_original<decltype(&hk_ped_creation_data_node)>()(node);

		if (lists::crash_model_check(node->m_model)) {
			ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Invalid Model(Ped Creation)" });
			LOG(INFO) << "Protections | Blocked Invalid Ped " << "Model: " << HEX_TO_UPPER(node->m_model);
			return true;
		}
		else if (lists::crash_model_check(node->m_prop_model)) {
			ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Invalid Model(Ped Creation)" });
			LOG(INFO) << "Protections | Blocked Invalid Ped Prop " << "Model: " << HEX_TO_UPPER(node->m_model);
			return true;
		}

		if (network::notifications::vars::m_vars.m_ped_creation) {
			LOG(INFO) << "[Notifications] Ped Created " << "Model: " << HEX_TO_UPPER(node->m_model);
			ImGui::InsertNotification({ ImGuiToastType_None, 2600, "ped created, model hash: ", node->m_model });
		}

		return result;
	}
}