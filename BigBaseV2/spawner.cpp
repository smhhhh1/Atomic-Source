#include "common.hpp"
#include "gta_util.hpp"
#include "spawner.h"
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
#include "../submenus.h"
#include "on_screen_ped.h"
#include "lists.h"
#include "fiber_pool.hpp"
#include "notify.h"
#include "script_global.hpp"
using namespace big::vehicle::spawner::vars;

namespace big::vehicle::spawner::vars
{
	variables m_vars;
	int spawn(std::string_view model)
	{


		if (const Hash hash = rage::joaat(model.data()); hash)
		{
			for (uint8_t i = 0; !STREAMING::HAS_MODEL_LOADED(hash) && i < 100; i++)
			{
				STREAMING::REQUEST_MODEL(hash);

				script::get_current()->yield();
			}
			if (!STREAMING::HAS_MODEL_LOADED(hash))
			{
				LOG(INFO) << "Invalid Vehicle Model";
				return -1;
			}
			bool isFlyingVehicle = VEHICLE::IS_THIS_MODEL_A_PLANE(hash);
			Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
			*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
			Vehicle veh = VEHICLE::CREATE_VEHICLE(hash, pos.x, pos.y, pos.z, 0.0f, true, false, false);
			*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

			script::get_current()->yield();

			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
			if (m_vars.m_notification)
				ImGui::InsertNotification({ ImGuiToastType_None, 2600, "spawned %s", HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(hash)) });

			if (m_vars.m_spawn_inside)
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);

			if (m_vars.m_spawned_max)
			{
				VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
				VEHICLE::TOGGLE_VEHICLE_MOD(veh, 18 /* Turbo */, TRUE);
				VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20 /* Tire Smoke */, TRUE);
				VEHICLE::TOGGLE_VEHICLE_MOD(veh, 17 /* Xenon Headlights */, TRUE);
				VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, 1);
				VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, false);
				for (int i = 0; i < 50; i++)
				{
					VEHICLE::SET_VEHICLE_MOD(veh, i, VEHICLE::GET_NUM_VEHICLE_MODS(veh, i) - 1, true);
				}
			}
			if (m_vars.m_spawn_air_vehicles_in_air && isFlyingVehicle) {
				ENTITY::SET_ENTITY_COORDS(veh, pos.x, pos.y, pos.z + m_vars.m_spawn_height, false, false, false, false);
				VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, true, false);
			}

			if (m_vars.m_godmode)
			{
				ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), m_vars.m_godmode);
			}

			if (m_vars.m_particleFX)
			{
				STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
				GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");
				GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE("scr_clown_appears", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 31086, 0.50, 0, 0, 0);
			}

			if (*g_pointers->m_is_session_started)
			{
				*script_global(4539659).as<bool*>() = true;
				DECORATOR::DECOR_SET_INT(veh, "MPBitset", 0);
				ENTITY::_SET_ENTITY_SOMETHING(veh, true);
				int networkId = NETWORK::VEH_TO_NET(veh);
				if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(veh))
					NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
				VEHICLE::SET_VEHICLE_IS_STOLEN(veh, false);
			}

			return veh;
		}

		return -1;
	}

}

namespace big::menu
{


