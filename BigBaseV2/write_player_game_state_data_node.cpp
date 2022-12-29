#include "hooking.hpp"
#include "network_spoofing_detection_flags.h"
#include "node_types.h"
namespace big
{
	bool hooks::hk_write_player_game_state_data_node(rage::netObject* player, CPlayerGameStateDataNode* node)
	{
		auto ret = g_hooking->og_write_player_game_state_data_node.get_original<decltype(&hooks::hk_write_player_game_state_data_node)>()(player, node);

		if (network::spoofing::detection_flags::vars::m_vars.m_godmode) {
			node->m_is_invincible = false;
		}

		if (network::spoofing::detection_flags::vars::m_vars.m_super_jump) {
			node->m_super_jump = false;
		}

		if (network::spoofing::detection_flags::vars::m_vars.m_spectate) {
			node->m_is_spectating = false;
			node->m_spectating_net_id = 0;
		}

		if (network::spoofing::detection_flags::vars::m_vars.m_health) {
			node->m_max_health = 400;
			node->m_is_max_armor_and_health_default = true;
		}

		if (network::spoofing::detection_flags::vars::m_vars.m_armor) {
			node->m_max_armor = 200;
			node->m_is_max_armor_and_health_default = true;
		}

		if (network::spoofing::detection_flags::vars::m_vars.m_defense_damage) {
			node->m_weapon_defence_modifier = 1.0f;
			node->m_weapon_defence_modifier_2 = false;
		}

		if (network::spoofing::detection_flags::vars::m_vars.m_weapon_damage) {
			node->m_weapon_damage_modifier = 1.0f;
		}

		if (network::spoofing::detection_flags::vars::m_vars.m_melee_damage) {
			node->m_melee_weapon_damage_modifier = 1.0f;
		}

		if (network::spoofing::detection_flags::vars::m_vars.m_proofs) {
			node->m_steam_proof = false;
			node->m_melee_proof = false;
			node->m_fire_proof = false;
			node->m_explosion_proof = false;
			node->m_bullet_proof = false;
			node->m_collision_proof = false;
		}

		return ret;
	}
}
