#include "common.hpp"
#include "logger.hpp"
#include "pointers.hpp"
#include "memory/all.hpp"
#include "../xorstr.h"
#include "hooking.hpp"
namespace big
{
	
	pointers::pointers()
	{
		memory::pattern_batch batch;
		
		

		batch.add(XOR("GS"), XOR("83 3D ? ? ? ? ? 75 17 8B 43 20"), [this](memory::handle ptr)
		{
			m_game_state = ptr.add(2).rip().as<eGameState*>();
		});

		batch.add(XOR("IST"), XOR("40 38 35 ? ? ? ? 75 0E 4C 8B C3 49 8B D7 49 8B CE"), [this](memory::handle ptr)
		{
			m_is_session_started = ptr.from_instruction().as<bool*>();
		});

		batch.add(XOR("PF"), XOR("48 8B 05 ? ? ? ? 48 8B 48 08 48 85 C9 74 52 8B 81"), [this](memory::handle ptr)
		{
			m_ped_factory = ptr.from_instruction().as<CPedFactory**>();
		});

		batch.add(XOR("MWL"), XOR("8B 43 6C 89 05"), [this](memory::handle ptr)
			{
				m_max_wanted_level = memory::byte_patch::make(ptr.add(5).rip().as<uint32_t*>(), 0).get();
				m_max_wanted_level_2 = memory::byte_patch::make(ptr.add(14).rip().as<uint32_t*>(), 0).get();
			});

		batch.add(XOR("NPM"), XOR("48 8B 0D ? ? ? ? 8A D3 48 8B 01 FF 50 ? 4C 8B 07 48 8B CF"), [this](memory::handle ptr)
		{
			m_network_player_mgr = ptr.from_instruction().as<CNetworkPlayerMgr**>();
		});
		batch.add(XOR("GLT"), XOR("75 ? E8 ? ? ? ? 8B 0D ? ? ? ? 65 48 8B 04 25 ? ? ? ? BA ? ? ? ? 48 8B 04 C8 8B 0C 02 D1 E9"), [this](memory::handle ptr)
			{
				m_get_label_text = ptr.sub(19).as<PVOID>();
			});
		batch.add(XOR("NH"), XOR("48 8D 0D ? ? ? ? 48 8B 14 FA E8 ? ? ? ? 48 85 C0 75 0A"), [this](memory::handle ptr)
			{
				m_native_registration_table = ptr.from_instruction().as<rage::scrNativeRegistrationTable*>();
				m_get_native_handler = ptr.add(12).rip().as<functions::get_native_handler_t>();
			});

		batch.add(XOR("FV"), XOR("83 79 18 00 48 8B D1 74 4A FF 4A 18 48 63 4A 18 48 8D 41 04 48 8B 4C CA"), [this](memory::handle ptr)
		{
			m_fix_vectors = ptr.as<functions::fix_vectors_t>();
		});

		batch.add(XOR("ST"), XOR("45 33 F6 8B E9 85 C9 B8"), [this](memory::handle ptr)
			{
				m_script_threads = ptr.sub(4).rip().sub(8).as<decltype(m_script_threads)>();
				m_run_script_threads = ptr.sub(0x1F).as<functions::run_script_threads_t>();
			});

		batch.add(XOR("SP"), XOR("48 8B 1D ? ? ? ? 41 83 F8 FF"), [this](memory::handle ptr)
			{
				m_script_program_table = ptr.from_instruction().as<decltype(m_script_program_table)>();
			});

		batch.add(XOR("SG"), XOR("48 8D 15 ? ? ? ? 4C 8B C0 E8 ? ? ? ? 48 85 FF 48 89 1D"), [this](memory::handle ptr)
		{
			m_script_globals = ptr.from_instruction().as<std::int64_t**>();
		});

		batch.add(XOR("CGSHM"), XOR("48 8B 0D ? ? ? ? 4C 8B CE E8 ? ? ? ? 48 85 C0 74 05 40 32 FF"), [this](memory::handle ptr)
			{
				m_script_handler_mgr = ptr.from_instruction().as<CGameScriptHandlerMgr**>();
			});

		batch.add(XOR("SC"), XOR("48 8B 0D ? ? ? ? 48 8B 01 44 8D 43 01 33 D2 FF 50 40 8B C8"), [this](memory::handle ptr)
			{
				m_swapchain = ptr.from_instruction().as<IDXGISwapChain**>();
			});

		batch.add(XOR("MSB"), XOR("48 8B C8 FF 52 30 84 C0 74 05 48"), [this](memory::handle ptr)
		{
			m_model_spawn_bypass = ptr.add(8).as<PVOID>();
		});

		batch.add(XOR("NR"), XOR("FF E3"), [this](memory::handle ptr)
		{
			m_native_return = ptr.as<PVOID>();
		});
		batch.add(XOR("RF"), XOR("C3 48 89 5C 24 ? 48 89 6C 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC 50"), [this](memory::handle ptr)
			{
				m_register_file = ptr.add(1).as<decltype(m_register_file)>();
			});
		batch.add(XOR("3DPED"), XOR("4C 8B 15 ? ? ? ? F3 0F 11 45 ? F3 0F 10 05 ? ? ? ? BF ? ? ? ? BB ? ? ? ? 41 BE ? ? ? ? F3 0F 11"), [this](memory::handle ptr)
			{
				ui_3d_draw_manager = ptr.from_instruction().as<decltype(ui_3d_draw_manager)>();
			});
		batch.add(XOR("PSPTM"), XOR("40 53 48 83 EC 20 8B 02 48 8D 54 24 38 48 8B D9 89 44 24 38 E8 ? ? ? ? 48 8B C8"), [this](memory::handle ptr)
			{
				push_scene_preset_manager = ptr.as<decltype(push_scene_preset_manager)>();
			});
		batch.add(XOR("AETS"), XOR("4C 8B DC 48 83 EC 58 8B"), [this](memory::handle ptr)
			{
				add_element_to_scene = ptr.as<decltype(add_element_to_scene)>();
			});
		batch.add(XOR("SCEL"), XOR("48 8B C4 48 89 58 10 48 89 70 18 57 48 83 EC 30 48 83 B9"), [this](memory::handle ptr)
			{
				set_scene_element_lighting = ptr.as<decltype(set_scene_element_lighting)>();
			});
		batch.add(XOR("GCP"), XOR("0F B7 81 10 08 00 00"), [this](memory::handle ptr)
			{
				get_scene_preset = ptr.as<decltype(get_scene_preset)>();
			});
		batch.add(XOR("WP"), XOR("48 8B 05 ? ? ? ? 45 ? ? ? ? 48 8B 48 08 48 85 C9 74 07"), [this](memory::handle ptr)
			{
				m_WorldPtr = ptr.from_instruction().as<uint64_t>();
			});
		/*batch.add(XOR("RCOEP"), XOR("48 89 5C 24 ? 57 48 83 EC 20 8B D9 E8 ? ? ? ? ? ? ? ? 8B CB"), [this](memory::handle ptr)
			{
				memory::byte_patch::make(ptr.add(0x13).as<std::uint16_t*>(), 0x9090)->apply();
			});*/
		batch.add(XOR("GNGP"), XOR("48 83 EC ? 33 C0 38 05 ? ? ? ? 74 ? 83 F9"), [this](memory::handle ptr)
			{
				m_net_game_player = ptr.as<decltype(m_net_game_player)>();
			});
		batch.add(XOR("TSE"), XOR("45 8B F0 41 8B F9 48 8B EA"), [this](memory::handle ptr)
			{
				m_trigger_script_event = ptr.sub(0x1C).as<decltype(m_trigger_script_event)>();
			});
		batch.add(XOR("RI"), XOR("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 49 8B F0 8B EA 8B F9 E8"), [this](memory::handle ptr)
			{
				m_remote_increment = ptr.as<decltype(m_remote_increment)>();
			});
		batch.add(XOR("SSMR"), XOR("40 8A 2D ? ? ? ? 48 83 64 24 40 00"), [this](memory::handle ptr)
			{
				should_sync_money_rewards = ptr.from_instruction().as<bool*>();
			});
		batch.add(XOR("RD"), XOR("40 53 48 83 EC 20 0F B7 D9 48 8B 0D ? ? ? ? B2 01 E8 ? ? ? ? 48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B C8 33 C0 48 85 C9 74 08 0F B7 D3 E8 ? ? ? ? 48 8B 0D"), [this](memory::handle ptr)
			{
				m_ragdoll = ptr.as<decltype(m_ragdoll)>();
			});
		batch.add("WMSB", "48 85 C0 0F 84 ? ? ? ? 8B 48 50", [this](memory::handle ptr)
			{
				m_world_model_spawn_bypass = ptr.as<PVOID>();
			});
		batch.add(XOR("BE"), XOR("0F 85 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 48 08 E8"), [this](memory::handle ptr)
			{
				m_blame_explode = ptr.as<decltype(m_blame_explode)>();
			});
		batch.add(XOR("GPR"), XOR("48 8B C8 33 C0 48 85 C9 74 0A 44 8B C3 8B D7 E8"), [this](memory::handle ptr)
			{
				m_give_pickup_rewards = ptr.sub(0x28).as<decltype(m_give_pickup_rewards)>();
			});
		batch.add(XOR("SNITL"), XOR("33 DB 48 83 C1 68 45 8B F0"), [this](memory::handle ptr)
			{
				m_send_net_info_to_lobby = ptr.sub(0x26).as<decltype(m_send_net_info_to_lobby)>();
			});
		batch.add(XOR("CNOM"), XOR("48 8B 0D ? ? ? ? 45 33 C0 E8 ? ? ? ? 33 FF 4C 8B F0"), [this](memory::handle ptr)
			{
				m_network_object_mgr = ptr.from_instruction().as<CNetworkObjectMgr**>();
			});
		batch.add(XOR("GTS"), XOR("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 8B FA 85 D2 75 2A 8B 15"), [this](memory::handle ptr)
			{
				m_gta_thread_start = ptr.as<PVOID>();
			});
		batch.add(XOR("TK"), XOR("48 89 5C 24 ? 57 48 83 EC 20 48 83 B9 ? ? ? ? ? 48 8B D9 74 14"), [this](memory::handle ptr)
			{
				m_gta_thread_kill = ptr.as<PVOID>();
			});
		batch.add(XOR("NW"), XOR("48 8B 0D ? ? ? ? 48 8B D7 E8 ? ? ? ? 84 C0 75 17 48 8B 0D ? ? ? ? 48 8B D7"), [this](memory::handle ptr)
			{
				m_network = ptr.from_instruction().as<Network**>();
			});
		batch.add(XOR("SGGSBGH"), XOR("E8 ? ? ? ? 84 C0 0F 84 ? ? ? ? 8B 05 ? ? ? ? 48 8D 4C 24"), [this](memory::handle ptr)
			{
				m_start_get_session_by_gamer_handle = ptr.call().as<functions::start_get_session_by_gamer_handle>();
			});
		batch.add(XOR("JGSBI"), XOR("E8 ? ? ? ? 0F B6 CB 84 C0 41 0F 44 CD"), [this](memory::handle ptr)
			{
				m_join_session_by_info = ptr.call().as<functions::join_session_by_info>();
			});
		batch.add(XOR("FR"), XOR("3B 0D ? ? ? ? 73 17"), [this](memory::handle ptr)
			{
				m_friend_registry = ptr.add(2).rip().as<FriendRegistry*>();
			});
		batch.add("API", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC 20 41 8A E8", [this](memory::handle ptr)
			{
				m_assign_physical_index = ptr.as<PVOID>();
			});
		batch.add("NPMI", "41 56 48 83 EC ? 48 8B F1 B9 ? ? ? ? 49 8B F9 41 8B E8 4C 8B F2 E8", [this](memory::handle ptr)
			{
				m_network_player_mgr_init = ptr.sub(0x13).as<decltype(m_network_player_mgr_init)>();
			});

		batch.add("NPMSD", "48 8D 9F ? ? ? ? EB ? 48 8B 13 48 85 D2 74 ? 48 8B CB E8 ? ? ? ? 48 83 7B ? ? 75 ? 48 8D 9F", [this](memory::handle ptr)
			{
				m_network_player_mgr_shutdown = ptr.sub(0x1A).as<decltype(m_network_player_mgr_shutdown)>();
			});
		
		batch.add(XOR("SGSBGH"), XOR("E8 ? ? ? ? 84 C0 0F 84 F6 FE FF FF"), [this](memory::handle ptr)
			{
				m_start_matchmaking_find_sessions = ptr.call().as<functions::start_matchmaking_find_sessions>();
			});
		batch.add(XOR("PMFR"), XOR("48 89 5C 24 08 48 89 74 24 10 57 48 81 EC 90 00 00 00 41"), [this](memory::handle ptr)
			{
				m_process_matchmaking_find_response = ptr.as<PVOID>();
			});
		batch.add(XOR("SPDM"), ("48 89 5C 24 08 48 89 74 24 10 48 89 7C 24 18 41 56 48 83 EC 20 BF 01 00 00 00"), [this](memory::handle ptr)
			{
				m_serialize_player_data_msg = ptr.as<PVOID>();
			});
		batch.add(XOR("SPDM"), "E8 ? ? ? ? 84 C0 0F 84 99 00 00 00 49 8D 8F 78 0D 00 00", [this](memory::handle ptr)
			{
				m_serialize_join_request_message = ptr.call().as<PVOID>();
			});
		batch.add(XOR("INT"), XOR("8B CB E8 ? ? ? ? 8B 43 70 ? 03 C4 A9 00 C0 FF FF"), [this](memory::handle ptr)
			{
				m_init_native_tables = ptr.from_instruction().as<PVOID>();
			});
		batch.add(XOR("VM"), XOR("E8 ? ? ? ? 48 85 FF 48 89 1D"), [this](memory::handle ptr)
			{
				m_script_vm = ptr.call().as<PVOID>();
			});
		batch.add(XOR("GU"), XOR("E8 ? ? ? ? 84 C0 74 0C 48 8B 44 24 ? 48 89 03"), [this](memory::handle ptr)
			{
				m_generate_uuid = ptr.call().as<functions::generate_uuid>();
			});
		batch.add(XOR("HT"), XOR("48 8B 05 ? ? ? ? 48 83 F8 FF"), [this](memory::handle ptr)
			{
				m_host_token = ptr.from_instruction().as<std::uint64_t*>();
			});
		batch.add(XOR("REH"), XOR("66 41 83 F9 ? 0F 83"), [this](memory::handle ptr)
			{
				m_received_event = ptr.as<decltype(m_received_event)>();
			});
		batch.add(XOR("SEA"), XOR("48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 80 7A"), [this](memory::handle ptr)
			{
				m_send_event_ack = ptr.sub(5).as<decltype(m_send_event_ack)>();
			});
		batch.add(XOR("RBWD"), XOR("48 89 74 24 ? 57 48 83 EC 20 48 8B D9 33 C9 41 8B F0 8A"), [this](memory::handle ptr)
			{
				m_read_bitbuf_dword = ptr.sub(5).as<decltype(m_read_bitbuf_dword)>();
			});
		batch.add(XOR("RBA"), XOR("48 89 5C 24 ? 57 48 83 EC 30 41 8B F8 4C"), [this](memory::handle ptr)
			{
				m_read_bitbuf_array = ptr.as<decltype(m_read_bitbuf_array)>();
			});
		batch.add(XOR("RBS"), XOR("E8 ? ? ? ? 48 8D 4F 3C"), [this](memory::handle ptr)
			{
				m_read_bitbuf_string = ptr.call().as<decltype(m_read_bitbuf_string)>();
			});
		batch.add(XOR("RBB"), XOR("E8 ? ? ? ? 84 C0 74 2D 48 8D 57 20"), [this](memory::handle ptr)
			{
				m_read_bitbuf_bool = ptr.call().as<decltype(m_read_bitbuf_bool)>();
			});
		batch.add(XOR("WBD"), XOR("48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 48 83 EC 20 8B EA BF 01"), [this](memory::handle ptr)
			{
				m_write_bitbuf_dword = ptr.as<decltype(m_write_bitbuf_dword)>();
			});
		batch.add(XOR("WBQ"), XOR("48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC 20 41 8B F0 48 8B EA 48 8B D9 41 83 F8 20"), [this](memory::handle ptr)
			{
				m_write_bitbuf_qword = ptr.as<decltype(m_write_bitbuf_qword)>();
			});
		batch.add(XOR("WBI64"), XOR("E8 ? ? ? ? 8A 53 39 48 8B CF"), [this](memory::handle ptr)
			{
				m_write_bitbuf_int64 = ptr.call().as<decltype(m_write_bitbuf_int64)>();
			});
		batch.add(XOR("WBI32"), XOR("E8 ? ? ? ? 8A 53 74"), [this](memory::handle ptr)
			{
				m_write_bitbuf_int32 = ptr.call().as<decltype(m_write_bitbuf_int32)>();
			});
		batch.add(XOR("WBB"), XOR("E8 ? ? ? ? 8A 57 39"), [this](memory::handle ptr)
			{
				m_write_bitbuf_bool = ptr.call().as<decltype(m_write_bitbuf_bool)>();
			});
		batch.add(XOR("WBA"), XOR("E8 ? ? ? ? 01 7E 08"), [this](memory::handle ptr)
			{
				m_write_bitbuf_array = ptr.call().as<decltype(m_write_bitbuf_array)>();
			});
		batch.add(XOR("RCS"), "4C 8B FA 41 0F B7 D1", [this](memory::handle ptr)
			{
				m_received_clone_sync = ptr.sub(0x1D).as<decltype(m_received_clone_sync)>();
			});
		batch.add(XOR("RCC"), XOR("48 8B C4 66 44 89 48"), [this](memory::handle ptr)
			{
				m_received_clone_create = ptr.as<PVOID>();
			});
		batch.add(XOR("RCR"), XOR("48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 54 41 56 41 57 48 83 EC 50 4C 8B F2 4D 8B E0 48"), [this](memory::handle ptr)
			{
				m_received_clone_remove = ptr.as<PVOID>();
			});
		batch.add(XOR("SCAD"), XOR("E8 ? ? ? ? 84 C0 0F 84 AF 01 00 00 48 8B 03"), [this](memory::handle ptr)
			{
				m_sync_can_apply_data = ptr.call().as<PVOID>();
			});
		batch.add(XOR("GSTFT"), XOR("0F B7 CA 83 F9 07"), [this](memory::handle ptr)
			{
				m_get_sync_tree_for_type = ptr.as<decltype(m_get_sync_tree_for_type)>();
			});
		batch.add(XOR("GNO"), XOR("E8 ? ? ? ? 0F B7 53 7C"), [this](memory::handle ptr)
			{
				m_get_net_object = ptr.call().as<decltype(m_get_net_object)>();
			});
		batch.add(XOR("GSTI"), XOR("44 0F B7 C1 4C 8D 0D "), [this](memory::handle ptr)
			{
				m_get_sync_type_info = ptr.as<decltype(m_get_sync_type_info)>();
			});
		batch.add(XOR("RBIST"), XOR("E8 ? ? ? ? 48 8B BC 24 B0 00 00 00"), [this](memory::handle ptr)
			{
				m_read_bitbuffer_into_sync_tree = ptr.call().as<functions::read_bitbuffer_into_sync_tree>();
			});
		batch.add(XOR("MHT"), ("4C 03 05 ? ? ? ? EB 03"), [this](memory::handle ptr)
			{
				m_model_table = ptr.from_instruction().as<HashTable<CBaseModelInfo*>*>();
			});
		batch.add(XOR("CC"), XOR("48 8B 1D ? ? ? ? 48 8D 4C 24 30"), [this](memory::handle ptr)
			{
				m_communications = ptr.from_instruction().as<CCommunications**>();
			});
		batch.add(XOR("NSHM"), XOR("E8 ? ? ? ? 84 C0 74 60 4C 39 77 40 74 29 48 8B 4C 24 ? 48 8B 01 FF 50 28 48 8B 4F 40 44 0F B7"), [this](memory::handle ptr)
			{
				m_new_script_host_message = ptr.call().as<uint64_t>();
			});
		batch.add(XOR("HNSHM"), XOR("48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 48 83 EC 30 48 8B 6A 10"), [this](memory::handle ptr)
			{
				m_handle_new_script_host_message = ptr.as<PVOID>();
			});
		batch.add(XOR("PGI"), XOR("48 8D 05 ? ? ? ? 48 8B FE"), [this](memory::handle ptr)
			{
				m_profile_gamer_info = ptr.from_instruction().as<rage::rlGamerInfo*>();
			});
		batch.add(XOR("PIGI"), XOR("E8 ? ? ? ? 48 8D 4D 20 48 8B D0 E8 ? ? ? ? 41 8A CF"), [this](memory::handle ptr)
			{
				m_player_info_gamer_info = ptr.call().from_instruction().as<rage::rlGamerInfo*>();
			});
		batch.add(XOR("SCS"), XOR("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 0F B7 42"), [this](memory::handle ptr)
			{
				m_send_clone_sync = ptr.as<decltype(m_send_clone_sync)>();
			});
		batch.add(XOR("QNP"), XOR("E8 ? ? ? ? 84 C0 74 4D B3 01"), [this](memory::handle ptr)
			{
				m_queue_packet = ptr.call().as<functions::queue_packet>();
			});
		batch.add(XOR("HRGC"), XOR("41 FF C6 FF C7"), [this](memory::handle ptr)
			{
				m_handle_remove_gamer_cmd = ptr.sub(0x6E).as<functions::handle_remove_gamer_cmd>();
			});
		batch.add(XOR("SRGC"), XOR("8D 42 FF 83 F8 FD 77 3D"), [this](memory::handle ptr)
			{
				m_get_connection_peer = ptr.add(23).rip().as<functions::get_connection_peer>();
				m_send_remove_gamer_cmd = ptr.add(65).rip().as<functions::send_remove_gamer_cmd>();
			});
		batch.add(XOR("WPGSDN"), XOR("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC 30 0F B7 81"), [this](memory::handle ptr)
			{
				m_write_player_game_state_data_node = ptr.as<functions::write_player_game_state_data_node>();
			});
		batch.add(XOR("WPGDN"), XOR("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 81 C1 ? ? ? ? 48 8B DA E8"), [this](memory::handle ptr)
			{
				m_write_player_gamer_data_node = ptr.as<PVOID>();
			});
		batch.add(XOR("WPMDN"), XOR("48 89 5C 24 18 55 56 57 48 83 EC 30 48 8B 02 48 8D 99 C0 00 00 00"), [this](memory::handle ptr)
			{
				m_write_ped_movement_data_node = ptr.as<PVOID>();
			});
		
		batch.add(XOR("OCDN"), XOR("48 89 5C 24 10 55 56 57 41 54 41 55 41 56 41 57 48 8B EC 48 83 EC 50 F7 81 4C 01 00 00 FD FF FF FF"), [this](memory::handle ptr)
			{
				m_object_creation_data_node = ptr.as<PVOID>();
			});
		batch.add(XOR("PCDN"), XOR("48 89 5C 24 10 55 48 8B EC 48 83 EC 20 8B 45 10 8B 89 C0 00 00 00"), [this](memory::handle ptr)
			{
				m_player_creation_data_node = ptr.as<PVOID>();
			});
		batch.add(XOR("PCDN2"), XOR("48 89 5C 24 10 55 48 8B EC 48 83 EC 20 8B 45 10 8B 89 C4 00 00 00"), [this](memory::handle ptr)
			{
				m_ped_creation_data_node = ptr.as<PVOID>();
			});
		batch.add(XOR("PUCDN"), XOR("48 8B EC 48 83 EC 20 80 B9 C0 00 00 00 00"), [this](memory::handle ptr)
			{
				m_pickup_creation_data_node = ptr.as<PVOID>();
			});
		batch.add(XOR("VCDN"), XOR("48 89 5C 24 ? 55 48 8B EC 48 83 EC 20 8B 45 10 8B 89 C8 00 00 00"), [this](memory::handle ptr)
			{
				m_vehicle_creation_data_node = ptr.as<PVOID>();
			});
		batch.add(XOR("AVCDN"), XOR("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC 40 48 8B B1"), [this](memory::handle ptr)
			{
				m_vehicle_control_data_node = ptr.as<PVOID>();
			});
		batch.add(XOR("APADN"), XOR("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B B1"), [this](memory::handle ptr)
			{
				m_player_appearance_data_node = ptr.as<PVOID>();
			});
		batch.add(XOR("PADN"), XOR("40 53 55 56 57 41 54 41 56 41 57 48 83 EC 30 4C 8D B1 C0 00 00 00"), [this](memory::handle ptr)
			{
				m_ped_attach_data_node = ptr.as<PVOID>();
			});
		batch.add(XOR("PADN2"), XOR("40 55 53 56 57 41 54 41 55 41 56 41 57 48 8B EC 48 83 EC 58 48 8B 02 48 8D 99 C0 00 00 00"), [this](memory::handle ptr)
			{
				m_physical_attach_data_node = ptr.as<PVOID>();
			});
		batch.add(XOR("TGSDN"), XOR("48 89 5C 24 ? 57 48 83 EC 30 48 8B 02 48 8B FA"), [this](memory::handle ptr)
			{
				m_train_game_state_data_node = ptr.as<PVOID>();
			});
		batch.add(XOR("SDEGSDN"), XOR("48 89 5C 24 18 55 56 57 41 56 41 57 48 83 EC 20 48 8B 02 48 8D 99"), [this](memory::handle ptr)
			{
				m_dynamic_entity_game_state_data_node = ptr.as<PVOID>();
			});
		batch.add(XOR("SPIDN"), XOR("48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 54 41 56 41 57 48 83 EC 20 48 8B 02 48 8B F1 48 8B CA 48 8B FA FF 90"), [this](memory::handle ptr)
			{
				m_ped_inventory_data_node = ptr.as<PVOID>();
			});
		batch.add(XOR("SVGDN"), XOR("48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 41 56 41 57 48 83 EC 30 48 8B 02 48 8D"), [this](memory::handle ptr)
			{
				m_vehicle_gadget_data_node = ptr.as<PVOID>();
			});
		batch.add(XOR("STOPVT"), "40 55 53 57 41 56 48 8B EC 48 83 EC 68", [this](memory::handle ptr)
			{
				m_serialize_take_off_ped_variation_task = ptr.as<PVOID>();
			});
		batch.add(XOR("GVGAS"), XOR("40 53 48 83 EC 40 33 DB E8"), [this](memory::handle ptr)
			{
				m_get_vehicle_gadget_array_size = ptr.as<functions::get_vehicle_gadget_array_size>();
			});
		batch.add(XOR("IEX"), XOR("E8 ? ? ? ? 8B 9C 24 B8 00 00 00 4C 8B AC 24 A8 00 00 00"), [this](memory::handle ptr)
			{
				indecent_exposure_add = ptr.call().as<PVOID>();
			});
		batch.add(XOR("MDCP"), XOR("48 8B C4 48 89 58 08 48 89 70 10 48 89 78 18 4C 89 68 20 55 41 56 41 57 48 8B EC 48 83 EC 40 4C 8D B1 A0 12 00 00"), [this](memory::handle ptr)
			{
				m_meltdown_patch = ptr.as<PVOID>();
			});
		batch.add(XOR("IMCP"), XOR("E8 ? ? ? ? 40 88 7C 24 ? 49 89 9C 24"), [this](memory::handle ptr)
			{
				m_invalid_mods_crash_detour = ptr.call().as<PVOID>();
			});
		batch.add(XOR("RNM"), XOR("48 83 EC 20 4C 8B 71 50 33 ED"), [this](memory::handle ptr)
			{
				m_receive_net_message = ptr.sub(0x19).as<PVOID>();
			});
		batch.add(XOR("GNED"), XOR("53 43 52 49 50 54 5F 4E 45 54 57 4F 52 4B"), [this](memory::handle ptr)
			{
				m_get_network_event_data = *ptr.sub(0x38).as<PVOID*>();
			});
		/*batch.add(XOR("SCI"), XOR("48 8B D3 48 8D 4C 24 ? 48 69 D2"), [this](memory::handle ptr)
			{
				m_scinfo = ptr.sub(4).rip().as<ScInfo*>();
			});*/
		batch.add(XOR("PCC"), XOR("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 8B F9 48 8B CA 49 8B E9"), [this](memory::handle ptr)
			{
				m_pack_clone_create = ptr.as<functions::clone_pack_create_t>();
			});

		batch.add(XOR("TACP"), XOR("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC 20 48 8B D9 48 8B 49 30 45 33"), [this](memory::handle ptr)
			{
				m_trailer_attach_crash_patch = ptr.as<PVOID>();
			});

		batch.add(XOR("TAACP"), XOR("48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 57 48 81 EC ? ? ? ? 48 8B D9 48 8B 89 ? ? ? ? 0F 29 70 E8 0F 29 78 D8 48 8B F2 E8"), [this](memory::handle ptr)
			{
				m_trailer_attach_audio_crash_patch = ptr.as<PVOID>();
			});

		batch.add(XOR("ISPC"), XOR("48 8B 01 4C 8B C1 48 3B D0 75 21 48 8B 40 18 48 89 01 33 C0 48 89 42 18 48 8B 09 48 85 C9 74 06 48 89 41 20 EB 4E 49"), [this](memory::handle ptr)
			{
				m_invalid_script_crash_patch = ptr.as<PVOID>();
			});

		batch.add(XOR("ISPC2"), XOR("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 8B F9 48 83 C1 30 41 8A F1 48 8B 19 EB 10"), [this](memory::handle ptr)
			{
				m_invalid_script_crash_patch2 = ptr.as<PVOID>();
			});

		batch.add(XOR("ISCP3"), XOR("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 80 3D ? ? ? ? ? 41 8B D8 8B F2 48 8B F9 74 2F E8"), [this](memory::handle ptr)
			{
				m_invalid_sub_crash_patch = ptr.as<PVOID>();
			});

		batch.add(XOR("ITECP"), XOR("48 8B C4 48 89 58 08 48 89 70 10 48 89 78 18 55 48 8D 68 A1 48 81 EC A0 00 00 00 0F 28 91 90 00 00 00"), [this](memory::handle ptr)
			{
				m_invalid_track_event_crash_patch = ptr.as<PVOID>();
			});
		batch.add(XOR("IACP"), XOR("40 53 48 83 EC 20 48 8B D9 48 8B 49 38 48 8B 01"), [this](memory::handle ptr)
			{
				m_invalid_attachment_crash_patch = ptr.as<PVOID>();
			});
		batch.add(XOR("IPCP"), 
			XOR("48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC 20 48 8B 59 40 4C 8B F2 48 8B F1 48 85 DB 74 22 48 8B 02 48 8B CA FF 50 48 4C 8D 05 ? ? ? ? 48 8D 15 ? ? ? ? 4C 8B C8 48 8B CB E8 ? ? ? ? 44 0F B7 46 ? 33 DB 33 C9 49 63 D0 45 85 C0 7E 18 48 8B 46 50 48 8B 18 48 85 DB 75 0C 48 FF C1 48 83 C0 08 48 3B CA 7C EC 33 FF 33 C9 45 85 C0 7E 69 48 8B 46 50 48 8B 18 48 85 DB 75 10 48 FF C1 FF C7 48 83 C0 08 49 3B C8 7C EA EB 4D 48 8B 4B 08 48 85 C9 74 12 48 8B 49 48 48 85 C9 74 09 48 8B 01 49 8B D6 FF 50 10"),
			[this](memory::handle ptr)
			{
				m_invalid_player_crash_patch = ptr.as<PVOID>();
			});
		batch.add(XOR("IMCP2"), XOR("48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 57 48 83 EC 30 48 8B 99 08 04 00 00"), [this](memory::handle ptr)
			{
				m_invalid_melee_crash_patch = ptr.as<PVOID>();
			});
		batch.add(XOR("IDECP"), XOR("48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 8B 81 F8 02 00 00"), [this](memory::handle ptr)
			{
				m_invalid_dynamic_entity_crash_patch = ptr.as<PVOID>();
			});
		
		batch.add(XOR("WBGH"), XOR("4C 8B DC 49 89 5B 08 57 48 83 EC 30 48 8B F9"), [this](memory::handle ptr)
			{
				m_write_bitbuffer_gamer_handle = ptr.as<PVOID>();
			});
		batch.add(XOR("RBGH"), XOR("48 8B C4 48 89 58 10 48 89 68 18 48 89 70 20 57 48 83 EC 30 C6"), [this](memory::handle ptr)
			{
				m_read_bitbuffer_gamer_handle = ptr.as<PVOID>();
			});

		batch.add(XOR("CW"), XOR("74 44 E8 ? ? ? ? 80 65 2B F8 48 8D 0D ? ? ? ? 48 89 4D 17 48 89 7D 1F 89 7D 27 C7 45"), [](memory::handle ptr)
			{
				memory::byte_patch::make(ptr.as<uint8_t*>(), 0xEB)->apply();
			});
		batch.add(XOR("CSH"), XOR("48 8D 05 ? ? ? ? 4C 8D 0D ? ? ? ? 41 83 C8 FF 48 89 03 89 53 70 88 53 74 4C 89 4B 68 48 89 93"), [this](memory::handle ptr)
			{
				m_create_script_handler = *(ptr.from_instruction().as<std::uint64_t**>() + 8);
			});
		batch.add("RS", "48 8B 1D ? ? ? ? 33 F6 BD C3 9E 26 00", [this](memory::handle ptr)
			{
				m_security = ptr.add(3).rip().as<rage::atSingleton<rage::RageSecurity>*>();
			});
		batch.add(XOR("FOM"), XOR("0F 2F 35 ? ? ? ? 0F 86 ? ? ? ? 0F 28 05 ? ? ? ? 48 8D 4D B0 41 0F 28 D9 48 8B D3 0F 28 D7 0F 29 45 A0"), [this](memory::handle ptr)
			{
				m_fog_on_map = ptr.as<uint64_t>();
			});

		batch.add(XOR("WQ"), XOR("4C 8D 0D ? ? ? ? 48 0F 45 D1 48 8B 0D ? ? ? ? 48 83 64 24 ? ? 4C 8D 05 ? ? ? ? E8 ? ? ? ? 84 C0 0F 85"), [this](memory::handle ptr)
			{
				m_water_quad = ptr.from_instruction().as<uintptr_t>();
			});
		batch.add(XOR("WQC"), XOR("48 8D 0D ? ? ? ? 66 44 89 05 ? ? ? ? E8 ? ? ? ? 0F B7 05 ? ? ? ?"), [this](memory::handle ptr)
			{
				m_water_quad_count = ptr.add(8).as<uintptr_t>();
			});
		batch.add(XOR("VS"), XOR("48 8D 0D ? ? ? ? 0F 29 44 24 ? E8 ? ? ? ? 0F 28 05 ? ? ? ? 0F 59 44 24 ? F3 48 0F 2C C0 0F C6 C0 55"), [this](memory::handle ptr)
			{
				m_visual_settings = ptr.from_instruction().as<CVisualVfx*>();
			});
	
		batch.add(XOR("EAP"), XOR("0F 29 62 20"), [this](memory::handle ptr)
			{
				m_east_azimuth_patch = ptr.as<decltype(m_east_azimuth_patch)>();
			});
		batch.add(XOR("WAP"), XOR("0F 29 62 50 8B 81 9C 03 00 00"), [this](memory::handle ptr)
			{
				m_west_azimuth_patch = ptr.as<decltype(m_west_azimuth_patch)>();
			});
		batch.add(XOR("ATP"), XOR("0F 29 A2 80 00 00 00"), [this](memory::handle ptr)
			{
				m_azimuth_transition_patch = ptr.as<decltype(m_azimuth_transition_patch)>();
			});
		batch.add(XOR("ZP"), XOR("0F 29 A2 B0 00 00 00 8B 81 58 03 00 00"), [this](memory::handle ptr)
			{
				m_zenith_patch = ptr.as<decltype(m_zenith_patch)>();
			});
		batch.add(XOR("ZTP"), XOR("0F 29 A2 E0 00 00 00"), [this](memory::handle ptr)
			{
				m_zenith_transition_patch = ptr.as<decltype(m_zenith_transition_patch)>();
			});
		batch.add(XOR("CMP"), XOR("0F 29 8B 60 03 00 00"), [this](memory::handle ptr)
			{
				m_cloud_mid_patch = ptr.as<decltype(m_cloud_mid_patch)>();
			});
		batch.add(XOR("CBP"), XOR("0F 29 A2 80 03 00 00"), [this](memory::handle ptr)
			{
				m_cloud_base_patch = ptr.as<decltype(m_cloud_base_patch)>();
			});
		batch.add(XOR("WVFX"), XOR("48 8D 0D ? ? ? ? 48 6B D2 ? 48 03 55"), [this](memory::handle ptr)
			{
				m_weather_fx = ptr.from_instruction().as<decltype(m_weather_fx)>();
			});
		batch.add(XOR("WD"), XOR("40 53 48 83 EC 30 0F 29 74 24 ? 48 8B D9 E8 ? ? ? ? F3 0F 10 83 ? ? ? ? F3 0F 10 35"), [this](memory::handle ptr)
			{
				m_weather_data = ptr.as<PVOID>();
			});
		batch.add(XOR("NTQVMC"), XOR("66 0F 6F 0D ? ? ? ? 66 0F 6F 05 ? ? ? ? 66 0F 66 C4"), [this](memory::handle ptr)
			{
				memory::byte_patch::make(ptr.add(4).rip().sub(32).as<uint64_t*>(), (uint64_t)&hooks::nt_query_virtual_memory)->apply();
			});
		batch.add(XOR("QD"), XOR("48 89 5C 24 ? 57 48 83 EC ? 0F B6 99"), [this](memory::handle ptr)
			{
				m_queue_dependency = ptr.as<PVOID>();
			});
		batch.add(XOR("ICF"), XOR("48 8D 0D ? ? ? ? 88 05 ? ? ? ? 48 8D 05"), [this](memory::handle ptr)
			{
				m_interval_check_func = ptr.add(3).rip().as<PVOID>();
			});


		batch.add(XOR("RPE"), XOR("E8 ? ? ? ? F6 C3 02 74 10"), [this](memory::handle ptr)
			{
				m_presence_events = ptr.call().as<decltype(m_presence_events)>();
			});

		batch.add(XOR("SCCCCCCCCCC"), XOR("48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 41 56 41 57 48 83 EC 20 48 8D 81 D4 00 00 00"), [this](memory::handle ptr)
		{
				shitter_crash = ptr.as<PVOID>();
		});

		batch.add("REEEEEEEEE", "83 89 10 03 00 00 FF 48 8D 05", [this](memory::handle ptr)
			{
				m_track_patch = ptr.as<PVOID>();
			});

		auto mem_region = memory::module("GTA5.exe");
		batch.run(mem_region);

		memory::pattern_batch sc_batch;

		// Presence Data
		sc_batch.add(XOR("PD"), XOR("48 8D 05 ? ? ? ? 48 8B F1 48 89 01 48 8D 99 90 00 00 00"), [this](memory::handle ptr)
			{
				auto presence_data_vft = ptr.from_instruction().as<PVOID*>();
				m_update_presence_attribute_int = presence_data_vft[1];
				m_update_presence_attribute_string = presence_data_vft[3];
			});

		auto sc_module = memory::module("socialclub.dll");

		sc_batch.run(sc_module);
		


		if (auto pat1 = mem_region.scan("3b 0a 0f 83 ? ? ? ? 48 ff c7"))
		{
			memory::byte_patch::make(pat1.add(2).as<uint32_t*>(), 0xc9310272)->apply();
			memory::byte_patch::make(pat1.add(6).as<uint16_t*>(), 0x9090)->apply();
		}

		if (auto pat2 = mem_region.scan("3b 0a 0f 83 ? ? ? ? 49 03 fa"))
		{
			memory::byte_patch::make(pat2.add(2).as<uint32_t*>(), 0xc9310272)->apply();
			memory::byte_patch::make(pat2.add(6).as<uint16_t*>(), 0x9090)->apply();
		}

		auto pat3 = mem_region.scan_all("3b 11 0f 83 ? ? ? ? 48 ff c7");
		for (auto& handle : pat3)
		{
			memory::byte_patch::make(handle.add(2).as<uint32_t*>(), 0xd2310272)->apply();
			memory::byte_patch::make(handle.add(6).as<uint16_t*>(), 0x9090)->apply();
		}

		auto pat4 = mem_region.scan_all("3b 11 0f 83 ? ? ? ? 49 03 fa");
		for (auto& handle : pat4)
		{
			memory::byte_patch::make(handle.add(2).as<uint32_t*>(), 0xd2310272)->apply();
			memory::byte_patch::make(handle.add(6).as<uint16_t*>(), 0x9090)->apply();
		}

		m_hwnd = FindWindowW(L"grcWindow", nullptr);
		if (!m_hwnd)
			throw std::runtime_error("Failed to find the game's window.");


		g_pointers = this;
	}

	pointers::~pointers()
	{

		memory::byte_patch::restore_all();
		g_pointers = nullptr;
	}
}
