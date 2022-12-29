#include "common.hpp"
#include "function_types.hpp"
#include "logger.hpp"
#include "gta/array.hpp"
#include "gta/player.hpp"
#include "gta/script_thread.hpp"
#include "menu.h"
#include "hooking.hpp"
#include "memory/module.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "renderer.hpp"
#include "script_mgr.hpp"
#include "custom_text.hpp"
#include "../xorstr.h"
#include <MinHook.h>
#include "../caller.hpp"
#include "gta/script_handler.hpp"
#include "../notify.h"
#include "gta/replay.hpp"
#include "../lists.h"
#include "../CObject.h"
namespace big
{

	hooking::hooking() :
		m_swapchain_hook(*g_pointers->m_swapchain, hooks::swapchain_num_funcs),
		m_set_cursor_pos_hook(XOR("SCP"), memory::module(XOR("user32.dll")).get_export(XOR("SetCursorPos")).as<void*>(), &hooks::set_cursor_pos),

		m_run_script_threads_hook(XOR("RST"), g_pointers->m_run_script_threads, &hooks::run_script_threads),
		m_convert_thread_to_fiber_hook(XOR("CTTF"), memory::module("kernel32.dll").get_export(XOR("ConvertThreadToFiber")).as<void*>(), &hooks::convert_thread_to_fiber),
		og_write_player_gamer_data_node(XOR("WPGDN"), g_pointers->m_write_player_gamer_data_node, &hooks::hk_write_player_gamer_data_node),
		og_write_player_game_state_data_node(XOR("WPGSDN"), g_pointers->m_write_player_game_state_data_node, &hooks::hk_write_player_game_state_data_node),
		og_send_net_info_to_lobby(XOR("SNITL"), g_pointers->m_send_net_info_to_lobby, &hooks::hk_send_net_info_to_lobby),
		og_gta_thread_start(XOR("GTS"), g_pointers->m_gta_thread_start, &hooks::hk_gta_thread_start),
		og_gta_thread_kill(XOR("GTK"), g_pointers->m_gta_thread_kill, &hooks::hk_gta_thread_kill),
		og_assign_physical_index(XOR("API"), g_pointers->m_assign_physical_index, &hooks::hk_assign_physical_index),
		og_network_player_mgr_init(XOR("NPMI"), g_pointers->m_network_player_mgr_init, &hooks::hk_network_player_mgr_init),
		og_network_player_mgr_shutdown(XOR("NPMSD"), g_pointers->m_network_player_mgr_shutdown, &hooks::hk_network_player_mgr_shutdown),
		og_init_native_tables(XOR("INT"), g_pointers->m_init_native_tables, &hooks::hk_init_native_tables),
		og_script_vm(XOR("SVM"), g_pointers->m_script_vm, &hooks::hk_script_vm),
		og_received_event(XOR("RNE"), g_pointers->m_received_event, &hooks::hk_received_event),
		og_received_clone_create(XOR("RCC"), g_pointers->m_received_clone_create, &hooks::hk_received_clone_create),
		og_received_clone_sync(XOR("RCS"), g_pointers->m_received_clone_sync, &hooks::hk_received_clone_sync),
		og_sync_can_apply_data(XOR("SCAD"), g_pointers->m_sync_can_apply_data, &hooks::hk_sync_can_apply_data),
		og_write_ped_movement_data_node(XOR("WPMDN"), g_pointers->m_write_ped_movement_data_node, &hooks::hk_write_ped_movement_data_node),
		
