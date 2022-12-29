#include "hooking.hpp"
#include "CObject.h"
#include "netObject.hpp"
#include "gta/player.hpp"
#include "generic_types.h"
#include "gta/net_object_mgr.hpp"
#include "node_types.h"
#include "notify.h"
#include "node_helpers.h"

namespace big
{

	bool hooks::hk_sync_can_apply_data(rage::netSyncTree* tree, rage::netObject* object)
	{

		if (!is_valid_ptr(object->m_object_id)) {
			return false;
		}
		
		if (tree->m_child_node_count <= 0 || tree->m_child_node_count > 100) {
			return false;
		}

		if (tree->m_child_node_count && get_creation_node(tree->m_sync_node, sync_sender, object)) {
			return false;
		}

		if (tree->m_child_node_count && get_attach_node(tree->m_sync_node, sync_sender, object)) {
			return false;
		}

		if (tree->m_child_node_count && get_position_node(tree->m_sync_node, sync_sender, object)) {
			return false;
		}


		return g_hooking->og_sync_can_apply_data.get_original<decltype(&hooks::hk_sync_can_apply_data)>()(tree, object);
	}
}