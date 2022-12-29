#pragma once
#include "blacklist_helper.h"
#include "player_service.hpp"


namespace big
{
	class player_database_service
	{
		std::unordered_map<std::uint64_t, blacklist_helper> m_players;
		blacklist_helper* m_selected = nullptr;

	public:
		std::filesystem::path m_file_path;
		player_database_service();
		~player_database_service();

		void save();
		void load();

		std::unordered_map<std::uint64_t, blacklist_helper>& get_players();
		blacklist_helper* get_player_by_rockstar_id(std::uint64_t rockstar_id);
		blacklist_helper* get_or_create_player(player_ptr player);
		void update_rockstar_id(std::uint64_t old, std::uint64_t _new);
		void remove_rockstar_id(std::uint64_t rockstar_id);

		void set_selected(blacklist_helper* selected);
		blacklist_helper* get_selected();
	};

	inline player_database_service* g_player_database_service;
}