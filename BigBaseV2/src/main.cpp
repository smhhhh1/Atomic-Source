#include "common.hpp"
#include "features.hpp"
#include "fiber_pool.hpp"
#include "menu.h"
#include "logger.hpp"
#include "hooking.hpp"
#include "pointers.hpp"
#include "renderer.hpp"
#include "script_mgr.hpp"
#include "custom_text.hpp"
#include "../render.h"
#include "../player.h"
#include "../weapon.h"
#include "../vehicle.h"
#include "../network.h"
#include "../native_timer.h"
#include "../native_hooks.h"
#include "../player_service.hpp"
#include "../security_types.h"
#include "../players.h"
#include "../iron_dome.h"
#include "../script_patcher_service.hpp"
#include <DbgHelp.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include "../world.h"
#include "../fx_sky.h"
#include "../blacklist_manager.h"

BOOL APIENTRY DllMain(HMODULE hmod, DWORD reason, PVOID)
{
	using namespace big;
	if (reason == DLL_PROCESS_ATTACH)
	{	
		DisableThreadLibraryCalls(hmod);

		g_hmodule = hmod;
		g_main_thread = CreateThread(nullptr, 0, [](PVOID) -> DWORD
		{
			while (!FindWindow(L"grcWindow", L"Grand Theft Auto V"))
				std::this_thread::sleep_for(1s);	

			auto logger_instance = std::make_unique<logger>();
			try
			{		
				auto pointers_instance = std::make_unique<pointers>();
				auto renderer_instance = std::make_unique<renderer>();
				auto fiber_pool_instance = std::make_unique<fiber_pool>(10);
				auto ui_instance = std::make_unique<ui::renderer>();	
				auto hooking_instance = std::make_unique<hooking>();
				auto player_service_instance = std::make_unique<player_service>();		

				auto script_patcher_service_instance = std::make_unique<script_patcher_service>();
				auto player_database_service_instance = std::make_unique<player_database_service>();
				g_settings.load();
				g_script_mgr.add_script(std::make_unique<script>(&features::script_func));
				g_script_mgr.add_script(std::make_unique<script>(&menu::gui::script_func));
				g_script_mgr.add_script(std::make_unique<script>(&menu::player_menu::script_func));
				g_script_mgr.add_script(std::make_unique<script>(&menu::weapon_menu::script_func));
				g_script_mgr.add_script(std::make_unique<script>(&menu::vehicle_menu::script_func));
				g_script_mgr.add_script(std::make_unique<script>(&menu::network_menu::script_func));
				g_script_mgr.add_script(std::make_unique<script>(&menu::world_menu::script_func));



				auto native_hooks_instance = std::make_unique<native_hooks>();
				g_hooking->enable();			

				LOG(INFO) << "Atomic Loaded";
				LOG(INFO) << "Menu Version 1.1.4";

				MODULEINFO module_info;
				GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(0), &module_info, sizeof(module_info));

				g_pointers->g_game_address = { (uint64_t)module_info.lpBaseOfDll, module_info.SizeOfImage };
				while (g_running)
				{					
					if (GetAsyncKeyState(VK_END))
					{
						g_running = false;
						std::this_thread::sleep_for(250ms);
					}
					std::this_thread::sleep_for(500ms);		
				}
				g_hooking->disable();
				native_hooks_instance.reset();
				std::this_thread::sleep_for(1000ms);
				g_script_mgr.remove_all_scripts();
				hooking_instance.reset();
				fiber_pool_instance.reset();
				ui_instance.reset();
				renderer_instance.reset();
				pointers_instance.reset();
				player_service_instance.reset();
				//script_patcher_service_instance.reset();
				//player_database_service_instance.reset();
				
			}
			catch (std::exception const &ex)
			{
				LOG(WARNING) << ex.what();
				MessageBoxA(nullptr, ex.what(), nullptr, MB_OK | MB_ICONEXCLAMATION);
			}
			logger_instance.reset();
			CloseHandle(g_main_thread);
			FreeLibraryAndExitThread(g_hmodule, 0);
		}, nullptr, 0, &g_main_thread_id);
	}

	return true;
}
