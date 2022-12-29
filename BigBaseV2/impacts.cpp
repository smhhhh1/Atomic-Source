#include "common.hpp"
#include "gta_util.hpp"
#include "impacts.h"
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
#include "scroll.h"
#include "util.h"
using namespace big::weapon::impacts::vars;

namespace big::weapon::impacts::vars {
	variables m_vars;


	std::vector<Hash> ammo_hash
	{
		0xAF3696A1, 0x476BF155, 0xA914799, 0xB1CA77B1, 0xA284510B, 0x4DD2DC56, //"Up-n-Atomizer", "Unholy Hellbringer", "Heavy Sniper Mk II", "RPG", "Grenade Launcher", "Grenade Launcher Smoke"
		0x7F7497E5, 0x6D544C99, 0x93E220BD, 0xA0973D5E, 0x24B17070, 0xAB564B93, 0x787F0BB, //"Firework Launcher", "Railgun", "Grenade", "BZ Gas", "Molotov Cocktail", "Proximity Mines", "Snowballs"
		0xBA45E8B8, 0x23C9F95C, 0xFDBC8A50, 0x497FACC3, 0xEFFD014B, 0x5D6660AB //"Pipe Bombs", "Baseball", "Tear Gas", "Flare"
	};
	const char* ammo_types[] =
	{
		"Up-n-Atomizer", "Red Laser", "Heavy Sniper Mk II", "RPG", "Grenade Launcher", "Grenade Launcher Smoke",
		"Firework Launcher", "Railgun", "Grenade", "BZ Gas", "Molotov Cocktail", "Proximity Mines", "Snowballs",
		"Pipe Bombs", "Baseball", "Tear Gas", "Flare", "Green Laser", "Red Laser"
	}; int ammo_pos = 0;

	void customImpacts(Hash hash) {
		if (m_vars.toggle) {

			Ped playerPed = PLAYER::PLAYER_PED_ID();
			float startDistance = must_Distance(CAM::GET_GAMEPLAY_CAM_COORD(), ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true));
			float endDistance = must_Distance(CAM::GET_GAMEPLAY_CAM_COORD(), ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true));
			startDistance += 5.25;
			endDistance += 1000.0;

			if (PED::IS_PED_ON_FOOT(playerPed) && PED::GET_PED_CONFIG_FLAG(playerPed, 58, 1))
			{

				if (!WEAPON::HAS_WEAPON_ASSET_LOADED(hash))
				{
					WEAPON::REQUEST_WEAPON_ASSET(hash, 31, false);
					while (!WEAPON::HAS_WEAPON_ASSET_LOADED(hash))
						script::get_current()->yield();
				}
				MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(addVector(CAM::GET_GAMEPLAY_CAM_COORD(), multiplyVector(RotationToDirection(CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance + ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()))).x,
					addVector(CAM::GET_GAMEPLAY_CAM_COORD(), multiply(RotationToDirection(CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance + ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()))).y,
					addVector(CAM::GET_GAMEPLAY_CAM_COORD(), multiplyVector(RotationToDirection(CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance + ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()))).z,
					addVector(CAM::GET_GAMEPLAY_CAM_COORD(), multiplyVector(RotationToDirection(CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance + ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()))).x,
					addVector(CAM::GET_GAMEPLAY_CAM_COORD(), multiplyVector(RotationToDirection(CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance + ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()))).y,
					addVector(CAM::GET_GAMEPLAY_CAM_COORD(), multiplyVector(RotationToDirection(CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance + ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()))).z,
					250, 1, hash, playerPed, 1, 0, -1.0
				);

			}

		}
	}
}

namespace big::menu
{


	void impacts_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Impacts", SubImpacts, [](sub* core)
			{
				core->add_option<scroll_option<const char*, int>>(("Impacts"), "Some Impacts Only Work In Online", &ammo_types, &ammo_pos, true);
				core->add_option<toggle_option<bool>>(("Toggle"), "Some Impacts Only Work In Online", &m_vars.toggle);
			});
	}

	void impacts_menu::script_init() {}

	void impacts_menu::script_on_tick() {

		customImpacts(ammo_hash[ammo_pos]);

	}

	void impacts_menu::script_func()
	{
		m_impacts_menu.script_init();
		while (true)
		{
			m_impacts_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}