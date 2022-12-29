#include "common.hpp"
#include "gta_util.hpp"
#include "movement.h"
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
#include "math.h"
#include "notify.h"
using namespace big::player::movement::vars;


namespace big::player::movement::vars
{
	variables m_vars;

	float get_analog_range(int stick) {
		return (((float)PAD::GET_CONTROL_VALUE(0, stick)) - 127) / 127;
	}

	void no_clip() {
		if (IsKeyPressed(VK_F6)) {
			m_vars.m_no_clip_bind ^= true;
			if (!m_vars.m_no_clip_bind) {
				ENTITY::SET_ENTITY_COLLISION(PLAYER::PLAYER_PED_ID(), true, true);
				ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), false);
				PAD::ENABLE_ALL_CONTROL_ACTIONS(0);
			}
		}

		if (m_vars.m_no_clip && m_vars.m_no_clip_bind) {
		    Vector3 pos;
			pos.x = get_analog_range(ControlFrontendAxisX) * m_vars.m_no_clip_speed;
			pos.y = get_analog_range(ControlFrontendAxisY) * m_vars.m_no_clip_speed * -1.f;

			Vector3 apos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), pos.x, pos.y, pos.z);
			float input = PAD::GET_CONTROL_NORMAL(0, ControlAttack) - PAD::GET_CONTROL_NORMAL(0, ControlAim);

			if (IsKeyPressed(VK_SPACE) || input > 0.f) {
				apos.z += m_vars.m_no_clip_speed;
			}

			if (IsKeyPressed(VK_SHIFT) || input < 0.f) {
				apos.z -= m_vars.m_no_clip_speed;
			}

			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(PLAYER::PLAYER_PED_ID(), apos.x, apos.y, apos.z, false, false, false);

			Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
			ENTITY::SET_ENTITY_ROTATION(PLAYER::PLAYER_PED_ID(), 0.f, rot.y, rot.z, 2, true);

			ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), true);
			ENTITY::SET_ENTITY_COLLISION(PLAYER::PLAYER_PED_ID(), false, false);

			PAD::DISABLE_CONTROL_ACTION(0, ControlFrontendLt, true);
			PAD::DISABLE_CONTROL_ACTION(0, ControlFrontendRt, true);
			PAD::DISABLE_CONTROL_ACTION(0, ControlFrontendCancel, true);
		}
	}

}

namespace big::menu
{
	void movement_menu::menu()
	{
		using namespace ui;
		m_renderer.new_sub<sub>("Movement", SubMovement, [](sub* core)
			{

				
				core->add_option<toggle_number_option<float, bool>>("No Clip",
					nullptr,
					&m_vars.m_no_clip,
					&m_vars.m_no_clip_speed,
					1.0f,
					10.0f,
					0.1f,
					1, 
					true,"", "", [] {
						if (m_vars.m_no_clip) {
							if (m_vars.m_no_clip_notify) {
								m_vars.m_no_clip_notify = false;

								ImGui::InsertNotification({ ImGuiToastType_None, 2000, "Press F6 to enable/disable noclip" });

								
							}
						}
						else {
							m_vars.m_no_clip_notify = true;
							ENTITY::SET_ENTITY_COLLISION(PLAYER::PLAYER_PED_ID(), true, true);
							ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), false);
							PAD::ENABLE_ALL_CONTROL_ACTIONS(0);
							PAD::DISABLE_CONTROL_ACTION(0, 27, true); // Disable phone
						}
					});


				core->add_option<toggle_number_option<float, bool>>("Run Speed",
					nullptr,
					&m_vars.m_super_run, &m_vars.m_run_speed,
					1.0f, 10.0f, 
					0.1f, 1
				);

				core->add_option<toggle_number_option<float, bool>>("Swim Speed",
					nullptr,
					&m_vars.m_super_swim, &m_vars.m_swim_speed,
					1.0f, 10.0f, 
					0.1f, 1
				);

				core->add_option<ui::toggle_option<bool>>(("Beast Jump"),
					nullptr,
					&m_vars.m_super_jump
				);		

			});
	}

	void movement_menu::script_init() {}

	void movement_menu::script_on_tick()
	{

		no_clip();
		if (m_vars.m_super_jump && PAD::IS_CONTROL_JUST_PRESSED(0, INPUT_JUMP) && !PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), NULL) && !ENTITY::IS_ENTITY_IN_AIR(PLAYER::PLAYER_PED_ID()))
		{
			TASK::TASK_JUMP(PLAYER::PLAYER_PED_ID(), TRUE, TRUE, TRUE);
		}

		if (m_vars.m_super_run)
			gta_util::get_local_ped()->m_player_info->m_run_speed = m_vars.m_run_speed;
		else if (!m_vars.m_super_run)
			gta_util::get_local_ped()->m_player_info->m_run_speed = 1.0f;


		if (m_vars.m_super_swim)
			gta_util::get_local_ped()->m_player_info->m_swim_speed = m_vars.m_swim_speed;
		else if (!m_vars.m_super_swim)
			gta_util::get_local_ped()->m_player_info->m_swim_speed = 1.0f;

	}

	void movement_menu::script_func()
	{
		m_movement_menu.script_init();
		while (true)
		{
			m_movement_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}