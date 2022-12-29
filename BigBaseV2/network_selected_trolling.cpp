#include "common.hpp"
#include "gta_util.hpp"
#include "network_selected_trolling.h"
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
#include "util.h"
#include "gta/PickupRewards.h"
using namespace big::network::selected_player::trolling::vars;


namespace big::network::selected_player::trolling::vars
{
    variables m_vars;
	void patch_blame(bool toggle)
	{
		*(unsigned short*)g_pointers->m_blame_explode = toggle ? 0xE990 : 0x850F;
	}
	void give_collectible(Player target, eCollectibleType col, int index = 0, bool uncomplete = false)
	{
		const size_t arg_count = 7;
		int64_t args[arg_count] = {
			(uint64_t)-1178972880,
			(uint64_t)PLAYER::PLAYER_ID(),
			(uint64_t)col, // iParam0
			(uint64_t)index, // iParam1
			!uncomplete, // bParam2
			true,
			0  // bParam3
		};

		g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target);
	}
	void turn_player_into_animal(Player target)
	{
		for (int i = 0; i < 30; i++)
		{
			give_collectible(target, eCollectibleType::Treat, 0, false);
			give_collectible(target, eCollectibleType::Treat, 0, true);
			g_pointers->m_give_pickup_rewards(1 << target, REWARD_HEALTH);
			g_pointers->m_give_pickup_rewards(1 << target, REWARD_ARMOUR);
			script::get_current()->yield(400ms);
			Ped playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target);
			Hash model = ENTITY::GET_ENTITY_MODEL(playerPed);
			if (model != $("mp_m_freemode_01") && model != $("mp_f_freemode_01"))
				return;
			if (ENTITY::IS_ENTITY_DEAD(playerPed, FALSE))
				script::get_current()->yield(7s);
		}
	}
	int ram()
	{
		std::string model = "INSURGENT";
		if (const Hash hash = rage::joaat(model.data()); hash)
		{
			for (uint8_t i = 0; !STREAMING::HAS_MODEL_LOADED(hash) && i < 100; i++)
			{
				STREAMING::REQUEST_MODEL(hash);

				script::get_current()->yield();
			}
			if (!STREAMING::HAS_MODEL_LOADED(hash))
			{
				LOG(INFO) << "model hasnt loaded";
				return -1;
			}


			Vector3 dim1, dim2;
			MISC::GET_MODEL_DIMENSIONS(hash, &dim1, &dim2);

			Vector3 pCoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(big::selected_player), 0.0, -10.0, 0.0);
			float offset;
			offset = dim2.y * 1.6;

			Vector3 dir = ENTITY::GET_ENTITY_FORWARD_VECTOR(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(big::selected_player));
			float rot = (ENTITY::GET_ENTITY_ROTATION(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(big::selected_player), 0)).z;
			pCoords.x + (dir.x * offset);
			pCoords.y + (dir.y * offset);

			*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
			Vehicle veh = VEHICLE::CREATE_VEHICLE(hash, pCoords.x, pCoords.y, pCoords.z, rot, true, false, false);
			*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

			script::get_current()->yield();

			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);




			VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh, 0);
			ENTITY::SET_ENTITY_VISIBLE(veh, true, 0);
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 1000.0);

			if (*g_pointers->m_is_session_started)
			{
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


    void network_selected_trolling_menu::menu()
    {
        using namespace ui;

        m_renderer.new_sub<PlayerSubmenu>(&selected_player, SubSelectedTrolling, [](PlayerSubmenu* core)
            {
                m_renderer.m_enable_player_info = true;
                core->add_option<submenu>("Entity Spammer", nullptr, SubSelectedTrollingEntitySpammer);
                core->add_option<submenu>("Notifications", nullptr, SubSelectedTrollingNotifications);
                core->add_option<toggle_option<bool>>(("Sound Spam"),
                    nullptr,
                    &m_vars.m_sound_spam
                    );
				core->add_option<simple_option>(("Explode"), nullptr, []
					{
						Vector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), 0);
						FIRE::ADD_EXPLOSION(c.x, c.y, c.z, 37, 1000, true, false, true, false);
					});
				core->add_option<simple_option>(("Kick From Vehicle"), nullptr, []
					{
						int64_t args[2] = { -714268990, selected_player };
						g_pointers->m_trigger_script_event(1, args, 2, 1 << selected_player);

						Ped vic = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player);
						take_control_of(vic);
						TASK::CLEAR_PED_TASKS_IMMEDIATELY(vic);
						TASK::CLEAR_PED_TASKS(vic);
						TASK::CLEAR_PED_SECONDARY_TASK(vic);
					});
				core->add_option<simple_option>(("Set On Fire"), nullptr, []
					{
						Player fireloopedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player);
						Vector3 Pos = ENTITY::GET_ENTITY_COORDS(fireloopedplayer, true);
						FIRE::ADD_EXPLOSION(Pos.x, Pos.y, Pos.z - 2, 12, 5, true, 0, 0, 0);
					});
				core->add_option<simple_option>(("Taze"), nullptr, []
					{
						int currentAttempt = 0;
						int maxAttempts = 20;
						while (!ENTITY::IS_ENTITY_DEAD(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), 0))
						{
							if (currentAttempt >= maxAttempts)
							{
								break;
							}
							else
							{
								Vector3 destination = PED::GET_PED_BONE_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), SKEL_ROOT, 0.0f, 0.0f, 0.0f);
								Vector3 origin = PED::GET_PED_BONE_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), SKEL_R_Hand, 0.0f, 0.0f, 0.2f);
								Hash tazerHash = MISC::GET_HASH_KEY("WEAPON_STUNGUN");
								MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(origin.x, origin.y, origin.z, destination.x, destination.y, destination.z, 1, 0, tazerHash, PLAYER::PLAYER_PED_ID(), false, false, 1);
								currentAttempt++;
							}
							script::get_current()->yield();
						}
					});
				core->add_option<simple_option>(("Ragdoll"), nullptr, []
					{
						PED::SET_PED_CAN_RAGDOLL(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), true);
						PED::SET_PED_TO_RAGDOLL(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), 1, -1, 1, 1, 1, 0);
					});

				core->add_option<simple_option>(("Turn into Animal"), nullptr, []
					{
						turn_player_into_animal(selected_player);
					});
				core->add_option<simple_option>(("Glitch Physics"), "Must Be In Vehicle", []
					{
						NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), true));
						if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), true)))
						{
							ENTITY::APPLY_FORCE_TO_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), true), 1, 0, 0, 20, 0, 0, 0, 1, false, true, true, true, true);
						}
					});
				core->add_option<simple_option>(("Blame"), nullptr, []
					{
						Player victim = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player);
						patch_blame(true);
						for (int i = 0; i < 33; i++) {
							Player targetPlayers = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
							Vector3 playerCoords = coordsOf(targetPlayers);
							if (targetPlayers != victim) {
								FIRE::ADD_OWNED_EXPLOSION(victim, playerCoords.x, playerCoords.y, playerCoords.z, 1, 10.0f, true, false, 0.f);
							}
						}
						patch_blame(false);
					});

				core->add_option<simple_option>(("Ram"), nullptr, []
					{
						ram();
					});
				core->add_option<simple_option>(("Rain Rockets"), nullptr, []
					{
						Vector3 Strike = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), 0);
						Hash weaponAssetRocket = $("WEAPON_VEHICLE_ROCKET");
						if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
						{
							WEAPON::REQUEST_WEAPON_ASSET(weaponAssetRocket, 31, 0);
						}

						MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Strike.x, Strike.y, Strike.z + 20.f, Strike.x, Strike.y, Strike.z, 100, 1, weaponAssetRocket, selected_player, 1, 0, 1000.0);
					});
				core->add_option<simple_option>(("Shake Cam"), nullptr, []
					{
						Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), false);
						FIRE::ADD_EXPLOSION(pos.x, pos.y, pos.z, 4, 0.f, false, true, 10000.f, true);
					});
				core->add_option<simple_option>(("Clone"), nullptr, []
					{
						Ped playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player);
						TASK::CLEAR_PED_TASKS_IMMEDIATELY(playerPed);
						Vector3 pos = ENTITY::GET_ENTITY_COORDS(playerPed, true);
						*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
						PED::CLONE_PED(playerPed, 1, 1, 1);
						*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;
					});



				core->add_option<simple_option>(("Small Cage"), nullptr, []
					{
						Ped playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player);
						TASK::CLEAR_PED_TASKS_IMMEDIATELY(playerPed);
						Vector3 pos = ENTITY::GET_ENTITY_COORDS(playerPed, true);
						*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
						OBJECT::CREATE_OBJECT(rage::joaat("prop_gold_cont_01"), pos.x, pos.y, pos.z - 1.f, true, false, false);
						*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;
					});
				core->add_option<simple_option>(("Big Cage"), nullptr, []
					{
						Player ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player);
						Vector3 c = ENTITY::GET_ENTITY_COORDS(ped, true);
						Hash hash = rage::joaat("stt_prop_stunt_tube_l");
						TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);
						*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
						Object cage = OBJECT::CREATE_OBJECT_NO_OFFSET(hash, c.x, c.y, c.z, true, false, false);
						*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;
						ENTITY::SET_ENTITY_ROTATION(cage, 0.0, 90.0, 0.0, 1, true);

					});
            });
    }

    void network_selected_trolling_menu::script_init() {}

    void network_selected_trolling_menu::script_on_tick()
    {
        if (m_vars.m_sound_spam) {
			int64_t sound_spam[3] = { 1111927333, PLAYER::PLAYER_ID(), 5};
            g_pointers->m_trigger_script_event(1, sound_spam, 3, 1 << selected_player);
        }
    }

    void network_selected_trolling_menu::script_func()
    {
        m_network_selected_trolling_menu.script_init();
        while (true)
        {


            m_network_selected_trolling_menu.script_on_tick();
            script::get_current()->yield();
        }
    }
}