	void spawner_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Spawner", SubSpawner, [](sub* core)
			{
				core->add_option<submenu>("Settings", nullptr, SubSpawnerSettings);
				core->add_option<break_option>(std::move(break_option()
					.SetRightText("Categories"))
					);
				core->add_option<submenu>(("Contract DLC"), nullptr, Spawner_ContractDLC);
				core->add_option<submenu>(("Cayo Perico Heist"), nullptr, Spawner_Cayo);
				core->add_option<submenu>(("Los Santos Summer"), nullptr, Spawner_Los_Summer);
				core->add_option<submenu>(("Diamond Casino Heist"), nullptr, Spawner_Casino);
				core->add_option<submenu>(("Super"), nullptr, Spawner_Super);
				core->add_option<submenu>(("Sports"), nullptr, Spawners_Sports);
				core->add_option<submenu>(("Sports Classic"), nullptr, Spawner_Classic);
				core->add_option<submenu>(("Offroad"), nullptr, Spawner_offroad);
				core->add_option<submenu>(("Sedans"), nullptr, Spawner_Sedans);
				core->add_option<submenu>(("Coupes"), nullptr, Spawner_Coups);
				core->add_option<submenu>(("Muscle"), nullptr, Spawner_Muscle);
				core->add_option<submenu>(("Boats"), nullptr, Spawner_Boats);
				core->add_option<submenu>(("Commercial"), nullptr, Spawner_commercial);
				core->add_option<submenu>(("Compacts"), nullptr, Spawner_Compacts);
				core->add_option<submenu>(("Cycles"), nullptr, Spawner_Cycles);
				core->add_option<submenu>(("Emergency"), nullptr, Spawner_Emergency);
				core->add_option<submenu>(("Helicopters"), nullptr, Spawner_Helicopters);
				core->add_option<submenu>(("Industrial"), nullptr, Spawner_Industrial);
				core->add_option<submenu>(("Military"), nullptr, Spawner_Military);
				core->add_option<submenu>(("Motorcycles"), nullptr, Spawner_Motorcycles);
				core->add_option<submenu>(("Planes"), nullptr, Spawner_Planes);
				core->add_option<submenu>(("Service"), nullptr, Spawner_Service);
				core->add_option<submenu>(("SUV"), nullptr, Spawner_Suv);
				core->add_option<submenu>(("Trailer"), nullptr, Spawner_Trailer);
				core->add_option<submenu>(("Trains"), nullptr, Spawner_Train);
				core->add_option<submenu>(("Utility"), nullptr, Spawner_Utility);
			});
		m_renderer.new_sub<sub>(("Spawn Settings"), SubSpawnerSettings, [](sub* core)
			{

				core->add_option<toggle_option<bool>>(("Notification"),
					nullptr,
					&m_vars.m_notification
					);
				core->add_option<toggle_option<bool>>(("Teleport Inside"),
					nullptr,
					&m_vars.m_spawn_inside
					);
				core->add_option<toggle_option<bool>>(("Godmode"),
					nullptr,
					&m_vars.m_spawn_inside
					);
				core->add_option<toggle_option<bool>>(("Air Vehicles In Air"),
					nullptr,
					&m_vars.m_spawn_air_vehicles_in_air
					);
				core->add_option<number_option<int>>(("Air Vehicles Height"),
					nullptr,
					&m_vars.m_spawn_height, 0,
					300, 10,
					2
					);
				core->add_option<toggle_option<bool>>(("Spawn Upgraded"),
					nullptr,
					&m_vars.m_spawned_max
					);

			});
		m_renderer.new_sub<sub>("Utility", Spawner_Utility, [](sub* core)
			{

				for (auto&& veh : lists::Utility1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>("Train", Spawner_Train, [](sub* core)
			{

				for (auto&& veh : lists::Trains1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});

				}
			});
		m_renderer.new_sub<sub>("Trailer", Spawner_Trailer, [](sub* core)
			{

				for (auto&& veh : lists::Trailer1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>("Suv", Spawner_Suv, [](sub* core)
			{

				for (auto&& veh : lists::SUVs1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>("Service", Spawner_Service, [](sub* core)
			{

				for (auto&& veh : lists::Service1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>("Planes", Spawner_Planes, [](sub* core)
			{

				for (auto&& veh : lists::Planes1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>("Motorcycles", Spawner_Motorcycles, [](sub* core)
			{

				for (auto&& veh : lists::Motorcycles1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>("Military", Spawner_Military, [](sub* core)
			{

				for (auto&& veh : lists::Military1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>("Industrial", Spawner_Industrial, [](sub* core)
			{

				for (auto&& veh : lists::Industrial1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>("Helicopters", Spawner_Helicopters, [](sub* core)
			{

				for (auto&& veh : lists::Helicopters1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>("Emergency", Spawner_Emergency, [](sub* core)
			{

				for (auto&& veh : lists::Emergency1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>("Cycles", Spawner_Cycles, [](sub* core)
			{

				for (auto&& veh : lists::Cycles1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>("Compacts", Spawner_Compacts, [](sub* core)
			{

				for (auto&& veh : lists::Compacts1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>("commercial", Spawner_commercial, [](sub* core)
			{

				for (auto&& veh : lists::Commercial1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>("Boats", Spawner_Boats, [](sub* core)
			{

				for (auto&& veh : lists::Boats1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>("Muscle", Spawner_Muscle, [](sub* core)
			{

				for (auto&& veh : lists::Muscle1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>("Coups", Spawner_Coups, [](sub* core)
			{

				for (auto&& veh : lists::Coupes1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>("Sedans", Spawner_Sedans, [](sub* core)
			{

				for (auto&& veh : lists::Sedans1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>("offroad", Spawner_offroad, [](sub* core)
			{

				for (auto&& veh : lists::OffRoad1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>("Classic", Spawner_Classic, [](sub* core)
			{

				for (auto&& veh : lists::SportsClassics1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>("Sports", Spawners_Sports, [](sub* core)
			{

				for (auto&& veh : lists::Sports1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>("Super", Spawner_Super, [](sub* core)
			{

				for (auto&& veh : lists::Super1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>("Casino", Spawner_Casino, [](sub* core)
			{

				for (auto&& veh : lists::casinoheists) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>("Los_Summer", Spawner_Los_Summer, [](sub* core)
			{

				for (auto&& veh : lists::lossummers) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}


			});
		m_renderer.new_sub<sub>("Cayo", Spawner_Cayo, [](sub* core)
			{

				for (auto&& veh : lists::CayoPericoHeistVehicles) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}


			});
		m_renderer.new_sub<sub>("ContractDLC", Spawner_ContractDLC, [](sub* core)
			{

				for (auto&& veh : lists::Contract) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}


			});
	}

	void spawner_menu::script_init() {}

	void spawner_menu::script_on_tick() {}

	void spawner_menu::script_func()
	{
		m_spawner_menu.script_init();
		while (true)
		{
			m_spawner_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}