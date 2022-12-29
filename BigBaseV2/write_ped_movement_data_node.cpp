#include "hooking.hpp"
#include "node_types.h"

#include "../network_spoofing.h"
namespace big
{
	uint64_t hooks::hk_write_ped_movement_data_node(CPedMovementDataNode* node, rage::netObject* object)
	{
		if (network::spoofing::vars::m_vars.m_movement_animation) {
			node->m_is_walking = false;
			node->m_is_running = false;
		}

		return g_hooking->og_write_ped_movement_data_node.get_original<decltype(&hooks::hk_write_ped_movement_data_node)>()(node, object);
	}
}