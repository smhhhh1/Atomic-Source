#pragma once
#include "common.hpp"
#include "detour_hook.hpp"
#include "gta/fwddec.hpp"
#include "gta/script_thread.hpp"
#include "script_hook.hpp"
#include "vmt_hook.hpp"
#include "gta/net_game_event.hpp"
class CPlayerGamerDataNode;
class CPlayerGameStateDataNode;
class CNetGamePlayerDataMsg;
class RemoteGamerInfoMsg;
namespace rage
{
	class rlMetric;
	class snSession;
	class JSONNode;
}
namespace big
{
	typedef unsigned __int64 QWORD;
	struct hooks
	{
		static bool run_script_threads(std::uint32_t ops_to_execute);		
		static void *convert_thread_to_fiber(void *param);
		static constexpr auto swapchain_num_funcs = 19;
		static constexpr auto swapchain_present_index = 8;
		static constexpr auto swapchain_resizebuffers_index = 13;
		static HRESULT swapchain_present(IDXGISwapChain *this_, UINT sync_interval, UINT flags);
		static HRESULT swapchain_resizebuffers(IDXGISwapChain *this_, UINT buffer_count, UINT width, UINT height, DXGI_FORMAT new_format, UINT swapchain_flags);
		static LRESULT wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
		static BOOL set_cursor_pos(int x, int y);
		static bool hk_send_net_info_to_lobby(rage::netPlayerData* player, int64_t a2, int64_t a3, DWORD* a4);
		static GtaThread* hk_gta_thread_start(unsigned int** a1, unsigned int a2);
		static rage::eThreadState hk_gta_thread_kill(GtaThread* thread);
		static bool hk_init_native_tables(rage::scrProgram* program);
		static rage::eThreadState hk_script_vm(uint64_t* start_stack, uint64_t** scr_globals, rage::scrProgram* program, rage::scrThreadContext* ctx);
		static void hk_network_player_mgr_init(CNetworkPlayerMgr* _this, std::uint64_t a2, std::uint32_t a3, std::uint32_t a4[4]);
		static void hk_network_player_mgr_shutdown(CNetworkPlayerMgr* _this);
		static void* hk_assign_physical_index(CNetworkPlayerMgr* netPlayerMgr, CNetGamePlayer* player, uint8_t new_index);
		static void hk_received_event(rage::netEventMgr* event_manager, CNetGamePlayer* source_player, CNetGamePlayer* target_player, uint16_t event_id, int event_index, int event_handled_bitset, int unk, rage::datBitBuffer* bit_buffer);
		static bool scripted_game_event(CScriptedGameEvent* scripted_game_event, CNetGamePlayer* player);
		static bool hk_received_clone_create(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, eNetObjType object_type, int32_t object_id, int32_t object_flag, rage::datBitBuffer* buffer, int32_t timestamp);
		static int64_t hk_received_clone_sync(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, eNetObjType object_type, uint16_t object_id, rage::datBitBuffer* bufer, uint16_t unk, uint32_t timestamp);
		static bool hk_sync_can_apply_data(rage::netSyncTree* tree, rage::netObject* object);
		static bool hk_new_script_host_message(uint64_t a1, uint64_t a2);
		static void hk_write_player_gamer_data_node(rage::netObject* player, CPlayerGamerDataNode* node);
		static void hk_ped_inventory_data_node(CPedInventoryDataNode* node, rage::CSyncDataBase* data);
		static void hk_dynamic_entity_game_state_data_node(CDynamicEntityGameStateDataNode* node, rage::CSyncDataBase* data);
		static void hk_vehicle_gadget_data_node(CVehicleGadgetDataNode* node, rage::CSyncDataBase* data);
		static void hk_player_appearance_data_node(rage::netObject* object, CPlayerAppearanceDataNode* node);
		static void hk_vehicle_control_data_node(rage::netObject* object, CVehicleControlDataNode* node);
		static void hk_train_game_state_data_node(rage::netObject* object, CTrainGameStateDataNode* node);
		static uint64_t hk_write_ped_movement_data_node(CPedMovementDataNode* node, rage::netObject* object);		
		static int64_t hk_ped_attach_data_node(CPedAttachDataNode* node, rage::netObject* data);
		static int64_t hk_physical_attach_data_node(CPhysicalAttachDataNode* node, rage::netObject* data);
		static bool hk_write_player_game_state_data_node(rage::netObject* player, CPlayerGameStateDataNode* node);
		static bool hk_pickup_creation_data_node(CPickupCreationDataNode* node, rage::netObject* obj);
		static bool hk_object_creation_data_node(CObjectCreationDataNode* node, rage::netObject* obj);
		static bool hk_vehicle_creation_data_node(CVehicleCreationDataNode* node);
		static bool hk_player_creation_data_node(CPlayerCreationDataNode* node);
		static bool hk_ped_creation_data_node(CPedCreationDataNode* node);
		static bool hk_meltdown_crash_patch(__int64 a1);
		static bool hk_indecent_exposure_hook_patch(__int64 a1, __int64 a2);
		static void hk_serialize_take_off_ped_variation_task(ClonedTakeOffPedVariationInfo* info, rage::CSyncDataBase* serializer);
		static void hk_invalid_mods_crash_detour(int64_t a1, int64_t a2, int a3, char a4);
		static bool hk_net_message(void* netConnectionManager, void* a2, rage::netConnection::InFrame* frame);
		static void hk_pack_clone_create(CNetworkObjectMgr* mgr, rage::netObject* netObject, CNetGamePlayer* src, rage::datBitBuffer* buffer);
		static bool hk_clone_remove(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, int32_t object_id, int32_t unk);
		static uint64_t hk_trailer_attach_crash_patch(uint64_t trailer, uint16_t flag);
		static uint64_t hk_trailer_attach_audio_crash_patch(uint64_t audio_entity, uint64_t a2);
		static uint64_t hk_invalid_script_crash_patch(uint64_t a1, uint64_t a2);
		static uint64_t hk_invalid_script_crash_patch2(uint64_t a1, uint16_t a2, uint32_t a3, bool a4);
		static uint64_t hk_invalid_sub_crash_patch(uint64_t a1, int a2, uint32_t a3);
		static uint64_t hk_invalid_tracked_event_crash_patch(__m128* a1, float* a2, bool a3, int a4);
		static uint64_t hk_invalid_attachment_crash_patch(uintptr_t a1);
		static bool hk_invalid_melee_crash_patch(uint64_t a1, bool a2, bool a3, bool a4);
		static void hk_invalid_player_crash_patch(uint64_t a1, uint64_t a2);
		static bool hk_write_bitbuffer_gamer_handle(rage::datBitBuffer* buffer, rage::rlGamerHandle* handle);
		static bool hk_read_bitbuffer_gamer_handle(rage::datBitBuffer* buffer, rage::rlGamerHandle* handle);
		static bool hk_invalid_dynamic_entity_crash_patch(uint64_t a1, uint64_t a2, bool a3);
		static void hk_get_network_event_data(int64_t unk, rage::CEventNetwork* event);
		static void hk_weather_data(CWeatherData* data);
		static int nt_query_virtual_memory(void* _this, HANDLE handle, PVOID base_addr, int info_class, MEMORY_BASIC_INFORMATION* info, int size, size_t* return_len);
		static uint64_t hk_nigger_crash(uint64_t data);
		static uint64_t hk_track_patch(uint64_t data);
		static bool hk_presence_event_handler(uint64_t a1, uint64_t a2, const char** payload, uint64_t a4);
		static bool hk_update_presence_attribute_int(void* data, int index, char* attribute, uint64_t value);
		static bool hk_update_presence_attribute_string(void* data, int index, char* attribute, char* value);

	};

