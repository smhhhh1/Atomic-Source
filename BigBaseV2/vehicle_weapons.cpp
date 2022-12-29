#include "common.hpp"
#include "gta_util.hpp"
#include "vehicle_weapons.h"
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
#include "gta/enums.hpp"
#include "util.h"
#include "scroll.h"
using namespace big::vehicle::weapons::vars;


namespace big::vehicle::weapons::vars
{
	variables m_vars;

    std::vector<Hash> vehicle_ammo_hash
    {
        0xAF3696A1, 0x476BF155, 0xA914799, 0xB1CA77B1, 0xA284510B, 0x4DD2DC56, //"Up-n-Atomizer", "Unholy Hellbringer", "Heavy Sniper Mk II", "RPG", "Grenade Launcher", "Grenade Launcher Smoke"
        0x7F7497E5, 0x6D544C99, 0x93E220BD, 0xA0973D5E, 0x24B17070, 0xAB564B93, 0x787F0BB, //"Firework Launcher", "Railgun", "Grenade", "BZ Gas", "Molotov Cocktail", "Proximity Mines", "Snowballs"
        0xBA45E8B8, 0x23C9F95C, 0xFDBC8A50, 0x497FACC3, 0xEFFD014B, 0x5D6660AB //"Pipe Bombs", "Baseball", "Tear Gas", "Flare"
    };

    const char* vehicle_ammo_types[] =
    {
        "Up-n-Atomizer", "Red Laser", "Heavy Sniper Mk II", "RPG", "Grenade Launcher", "Grenade Launcher Smoke",
        "Firework Launcher", "Railgun", "Grenade", "BZ Gas", "Molotov Cocktail", "Proximity Mines", "Snowballs",
        "Pipe Bombs", "Baseball", "Tear Gas", "Flare", "Green Laser", "Red Laser"
    }; int vehicle_ammo_pos = 0;

	void Weapons(Hash hash)
	{
		if (m_vars.m_toggle)
		{
            DWORD featureWeaponVehShootLastTime = 0;
            Player player = PLAYER::PLAYER_ID();
            Ped playerPed = PLAYER::PLAYER_PED_ID();

            if (!ENTITY::DOES_ENTITY_EXIST(playerPed)) return;

            bool bSelect = GetAsyncKeyState(VK_ADD); // num plus
            if (m_vars.m_aiming_lines) {
                Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
                Vector3 v0, v1;
                MISC::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(veh), &v0, &v1);
                Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.25f), v1.y + 1.25f, 0.1);
                Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.25f), v1.y + 1.25f, 0.1);
              //  GRAPHICS::DRAW_LINE(coords0from.x, coords0from.y, coords0from.z, add(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply(&rot_to_direction(&CAM::GET_GAMEPLAY_CAM_ROT(0)), 10.f)).x, add(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply(&rot_to_direction(&CAM::GET_GAMEPLAY_CAM_ROT(0)), 10.f)).y, add(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply(&rot_to_direction(&CAM::GET_GAMEPLAY_CAM_ROT(0)), 10.f)).z, 255, 0, 0, 255);
              //  GRAPHICS::DRAW_LINE(coords1from.x, coords1from.y, coords1from.z, add(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply(&rot_to_direction(&CAM::GET_GAMEPLAY_CAM_ROT(0)), 10.f)).x, add(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply(&rot_to_direction(&CAM::GET_GAMEPLAY_CAM_ROT(0)), 10.f)).y, add(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply(&rot_to_direction(&CAM::GET_GAMEPLAY_CAM_ROT(0)), 10.f)).z, 255, 0, 0, 255);
            }
            if (bSelect && featureWeaponVehShootLastTime + m_vars.m_bullet_speed < GetTickCount() &&
                PLAYER::IS_PLAYER_CONTROL_ON(player) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
            {
                Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

                Vector3 v0, v1;
                MISC::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(veh), &v0, &v1);

                Hash weaponAssetRocket = hash;
                if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
                {
                    WEAPON::REQUEST_WEAPON_ASSET(weaponAssetRocket, 31, 0);
                    while (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
                        script::get_current()->yield();
                }

                Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.25f), v1.y + 1.25f, 0.1);
                Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.25f), v1.y + 1.25f, 0.1);
                Vector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -v1.x, v1.y + 100.0f, 0.1f);
                Vector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, v1.x, v1.y + 100.0f, 0.1f);



                MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords0from.x, coords0from.y, coords0from.z,
                    coords0to.x, coords0to.y, coords0to.z,
                    250, 0, weaponAssetRocket, playerPed, 1, 0, -1.0);
                MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1from.x, coords1from.y, coords1from.z,
                    coords1to.x, coords1to.y, coords1to.z,
                    250, 0, weaponAssetRocket, playerPed, 1, 0, -1.0);

                featureWeaponVehShootLastTime = GetTickCount();

            }
        }
	}
}


namespace big::menu
{


	void vehicle_weapons_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Vehicle Weapons", SubVehicleWeapons, [](sub* core)
			{
                core->add_option<toggle_option<bool>>(("Toggle Weapons"), nullptr, &m_vars.m_toggle);
                core->add_option<number_option<int>>(("Bullet Speed"), nullptr, &m_vars.m_bullet_speed, 0, 2000, 10, 1, false);
                core->add_option<toggle_option<bool>>(("Aiming Lines"), nullptr, &m_vars.m_aiming_lines);
                core->add_option<scroll_option<const char*, int>>(("Impacts"), nullptr, &vehicle_ammo_types, &vehicle_ammo_pos, true);
			});
	}

	void vehicle_weapons_menu::script_init() {}

	void vehicle_weapons_menu::script_on_tick()
	{
        Weapons(vehicle_ammo_hash[vehicle_ammo_pos]);
	}

	void vehicle_weapons_menu::script_func()
	{
		m_vehicle_weapons_menu.script_init();
		while (true)
		{
			m_vehicle_weapons_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}