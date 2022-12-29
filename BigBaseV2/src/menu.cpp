#include "common.hpp"
#include "fiber_pool.hpp"
#include "gta/player.hpp"
#include "gta_util.hpp"
#include "menu.h"
#include "logger.hpp"
#include "memory/module.hpp"
#include "memory/pattern.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "renderer.hpp"
#include "script.hpp"

#include <imgui.h>
#include "../HTTPRequest.hpp"
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
#include "../scroll.h"
#include "../submenus.h"
#include "../security_types.h"
#include "../instructions.h"
#include "../world.h"
#include "script.hpp"
enum ePlayerSwitchType
{
	SWITCH_TYPE_AUTO,
	SWITCH_TYPE_LONG,
	SWITCH_TYPE_MEDIUM,
	SWITCH_TYPE_SHORT
};
namespace
{
	void tp_to_waypoint()
	{
		big::g_fiber_pool->queue_job([] {
			Vector3 coords = HUD::GET_BLIP_INFO_ID_COORD(HUD::GET_FIRST_BLIP_INFO_ID(8));

			Entity entity = PLAYER::PLAYER_PED_ID();

			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false)) {
				entity = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			}



			bool ground_found = false;
			float ground_check_height[] = { 100.0f, 150.0f, 50.0f, 0.0f, 200.0f, 250.0f, 300.0f, 350.0f, 400.0f, 450.0f, 500.0f, 550.0f, 600.0f, 650.0f, 700.0f, 750.0f, 800.0f };
			for (int i = 0; i < sizeof(ground_check_height) / sizeof(float); i++) {
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(entity, coords.x, coords.y, ground_check_height[i], 0, 0, 1);
				big::script::get_current()->yield();
				if (MISC::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, ground_check_height[i], &coords.z, 0, 0)) {
					ground_found = true;
					break;
				}
			}

			if (!ground_found) {
				coords.z = 1000.0f;
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, 1, 0);
			}

			if (!STREAMING::HAS_MODEL_LOADED(0x62018559)) {
				STREAMING::REQUEST_MODEL(0x62018559);
				big::script::get_current()->yield();
			}
			*(unsigned short*)big::g_pointers->m_model_spawn_bypass = 0x9090;
			auto m_ped = PED::CREATE_PED(1, 0x62018559, coords.x, coords.y, coords.z, 0.f, true, false);
			*(unsigned short*)big::g_pointers->m_model_spawn_bypass = 0x0574;
			STREAMING::START_PLAYER_SWITCH(PLAYER::PLAYER_PED_ID(), m_ped, 0, (int)ePlayerSwitchType::SWITCH_TYPE_AUTO);
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(m_ped, true, true);
			ENTITY::DELETE_ENTITY(&m_ped);
			if (STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS()) {
				while (STREAMING::GET_PLAYER_SWITCH_STATE() != 8) {
					big::script::get_current()->yield();
					if (STREAMING::GET_PLAYER_SWITCH_STATE() == 12) break;
					PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), coords.x, coords.y, coords.z);
				}
			}
		});
	}
}

namespace big::menu
{

	const char* HeaderTypesFrontend[]
	{
		"Static",
		"Gradient"
	};

	ui::HeaderType HeaderTypesBackend[]
	{
		ui::HeaderType::Static,
		ui::HeaderType::Gradient
	};

	inline std::size_t HeaderTypesPosition = 1;

	class WaterQuad
	{
	public:
		std::int16_t minX; //0x0000
		std::int16_t minY; //0x0002
		std::int16_t maxX; //0x0004
		std::int16_t maxY; //0x0006
		std::int8_t a1; //0x0008
		std::int8_t a2; //0x0009
		std::int8_t a3; //0x000A
		std::int8_t a4; //0x000B
		std::float_t unk; //0x000C
		std::uint8_t pad_0010[4]; //0x0010
		std::float_t z; //0x0014
		std::uint8_t pad_0018[1]; //0x0018
		std::int8_t Type; //0x0019
		std::uint8_t pad_001A[2]; //0x001A
	}; //Size: 0x001C

