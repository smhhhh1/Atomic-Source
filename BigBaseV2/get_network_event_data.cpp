#include "hooking.hpp"
#include "gta/net_game_event.hpp"
#include "xorstr.h"
#include "notify.h"
#include "network_notifications.h"
namespace big
{
	struct event_player_spawn {
		char _0x0000[0x18];
		char m_name[0x20];
	};
	struct event_player_collected_ambient_pickup {
		char _0x0000[0x18];
		uint32_t m_pickup_hash;
		char _0x001c[0x4];
		int m_value;
		char _0x0024[0xc];
		uint32_t m_model;
	};
	void hooks::hk_get_network_event_data(int64_t unk, rage::CEventNetwork* event)
	{
		switch (event->get_type())
		{
		case rage::eEventNetworkType::CEventNetworkRemovedFromSessionDueToComplaints:
		{
			ImGui::InsertNotification({ ImGuiToastType_None, 2600, XOR("you were desynced by an unknown player") });
			LOG(INFO) << XOR("You Were Desynced by an unknown player");
			break;
		}
		case rage::eEventNetworkType::CEventNetworkPlayerSpawn:
		{
			event_player_spawn* _event = (event_player_spawn*)event;;
			event->get_extra_information(_event, sizeof(_event));

			if (network::notifications::vars::m_vars.m_player_spawn) {
				ImGui::InsertNotification({ ImGuiToastType_None, 2600, XOR("% just spawned"), _event->m_name });
			}
			break;
		}
		case rage::eEventNetworkType::CEventNetworkPlayerCollectedAmbientPickup:
		{
			event_player_collected_ambient_pickup* _event = (event_player_collected_ambient_pickup*)event;
			event->get_extra_information(_event, sizeof(_event));
			if (network::notifications::vars::m_vars.m_pickup_processing) {
				ImGui::InsertNotification({ ImGuiToastType_None, 2600, XOR("pickup processing") });
			}
			break;
		}
		}

		return g_hooking->og_get_network_event_data.get_original<decltype(&hooks::hk_get_network_event_data)>()(unk, event);
	}
}