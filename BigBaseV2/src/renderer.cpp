#include "common.hpp"
#include "fonts.hpp"
#include "logger.hpp"
#include "menu.h"
#include "pointers.hpp"
#include "renderer.hpp"
#include <imgui.h>
#include <backends/imgui_impl_dx11.h>
#include <backends/imgui_impl_win32.h>
#include <imgui_internal.h>
#include "../player.h"
#include "../movement.h"
#include "../appearance.h"
#include "../wardrobe.h"
#include "../notify.h"
#include "../model.h"
#include "../animation.h"
#include "../animations.h"
#include "../scenario.h"
#include "../clipsets.h"
#include "../ptfx.h"
#include "../hand_trails.h"
#include "../proofs.h"
#include "../weapon.h"
#include "../aimbot.h"
#include "../impacts.h"
#include "../entity_gun.h"
#include "../paint_gun.h"
#include "../gravity_gun.h"
#include "../magnet_gun.h"
#include "../explosion_gun.h"
#include "../particle_gun.h"
#include "../gun_locker.h"
#include "../spawner.h"
#include "../vehicle.h"
#include "../customs.h"
#include "../vehicle_health.h"
#include "../vehicle_color.h"
#include "../vehicle_primary_color.h"
#include "../vehicle_secondary_color.h"
#include "../vehicle_weapons.h"
#include "../vehicle_ptfx.h"
#include "../vehicle_movement.h"
#include "../vehicle_parachute.h"
#include "../vehicle_acrobatics.h"
#include "../vehicle_boost.h"
#include "../vehicle_collision.h"
#include "../vehicle_gravity.h"
#include "../vehicle_multipliers.h"
#include "../vehicle_handling.h"
#include "../vehicle_autopilot.h"
#include "../vehicle_ramp.h"
#include "../vehicle_randomization.h"
#include "../vehicle_doors.h"
#include "../vehicle_proofs.h"
#include "../network.h"
#include "../network_players.h"
#include "../network_selected_player.h"
#include "../network_selected_friendly.h"
#include "../network_selected_friendly_drops.h"
#include "../network_selected_abusive.h"
#include "../network_selected_abusive_attackers.h"
#include "../network_selected_abusive_explosion.h"
#include "../network_selected_abusive_increment.h"
#include "../network_selected_trolling.h"
#include "../network_selected_trolling_entity_spammer.h"
#include "../network_selected_trolling_notifications.h"
#include "../network_selected_teleport.h"
#include "../network_selected_teleport_apartment.h"
#include "../network_selected_text.h"
#include "../network_selected_esp.h"
#include "../network_selected_kicks.h"
#include "../network_selected_crashes.h"
#include "../network_selected_spawner.h"
#include "../network_selected_vehicle.h"
#include "../network_spoofing.h"
#include "../network_spoofing_crew.h"
#include "../network_spoofing_crew_name.h"
#include "../network_spoofing_crew_tag.h"
#include "../network_spoofing_crew_icon.h"
#include "../network_spoofing_name.h"
#include "../network_spoofing_ip.h"
#include "../network_spoofing_rid.h"
#include "../network_spoofing_detection_flags.h"
#include "../network_friends.h"
#include "../network_recent_players.h"
#include "../network_recovery_rank.h"
#include "../network_recovery_unlocks.h"
#include "../network_recovery_stats.h"
#include "../network_recovery_misc.h"
#include "../network_services.h"
#include "../network_toolkit.h"
#include "../network_player_search.h"
#include "../network_notifications.h"
#include "../protections.h"
#include "../protections_network_events.h"
#include "../protections_script_events.h"
#include "../protections_reactions.h"
#include "../protections_presence.h"
#include "../protections_join_blocking.h"
#include "../protections_entity.h"
#include "../protections_misc.h"
#include "../world.h"
#include "../game_fx.h"
#include "../fx_visuals.h"
#include "../fx_sky.h"
#include "../weather.h"
#include "../weather_fx.h"
#include "../fx_world_glow.h"
IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace big
{
	renderer::renderer() :
		m_dxgi_swapchain(*g_pointers->m_swapchain)
	{
		void *d3d_device{};
		if (SUCCEEDED(m_dxgi_swapchain->GetDevice(__uuidof(ID3D11Device), &d3d_device)))
		{
			m_d3d_device.Attach(static_cast<ID3D11Device*>(d3d_device));
		}
		else
		{
			throw std::runtime_error("Failed to get D3D device.");
		}

		m_d3d_device->GetImmediateContext(m_d3d_device_context.GetAddressOf());

		auto file_path = std::filesystem::path(std::getenv("appdata"));
		file_path /= "BigBaseV2";
		if (!std::filesystem::exists(file_path))
		{
			std::filesystem::create_directory(file_path);
		}
		else if (!std::filesystem::is_directory(file_path))
		{
			std::filesystem::remove(file_path);
			std::filesystem::create_directory(file_path);
		}
		file_path /= "imgui.ini";
		
		ImGuiContext* ctx = ImGui::CreateContext();

		static std::string path = file_path.make_preferred().string();
		ctx->IO.IniFilename = path.c_str();

		ImGui_ImplDX11_Init(m_d3d_device.Get(), m_d3d_device_context.Get());
		ImGui_ImplWin32_Init(g_pointers->m_hwnd);

		ImFontConfig font_cfg{};
		font_cfg.FontDataOwnedByAtlas = false;
		std::strcpy(font_cfg.Name, "Rubik");

		m_font = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(font_rubik), sizeof(font_rubik), 20.f, &font_cfg);
		m_monospace_font = ImGui::GetIO().Fonts->AddFontDefault();

		auto& style = ImGui::GetStyle();
		style.WindowPadding = { 0.f, 15.f };
		style.PopupRounding = 0.f;
		style.FramePadding = { 0.f, 15.f };
		style.ItemSpacing = { 10.f, 8.f };
		style.ItemInnerSpacing = { 6.f, 6.f };
		style.TouchExtraPadding = { 8.f, 0.f };
		style.IndentSpacing = 21.f;
		style.ScrollbarSize = 15.f;
		style.GrabMinSize = 8.f;
		style.WindowBorderSize = 0.f;
		style.ChildBorderSize = 0.f;
		style.PopupBorderSize = 1.f;
		style.FrameBorderSize = 0.f;
		style.TabBorderSize = 0.f;
		style.WindowRounding = 2.f;
		style.ChildRounding = 0.f;
		style.FrameRounding = 0.f;
		style.ScrollbarRounding = 0.f;
		style.GrabRounding = 0.f;
		style.TabRounding = 0.f;
		style.WindowTitleAlign = { 5.5f, 0.5f };
		style.ButtonTextAlign = { 0.5f, 0.5f };
		style.DisplaySafeAreaPadding = { 3.f, 3.f };

		auto& colors = style.Colors;
		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(1.00f, 0.90f, 0.19f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
		colors[ImGuiCol_Border] = ImVec4(0.30f, 0.30f, 0.30f, 0.50f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.21f, 0.21f, 0.21f, 0.54f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.21f, 0.21f, 0.21f, 0.78f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.28f, 0.27f, 0.27f, 0.54f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.17f, 0.17f, 0.17f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.39f, 0.38f, 0.38f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(0.41f, 0.41f, 0.41f, 0.74f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.41f, 0.41f, 0.41f, 0.78f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.41f, 0.41f, 0.41f, 0.87f);
		colors[ImGuiCol_Header] = ImVec4(0.37f, 0.37f, 0.37f, 0.31f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.38f, 0.38f, 0.38f, 0.37f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.37f, 0.37f, 0.37f, 0.51f);
		colors[ImGuiCol_Separator] = ImVec4(0.38f, 0.38f, 0.38f, 0.50f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.46f, 0.46f, 0.46f, 0.50f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.46f, 0.46f, 0.46f, 0.64f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
		colors[ImGuiCol_Tab] = ImVec4(0.21f, 0.21f, 0.21f, 0.86f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.27f, 0.27f, 0.27f, 0.86f);
		colors[ImGuiCol_TabActive] = ImVec4(0.34f, 0.34f, 0.34f, 0.86f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.10f, 0.10f, 0.10f, 0.97f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
		g_renderer = this;
	}

	renderer::~renderer()
	{
		ImGui_ImplWin32_Shutdown();
		ImGui_ImplDX11_Shutdown();
		ImGui::DestroyContext();

		g_renderer = nullptr;
	}

	void renderer::on_present()
	{

		ImGui::GetIO().MouseDrawCursor = false;
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouse;
		

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		notify::tick();

		if (menu::g_gui.m_opened)
		{
			menu::g_gui.dx_on_tick();
			menu::m_player_menu.menu();
			menu::m_movement_menu.menu();
			menu::m_appearance_menu.menu();
			menu::m_wardrobe_menu.menu();
			menu::m_model_menu.menu();
			menu::m_animation_menu.menu();
			menu::m_animations_menu.menu();
			menu::m_scenario_menu.menu();
			menu::m_clipsets_menu.menu();
			menu::m_ptfx_menu.menu();
			menu::m_hand_trails_menu.menu();
			menu::m_proofs_menu.menu();
			menu::m_weapon_menu.menu();
			menu::m_aimbot_menu.menu();
			menu::m_impacts_menu.menu();
		    menu::m_entity_gun_menu.menu();
			menu::m_paint_gun_menu.menu();
			menu::m_gravity_gun_menu.menu();
			menu::m_magnet_gun_menu.menu();
			menu::m_explosion_gun_menu.menu();
			menu::m_particle_gun_menu.menu();
			menu::m_gun_locker_menu.menu();
			menu::m_spawner_menu.menu();
			menu::m_vehicle_menu.menu();
			menu::m_customs_menu.menu();
			menu::m_vehicle_health_menu.menu();
			menu::m_vehicle_color_menu.menu();
			menu::m_vehicle_primary_color_menu.menu();
			menu::m_vehicle_secondary_color_menu.menu();
			menu::m_vehicle_weapons_menu.menu();
			menu::m_vehicle_ptfx_menu.menu();
			menu::m_vehicle_movement_menu.menu();
			menu::m_vehicle_parachute_menu.menu();
			menu::m_vehicle_acrobatics_menu.menu();
			menu::m_vehicle_boost_menu.menu();
			menu::m_vehicle_collision_menu.menu();
			menu::m_vehicle_gravity_menu.menu();
			menu::m_vehicle_multiplier_menu.menu();
			menu::m_vehicle_handling_menu.menu();
			menu::m_vehicle_autopilot_menu.menu();
			menu::m_vehicle_ramp_menu.menu();
			menu::m_vehicle_randomization_menu.menu();
			menu::m_vehicle_doors_menu.menu();
			menu::m_vehicle_proofs_menu.menu();
			menu::m_network_menu.menu();
			menu::m_network_players_menu.menu();
			menu::m_network_selected_player_menu.menu();
			menu::m_network_selected_friendly_menu.menu();
			menu::m_network_selected_friendly_drops_menu.menu();
			menu::m_network_selected_abusive_menu.menu();
			menu::m_network_selected_abusive_attackers_menu.menu();
			menu::m_network_selected_abusive_explosion_menu.menu();
			menu::m_network_selected_abusive_increment_menu.menu();
			menu::m_network_selected_trolling_menu.menu();
			menu::m_network_selected_trolling_entity_spammer_menu.menu();
			menu::m_network_selected_trolling_notifications_menu.menu();
			menu::m_network_selected_teleport_menu.menu();
			menu::m_network_selected_teleport_apartment_menu.menu();
			menu::m_network_selected_text_menu.menu();
			menu::m_network_selected_esp_menu.menu();
			menu::m_network_selected_kicks_menu.menu();
			menu::m_network_selected_crashes_menu.menu();
			menu::m_network_selected_spawner_menu.menu();
			menu::m_network_selected_vehicle_menu.menu();
			menu::m_network_spoofing_menu.menu();
			menu::m_network_spoofing_crew_menu.menu();
			menu::m_network_spoofing_crew_name_menu.menu();
			menu::m_network_spoofing_crew_tag_menu.menu();
			menu::m_network_spoofing_crew_icon_menu.menu();
			menu::m_network_spoofing_name_menu.menu();
			menu::m_network_spoofing_ip_menu.menu();
			menu::m_network_spoofing_rid_menu.menu();
			menu::m_network_spoofing_detection_flags_menu.menu();
			menu::m_network_friends_menu.menu();
			menu::m_network_recent_players_menu.menu();
			menu::m_network_recovery_rank_menu.menu();
			menu::m_network_recovery_unlocks_menu.menu();
			menu::m_network_recovery_misc_menu.menu();
			menu::m_network_services_menu.menu();
			menu::m_network_toolkit_menu.menu();
			menu::m_network_player_search_menu.menu();
			menu::m_network_notifications_menu.menu();

			menu::m_protections_menu.menu();
			menu::m_protections_network_events_menu.menu();
			menu::m_protections_script_events_menu.menu();
			menu::m_protections_reactions_menu.menu();
			menu::m_protections_presence_menu.menu();
			menu::m_protections_entity_menu.menu();
			menu::m_protections_misc_menu.menu();

			menu::m_world_menu.menu();
			menu::m_game_fx_menu.menu();
			menu::m_game_fx_visuals_menu.menu();
			menu::m_game_fx_sky_menu.menu();
			menu::m_game_fx_world_glow_menu.menu();

			menu::m_weather_menu.menu();
			menu::m_weather_fx_menu.menu();
		}

	
		ImGui::EndMenu();
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	void renderer::pre_reset()
	{
		ImGui_ImplDX11_InvalidateDeviceObjects();
	}

	void renderer::post_reset()
	{
		ImGui_ImplDX11_CreateDeviceObjects();
	}

	void renderer::wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		if (msg == WM_KEYUP && wparam == VK_INSERT)
		{
			//Persist and restore the cursor position between menu instances.
			static POINT cursor_coords{};
			if (menu::g_gui.m_opened)
			{
				GetCursorPos(&cursor_coords);
			}
			else if (cursor_coords.x + cursor_coords.y != 0)
			{
				SetCursorPos(cursor_coords.x, cursor_coords.y);
			}

			//g_gui.m_opened ^= true;
		}
			

		if (menu::g_gui.m_opened)
		{
			ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam);
		}
	}
}
