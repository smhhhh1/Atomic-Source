#include "hooking.hpp"
#include "node_types.h"

#include "network_spoofing_crew_name.h"
#include "network_spoofing_crew_tag.h"
#include "network_spoofing_crew_icon.h"
namespace big
{
	void hooks::hk_write_player_gamer_data_node(rage::netObject* player, CPlayerGamerDataNode* node)
	{

		g_hooking->og_write_player_gamer_data_node.get_original<decltype(&hooks::hk_write_player_gamer_data_node)>()(player, node);

		if (network::spoofing::crew::name::vars::m_vars.m_spoof) {
			strcpy(node->m_clan_data.m_clan_name, network::spoofing::crew::name::vars::m_vars.m_name.c_str());
		}

		if (network::spoofing::crew::tag::vars::m_vars.m_spoof) {
			strcpy(node->m_clan_data.m_clan_tag,network::spoofing::crew::tag::vars::m_vars.m_tag.c_str());
		}

		if (network::spoofing::crew::icon::vars::m_vars.m_spoof) {
			strcpy(node->m_clan_data.m_clan_tag, std::to_string(network::spoofing::crew::icon::vars::m_vars.m_id).c_str());
		}
	}
}