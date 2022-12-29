#include "hooking.hpp"
#include "lists.h"
#include "notify.h"
#include "network_notifications.h"
namespace big
{
	bool hooks::hk_object_creation_data_node(CObjectCreationDataNode* node, rage::netObject* obj)
	{
		auto result = g_hooking->og_object_creation_data_node.get_original<decltype(&hk_object_creation_data_node)>()(node, obj);



		if (lists::crash_model_check(node->m_model)) {
			ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Invalid Model(Object Creation)" });
			LOG(INFO) << "Protections | Blocked Invalid Object " << "Model: " << HEX_TO_UPPER(node->m_model);
			return true;
		}
		else if (lists::cage_model_check(node->m_model)) {
			ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Cage" });
			LOG(INFO) << "Protections |  Blocked Cage " << "Model: " << HEX_TO_UPPER(node->m_model);
			return true;
		}

		if (network::notifications::vars::m_vars.m_object_creation) {
			LOG(INFO) << "[Notifications] Object Created " << "Model: " << HEX_TO_UPPER(node->m_model);
			ImGui::InsertNotification({ ImGuiToastType_None, 2600, "object created, model hash: ", node->m_model });
		}

		return result;
	}
}