	void gui::dx_on_tick()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("OZARK BETA", SubHome, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;
				core->add_option<submenu>("Player", nullptr, SubPlayer);
				core->add_option<submenu>("Network", nullptr, SubNetwork);
				core->add_option<submenu>("Protections", nullptr, SubProtections);
				core->add_option<submenu>("Weapon", nullptr, SubWeapon);
				core->add_option<submenu>("Vehicle", nullptr, SubVehicle);
				core->add_option<submenu>("Spawner", nullptr, SubSpawner);
				core->add_option<submenu>("Teleport", nullptr, SubTeleport);
				core->add_option<submenu>("World", nullptr, SubWorld);
				core->add_option<submenu>("Miscellanous", nullptr, SubPlayer);
				core->add_option<submenu>("Settings", nullptr, SubmenuSettings);
			});
		// all subs under the home sub are drafts
		m_renderer.new_sub<sub>("Teleport", SubTeleport, [](sub* core)//TODO
			{
				m_renderer.m_enable_player_info = false;
				core->add_option<simple_option>(("Waypoint"),
					nullptr,
					[&] {
						tp_to_waypoint();
					});
			});
		m_renderer.new_sub<sub>("Settings", SubmenuSettings, [](sub* core)//TODO
			{
				core->add_option<toggle_option<bool>>(("Arrow Submenu Indicator"),
					nullptr,
					&m_renderer.m_arrow_indicator
				);
				core->add_option<number_option<float>>("Rect Padding", nullptr, &m_renderer.m_rect_padddding, 0.f, 3.f, 0.01f, 2);
				core->add_option<number_option<float>>("Rect Width", nullptr, &m_renderer.m_rect_width, 0.f, 1.f, 0.001f, 3);
				core->add_option<number_option<float>>("X Position", nullptr, &m_renderer.m_PosX, 0.f, 3.f, 0.01f, 2);
				core->add_option<number_option<float>>("Y Position", nullptr, &m_renderer.m_PosY, 0.f, 3.f, 0.01f, 2);
				core->add_option<number_option<float>>("Glare X", nullptr, &m_renderer.GlareX, 0.001f, 3.f, 0.001f, 3);
				core->add_option<number_option<float>>("Glare Y", nullptr, &m_renderer.GlareY, 0.001f, 3.f, 0.001f, 3);
				core->add_option<number_option<float>>("Glare Width", nullptr, &m_renderer.Glarewidth, 0.001f, 3.f, 0.001f, 3);
				core->add_option<number_option<float>>("Width", nullptr, &m_renderer.m_Width, 0.001f, 3.f, 0.001f, 3);
				core->add_option<number_option<float>>("Info Bar Height", nullptr, &m_renderer.m_SubmenuBarHeight, 0.01f, 3.1f, 0.001f, 3);
				core->add_option<number_option<float>>("Option Height", nullptr, &m_renderer.m_OptionHeight, 0.01f, 3.1f, 0.001f, 3);
				core->add_option<number_option<float>>("Option Text Size", nullptr, &m_renderer.m_OptionTextSize, 0.01f, 3.1f, 0.001f, 3);
				core->add_option<number_option<float>>("Info Bar Text Size", nullptr, &m_renderer.m_SubmenuBarTextSize, 0.01f, 3.1f, 0.001f, 3);
				core->add_option<simple_option>(("Unload"),
					nullptr,
					[&] {
						g_running = false;
					});
			});

		

	}


	void gui::script_init() {}

	void gui::script_on_tick()
	{
		TRY_CLAUSE
		{
			m_renderer.OnTick();
		}
		EXCEPT_CLAUSE
	}
	
	void gui::script_func()
	{
		g_gui.script_init();
		while (true)
		{
			
			if (m_renderer.m_enable_player_info && ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selected_player)))
				m_renderer.draw_player_info(selected_player);

			g_gui.script_on_tick();
			script::get_current()->yield();
		}
	}
}
