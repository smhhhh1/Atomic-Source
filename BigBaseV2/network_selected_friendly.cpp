#include "common.hpp"
#include "gta_util.hpp"
#include "network_selected_friendly.h"
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
using namespace big::network::selected_player::friendly::vars;


namespace big::network::selected_player::friendly::vars
{
    variables m_vars;

    const char* commend[] = {
        "Friendly", "Helpful"

    };

    const char* commend_stat[] = {
        "MPPLY_FRIENDLY", "MPPLY_HELPFUL"
    }; std::size_t commend_id = 0;

    void copy_outfit()
    {
        for (int i = 0; i < 12; i++)
        {
            PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), i, PED::GET_PED_DRAWABLE_VARIATION(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(big::selected_player), i), PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(big::selected_player), i), PED::GET_PED_PALETTE_VARIATION(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(big::selected_player), i));
            for (int i = 0; i < 2; i++) {
                script::get_current()->yield();
            }
        }
    }
    
    void give_all_weapons()
    {
        int Weapons[] = { 0x92A27487, 0x958A4A8F, 0xF9E6AA4B, 0x84BD7BFD, 0x8BB05FD7, 0x440E4788, 0x4E875F73, 0xF9DCBF2D, 0xD8DF3C3C, 0x99B507EA, 0xDD5DF8D9, 0xDFE37640, 0x678B81B1, 0x19044EE0, 0xCD274149, 0x94117305, 0x3813FC08, 0x1B06D571,  0xBFE256D4, 0x5EF9FEC4, 0x22D8FE39, 0x3656C8C1, 0x99AEEB3B, 0xBFD21232, 0x88374054 ,0xD205520E, 0x83839C4, 0x47757124, 0xDC4DB296, 0xC1B3C3D1, 0xCB96392F, 0x97EA20B8, 0xAF3696A1, 0x2B5EF5EC, 0x917F6C8C, 0x57A4368C, 0x45CD9CF3, 0x13532244, 0x2BE6766B, 0x78A97CD0, 0xEFE7E2DF, 0x0A3D4D34, 0xDB1AA450, 0xBD248B55, 0x476BF155, 0x1D073A89, 0x555AF99A, 0x7846A318, 0xE284C527, 0x9D61E50F, 0xA89CB99E, 0x3AABBBAA, 0xEF951FBB, 0x12E82D3D, 0x5A96BA4, 0xBFEFFF6D, 0x394F415C, 0x83BF0278, 0xFAD1F1C9, 0xAF113F99, 0xC0A3098D, 0x969C3D67, 0x7F229F94, 0x84D6FAFD, 0x624FE830, 0x9D1F17E6, 0xC78D71B4, 0x9D07F764, 0x7FD62962, 0xDBBD7280, 0x61012683, 0x05FC3C11, 0x0C472FE2, 0xA914799, 0xC734385A, 0x6A6C02E0, 0xB1CA77B1, 0xA284510B, 0x4DD2DC56, 0x42BF8A85, 0x7F7497E5, 0x6D544C99, 0x63AB0442, 0x0781FE4A, 0xB62D1F67, 0xDB26713A, 0x93E220BD, 0xA0973D5E, 0x24B17070, 0x2C3731D9, 0xAB564B93, 0x787F0BB, 0xBA45E8B8, 0x23C9F95C, 0xFDBC8A50, 0x497FACC3, 0x34A67B97, 0xFBAB5776, 0x060EC506, 0xBA536372, 0x184140A1 };
        for (int i = 0; i < (sizeof(Weapons) / 4); i++) {
            if (!WEAPON::HAS_PED_GOT_WEAPON(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(big::selected_player), Weapons[i], false))
                WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(big::selected_player), Weapons[i], 9999, 1);

        }
        if (!WEAPON::HAS_PED_GOT_WEAPON(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(big::selected_player), rage::joaat("WEAPON_TACTICALRIFLE"), false))
            WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(big::selected_player), rage::joaat("WEAPON_TACTICALRIFLE"), 9999, 1);
    }
    
    void give_all_attachments()
    {
        std::vector<Hash> pistolMk2{ 1329061674, 2396306288, 1140676955, 1709866683, 568543123, 2467084625 };
        std::vector<Hash> smgMk2{ 190476639, 2076495324, 2681951826, 3842157419, 1038927834, 1303784126, 2774849419, 966612367 };
        std::vector<Hash> assltRifleMk2{ 1675665560, 2640679034, 2076495324, 1108334355, 77277509, 3328927042, 2805810788, 1303784126, 1447477866, 3115408816 };
        std::vector<Hash> carbineRifleMk2{ 0x420FD713, 0x7BC4CDDC, 0x9D65907A, 0x837445AA, 0xE50C424D };
        std::vector<Hash> combatMgMk2{ 1475288264, 2640679034, 1108334355, 1060929921, 3328927042, 1303784126, 3051509595, 3607349581 };
        std::vector<Hash> heavySniperMk2{ 2313935527, 2193687427, 3159677559, 3061846192, 776198721, 2890063729, 1764221345, 277524638, 1815270123 };
        std::vector<Hash> WeaponHash{ 0xBFE256D4, 0x78A97CD0, 0xDBBD7280, 0x394F415C, 0xFAD1F1C9, 0xA914799 };
        //now lets give them
        for (Hash hash : pistolMk2)
            WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(big::selected_player), rage::joaat("WEAPON_PISTOL_MK2"), hash);

        for (Hash hash : smgMk2)
            WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(big::selected_player), rage::joaat("WEAPON_SMG_MK2"), hash);

        for (Hash hash : assltRifleMk2)
            WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(big::selected_player), rage::joaat("WEAPON_ASSAULTRIFLE_MK2"), hash);

        for (Hash hash : carbineRifleMk2)
            WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(big::selected_player), rage::joaat("WEAPON_CARBINERIFLE_MK2"), hash);

        for (Hash hash : combatMgMk2)
            WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(big::selected_player), rage::joaat("WEAPON_COMBATMG_MK2"), hash);

        for (Hash hash : heavySniperMk2)
            WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(big::selected_player), rage::joaat("WEAPON_HEAVYSNIPER_MK2"), hash);

        for (Hash hash : WeaponHash)
            WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(big::selected_player), hash, 9999, 0);
    }
}

