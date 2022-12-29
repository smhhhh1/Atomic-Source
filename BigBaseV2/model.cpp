#include "common.hpp"
#include "gta_util.hpp"
#include "model.h"
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
namespace big::menu
{
	void applyChosenSkin(const char* To_Change)
	{
		Hash Model_To_Change = rage::joaat(To_Change);
		{

			Vector3 Coordinates = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
			Coordinates.x + 2;
			if (STREAMING::IS_MODEL_IN_CDIMAGE(Model_To_Change))
			{
				if (!STREAMING::HAS_MODEL_LOADED(Model_To_Change)) {
					STREAMING::REQUEST_MODEL(Model_To_Change);

					script::get_current()->yield();
				}
				if (!STREAMING::HAS_MODEL_LOADED(Model_To_Change))
				{

					LOG(INFO) << "Invalid Ped Model";
					return;
				}

				if (STREAMING::IS_MODEL_VALID(Model_To_Change))
				{
					*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
					Ped PED_Spawn = PED::CREATE_PED(26, Model_To_Change, Coordinates.x, Coordinates.y, Coordinates.z, 0, true, true);
					*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

					script::get_current()->yield();

					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(Model_To_Change);
					if (*g_pointers->m_is_session_started) {
						NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PED_Spawn);
						auto NET_ID = NETWORK::PED_TO_NET(PED_Spawn);
						DECORATOR::DECOR_SET_INT(PED_Spawn, (char*)"MPBitset", 0);
						NETWORK::NETWORK_REGISTER_ENTITY_AS_NETWORKED(PED_Spawn);
						ENTITY::_SET_ENTITY_SOMETHING(PED_Spawn, false);
						if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(PED_Spawn))
							NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(NET_ID, true);
						ENTITY::SET_ENTITY_AS_MISSION_ENTITY(PED_Spawn, true, true);
						NETWORK::SET_NETWORK_ID_CAN_MIGRATE(NETWORK::PED_TO_NET(PED_Spawn), TRUE);

						if (!DECORATOR::DECOR_EXIST_ON(PED_Spawn, "MissionType"))
						{
							DECORATOR::DECOR_REGISTER("MissionType", 3);
							DECORATOR::DECOR_SET_INT(PED_Spawn, "MissionType", 0);

						}
					}

					Ped PED_TO_DELETE = PLAYER::PLAYER_PED_ID();
					PLAYER::CHANGE_PLAYER_PED(PLAYER::PLAYER_ID(), PED_Spawn, true, true);
					ENTITY::SET_ENTITY_ALPHA(PED_Spawn, 255, 0);
					ENTITY::SET_ENTITY_VISIBLE(PED_Spawn, true, 1);
					ENTITY::DELETE_ENTITY(&PED_TO_DELETE);
				}
			}
		}
	}



	void model_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Model Changers", SubModel, [](sub* core)
			{
				core->add_option<submenu>("Popular", nullptr, SubModelPopular);
				core->add_option<submenu>("Animal", nullptr, SubModelAnimal);
				core->add_option<submenu>("Emergency", nullptr, SubModelEmergency);
				core->add_option<submenu>("Role", nullptr, SubModelRole);
				core->add_option<submenu>("Ambient", nullptr, SubModelAmbient);
				core->add_option<submenu>("Misc", nullptr, SubModelMisc);

			});
		m_renderer.new_sub<sub>("Popular Models", SubModelPopular, [](sub* core)
			{
				for (auto model : lists::g_ped_model_popular)
				{
					core->add_option<simple_option>(model, nullptr, [model] { g_fiber_pool->queue_job([model] { applyChosenSkin(model); }); });
				}

			});
		m_renderer.new_sub<sub>("Story Mode Models", SubModelStory, [](sub* core)
			{
				for (auto model : lists::g_ped_model_story)
				{
					core->add_option<simple_option>(model, nullptr, [model] { g_fiber_pool->queue_job([model] { applyChosenSkin(model); }); });
				}

			});
		m_renderer.new_sub<sub>("Animal Models", SubModelAnimal, [](sub* core)
			{
				for (auto model : lists::g_ped_model_animal)
				{
					core->add_option<simple_option>(model, nullptr, [model] { g_fiber_pool->queue_job([model] { applyChosenSkin(model); }); });
				}

			});
		m_renderer.new_sub<sub>("Emergency Models", SubModelEmergency, [](sub* core)
			{
				for (auto model : lists::g_ped_model_emergency)
				{
					core->add_option<simple_option>(model, nullptr, [model] { g_fiber_pool->queue_job([model] { applyChosenSkin(model); }); });
				}

			});
		m_renderer.new_sub<sub>("Role Models", SubModelRole, [](sub* core)
			{
				for (auto model : lists::g_ped_model_role)
				{
					core->add_option<simple_option>(model, nullptr, [model] { g_fiber_pool->queue_job([model] { applyChosenSkin(model); }); });
				}

			});
		m_renderer.new_sub<sub>("Ambient Models", SubModelAmbient, [](sub* core)
			{
				for (auto model : lists::g_ped_model_ambient)
				{
					core->add_option<simple_option>(model, nullptr, [model] { g_fiber_pool->queue_job([model] { applyChosenSkin(model); }); });
				}

			});
		m_renderer.new_sub<sub>("Misc Models", SubModelMisc, [](sub* core)
			{
				for (auto model : lists::g_ped_model_misc)
				{
					core->add_option<simple_option>(model, nullptr, [model] { g_fiber_pool->queue_job([model] { applyChosenSkin(model); }); });
				}

			});
	}

	void model_menu::script_init() {}

	void model_menu::script_on_tick() {}

	void model_menu::script_func()
	{
		m_model_menu.script_init();
		while (true)
		{
			m_model_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}