		og_new_script_host_message(XOR("NSHM"), g_pointers->m_handle_new_script_host_message, &hooks::hk_new_script_host_message),
		og_pickup_creation_data_node(XOR("PCDN"), g_pointers->m_pickup_creation_data_node, &hooks::hk_pickup_creation_data_node),
		og_player_creation_data_node(XOR("PCDN2"), g_pointers->m_player_creation_data_node, &hooks::hk_player_creation_data_node),
		og_ped_creation_data_node(XOR("PCDN3"), g_pointers->m_ped_creation_data_node, &hooks::hk_ped_creation_data_node),
		og_object_creation_data_node(XOR("OCDN"), g_pointers->m_object_creation_data_node, &hooks::hk_object_creation_data_node),
		og_vehicle_creation_data_node(XOR("VCDN"), g_pointers->m_vehicle_creation_data_node, &hooks::hk_vehicle_creation_data_node),
		og_player_appearance_data_node(XOR("PADN"), g_pointers->m_player_appearance_data_node, &hooks::hk_player_appearance_data_node),
		og_vehicle_control_data_node(XOR("VCDN2"), g_pointers->m_vehicle_control_data_node, &hooks::hk_vehicle_control_data_node),
		og_train_game_state_data_node(XOR("TGDN"), g_pointers->m_train_game_state_data_node, &hooks::hk_train_game_state_data_node),
		og_ped_attach_data_node(XOR("PADN2"), g_pointers->m_ped_attach_data_node, &hooks::hk_ped_attach_data_node),
		og_physical_attach_data_node(XOR("PADN3"), g_pointers->m_physical_attach_data_node, &hooks::hk_physical_attach_data_node),
		og_dynamic_entity_game_state_data_node(XOR("DEGSDN"), g_pointers->m_dynamic_entity_game_state_data_node, &hooks::hk_dynamic_entity_game_state_data_node),
		og_ped_inventory_data_node(XOR("PIDN"), g_pointers->m_ped_inventory_data_node, &hooks::hk_ped_inventory_data_node),
		og_vehicle_gadget_data_node(XOR("VGDN"), g_pointers->m_vehicle_gadget_data_node, &hooks::hk_vehicle_gadget_data_node),
		og_meltdown_crash_patch(XOR("MDCP"), g_pointers->m_meltdown_patch, &hooks::hk_meltdown_crash_patch),
		og_indecent_exposure_hook_patch(XOR("IECP"), g_pointers->indecent_exposure_add, &hooks::hk_indecent_exposure_hook_patch),
		og_serialize_take_off_ped_variation_task(XOR("TOPVT"), g_pointers->m_serialize_take_off_ped_variation_task, &hooks::hk_serialize_take_off_ped_variation_task),
		og_invalid_mods_crash_detour(XOR("IMCP"), g_pointers->m_invalid_mods_crash_detour, &hooks::hk_invalid_mods_crash_detour),
		og_net_message(XOR("RNE"), g_pointers->m_receive_net_message, &hooks::hk_net_message),
		og_pack_clone_create(XOR("PCC"), g_pointers->m_pack_clone_create, &hooks::hk_pack_clone_create),
		og_clone_remove(XOR("RCR"), g_pointers->m_received_clone_remove, &hooks::hk_clone_remove),
		og_trailer_attach_crash_patch(XOR("TACP"), g_pointers->m_trailer_attach_crash_patch, &hooks::hk_trailer_attach_crash_patch),
		og_trailer_attach_audio_crash_patch(XOR("TAACP"), g_pointers->m_trailer_attach_audio_crash_patch, &hooks::hk_trailer_attach_audio_crash_patch),
		og_invalid_script_crash_patch(XOR("ISCP"), g_pointers->m_invalid_script_crash_patch, &hooks::hk_invalid_script_crash_patch),
		og_invalid_script_crash_patch2(XOR("ISCP2"), g_pointers->m_invalid_script_crash_patch2, &hooks::hk_invalid_script_crash_patch2),
		og_invalid_sub_crash_patch(XOR("ISCP3"), g_pointers->m_invalid_sub_crash_patch, &hooks::hk_invalid_sub_crash_patch),
		og_invalid_tracked_event_crash_patch(XOR("ITECP"), g_pointers->m_invalid_track_event_crash_patch, &hooks::hk_invalid_tracked_event_crash_patch),
		og_invalid_attachment_crash_patch(XOR("IACP"), g_pointers->m_invalid_attachment_crash_patch, &hooks::hk_invalid_attachment_crash_patch),
		og_invalid_melee_crash_patch(XOR("IMCP2"), g_pointers->m_invalid_melee_crash_patch, &hooks::hk_invalid_melee_crash_patch),
		og_write_bitbuffer_gamer_handle(XOR("WBGH"), g_pointers->m_write_bitbuffer_gamer_handle, &hooks::hk_write_bitbuffer_gamer_handle),
		og_read_bitbuffer_gamer_handle(XOR("RBGH"), g_pointers->m_read_bitbuffer_gamer_handle, &hooks::hk_read_bitbuffer_gamer_handle),
		og_invalid_player_crash_patch(XOR("IPCP"), g_pointers->m_invalid_player_crash_patch, &hooks::hk_invalid_player_crash_patch),
		og_invalid_dynamic_entity_crash_patch(XOR("IDECP"), g_pointers->m_invalid_dynamic_entity_crash_patch, &hooks::hk_invalid_attachment_crash_patch),
		og_get_network_event_data(XOR("GNED"), g_pointers->m_get_network_event_data, &hooks::hk_get_network_event_data),
		og_weather_data(XOR("WD"), g_pointers->m_weather_data, &hooks::hk_weather_data),
		og_nigger_crash(XOR("NGGGGGGG"), g_pointers->shitter_crash, &hooks::hk_nigger_crash),
		og_track_patch(XOR("BRUH"), g_pointers->m_track_patch, &hooks::hk_track_patch),
		og_presence_event_handler(XOR("RPE"), g_pointers->m_presence_events, &hooks::hk_presence_event_handler),
		og_update_presence_attribute_int("PAI", g_pointers->m_update_presence_attribute_int, &hooks::hk_update_presence_attribute_int),
		og_update_presence_attribute_string("PAS", g_pointers->m_update_presence_attribute_string, &hooks::hk_update_presence_attribute_string)

