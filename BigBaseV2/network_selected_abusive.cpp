#include "common.hpp"
#include "gta_util.hpp"
#include "network_selected_abusive.h"
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
#include "scroll.h"
#include "native_timer.h"
#include "util.h"
#include "caller.hpp"
using namespace big::network::selected_player::abusive::vars;


namespace big::network::selected_player::abusive::vars
{
    variables m_vars;

    void kick_from_vehicle(Player player) {
        Ped vic = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
        take_control_of(vic);
        TASK::CLEAR_PED_TASKS_IMMEDIATELY(vic);
        TASK::CLEAR_PED_TASKS(vic);
        TASK::CLEAR_PED_SECONDARY_TASK(vic);
    }
    void taze(Player player) {
        int currentAttempt = 0;
        int maxAttempts = 20;
        while (!ENTITY::IS_ENTITY_DEAD(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), 0))
        {
            if (currentAttempt >= maxAttempts)
            {
                break;
            }
            else
            {
                Vector3 destination = PED::GET_PED_BONE_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player),SKEL_ROOT, 0.0f, 0.0f, 0.0f);
                Vector3 origin = PED::GET_PED_BONE_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), SKEL_R_Hand, 0.0f, 0.0f, 0.2f);
                Hash tazerHash = MISC::GET_HASH_KEY("WEAPON_STUNGUN");
                MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(origin.x, origin.y, origin.z, destination.x, destination.y, destination.z, 1, 0, tazerHash, PLAYER::PLAYER_PED_ID(), false, false, 1);
                currentAttempt++;
            }
            script::get_current()->yield();
        }
    }
    void ragdoll(Player player) {
        call<int>(g_pointers->m_ragdoll, g_pointers->m_net_game_player(player)->m_player_id);
    }
    constexpr size_t patch_size = 24;
    static inline std::once_flag once_flag;
    static inline std::array<byte, patch_size> backup;
    static inline void setup_backup()
    {
        memcpy(backup.data(), g_pointers->m_world_model_spawn_bypass, patch_size);
    }
    inline Object SpawnObject(Hash hash, float x, float y, float z, bool is_networked = true)
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
    void glitch_physics(Player player) {
      
        uint32_t model = 0xd5c0bc07;
        Object guitar = SpawnObject(model, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), 1).x, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), 1).y, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), 1).z, true);
        if (ENTITY::DOES_ENTITY_EXIST(guitar)) {
            ENTITY::SET_ENTITY_VISIBLE(guitar, false, false);
            ENTITY::ATTACH_ENTITY_TO_ENTITY(guitar, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), PED::GET_PED_BONE_INDEX(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), 23553), 0.5f, -0.2f, 0.f, 0.f, 75.0f, 0.f, true, true, false, true, 1, true);
            ENTITY::SET_ENTITY_COLLISION(guitar, true, true);
        }
    }
    void rain_rockets(Player player) {
        int currentAttempt = 0;
        int maxAttempts = 20;
        while (!ENTITY::IS_ENTITY_DEAD(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), 0))
        {
            if (currentAttempt >= maxAttempts)
            {
                break;
            }
            else
            {
                uint32_t model = 0x13579279;
                Vector3 start_position = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), 1);
                start_position.x += MISC::GET_RANDOM_FLOAT_IN_RANGE(-20.f, 20.f);
                start_position.y += MISC::GET_RANDOM_FLOAT_IN_RANGE (-20.f, 20.f);
                Hash tazerHash = MISC::GET_HASH_KEY("WEAPON_STUNGUN");
                MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS_IGNORE_ENTITY(start_position.x, start_position.y, start_position.z + MISC::GET_RANDOM_FLOAT_IN_RANGE(50.f, 150.f), start_position.x, start_position.y, start_position.z, 250, 0, model, PLAYER::PLAYER_PED_ID(), true, false, 1000.f, PLAYER::PLAYER_PED_ID(), 0);
                currentAttempt++;
            }
            script::get_current()->yield();
        }
    }
    void set_wanted_level(Player player, int level) {
        PLAYER::REPORT_CRIME(g_pointers->m_net_game_player(player)->m_player_id, 8, PLAYER::GET_WANTED_LEVEL_THRESHOLD(level));
    }
    void set_on_fire(Player player) {
        Player fireloopedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
        Vector3 Pos = ENTITY::GET_ENTITY_COORDS(fireloopedplayer, true);
        FIRE::ADD_EXPLOSION(Pos.x, Pos.y, Pos.z - 2, 12, 5, true, 0, 0, 0);
    }
    void patch_blame(bool toggle)
    {
        *(unsigned short*)g_pointers->m_blame_explode = toggle ? 0xE990 : 0x850F;
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


    void network_selected_abusive_menu::menu()
    {
        using namespace ui;

        m_renderer.new_sub<PlayerSubmenu>(&selected_player, SubSelectedAbusive, [](PlayerSubmenu* core)
            {
                m_renderer.m_enable_player_info = true;
                core->add_option<submenu>("Attackers", nullptr, SubSelectedAbusiveAttackers);
                core->add_option<submenu>("Explosions", nullptr, SubSelectedAbusiveExplosions);
                core->add_option<submenu>("Increments", nullptr, SubSelectedAbusiveIncrements);

                core->add_option<toggle_option<bool>>(("Freeze"),
                    nullptr,
                    &m_vars.m_freeze
                );

                core->add_option<toggle_option<bool>>(("Explode"),
                    nullptr,
                    &m_vars.m_explode
                );

                core->add_option<toggle_option<bool>>(("Kick From Vehicle"),
                    nullptr,
                    &m_vars.m_kick_from_vehicle
                );

                core->add_option<toggle_option<bool>>(("Set on Fire"),
                    nullptr,
                    &m_vars.m_set_on_fire
                );

                core->add_option<toggle_option<bool>>(("Taze"),
                    nullptr,
                    &m_vars.m_taze
                );

                core->add_option<toggle_option<bool>>(("Ragdoll"),
                    nullptr,
                    &m_vars.m_ragdoll
                );

                core->add_option<toggle_option<bool>>(("Glitch Phyisics"),
                    "works best when theyre in a vehicle",
                    &m_vars.m_glitch_physics
                );

                core->add_option<toggle_option<bool>>(("Blame"),
                    nullptr,
                    &m_vars.m_blame
                );

                core->add_option<toggle_option<bool>>(("Rain Rockets"),
                    nullptr,
                    &m_vars.m_rain_rockets
                );

                core->add_option<toggle_option<bool>>(("Always Wanted"),
                    nullptr,
                    &m_vars.m_always_wanted
                );

                core->add_option<toggle_option<bool>>(("Ram"),
                    nullptr,
                    &m_vars.m_vehicle_ram
                );

                core->add_option<toggle_option<bool>>(("Clone"),
                    nullptr,
                    &m_vars.m_clone
                );

                core->add_option<simple_option>(("Ceo Kick"), nullptr, []
                    {
                        int64_t ceokick[4] = { -1425016400, PLAYER::PLAYER_ID(), 0, 0 };
                        g_pointers->m_trigger_script_event(1, ceokick, 4, 1 << selected_player);
                    });
                core->add_option<simple_option>(("Ceo Ban"), nullptr, []
                    {
                        int64_t ceoban[4] = { 1240068495, PLAYER::PLAYER_ID(), 0, 0 };
                        g_pointers->m_trigger_script_event(1, ceoban, 4, 1 << selected_player);
                    });
                core->add_option<simple_option>(("Force To Mission"), nullptr, []
                    {
                        int64_t force_to_mission[2] = { -283041276, PLAYER::PLAYER_ID() };
                        g_pointers->m_trigger_script_event(1, force_to_mission, 2, 1 << selected_player);

                        int64_t force_to_missionn[2] = { -1908874529, PLAYER::PLAYER_ID() };
                        g_pointers->m_trigger_script_event(1, force_to_missionn, 2, 1 << selected_player);
                    });
                core->add_option<simple_option>(("Force To Cutscene"), nullptr, []
                    {
                        int64_t cutscene[2] = { 2131601101, PLAYER::PLAYER_ID() };
                        g_pointers->m_trigger_script_event(1, cutscene, 2, 1 << selected_player);


                    });
                core->add_option<simple_option>(("Force To Cayo Perico"), nullptr, []
                    {
                        int64_t cayo[2] = { 1361475530, PLAYER::PLAYER_ID() };
                        g_pointers->m_trigger_script_event(1, cayo, 2, 1 << selected_player);


                    });
                core->add_option<simple_option>(("Rotate Cam"), nullptr, []
                    {

                        int64_t rot_cam[2] = { -1388926377, PLAYER::PLAYER_ID() };
                        g_pointers->m_trigger_script_event(1, rot_cam, 2, 1 << selected_player);
                    });

                core->add_option<simple_option>(("Banner Effect"), nullptr, []
                    {

                        int64_t banner[4] = { 145637109, PLAYER::PLAYER_ID(), 0, 0 };
                        g_pointers->m_trigger_script_event(1, banner, 4, 1 << selected_player);
                    });
            });
    }

    void network_selected_abusive_menu::script_init() {}

    void network_selected_abusive_menu::script_on_tick()
    {
        Vector3 m_coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), 1);
        if (m_vars.m_freeze) {
            TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player));
        }
        if (m_vars.m_explode) {
            FIRE::ADD_EXPLOSION(m_coords.x, m_coords.y, m_coords.z, 0, 10.f, true, false, 0.f, false);
        }
        if (m_vars.m_kick_from_vehicle) {
             timers::run_timed(&m_vars.m_kick_from_vehicle_timer, 1000, [&] {
                kick_from_vehicle(selected_player);
             });
        }
        if (m_vars.m_taze) {
            timers::run_timed(&m_vars.m_taze_timer, 5000, [&] {
                taze(selected_player);
            });
        }
        if (m_vars.m_ragdoll) {
            timers::run_timed(&m_vars.m_taze_timer, 1000, [&] {
                ragdoll(selected_player);
            });
        }
        if (m_vars.m_glitch_physics) {
            menu::timers::run_timed(&m_vars.m_glitch_physics_timer, 1000, [&] {
                Object guitar = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(m_coords.x, m_coords.y, m_coords.z, 5.f, 0xd5c0bc07, false, false, false);
                if (!guitar || !ENTITY::DOES_ENTITY_EXIST(guitar) || !ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(guitar, PLAYER::PLAYER_PED_ID())) {
                    glitch_physics(selected_player);
                }
                });
        }
        if (m_vars.m_rain_rockets) {
            timers::run_timed(&m_vars.m_rain_rockets_timer, 750, [&] {
                rain_rockets(selected_player);
            });
        }
        if (m_vars.m_always_wanted) {
            set_wanted_level(selected_player, 5);
        }
        if (m_vars.m_set_on_fire) {
            timers::run_timed(&m_vars.m_set_on_fire_timer, 5000, [&] {
                set_on_fire(selected_player);
            });
        }
        if (m_vars.m_blame) {
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
        }
        if (m_vars.m_clone) {
            auto vic = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player);
            if (ENTITY::DOES_ENTITY_EXIST(vic)) {
                *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
                PED::CLONE_PED(vic, 1, 1, 1);
                *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;
            }
        }
        if (m_vars.m_vehicle_ram) {
            timers::run_timed(&m_vars.m_set_on_fire_timer, 2500, [&] {
                ram();
            });
        }
    }

    void network_selected_abusive_menu::script_func()
    {
        m_network_selected_abusive_menu.script_init();
        while (true)
        {
            m_network_selected_abusive_menu.script_on_tick();
            script::get_current()->yield();
        }
    }
}