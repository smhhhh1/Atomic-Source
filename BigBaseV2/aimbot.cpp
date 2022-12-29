#include "common.hpp"
#include "gta_util.hpp"
#include "aimbot.h"
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
using namespace big::weapon::aimbot::vars;

namespace big::weapon::aimbot::vars {
	variables m_vars;

	const char* TargetList[3]
	{
		"Player",
		"Ped",
		"Both"
	};
	const char* SelectList[2]
	{
		"Single",
		"Everyone"
	};
	const char* ModeList[2]
	{
		"In & Out FOV",
		"In FOV"
	};
	std::size_t TargetListPos = 2;
	std::size_t SelectListPos = 1;
	std::size_t ModeListPos = 0;
}

namespace big::menu
{


	void aimbot_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Aimbot", SubAimbot, [](sub* core)
			{
				core->add_option<toggle_option<bool>>(("AimBot"),
					nullptr,
					&m_vars.m_toggle
				);
				core->add_option<toggle_option<bool>>(("Multi Bullet"), 
					nullptr,
					&m_vars.m_multi_bullet
				);
				core->add_option<number_option<int>>(("Shoot Delay"),
					nullptr,
					&m_vars.shoot_delay,
					20, 60,
					1, 1, 
					false
				);

				core->add_option<scroll_option<const char*, std::size_t>>(("Selection"),
					nullptr,
					&SelectList, 
					&SelectListPos
				);
				core->add_option<scroll_option<const char*, std::size_t>>(("Target"),
					nullptr,
					&TargetList,
					&TargetListPos
				);
			});
	}

	void aimbot_menu::script_init() {}

	void aimbot_menu::script_on_tick() {

		if (m_vars.m_toggle) {

			static int ped_amt = -1;

			if (IsKeyPressed(VK_RBUTTON))
			{
				if (ModeListPos == 1 && IsKeyPressed(VK_LBUTTON)) PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_ID(), FALSE);
				const int numElements = 10;
				const int arrSize = numElements * 2 + 2;
				int veh[arrSize];
				veh[0] = numElements;
				int count = PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), veh, -1);
				Ped closest = 0;
				if (veh != NULL)
				{
					for (int i = 0; i < count; i++)
					{
						int offsettedID = i * 2 + 2;
						if (veh[offsettedID] != NULL && ENTITY::DOES_ENTITY_EXIST(veh[offsettedID]))
						{
							ped_amt = -1;
							for (int j = -1; j <= 2; ++j)
							{

								Any ped = veh[offsettedID];

								Vector3 ped_coords = ENTITY::GET_ENTITY_COORDS(ped, TRUE);
								Vector3 self_head_coords = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), 0x796e, 0, 0, 0);
								Vector3 ped_head_coords = PED::GET_PED_BONE_COORDS(ped, 0x796e, 0, 0, 0);
								//GRAPHICS::DRAW_LINE(ped_head_coords.x, ped_head_coords.y, ped_head_coords.z, self_head_coords.x, self_head_coords.y, self_head_coords.z, 255, 0, 0, 200);



								Vector3 self_coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), TRUE);
								if (closest == 0) closest = ped;
								else if (MISC::GET_DISTANCE_BETWEEN_COORDS(self_coords.x, self_coords.y, self_coords.z, ped_coords.x, ped_coords.y, ped_coords.z, TRUE) < MISC::GET_DISTANCE_BETWEEN_COORDS(self_coords.x, self_coords.y, self_coords.z, ENTITY::GET_ENTITY_COORDS(closest, TRUE).x, ENTITY::GET_ENTITY_COORDS(closest, TRUE).y, ENTITY::GET_ENTITY_COORDS(closest, TRUE).z, TRUE) || SelectListPos == 1) closest = ped;//                                                                                                                            
								Hash weaponhash;
								WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &weaponhash, 1);
								if (!WEAPON::IS_WEAPON_VALID(weaponhash)) continue;
								float screenX, screenY;
								BOOL onScreen = GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(ENTITY::GET_ENTITY_COORDS(closest, true).x, ENTITY::GET_ENTITY_COORDS(closest, true).y, ENTITY::GET_ENTITY_COORDS(closest, true).z, &screenX, &screenY);
								if (ModeListPos == 0) onScreen = TRUE;
								switch ((unsigned long long)TargetListPos) {
								case 0:
									if (!PED::IS_PED_A_PLAYER(ped)) continue;
									break;
								case 1:
									if (PED::IS_PED_A_PLAYER(ped)) continue;
									break;
								case 2:

									break;
								}
								PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_ID(), FALSE);
								int bones[] = { 0x0,0x2e28,0xe39f,0xf9bb,0x3779,0x83c,0xfedd,0xe175,0xb3fe,0xca72,0x9000,0xcc4d,0x512d,0x8aae,0x60e6,0x3fcf,0x5c57,0x192a,0xe0fd,0x5c01,0x60f0,0x60f1,0x60f2,0xfcd9,0xb1c5,0xeeeb,0x49d9,0x67f2, 0xff9, 0xffa, 0x67f3, 0x1049, 0x104a, 0x67f4, 0x1059, 0x105a, 0x67f5, 0x1029, 0x102a, 0x67f6, 0x1039, 0x103a, 0xeb95, 0x8cbd, 0xee4f, 0x1470, 0x58b7, 0x29d2, 0x9d4d, 0x6e5c, 0xdead, 0xe5f2, 0xfa10, 0xfa11, 0xe5f3, 0xfa60, 0xfa61, 0xe5f4, 0xfa70,0xfa71, 0xe5f5,0xfa40, 0xfa41,0xe5f6,0xfa50, 0xfa51,0x6f06, 0x188e,0xab22,0x90ff,0xbb0, 0x9995,0x796e, 0x322c,0xfe2c, 0xe3db,0xb2b6, 0x62ac,0x542e, 0x74ac,0xaa10, 0x6b52,0x4b88, 0x54c,0x2ba6, 0x9149,0x4ed2, 0xf18f,0x4f37, 0x4537,0xb4a0, 0x4324,0x508f,0xb93b,0xc33b,0xb987,0x8b93,0xdd1c };

								if (((closest != NULL && !ENTITY::IS_ENTITY_DEAD(closest, 0) && onScreen) || SelectListPos == 1))
								{

									if (!ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(PLAYER::PLAYER_PED_ID(), closest, 1000)) continue;
									//Text(PED::IS_PED_A_PLAYER(closest) ? "Player Found" : "Peds Found", 255, 0, 0, 255, 0.5f, 0.5f, 0.3f, 0.3f, true);

									//PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_ID(), TRUE);


									Vector3 target_coords = PED::GET_PED_BONE_COORDS(closest, 0x796e, 0, 0, 0);

									

									if ((IsKeyPressed(VK_LBUTTON)) && GetTickCount() % (m_vars.shoot_delay > 0 ? m_vars.shoot_delay : 1) == 0)
									{
										if (m_vars.m_multi_bullet)
										{


											for (int bone : bones)
											{
												self_head_coords = PED::GET_PED_BONE_COORDS(closest, bone, 0, 0, 0);

												MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(target_coords.x, target_coords.y, target_coords.z, self_head_coords.x, self_head_coords.y, self_head_coords.z, 50, 1, weaponhash, PLAYER::PLAYER_PED_ID(), 1, 1, 0xbf800000);
											}
										}
										else MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(self_head_coords.x, self_head_coords.y, self_head_coords.z, target_coords.x, target_coords.y, target_coords.z, 50, 1, weaponhash, PLAYER::PLAYER_PED_ID(), 1, 1, 0xbf800000);


									}



									//GRAPHICS::DRAW_MARKER(2, target_coords.x, target_coords.y, target_coords.z + 2, 0, 0, 0, 0, 180, 0, 0.5f, 0.5f, 0.5f, 255, 0, 0, 50, 0, 1, 1, 0, 0, 0, 0);

								}
							}
						}
					}


				}
			}
			else
			{

			}
		}
	
	}

	void aimbot_menu::script_func()
	{
		m_aimbot_menu.script_init();
		while (true)
		{
			m_aimbot_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}