#include "common.hpp"
#include "gta_util.hpp"
#include "network_selected_crashes.h"
#include "natives.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "../render.h"
#include "../abstract_submenu.h"
#include "../break_option.h"
#include "../toggle_option.h"
#include "../number.h"
#include "../option.h"
#include "../submenu_option.h"
#include "../simple_option.h"
#include "../simple_submenu.h"
#include "../bool_and_number.h"
#include "../submenu_option.h"
#include "player_submenu.h"
#include "../submenus.h"
#include "on_screen_ped.h"
#include "lists.h"
#include "fiber_pool.hpp"
#include "gta/enums.hpp"
#include "script_global.hpp"
#include "util.h"
#include "notify.h"
namespace big::menu
{
	constexpr size_t patch_size = 24;
	static inline std::once_flag once_flag;
	static inline std::array<byte, patch_size> backup;
	static inline void setup_backup()
	{
		memcpy(backup.data(), g_pointers->m_world_model_spawn_bypass, patch_size);
	}
	Object SpawnObject(Hash hash, float x, float y, float z, bool is_networked = true)
	{
		STREAMING::REQUEST_MODEL(hash);
		for (int i = 0; i < 100 && !STREAMING::HAS_MODEL_LOADED(hash); i++)
		{
			script::get_current()->yield();
		}
		if (!STREAMING::HAS_MODEL_LOADED(hash))
		{

			return 0;
		}

		std::call_once(once_flag, setup_backup);
		memset(g_pointers->m_world_model_spawn_bypass, 0x90, patch_size);

		const auto object = OBJECT::CREATE_OBJECT(hash, x, y, z, is_networked, false, false);

		memcpy(g_pointers->m_world_model_spawn_bypass, backup.data(), patch_size);

		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);

