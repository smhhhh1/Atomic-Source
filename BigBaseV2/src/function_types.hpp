#pragma once
#include "common.hpp"
#include "gta/fwddec.hpp"
#include "gta/natives.hpp"
#include "../node_types.h"
#include "../rlSessionByGamerTaskResult.hpp"
#include "../Network.hpp"
#include "../netObject.hpp"
class NetworkGameFilterMatchmakingComponent;

namespace rage
{
	class netConnectionPeer;
	class snMsgRemoveGamersFromSessionCmd;
	class snSession;
	class snPlayer;
}

namespace big::functions
{
	typedef unsigned __int64 QWORD;
	using run_script_threads_t = bool(*)(std::uint32_t ops_to_execute);
	using get_native_handler_t = rage::scrNativeHandler(*)(rage::scrNativeRegistrationTable*, rage::scrNativeHash);
	using fix_vectors_t = void(*)(rage::scrNativeCallContext*);
	using FileRegister = std::uint32_t(*)(std::uint32_t* texture_id, const char* path, bool p1, const char* name, bool p2);
	using get_net_game_player = CNetGamePlayer * (*) (uint32_t player);
	using trigger_script_event = void(*)(int event_group, int64_t* args, int arg_count, int player_bits);
	using increment_Stat = void (*) (Hash hash, unsigned int value, CNetGamePlayer* player);
	using give_pickup_rewards = void(*)(int players, uint32_t hash);
	using write_player_game_state_data_node = bool(*)(rage::netObject* plr, CPlayerGameStateDataNode* node);
	using start_get_session_by_gamer_handle = bool(*)(int metric_manager, rage::rlGamerHandle* handles, int count, rage::rlSessionByGamerTaskResult* result, int unk, bool* success, int* state);
	using join_session_by_info = bool(*)(Network* network, rage::rlSessionInfo* info, int unk, int flags, rage::rlGamerHandle* handles, int handlecount);
	using start_matchmaking_find_sessions = bool(*)(int profile_index, int available_slots, NetworkGameFilterMatchmakingComponent* m_filter, unsigned int max_sessions, rage::rlSessionInfo* result_sessions, int* result_session_count, int* state);
	using generate_uuid = bool(*)(std::uint64_t* uuid);
	using read_bitbuf_dword = bool(*)(rage::datBitBuffer* buffer, PVOID read, int bits);
	using read_bitbuf_string = bool(*)(rage::datBitBuffer* buffer, char* read, int bits);
	using read_bitbuf_bool = bool(*)(rage::datBitBuffer* buffer, bool* read, int bits);
	using read_bitbuf_array = bool(*)(rage::datBitBuffer* buffer, PVOID read, int bits, int unk);
	using write_bitbuf_qword = bool(*)(rage::datBitBuffer* buffer, uint64_t val, int bits);
	using write_bitbuf_dword = bool(*)(rage::datBitBuffer* buffer, uint32_t val, int bits);
	using write_bitbuf_int64 = bool(*)(rage::datBitBuffer* buffer, int64_t val, int bits);
	using write_bitbuf_int32 = bool(*)(rage::datBitBuffer* buffer, int32_t val, int bits);
	using write_bitbuf_bool = bool(*)(rage::datBitBuffer* buffer, bool val, int bits);
	using write_bitbuf_array = bool(*)(rage::datBitBuffer* buffer, void* val, int bits, int unk);
	using send_event_ack = void(*)(rage::netEventMgr* event_manager, CNetGamePlayer* source_player, CNetGamePlayer* target_player, int event_index, int event_handled_bitset);
	using get_sync_type_info = const char* (*)(uint16_t sync_type, char a2);
	using get_sync_tree_for_type = rage::netSyncTree* (*)(CNetworkObjectMgr* mgr, uint16_t sync_type);
	using get_net_object = rage::netObject* (*)(CNetworkObjectMgr* mgr, int16_t id, bool can_delete_be_pending);
	using get_net_object_for_player = rage::netObject* (*)(CNetworkObjectMgr*, int16_t, bool flag);
	using read_bitbuffer_into_sync_tree = void(*)(rage::netSyncTree* tree, uint64_t flag, uint32_t flag2, rage::datBitBuffer* buffer, uint64_t netLogStub);
	using new_script_host_message = bool(*)(QWORD* a1, __int64 a2, unsigned int a3, DWORD* a4);
	using queue_packet = bool(*)(rage::netConnectionManager* mgr, int msg_id, void* data, int size, int flags, void* unk);
	using get_connection_peer = rage::netConnectionPeer* (*)(rage::netConnectionManager* manager, int peer_id);
	using send_remove_gamer_cmd = void(*)(rage::netConnectionManager* net_connection_mgr, rage::netConnectionPeer* player, int connection_id, rage::snMsgRemoveGamersFromSessionCmd* cmd, int flags);
	using handle_remove_gamer_cmd = void* (*)(rage::snSession* session, rage::snPlayer* origin, rage::snMsgRemoveGamersFromSessionCmd* cmd);
	using get_vehicle_gadget_array_size = int(*)(eVehicleGadgetType type);
	using clone_pack_create_t = void (*) (CNetworkObjectMgr* mgr, rage::netObject* netObject, CNetGamePlayer* src, rage::datBitBuffer* buffer);
	using clone_pack_sync_t = bool (*) (CNetworkObjectMgr* mgr, rage::netObject* netObject, CNetGamePlayer* src);

}
