#include "hooking.hpp"
#include "lists.h"
#include "notify.h"
namespace big
{
	void hooks::hk_player_appearance_data_node(rage::netObject* object, CPlayerAppearanceDataNode* node)
	{

		if (lists::crash_model_check(node->m_model_hash))
		{
			ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Invalid Model" });
			LOG(INFO) << "[Protections] Blocked Invalid Player Model";
			return;
		}

		if (
			node->components.get_drawable(0) == 45 ||
			node->components.get_drawable(1) == 197 ||
			node->components.get_drawable(2) == 76 ||
			node->components.get_drawable(3) == 196 ||
			node->components.get_drawable(4) == 144 ||
			node->components.get_drawable(5) == 99 ||
			node->components.get_drawable(6) == 102 ||
			node->components.get_drawable(7) == 151 ||
			node->components.get_drawable(8) == 189 ||
			node->components.get_drawable(9) == 56 ||
			node->components.get_drawable(10) == 132 ||
			node->components.get_drawable(11) == 393 ||
			node->components.get_drawable(0) == 393 ||
			node->components.get_drawable(0) == 415 ||
			node->components.get_drawable(4) == 151 ||
			node->components.get_drawable(6) == 106
			)
		{
			ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Next Gen Crash" });
			LOG(INFO) << "[Protections] Blocked Next Gen Crash";
			return;
		}

		g_hooking->og_player_appearance_data_node.get_original<decltype(&hk_player_appearance_data_node)>()(object, node);
	}
}