	{
		m_swapchain_hook.hook(hooks::swapchain_present_index, &hooks::swapchain_present);
		m_swapchain_hook.hook(hooks::swapchain_resizebuffers_index, &hooks::swapchain_resizebuffers);

		g_hooking = this;
	}

	hooking::~hooking()
	{
		if (m_enabled)
			disable();

		g_hooking = nullptr;
	}

	void hooking::enable()
	{
		m_swapchain_hook.enable();
		m_og_wndproc = WNDPROC(SetWindowLongPtrW(g_pointers->m_hwnd, GWLP_WNDPROC, LONG_PTR(&hooks::wndproc)));

		m_set_cursor_pos_hook.enable();
		m_run_script_threads_hook.enable();
		m_convert_thread_to_fiber_hook.enable();
		og_write_player_gamer_data_node.enable();
	    og_write_player_game_state_data_node.enable();
		og_send_net_info_to_lobby.enable();
		og_gta_thread_start.enable();
		og_gta_thread_kill.enable();
		og_init_native_tables.enable();
		og_script_vm.enable();
		og_assign_physical_index.enable();
		og_network_player_mgr_init.enable();
		og_network_player_mgr_shutdown.enable();
		og_received_event.enable();
		og_received_clone_create.enable();
		og_received_clone_sync.enable();
		og_write_ped_movement_data_node.enable();
		og_new_script_host_message.enable();
		og_object_creation_data_node.enable();
		og_vehicle_creation_data_node.enable();
		og_player_appearance_data_node.enable();
		og_vehicle_control_data_node.enable();
		og_train_game_state_data_node.enable();
		og_player_creation_data_node.enable();
		og_pickup_creation_data_node.enable();
		og_ped_creation_data_node.enable();
	    og_ped_attach_data_node.enable();
		og_physical_attach_data_node.enable();
		og_dynamic_entity_game_state_data_node.enable();
		og_ped_inventory_data_node.enable();
		og_vehicle_gadget_data_node.enable();
		og_meltdown_crash_patch.enable();
	    og_indecent_exposure_hook_patch.enable();
		og_invalid_mods_crash_detour.enable();
		og_serialize_take_off_ped_variation_task.enable();
		og_net_message.enable();
		og_pack_clone_create.enable();
		og_clone_remove.enable();
		og_trailer_attach_crash_patch.enable();
		og_trailer_attach_audio_crash_patch.enable();
	    og_invalid_script_crash_patch.enable();
		og_invalid_script_crash_patch2.enable();
		og_invalid_sub_crash_patch.enable();
		og_invalid_tracked_event_crash_patch.enable();
		og_invalid_attachment_crash_patch.enable();
		og_invalid_player_crash_patch.enable();	
		og_write_bitbuffer_gamer_handle.enable();
		og_read_bitbuffer_gamer_handle.enable();
	    og_get_network_event_data.enable();
		og_weather_data.enable();
		og_nigger_crash.enable();
		og_track_patch.enable();
		og_invalid_melee_crash_patch.enable();
		og_invalid_dynamic_entity_crash_patch.enable();
		og_presence_event_handler.enable();
		og_update_presence_attribute_int.enable();
		og_update_presence_attribute_string.enable();

		LOG(G3LOG_DEBUG) << XOR("Hook | Created ") << XOR("59") << XOR(" Hooks");
		m_enabled = true;
	}

