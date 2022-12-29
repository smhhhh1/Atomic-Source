#include "gta/enums.hpp"
#include "gta/net_game_event.hpp"
#include "hooking.hpp"
#include "gta/player.hpp"
#include "gta/script_id.hpp"
#include "notify.h"
#include "protections_network_events.h"
#include "gta/ped_factory.hpp"
#include "gta_util.hpp"
#include "player_service.hpp"
#include "lists.h"
namespace big
{
	
	static void script_id_deserialize(CGameScriptId& id, rage::datBitBuffer& buffer)
	{
		id.m_hash = buffer.Read<uint32_t>(32);
		id.m_timestamp = buffer.Read<uint32_t>(32);

		if (buffer.Read<bool>(1))
			id.m_position_hash = buffer.Read<uint32_t>(32);

		if (buffer.Read<bool>(1))
			id.m_instance_id = buffer.Read<int32_t>(8);
	}

	void hooks::hk_received_event(
		rage::netEventMgr* event_manager,
		CNetGamePlayer* source_player,
		CNetGamePlayer* target_player,
		uint16_t event_id,
		int event_index,
		int event_handled_bitset,
		int buffer_size,
		rage::datBitBuffer* buffer
	)
	{
		if (event_id > 91u)
		{
			g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

			return;
		}

		const auto event_name = *(char**)((DWORD64)event_manager + 8i64 * event_id + 243376);
		if (event_name == nullptr || source_player == nullptr || source_player->m_player_id < 0 || source_player->m_player_id >= 32)
		{
			g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
			return;
		}

		switch (static_cast<eNetworkEvents>(event_id))
		{
		case eNetworkEvents::CExplosionEvent:
		{

			if (source_player->m_player_id < 32)
			{
				uint16_t explosion_owner{};
				uint32_t explosion_flags{};
				int32_t explosion_type{};
				buffer->Seek(29);
				buffer->ReadWord(&explosion_owner, 13);
				buffer->Seek(55);
				buffer->ReadInt32(&explosion_type, 8);
				buffer->Seek(149);
				buffer->ReadDword(&explosion_flags, 32);
				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);		

				switch (lists::explosion_event_id)
				{
				case 0:
					break;
				case 1:
					LOG(INFO) << "Protections | Blocked Network Event Type: Explosion From: " << source_player->get_name();
					return;
					break;
				case 2:
					LOG(INFO) << "Protections | Blocked Network Event Type: Explosion From: " << source_player->get_name();
					ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Explosion From %s", source_player->get_name() });
					return;
					break;
				}
		
			}
			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::CScriptedGameEvent:
		{
			const auto scripted_game_event = std::make_unique<CScriptedGameEvent>();
			buffer->ReadDword(&scripted_game_event->m_args_size, 32);
			if (scripted_game_event->m_args_size - 1 <= 0x1AF)
				buffer->ReadArray(&scripted_game_event->m_args, 8 * scripted_game_event->m_args_size);

			if (hooks::scripted_game_event(scripted_game_event.get(), source_player))
			{
				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

				return;
			}
			buffer->Seek(0);

			break;
		}
		case eNetworkEvents::CNetworkPtfxEvent:
		{
			
			if (source_player->m_player_id < 32)
			{
				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
				
				
				switch (lists::ptfx_event_id)
				{
				case 0:
					break;
				case 1:
					LOG(INFO) << "Protections | Blocked Network Event Type: Ptfx From: " << source_player->get_name();
					return;
					break;
				case 2:
					LOG(INFO) << "Protections | Blocked Network Event Type: Ptfx From: " << source_player->get_name();
					ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Ptfx From %s", source_player->get_name() });
					return;
					break;
				}
			}
			buffer->Seek(0);
			break;
		
		}
		case eNetworkEvents::CRemoveWeaponEvent:
		{
		
			uint32_t hash = buffer->Read<uint32_t>(32);

			if (hash == RAGE_JOAAT("WEAPON_UNARMED"))
			{
				LOG(INFO) << "Protections | Blocked Crash Type: Weapon From: " << source_player->get_name();
				ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Weapon Crash From %s", source_player->get_name() });
				return;
			}

			if (source_player->m_player_id < 32)
			{
				switch (lists::remove_weapons_event_id)
				{
				case 0:
					break;
				case 1:
					LOG(INFO) << "Protections | Blocked Network Event Type: Remove Weapons From: " << source_player->get_name();
					return;
					break;
				case 2:
					LOG(INFO) << "Protections | Blocked Network Event Type: Remove Weapons From: " << source_player->get_name();
					ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Remove Weapons From %s", source_player->get_name() });
					return;
					break;
				}
			}

			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::CRemoveAllWeaponsEvent:
		{
			if (source_player->m_player_id < 32)
			{
				switch (lists::remove_all_weapons_event_id)
				{
				case 0:
					break;
				case 1:
					LOG(INFO) << "Protections | Blocked Network Event Type: Remove All Weapons From: " << source_player->get_name();
					return;
					break;
				case 2:
					LOG(INFO) << "Protections | Blocked Network Event Type: Remove All Weapons From: " << source_player->get_name();
					ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Remove All Weapons From %s", source_player->get_name() });
					return;
					break;
				}
			}

			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::CRagdollRequestEvent:
		{
			if (source_player->m_player_id < 32)
			{
				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

				switch (lists::ragdoll_event_id)
				{
				case 0:
					break;
				case 1:
					LOG(INFO) << "Protections | Blocked Network Event Type: Ragdoll From: " << source_player->get_name();
					return;
					break;
				case 2:
					LOG(INFO) << "Protections | Blocked Network Event Type: Ragdoll From: " << source_player->get_name();
					ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Ragdoll From %s", source_player->get_name() });
					return;
					break;
				}
			}

			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::CScriptEntityStateChangeEvent:
		{
			uint16_t entity = buffer->Read<uint16_t>(13);
			auto type = buffer->Read<ScriptEntityChangeType>(4);
			uint32_t unk = buffer->Read<uint32_t>(32);
			if (type == ScriptEntityChangeType::SettingOfTaskVehicleTempAction)
			{
				uint16_t unk2 = buffer->Read<uint16_t>(13);
				uint32_t action = buffer->Read<uint32_t>(8);

				if ((action >= 15 && action <= 18) || action == 33)
				{
					g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
					LOG(INFO) << "Protections | Blocked Crash Event Type: Script State Change From: " << source_player->get_name();
					ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Script State Change From %s", source_player->get_name() });
					return;
				}
			}
			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::CScriptWorldStateEvent:
		{
			auto type = buffer->Read<WorldStateDataType>(4);
			buffer->Read<bool>(1);
			CGameScriptId id;
			script_id_deserialize(id, *buffer);

			if (type == WorldStateDataType::Rope)
			{
				buffer->Read<int>(9); // unk
				buffer->Read<float>(19); // pos x
				buffer->Read<float>(19); // pos y
				buffer->Read<float>(19); // pos z
				buffer->Read<float>(19); // rot x
				buffer->Read<float>(19); // rot y
				buffer->Read<float>(19); // rot z
				buffer->Read<float>(16); // length
				int type = buffer->Read<int>(4);
				float initial_length = buffer->Read<float>(16);
				float min_length = buffer->Read<float>(16);

				if (type == 0 || initial_length < min_length) 
				{
					LOG(INFO) << "Protections | Blocked Crash Event Type: Rope From: " << source_player->get_name();
					ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Rope Crash From %s", source_player->get_name() });
					g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
					return;
				}
			}
			else if (type == WorldStateDataType::PopGroupOverride)
			{
				int unk = buffer->ReadSigned<int>(8);
				int unk2 = buffer->Read<int>(32);
				int unk3 = buffer->Read<int>(7);

				if (unk2 == 0 && (unk3 == 0 || unk3 == 103))
				{
					LOG(INFO) << "Protections | Blocked Crash Event Type: Group Override From: " << source_player->get_name();
					ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Group Override From %s", source_player->get_name() });
					g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
					return;
				}
			}

			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::CGiveControlEvent:
		{
			uint32_t timestamp = buffer->Read<uint32_t>(32);
			int count = buffer->Read<int>(2);
			bool unk = buffer->Read<bool>(1);

			if (count > 3)
			{
				count = 3;
			}

			for (int i = 0; i < count; i++)
			{
				int net_id = buffer->Read<int>(13);
				eNetObjType object_type = buffer->Read<eNetObjType>(4);
				int unk = buffer->Read<int>(3);

				if (object_type < eNetObjType::NET_OBJ_TYPE_AUTOMOBILE || object_type > eNetObjType::NET_OBJ_TYPE_TRAIN)
				{
					g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
					return;
				}
			}

			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::CNetworkPlaySoundEvent:
		{
			auto plyr = g_player_service->get_by_id(source_player->m_player_id);
			if (plyr->m_play_sound_rate_limit.process())
			{
				if (plyr->m_play_sound_rate_limit.exceeded_last_process())
				{
					LOG(INFO) << "Protections | Blocked Network Event Type: Sound Spam From: " << source_player->get_name();
					ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Sound Spam From %s", source_player->get_name() });
				}
				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
				return;
			}
			break;
		}
		case eNetworkEvents::CRequestControlEvent:
		{
			if (source_player->m_player_id < 32)
			{
				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

				switch (lists::request_control_event_id)
				{
				case 0:
					break;
				case 1:
					LOG(INFO) << "Protections | Blocked Network Event Type: Request Control From: " << source_player->get_name();
					return;
					break;
				case 2:
					LOG(INFO) << "Protections | Blocked Network Event Type: Request Control From: " << source_player->get_name();
					ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Request Control From %s", source_player->get_name() });
					return;
					break;
				}
			}
			buffer->Seek(0);
			break;
		}
		default:
			break;
		}

		g_hooking->og_received_event.get_original<decltype(&hooks::hk_received_event)>()(event_manager, source_player, target_player, event_id, event_index, event_handled_bitset, buffer_size, buffer);
	}
}