namespace big::menu
{


    void network_selected_friendly_menu::menu()
    {
        using namespace ui;

        m_renderer.new_sub<PlayerSubmenu>(&selected_player, SubSelectedFriendly, [](PlayerSubmenu* core)
            {
                m_renderer.m_enable_player_info = true;
                core->add_option<submenu>("Drops", nullptr, SubSelectedFriendlyDrops);

                core->add_option<toggle_option<bool>>(("Demi Godmode"),
                    nullptr,
                    &m_vars.m_demi_godmode
                );

                core->add_option<toggle_option<bool>>(("Off the Radar"),
                    nullptr,
                    &m_vars.m_off_the_radar
                );

                core->add_option<toggle_option<bool>>(("Disable Police"),
                    nullptr,
                    &m_vars.m_disable_police
                );

                core->add_option<toggle_option<bool>>(("Kill Killers"),
                    nullptr,
                    &m_vars.m_kill_killers
                );

                core->add_option<toggle_option<bool>>(("Force Visible"),
                    nullptr,
                    &m_vars.m_force_visible
                );

                core->add_option<scroll_option<const char*, std::size_t>>(("Commend"),
                    nullptr, 
                    &commend, &commend_id,
                    true, [] {
                        g_pointers->m_remote_increment(*(Hash*)commend_stat[commend_id], 100, g_pointers->m_net_game_player(selected_player));
                });

                core->add_option<simple_option>(("Copy Outfit"), nullptr, []
                    {
                        copy_outfit();
                    });

                core->add_option<simple_option>(("Give All Weapons"), nullptr, []
                    {
                        give_all_weapons();
                    });

                core->add_option<simple_option>(("Give All Attachments"), nullptr, []
                    {
                        give_all_attachments();
                    });


            });
    }

    void network_selected_friendly_menu::script_init() {}

    void network_selected_friendly_menu::script_on_tick()
    {
        if (m_vars.m_demi_godmode)
        {
            Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), true);
            int hash = rage::joaat("prop_juicestand");
            int attacc = 0;
            if (STREAMING::IS_MODEL_IN_CDIMAGE(hash))
            {
                if (STREAMING::IS_MODEL_VALID(hash))
                {
                    STREAMING::REQUEST_MODEL(hash);
                    if (STREAMING::HAS_MODEL_LOADED(hash))
                    {
                        attacc = OBJECT::CREATE_OBJECT(hash, pos.x, pos.y, pos.z, 1, 1, 1);
                        if (ENTITY::DOES_ENTITY_EXIST(attacc))
                        {
                            ENTITY::ATTACH_ENTITY_TO_ENTITY(attacc, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), 31086, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 2, 1);
                            ENTITY::SET_ENTITY_VISIBLE(attacc, false, 0);
                        }
                    }
                }
            }
        }
        if (m_vars.m_disable_police) {
            constexpr size_t arg_count = 3;
            int64_t args[arg_count] = {
                static_cast<int64_t>(1449852136),
                PLAYER::PLAYER_ID(),
                *script_global(1892703).at(g_pointers->m_net_game_player(selected_player)->m_player_id, 599).at(510).as<int*>()
            };

            g_pointers->m_trigger_script_event(1, args, arg_count, 1 << g_pointers->m_net_game_player(selected_player)->m_player_id);
        }
        if (m_vars.m_off_the_radar) {
            int64_t args[2] = { -1973627888, PLAYER::PLAYER_ID() };
            g_pointers->m_trigger_script_event(1, args, 2, 1 << selected_player);
        }
        if (m_vars.m_kill_killers) {
            Entity killer = PED::GET_PED_SOURCE_OF_DEATH(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player));
            if (killer) {
                if (PED::IS_PED_A_PLAYER(killer)) {
                    if (!ENTITY::IS_ENTITY_DEAD(killer, 1)) {
                        Vector3 coords = ENTITY::GET_ENTITY_COORDS(killer, true);
                        FIRE::ADD_EXPLOSION(coords.x, coords.y, coords.z, 1, 100.f, true, false, 0.f, false);
                    }
                }
            }
        }
        if (m_vars.m_force_visible) {
            if (!ENTITY::IS_ENTITY_VISIBLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player))) {
                NETWORK::SET_ENTITY_LOCALLY_VISIBLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player));
                ENTITY::SET_ENTITY_VISIBLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player), true, true);
            }
        }
    }

    void network_selected_friendly_menu::script_func()
    {
        m_network_selected_friendly_menu.script_init();
        while (true)
        {
            m_network_selected_friendly_menu.script_on_tick();
            script::get_current()->yield();
        }
    }
}