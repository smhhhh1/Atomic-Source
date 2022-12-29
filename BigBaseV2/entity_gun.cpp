#include "common.hpp"
#include "gta_util.hpp"
#include "entity_gun.h"
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
using namespace big::weapon::entity_gun::vars;

namespace big::weapon::entity_gun::vars {
	variables m_vars;

	const char* entity_gun_model[] =
	{
		"adder", "bati", "buzzard", "lazer", "italigtb", "toro", "toros", "bulldozer", "benson", "bmx"
	}; int entity_gun_pos = 0;

	int spawn(std::string_view model, Vector3 location, float heading, bool is_networked = true)
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
				LOG(INFO) << "model hasnt loaded";
				return -1;
			}

			*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
			Vehicle veh = VEHICLE::CREATE_VEHICLE(hash, location.x, location.y, location.z, heading, is_networked, false, false);
			*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

			script::get_current()->yield();

			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);

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


	void entity_gun_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Entity Gun", SubEntityGun, [](sub* core)
			{
				core->add_option<scroll_option<const char*, int>>(("Entity"), nullptr, &entity_gun_model, &entity_gun_pos, true);
				core->add_option<toggle_option<bool>>(("Toggle"), nullptr, &m_vars.toggle);
			});
	}

	void entity_gun_menu::script_init() {}

	void entity_gun_menu::script_on_tick() {

		
		if (m_vars.toggle) {
			static auto last_time = std::chrono::steady_clock::now();
			const auto time_now = std::chrono::steady_clock::now();

			const auto elapsed_time_in_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time_now - last_time).count();

			if (elapsed_time_in_ms >= 100 && PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK)) {
				Vector3 location = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);

				constexpr int rotation_order = 2;

				Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(rotation_order);
				float pitch = DegreeToRadian(rot.x); 

				float yaw = DegreeToRadian(rot.z + 90); 

				float dist = 10.f;
				location.x += dist * cos(pitch) * cos(yaw);
				location.y += dist * sin(yaw) * cos(pitch);
				location.z += dist * sin(pitch);

				
				Vehicle veh = spawn(
					(const char*)entity_gun_model[entity_gun_pos],
					location,
					ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID())
				);
				
				dist = 150.f;
				Vector3 velocity
				{
					dist * cos(pitch) * cos(yaw),
					dist * sin(yaw) * cos(pitch),
					dist * sin(pitch)
				};

				ENTITY::SET_ENTITY_ROTATION(veh, rot.x, rot.y, rot.z, rotation_order, 1);
				ENTITY::SET_ENTITY_VELOCITY(veh, velocity.x, velocity.y, velocity.z);

				ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);

				last_time = time_now;
			}
		}

	}

	void entity_gun_menu::script_func()
	{
		m_entity_gun_menu.script_init();
		while (true)
		{
			m_entity_gun_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}