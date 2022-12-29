#pragma once
#include "common.hpp"
#include "gta/fwddec.hpp"
#include "gta/enums.hpp"
#include "function_types.hpp"
#include "../FriendRegistry.hpp"
#include "../byte_patch.hpp"
#include "../HashTable.hpp"
#include "../generic_types.h"
#include "../CCommunications.h"
#include "../ScInfo.hpp"
#include "../vfx_types.h"
namespace rage
{
	template<typename T>
	class atSingleton;
	class RageSecurity;
}

namespace big
{
	class pointers
	{
	public:
		explicit pointers();
		~pointers();
	public:
		HWND m_hwnd{};

		memory::byte_patch* m_max_wanted_level;
		memory::byte_patch* m_max_wanted_level_2;

		CVisualVfx* m_visual_settings;
		ScInfo** m_scinfo;
		eGameState* m_game_state{};
		CPedFactory **m_ped_factory{};
		CNetworkPlayerMgr **m_network_player_mgr{};
		FriendRegistry* m_friend_registry{};
		Network** m_network;
		CGameScriptHandlerMgr** m_script_handler_mgr{};
		CNetworkObjectMgr** m_network_object_mgr{};
		CCommunications** m_communications{};
		HashTable<CBaseModelInfo*>* m_model_table;
		rage::scrNativeRegistrationTable* m_native_registration_table{};
		rage::atArray<GtaThread*>* m_script_threads{};
		rage::scrProgramTable* m_script_program_table{};
		rage::atSingleton<rage::RageSecurity>* m_security;
		rage::rlGamerInfo* m_profile_gamer_info{};
		rage::rlGamerInfo* m_player_info_gamer_info{};
		IDXGISwapChain** m_swapchain{};
	
		functions::get_native_handler_t m_get_native_handler{};
		functions::fix_vectors_t m_fix_vectors{};
		functions::FileRegister m_register_file;
		functions::give_pickup_rewards m_give_pickup_rewards{};
		functions::run_script_threads_t m_run_script_threads{};
		functions::get_net_game_player m_net_game_player;
		functions::trigger_script_event m_trigger_script_event;
		functions::increment_Stat m_remote_increment;
		functions::start_get_session_by_gamer_handle m_start_get_session_by_gamer_handle;
		functions::join_session_by_info m_join_session_by_info;
		functions::start_matchmaking_find_sessions m_start_matchmaking_find_sessions;
		functions::read_bitbuf_dword m_read_bitbuf_dword{};
		functions::read_bitbuf_string m_read_bitbuf_string{};
		functions::read_bitbuf_bool m_read_bitbuf_bool{};
		functions::read_bitbuf_array m_read_bitbuf_array{};
		functions::write_bitbuf_qword m_write_bitbuf_qword{};
		functions::write_bitbuf_dword m_write_bitbuf_dword{};
		functions::write_bitbuf_int64 m_write_bitbuf_int64{};
		functions::write_bitbuf_int32 m_write_bitbuf_int32{};
		functions::write_bitbuf_bool m_write_bitbuf_bool{};
		functions::write_bitbuf_array m_write_bitbuf_array{};
		functions::send_event_ack m_send_event_ack{};
		functions::generate_uuid m_generate_uuid{};
		functions::get_sync_tree_for_type m_get_sync_tree_for_type{};
		functions::get_sync_type_info m_get_sync_type_info{};
		functions::get_net_object m_get_net_object{};
		functions::get_net_object_for_player m_get_net_object_for_player{};
		functions::read_bitbuffer_into_sync_tree m_read_bitbuffer_into_sync_tree{};
		functions::queue_packet m_queue_packet;
		functions::get_connection_peer m_get_connection_peer{};
		functions::send_remove_gamer_cmd m_send_remove_gamer_cmd{};
		functions::handle_remove_gamer_cmd m_handle_remove_gamer_cmd{};
		functions::write_player_game_state_data_node m_write_player_game_state_data_node{};
		functions::get_vehicle_gadget_array_size m_get_vehicle_gadget_array_size;
		functions::clone_pack_create_t m_pack_clone_create{};
		functions::clone_pack_sync_t m_pack_clone_sync{};

		int64_t **m_script_globals{};
		uint64_t g_font_table;
		uint64_t g_font_memory_helper;
		uint64_t m_WorldPtr;
		uint64_t m_ragdoll;
		uint64_t g_global_chat_ptr;
		uint64_t g_send_global_chat_message;
		uint64_t* m_host_token{};
		uint64_t m_new_script_host_message;
		uint64_t m_fog_on_map;
		uint64_t m_weather_fx;

		uintptr_t ui_3d_draw_manager;
		uintptr_t add_element_to_scene;
		uintptr_t push_scene_preset_manager;
		uintptr_t set_scene_element_lighting;
		uintptr_t get_scene_preset;
		uintptr_t m_water_quad;
		uintptr_t m_water_quad_count;

		bool* m_is_session_started{};
		bool* should_sync_money_rewards;	
		bool* m_send_clone_sync;

