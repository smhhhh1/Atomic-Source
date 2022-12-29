#pragma once
#include "player_service.hpp"
#include "snSession.hpp"
#include "rate_limiter.hpp"
namespace big
{
	class player final
	{
		friend class player_service;

		CNetGamePlayer* m_net_game_player = nullptr;
		std::string m_identifier;
		bool m_is_friend;

	public:
		explicit player(CNetGamePlayer* net_game_player);
		~player() = default;

		player(const player&) = default;
		player(player&&) noexcept = default;
		player& operator=(const player&) = default;
		player& operator=(player&&) noexcept = default;

		float screen_position_x = -1.f;
		float screen_position_y = -1.f;


		[[nodiscard]] const char* get_name() const;
		[[nodiscard]] rage::rlGamerInfo* get_net_data() const;
		[[nodiscard]] CNetGamePlayer* get_net_game_player() const;
		[[nodiscard]] CPed* get_ped() const;
		[[nodiscard]] CPlayerInfo* get_player_info() const;
		[[nodiscard]] class rage::snPlayer* get_session_player();
		[[nodiscard]] class rage::snPeer* get_session_peer();

		[[nodiscard]] uint8_t id() const;

		[[nodiscard]] bool is_friend() const;
		[[nodiscard]] bool is_host() const;
		[[nodiscard]] bool is_valid() const;

		bool never_wanted = false;

		std::chrono::system_clock::time_point m_last_transition_msg_sent{};
		int m_num_failed_transition_attempts = 0;

		bool is_modder = false;

		rate_limiter m_host_migration_rate_limit{ 1s, 20 };
		rate_limiter m_play_sound_rate_limit{ 1s, 10 };


	protected:
		bool equals(const CNetGamePlayer* net_game_player) const;

		[[nodiscard]] std::string to_lowercase_identifier() const;

	};
}