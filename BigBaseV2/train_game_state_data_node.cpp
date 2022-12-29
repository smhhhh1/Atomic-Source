#include "hooking.hpp"
#include "lists.h"
#include "notify.h"
namespace big
{
	void  hooks::hk_train_game_state_data_node(rage::netObject* player, CTrainGameStateDataNode* node)
	{
		if (player->m_object_id == node->m_linked_to_backward_id && player->m_object_id == node->m_linked_to_forward_id 
			&& player->m_object_id == node->m_engine_id)
		{
			return;
		}
		if (++node->m_carriage_config_index > 20)
		{
			return;
		}
		return g_hooking->og_train_game_state_data_node.get_original<decltype(&hk_train_game_state_data_node)>()(player, node);
	}
}