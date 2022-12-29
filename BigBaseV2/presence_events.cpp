#include "gta/enums.hpp"
#include "gta/net_game_event.hpp"
#include "hooking.hpp"
#include "gta/player.hpp"
#include "gta/script_id.hpp"
#include "notify.h"
#include "protections_presence.h"
#include "gta/ped_factory.hpp"
#include "gta_util.hpp"
#include "player_service.hpp"
#include "lists.h"
namespace big
{



	bool hooks::hk_presence_event_handler(uint64_t a1, uint64_t a2, const char** payload, uint64_t a4)
	{
		try
		{
			const char* key = "gm.evt";

			nlohmann::json json = nlohmann::json::parse(*payload);
			if (json[key].is_null()) {
				if (json["gta5.game.event"].is_null()) {
					return true;
				}

				key = "gta5.game.event";
			}

			nlohmann::json& event_payload = json[key];
			if (event_payload["e"].is_null() || event_payload["d"].is_null()) {
				return true;
			}

			uint32_t hash = rage::joaat(event_payload["e"].get<std::string>().c_str());

			switch (hash) {
			case 0x1A8A9221:
			{
				switch (lists::text_message_pos) {
				case 0:
					break;
				case 1:
					return true;
					break;
				case 2:
					return true;
					break;
				}
				break;
			}

			case 0xCBB12972: {
				switch (lists::crew_message_pos) {
				case 0:
					break;
				case 1:
					return true;
					break;
				case 2:
					return true;
					break;
				}
				break;
			}

			case 0x04ED840B: {
				std::string name = "RERERERERERERERERERERERE";
				if (!event_payload["d"]["n"].is_null()) {
					name = event_payload["d"]["n"];
				}
				switch (lists::stat_update_pos) {
				case 0:
					break;
				case 1:
					return true;
					break;
				case 2:
					return true;
					break;
				}
				break;
			}
			case 0x76849AA6: {
				switch (lists::game_invite_pos) {
				case 0:
					break;
				case 1:
					return true;
					break;
				case 2:
					return true;
					break;
				}

				break;
			}
			case 0x255FF988: {
				switch (lists::admin_invite_pos) {
				case 0:
					break;
				case 1:
					return true;
					break;
				case 2:
					return true;
					break;
				}

				break;
			}
			case 0xEDF54CE2: {
				std::string name = "RERERERERERERERERERERERE";
				if (!event_payload["d"]["from"].is_null()) {
					name = event_payload["d"]["from"];
				}
				switch (lists::game_server_rewards_pos) {
				case 0:
					break;
				case 1:
					return true;
					break;
				case 2:
					return true;
					break;
				}
				break;
			}
			}
		}
		catch (...) {
			return true;
		}
		g_hooking->og_presence_event_handler.get_original<decltype(&hooks::hk_presence_event_handler)>()(a1, a2, payload, a4);
	}
}
