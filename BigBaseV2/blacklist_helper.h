#pragma once
#include <unordered_set>
#include "json_util.h"

namespace big
{
	struct blacklist_helper
	{
		std::string name;
		std::uint64_t rockstar_id = 0;
		bool is_modder = false;
		std::unordered_set<int> infractions;
	};

	static void to_json(nlohmann::json& j, const blacklist_helper& player)
	{
		j = nlohmann::json{
			{ "name", player.name },
			{ "rockstar_id", player.rockstar_id },
			{ "modder", player.is_modder },
			{ "modder_reason", player.infractions },
		};
	};

	static void from_json(const nlohmann::json& j, blacklist_helper& player)
	{
		set_from_key_or_default(j, "name", player.name);
		set_from_key_or_default(j, "rockstar_id", player.rockstar_id);
		set_from_key_or_default(j, "modder", player.is_modder);
		set_from_key_or_default(j, "modder_reason", player.infractions);
	}
};