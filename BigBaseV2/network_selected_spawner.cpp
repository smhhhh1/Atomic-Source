#include "common.hpp"
#include "gta_util.hpp"
#include "network_selected_spawner.h"
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

namespace big::menu
{

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
				//g_notification_service->push_warning("Spawn", "Failed to spawn model, did you give an incorrect model?");
				LOG(INFO) << "Invalid Vehicle Model";
				return -1;
			}
			Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), true);
			*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
			Vehicle veh = VEHICLE::CREATE_VEHICLE(hash, pos.x, pos.y, pos.z, 0.0f, true, false, false);
			*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

			script::get_current()->yield();

			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);

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
	void network_selected_spawner_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<PlayerSubmenu>(&selected_player, SubSelectedSpawner, [](PlayerSubmenu* core)
			{
				m_renderer.m_enable_player_info = true;
				core->add_option<submenu>(("Contract DLC"), nullptr, Remote_ContractDLC);
				core->add_option<submenu>(("Cayo Perico Heist"), nullptr, Remote_Cayo);
				core->add_option<submenu>(("Los Santos Summer"), nullptr, Remote_Los_Summer);
				core->add_option<submenu>(("Diamond Casino Heist"), nullptr, Remote_Casino);

				core->add_option<submenu>(("Super"), nullptr, Remote_Super);
				core->add_option<submenu>(("Sports"), nullptr, Remotes_Sports);
				core->add_option<submenu>(("Sports Classic"), nullptr, Remote_Classic);
				core->add_option<submenu>(("Offroad"), nullptr, Remote_offroad);
				core->add_option<submenu>(("Sedans"), nullptr, Remote_Sedans);
				core->add_option<submenu>(("Coupes"), nullptr, Remote_Coups);
				core->add_option<submenu>(("Muscle"), nullptr, Remote_Muscle);
				core->add_option<submenu>(("Boats"), nullptr, Remote_Boats);
				core->add_option<submenu>(("Commercial"), nullptr, Remote_commercial);
				core->add_option<submenu>(("Compacts"), nullptr, Remote_Compacts);
				core->add_option<submenu>(("Cycles"), nullptr, Remote_Cycles);
				core->add_option<submenu>(("Emergency"), nullptr, Remote_Emergency);
				core->add_option<submenu>(("Helicopters"), nullptr, Remote_Helicopters);
				core->add_option<submenu>(("Industrial"), nullptr, Remote_Industrial);
				core->add_option<submenu>(("Military"), nullptr, Remote_Military);
				core->add_option<submenu>(("Motorcycles"), nullptr, Remote_Motorcycles);
				core->add_option<submenu>(("Planes"), nullptr, Remote_Planes);
				core->add_option<submenu>(("Service"), nullptr, Remote_Service);
				core->add_option<submenu>(("SUV"), nullptr, Remote_Suv);
				core->add_option<submenu>(("Trailer"), nullptr, Remote_Trailer);
				core->add_option<submenu>(("Trains"), nullptr, Remote_Train);
				core->add_option<submenu>(("Utility"), nullptr, Remote_Utility);
			});
		m_renderer.new_sub<sub>(("Utility"), Remote_Utility, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				for (auto&& veh : lists::Utility1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>(("Train"), Remote_Train, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				for (auto&& veh : lists::Trains1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>(("Trailer"), Remote_Trailer, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				for (auto&& veh : lists::Trailer1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>(("Suv"), Remote_Suv, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				for (auto&& veh : lists::SUVs1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>(("Service"), Remote_Service, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				for (auto&& veh : lists::Service1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>(("Planes"), Remote_Planes, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				for (auto&& veh : lists::Planes1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>(("Motorcycles"), Remote_Motorcycles, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				for (auto&& veh : lists::Motorcycles1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>(("Military"), Remote_Military, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				for (auto&& veh : lists::Military1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>(("Industrial"), Remote_Industrial, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				for (auto&& veh : lists::Industrial1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>(("Helicopters"), Remote_Helicopters, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				for (auto&& veh : lists::Helicopters1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>(("Emergency"), Remote_Emergency, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				for (auto&& veh : lists::Emergency1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>(("Cycles"), Remote_Cycles, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				for (auto&& veh : lists::Cycles1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>(("Compacts"), Remote_Compacts, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				for (auto&& veh : lists::Compacts1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>(("commercial"), Remote_commercial, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				for (auto&& veh : lists::Commercial1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>(("Boats"), Remote_Boats, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				for (auto&& veh : lists::Boats1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>(("Muscle"), Remote_Muscle, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				for (auto&& veh : lists::Muscle1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>(("Coups"), Remote_Coups, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				for (auto&& veh : lists::Coupes1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>(("Sedans"), Remote_Sedans, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				for (auto&& veh : lists::Sedans1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>(("offroad"), Remote_offroad, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				for (auto&& veh : lists::OffRoad1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>(("Classic"), Remote_Classic, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				for (auto&& veh : lists::SportsClassics1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>(("Sports"), Remotes_Sports, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				for (auto&& veh : lists::Sports1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>(("Super"), Remote_Super, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				for (auto&& veh : lists::Super1) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>(("Casino"), Remote_Casino, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				for (auto&& veh : lists::casinoheists) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}
			});
		m_renderer.new_sub<sub>(("Los_Summer"), Remote_Los_Summer, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				for (auto&& veh : lists::lossummers) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}


			});
		m_renderer.new_sub<sub>(("Cayo"), Remote_Cayo, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				for (auto&& veh : lists::CayoPericoHeistVehicles) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}


			});
		m_renderer.new_sub<sub>(("ContractDLC"), Remote_ContractDLC, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				for (auto&& veh : lists::Contract) {
					core->add_option<simple_option>(veh, nullptr, [=]
						{

							spawn(veh);

						});
				}


			});
	}

	void network_selected_spawner_menu::script_init() {}

	void network_selected_spawner_menu::script_on_tick()
	{
	}

	void network_selected_spawner_menu::script_func()
	{
		m_network_selected_spawner_menu.script_init();
		while (true)
		{


			m_network_selected_spawner_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}