		PVOID m_handle_new_script_host_message;
		PVOID m_get_label_text;
		PVOID m_model_spawn_bypass;
		PVOID m_world_model_spawn_bypass;
		PVOID m_native_return;
		PVOID m_blame_explode;
		PVOID m_send_net_info_to_lobby{};	
		PVOID m_gta_thread_start{};
		PVOID m_gta_thread_kill{};	
		PVOID m_assign_physical_index{};
		PVOID m_network_player_mgr_init;
		PVOID m_network_player_mgr_shutdown;
		PVOID m_process_matchmaking_find_response;
		PVOID m_serialize_player_data_msg;
		PVOID m_serialize_join_request_message;
		PVOID m_init_native_tables{};
		PVOID m_script_vm{};
		PVOID m_received_event{};
		PVOID m_received_clone_create;
		PVOID m_received_clone_sync;
		PVOID m_received_clone_remove;
		PVOID m_sync_can_apply_data;		
		PVOID m_write_player_gamer_data_node{};
		PVOID m_write_ped_movement_data_node{};
		PVOID m_write_ped_orientation_data_node{};
		PVOID m_pickup_creation_data_node{};
		PVOID m_pickup_placement_creation_data_node{};
		PVOID m_ped_creation_data_node{};
		PVOID m_player_creation_data_node{};
		PVOID m_object_creation_data_node{};
		PVOID m_vehicle_creation_data_node{};
		PVOID m_player_appearance_data_node{};
		PVOID m_vehicle_control_data_node{};
		PVOID m_train_game_state_data_node{};
		PVOID m_ped_attach_data_node{};
		PVOID m_physical_attach_data_node{};
		PVOID m_sector_data_node{};
		PVOID m_dynamic_entity_game_state_data_node{};
		PVOID m_ped_inventory_data_node{};
		PVOID m_vehicle_gadget_data_node{};
		PVOID m_serialize_take_off_ped_variation_task;
		PVOID m_receive_net_message;
		PVOID m_get_network_event_data;
		PVOID m_meltdown_patch;
		PVOID indecent_exposure_add{};
		PVOID m_invalid_mods_crash_detour;
		PVOID m_vehicle_data_crash_patch;//48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC 40 48 8B B1 ? ? ? ? 8A 9A ? ? ? ? 32
		PVOID m_trailer_attach_crash_patch;//48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC 20 48 8B D9 48 8B 49 30 45 33
		PVOID m_trailer_attach_audio_crash_patch;//48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 57 48 81 EC ? ? ? ? 48 8B D9 48 8B 89 ? ? ? ? 0F 29 70 E8 0F 29 78 D8 48 8B F2 E8
		PVOID m_invalid_script_crash_patch;//48 8B 01 4C 8B C1 48 3B D0 75 21 48 8B 40 18 48 89 01 33 C0 48 89 42 18 48 8B 09 48 85 C9 74 06 48 89 41 20 EB 4E 49
		PVOID m_invalid_script_crash_patch2;//48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 8B F9 48 83 C1 30 41 8A F1 48 8B 19 EB 10
		PVOID m_invalid_sub_crash_patch;//48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 80 3D ? ? ? ? ? 41 8B D8 8B F2 48 8B F9 74 2F E8
		PVOID m_invalid_track_event_crash_patch;//48 8B C4 48 89 58 08 48 89 70 10 48 89 78 18 55 48 8D 68 A1 48 81 EC A0 00 00 00 0F 28 91 90 00 00 00
		PVOID m_invalid_attachment_crash_patch;
		PVOID m_invalid_player_crash_patch;
		PVOID m_invalid_melee_crash_patch;
		PVOID m_invalid_dynamic_entity_crash_patch;//48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 8B 81 F8 02 00 00
		PVOID m_invalid_contact_task_crash_patch;//48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 48 8B D9 E8 ?? ?? ?? ?? 48 8B 93 90 00 00 00
		PVOID m_write_bitbuffer_gamer_handle;
		PVOID m_read_bitbuffer_gamer_handle;
		PVOID m_create_script_handler;
		PVOID m_weather_data;
		PVOID m_queue_dependency;
		PVOID m_interval_check_func;
		PVOID shitter_crash;
		PVOID m_presence_events;
		PVOID m_update_presence_attribute_int;
		PVOID m_update_presence_attribute_string;
		PVOID m_track_patch;

		char* m_east_azimuth_patch;//0F 29 62 20
		char* m_west_azimuth_patch;//0F 29 62 50
		char* m_azimuth_transition_patch;//0F 29 A2 80 00 00 00
		char* m_zenith_patch;//0F 29 A2 B0 00 00 00 8B 81 58 03 00 00
		char* m_zenith_transition_patch;//0F 29 A2 E0 00 00 00
		char* m_cloud_mid_patch;//0F 29 8B 60 03 00 00
		char* m_cloud_base_patch;//0F 29 A2 80 03 00 00
	
		std::pair<uint64_t, uint32_t> g_game_address;
	};

	inline pointers *g_pointers{};
}