		return object;
	}
	void network_selected_crashes_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<PlayerSubmenu>(&selected_player, SubSelectedCrashes, [](PlayerSubmenu* core)
			{
				m_renderer.m_enable_player_info = true;
				core->add_option<simple_option>(("Vegan Crash"), nullptr, []
					{
						Player target = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player);
						Vector3 fposition = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(target, 0.0, 5.0, 0.0);
						while (!STREAMING::HAS_MODEL_LOADED(0xD75E01A6))
						{
							STREAMING::REQUEST_MODEL(0xD75E01A6);
							script::get_current()->yield();
						}
						for (std::uint32_t i = 0; i < 12; ++i)
						{
							g_fiber_pool->queue_job([=]
								{
									*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
									Object obj1 = OBJECT::CREATE_OBJECT(0xD75E01A6, fposition.x, fposition.y, fposition.z, 0, TRUE, false);
									*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;
									script::get_current()->yield(400ms);
									ENTITY::DELETE_ENTITY(&obj1);
								});
						}
						while (!STREAMING::HAS_MODEL_LOADED(0x66F34017))
						{
							STREAMING::REQUEST_MODEL(0x66F34017);
							script::get_current()->yield();
						}
						for (std::uint32_t i = 0; i < 12; ++i)
						{
							g_fiber_pool->queue_job([=]
								{
									*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
									Object obj = OBJECT::CREATE_OBJECT(0, 0x66F34017, fposition.x, fposition.y, fposition.z, 0, TRUE);
									*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;
									script::get_current()->yield(400ms);
									ENTITY::DELETE_ENTITY(&obj);
								});
						}
					});
				core->add_option<simple_option>(("Curry Crash"), nullptr, []
					{
						Player target = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player);
						Vector3 fposition = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(target, 0.0, 5.0, 0.0);
						while (!STREAMING::HAS_MODEL_LOADED(0xB5CF80E4))
						{
							STREAMING::REQUEST_MODEL(0xB5CF80E4);
							script::get_current()->yield();
						}
						for (std::uint32_t i = 0; i < 12; ++i)
						{
							g_fiber_pool->queue_job([=]
								{
									*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
									Ped ped = PED::CREATE_PED(0, 0xB5CF80E4, fposition.x, fposition.y, fposition.z, 0, TRUE, false);
									*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;
									script::get_current()->yield(400ms);
									ENTITY::DELETE_ENTITY(&ped);
								});
						}
					});
				core->add_option<simple_option>(("Next Gen Crash"), nullptr, []
					{
						Player target = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player);
						Vector3 fposition = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(target, 0.0, 5.0, 0.0);
						while (!STREAMING::HAS_MODEL_LOADED($("arbitergt")))
						{
							STREAMING::REQUEST_MODEL($("arbitergt"));
							script::get_current()->yield();
						}
						for (std::uint32_t i = 0; i < 12; ++i)
						{
							g_fiber_pool->queue_job([=]
								{
									*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
									Vehicle Veh = VEHICLE::CREATE_VEHICLE($("arbitergt"), fposition.x, fposition.y, fposition.z, 0.f, true, false, false);
									*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;
									script::get_current()->yield(400ms);
									ENTITY::DELETE_ENTITY(&Veh);
								});
						}
					});
				core->add_option<simple_option>(("Drip Crash"), nullptr, []
					{
						auto Ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player);
						Vector3 pos = ENTITY::GET_ENTITY_COORDS(Ped, 1);
						auto Crash1 = $("mp_m_freemode_01");
						auto Crash2 = $("mp_f_freemode_01");

						while (!STREAMING::HAS_MODEL_LOADED(Crash1)) {
							STREAMING::REQUEST_MODEL(Crash1);

							script::get_current()->yield(10ms);
						}
						while (!STREAMING::HAS_MODEL_LOADED(Crash2)) {
							STREAMING::REQUEST_MODEL(Crash2);

							script::get_current()->yield(10ms);
						}

						*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
						auto Male = PED::CREATE_PED(2, Crash1, pos.x, pos.y, pos.z, 0.f, TRUE, TRUE);
						PED::SET_PED_COMPONENT_VARIATION(Male, 0, 393, 0, 0);
						PED::SET_PED_COMPONENT_VARIATION(Male, 4, 144, 0, 0);
						PED::SET_PED_COMPONENT_VARIATION(Male, 6, 102, 0, 0);

						auto Female = PED::CREATE_PED(1, Crash2, pos.x, pos.y, pos.z, 0.f, TRUE, TRUE);
						PED::SET_PED_COMPONENT_VARIATION(Female, 0, 415, 0, 0);
						PED::SET_PED_COMPONENT_VARIATION(Female, 4, 151, 0, 0);
						PED::SET_PED_COMPONENT_VARIATION(Female, 6, 106, 0, 0);
						*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;
					});
				core->add_option<simple_option>(("Whale Crash"), nullptr, []
					{
						Player target = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player);
						Vector3 fposition = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(target, 0.0, 5.0, 0.0);
						while (!STREAMING::HAS_MODEL_LOADED(0x92991B72))
						{
							STREAMING::REQUEST_MODEL(0x92991B72);
							script::get_current()->yield();
						}
						*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
						PED::CREATE_PED(26, 0x92991B72, fposition.x, fposition.y, fposition.z, 0, TRUE, false);
						*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;
						Entity handle;
						Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target), false);
						PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false) ? handle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()) : handle = PLAYER::PLAYER_PED_ID();
						ENTITY::SET_ENTITY_COORDS(handle, coords.x, coords.y, coords.z, false, false, false, false);
						if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target), FALSE))
						{
							Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target), false);
							for (int i = -1; i < 16; i++)
							{
								if (VEHICLE::IS_VEHICLE_SEAT_FREE(veh, i, 0))
								{
									PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, i);
									return;
								}
							}
						}
						Hash model = MISC::GET_HASH_KEY("a_c_humpback");
						STREAMING::REQUEST_MODEL(model);
						while (!STREAMING::HAS_MODEL_LOADED(model))
						{
							STREAMING::REQUEST_MODEL(model);
							script::get_current()->yield();
						}
						PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), model);
					});
				core->add_option<simple_option>(("Monkey Crash"), nullptr, []
					{
						Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player);
						take_control_of(ped);

						Vector3 pos = ENTITY::GET_ENTITY_COORDS(ped, 1);
						Object x = SpawnObject(3613262246, pos.x, pos.y, pos.z, true);
						script::get_current()->yield(50ms);
						ENTITY::DELETE_ENTITY(&x);
						script::get_current()->yield(50ms);
					});
				core->add_option<simple_option>(("Gay Crash"), "must be in a vehicle", []
					{
						Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player);
						if (PED::IS_PED_IN_ANY_VEHICLE(ped, 1))
						{
							Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, FALSE);

							TASK::TASK_VEHICLE_TEMP_ACTION(ped, vehicle, 15, 100);
							TASK::TASK_VEHICLE_TEMP_ACTION(ped, vehicle, 16, 100);
							TASK::TASK_VEHICLE_TEMP_ACTION(ped, vehicle, 17, 100);
							TASK::TASK_VEHICLE_TEMP_ACTION(ped, vehicle, 18, 100);
						}
						else
						{
							ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Player is not in a vehicle" });
						}
					});
			});
	}

	void network_selected_crashes_menu::script_init() {}

	void network_selected_crashes_menu::script_on_tick()
	{

	}

	void network_selected_crashes_menu::script_func()
	{
		m_network_selected_crashes_menu.script_init();
		while (true)
		{


			m_network_selected_crashes_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}