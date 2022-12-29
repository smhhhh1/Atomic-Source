#include "hooking.hpp"
#include "lists.h"
#include "notify.h"
#include "gta/player.hpp"
#include "gta/ped_factory.hpp"
#include "CObject.h"
namespace big
{
	int64_t hooks::hk_physical_attach_data_node(CPhysicalAttachDataNode* node, rage::netObject* data)
	{
		auto result = g_hooking->og_physical_attach_data_node.get_original<decltype(&hk_physical_attach_data_node)>()(node, data);

		if (!result)
			return result;

		if (node->m_attached && node->m_attached_to == data->m_object_id)
		{
			return true;
		}

		return result;
	}
}