#include "hooking.hpp"
#include "lists.h"
#include "notify.h"
#include "network_notifications.h"
namespace big
{
	int64_t hooks::hk_ped_attach_data_node(CPedAttachDataNode* node, rage::netObject* data)
	{
		auto result = g_hooking->og_ped_attach_data_node.get_original<decltype(&hk_ped_attach_data_node)>()(node, data);

		if (!result)
			return result;

		if (node->m_attached && node->m_attached_to == data->m_object_id)
		{
			return true;
		}

		return result;
	}
}