	struct minhook_keepalive
	{
		minhook_keepalive();
		~minhook_keepalive();
	};

	class hooking
	{
		friend hooks;
	public:
		explicit hooking();
		~hooking();

		void enable();
		void disable();

	public:
		bool m_enabled{};

		WNDPROC m_og_wndproc;

		minhook_keepalive m_minhook_keepalive;

		vmt_hook m_swapchain_hook;

		detour_hook m_set_cursor_pos_hook;
		detour_hook m_run_script_threads_hook;
		detour_hook m_convert_thread_to_fiber_hook;
		detour_hook og_send_net_info_to_lobby;
		detour_hook og_gta_thread_start;
		detour_hook og_gta_thread_kill;
		detour_hook og_network_player_mgr_init;
		detour_hook og_network_player_mgr_shutdown;
		detour_hook og_assign_physical_index;
		detour_hook og_script_vm;
		detour_hook og_init_native_tables;
		detour_hook og_received_event;
		detour_hook og_received_clone_create;
		detour_hook og_received_clone_sync;
		detour_hook og_sync_can_apply_data;
		detour_hook og_new_script_host_message;
		detour_hook og_write_player_gamer_data_node;
		detour_hook og_write_player_game_state_data_node;
		detour_hook og_write_ped_movement_data_node;

		detour_hook og_ped_inventory_data_node;
		detour_hook og_dynamic_entity_game_state_data_node;
		detour_hook og_vehicle_gadget_data_node;
		detour_hook og_player_appearance_data_node;
		detour_hook og_vehicle_control_data_node;
		detour_hook og_train_game_state_data_node;
		detour_hook og_ped_attach_data_node;
		detour_hook og_physical_attach_data_node;
		detour_hook og_pickup_creation_data_node;
		detour_hook og_object_creation_data_node;
		detour_hook og_vehicle_creation_data_node;
		detour_hook og_player_creation_data_node;
		detour_hook og_ped_creation_data_node;
		detour_hook og_meltdown_crash_patch;
		detour_hook og_indecent_exposure_hook_patch;
		detour_hook og_serialize_take_off_ped_variation_task;
		detour_hook og_invalid_mods_crash_detour;
		detour_hook og_net_message;
		detour_hook og_pack_clone_create;
		detour_hook og_clone_remove;
		detour_hook og_trailer_attach_crash_patch;
		detour_hook og_trailer_attach_audio_crash_patch;
		detour_hook og_invalid_script_crash_patch;
		detour_hook og_invalid_script_crash_patch2;
		detour_hook og_invalid_sub_crash_patch;
		detour_hook og_invalid_tracked_event_crash_patch;
		detour_hook og_invalid_attachment_crash_patch;
		detour_hook og_invalid_player_crash_patch;
		detour_hook og_invalid_melee_crash_patch;
		detour_hook og_invalid_dynamic_entity_crash_patch;
		detour_hook og_write_bitbuffer_gamer_handle;
		detour_hook og_read_bitbuffer_gamer_handle;
		detour_hook og_get_network_event_data;
		detour_hook og_presence_event_handler;
		detour_hook og_weather_data;
		detour_hook og_nigger_crash;
		detour_hook og_track_patch;
		detour_hook og_update_presence_attribute_int;
		detour_hook og_update_presence_attribute_string;
	};

	inline hooking *g_hooking{};
}