	void hooking::disable()
	{
		m_enabled = false;
		og_update_presence_attribute_int.disable();
		og_update_presence_attribute_string.disable();
		og_presence_event_handler.disable();
		og_invalid_dynamic_entity_crash_patch.disable();
		og_invalid_melee_crash_patch.disable();
		og_track_patch.disable();
		og_nigger_crash.disable();
		og_weather_data.disable();
		og_get_network_event_data.disable();
		og_write_bitbuffer_gamer_handle.disable();
		og_read_bitbuffer_gamer_handle.disable();
	    og_invalid_player_crash_patch.disable();
		og_invalid_attachment_crash_patch.disable();
		og_invalid_tracked_event_crash_patch.disable();
		og_trailer_attach_crash_patch.disable();
		og_trailer_attach_audio_crash_patch.disable();
		og_invalid_script_crash_patch.disable();
		og_invalid_script_crash_patch2.disable();
		og_invalid_sub_crash_patch.disable();
		og_clone_remove.disable();
		og_pack_clone_create.disable();
		og_net_message.disable();
		og_received_clone_create.disable();
		og_serialize_take_off_ped_variation_task.disable();
		og_invalid_mods_crash_detour.disable();
	    og_meltdown_crash_patch.disable();
		og_indecent_exposure_hook_patch.disable();
		og_object_creation_data_node.disable();
		og_vehicle_creation_data_node.disable();
		og_player_appearance_data_node.disable();
		og_vehicle_control_data_node.disable();
		og_train_game_state_data_node.disable();
		og_player_creation_data_node.disable();
		og_pickup_creation_data_node.disable();
		og_ped_creation_data_node.disable();
		og_ped_attach_data_node.disable();
		og_physical_attach_data_node.disable();
		og_dynamic_entity_game_state_data_node.disable();
		og_ped_inventory_data_node.disable();
	    og_new_script_host_message.disable();
		og_write_ped_movement_data_node.disable();
		og_received_clone_sync.disable();
		og_received_event.disable();
		og_assign_physical_index.disable();
		og_network_player_mgr_init.disable();
		og_network_player_mgr_shutdown.disable();
		og_init_native_tables.disable();
		og_script_vm.disable();
	    og_gta_thread_start.disable();
		og_gta_thread_kill.disable();
		og_write_player_gamer_data_node.disable();
		og_write_player_game_state_data_node.disable();
		og_send_net_info_to_lobby.disable();
		m_convert_thread_to_fiber_hook.disable();
		m_run_script_threads_hook.disable();
		m_set_cursor_pos_hook.disable();

		SetWindowLongPtrW(g_pointers->m_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(m_og_wndproc));
		m_swapchain_hook.disable();
	}
	uint64_t hooks::hk_nigger_crash(uint64_t data)
	{
		uint64_t v3; // rbx

		if (!data) {
			return false;
		}

		v3 = engine::memory::scan_address(g_base_address + 0x15E4D2E, {});

		if (!v3) {
			return false;
		}
		return g_hooking->og_nigger_crash.get_original<decltype(&hk_nigger_crash)>()(data);
	}
	uint64_t hooks::hk_track_patch(uint64_t data)
	{

		if (!data) {
			return false;
		}

		if (!data + 0x30C) {
			return false;
		}
		
		return g_hooking->og_track_patch.get_original<decltype(&hk_track_patch)>()(data);
	}
	int hooks::nt_query_virtual_memory(void* _this, HANDLE handle, PVOID base_addr, int info_class, MEMORY_BASIC_INFORMATION* info, int size, size_t* return_len)
	{
		LOG(INFO) << "Reached here, base addr: " << base_addr;
		return 1;
	}
	minhook_keepalive::minhook_keepalive()
	{
		MH_Initialize();
	}

	minhook_keepalive::~minhook_keepalive()
	{
		MH_Uninitialize();
	}

	LRESULT hooks::wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		TRY_CLAUSE
		{
			if (g_running)
			{
				g_renderer->wndproc(hwnd, msg, wparam, lparam);
			}

			return CallWindowProcW(g_hooking->m_og_wndproc, hwnd, msg, wparam, lparam);
		} EXCEPT_CLAUSE
		return NULL;
	}

	BOOL hooks::set_cursor_pos(int x, int y)
	{
		TRY_CLAUSE
		{
			if (menu::g_gui.m_opened)
				return true;

			return g_hooking->m_set_cursor_pos_hook.get_original<decltype(&set_cursor_pos)>()(x, y);
		} EXCEPT_CLAUSE
		return FALSE;
	}
}
