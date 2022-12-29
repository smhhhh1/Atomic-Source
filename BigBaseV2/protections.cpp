#include "common.hpp"
#include "gta_util.hpp"
#include "protections.h"
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
#include "network_spoofing.h"
using namespace big::protections::vars;

namespace big::protections::vars {

	variables m_vars;

}

namespace big::menu
{

	void protections_menu::menu()
	{
		using namespace ui;


		m_renderer.new_sub<sub>("Protections", SubProtections, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;

				core->add_option<submenu>("Network Events",
					nullptr,
					SubProtectionsNetworkEvents
				);

				core->add_option<submenu>("Scripted Events",
					nullptr,
					SubProtectionsScriptEvents
				);

				core->add_option<submenu>("Presence Events",
					nullptr,
					SubProtectionsPresence
				);

				core->add_option<submenu>("Join Blocking",
					nullptr,
					SubProtectionsJoinBlocking
				);

				core->add_option<submenu>("Anti Detection",
					nullptr,
					SubNetworkDetectionFlags
				);

				core->add_option<submenu>("Entity",
					nullptr,
					SubProtectionsEntity
				);

				core->add_option<submenu>("Miscellanous",
					nullptr,
					SubProtectionsMisc
				);

				core->add_option<toggle_option<bool>>(("Fake Lag"),
					nullptr,
					&network::spoofing::vars::m_vars.m_fake_lag
				);

				core->add_option<toggle_option<bool>>(("Force Entities Visible"),
					nullptr,
					&network::spoofing::vars::m_vars.m_rockstar_dev
				);


				core->add_option<toggle_option<bool>>(("Log Script Events"),
					nullptr,
					&network::spoofing::vars::m_vars.m_movement_animation
				);

				core->add_option<simple_option>("Enable All Protections", nullptr, []
					{
						lists::explosion_event_id = 2;
						lists::freeze_event_id = 2;
						lists::ptfx_event_id = 2;
						lists::ragdoll_event_id = 2;
						lists::remove_weapons_event_id = 2;
						lists::remove_all_weapons_event_id = 2;
						lists::request_control_event_id = 2;
						lists::give_control_event_id = 2;

						lists::bounty_script_event_id = 2;
						lists::ceo_ban_script_event_id = 2;
						lists::ceo_kick_script_event_id = 2;
						lists::ceo_money_script_event_id = 2;
						lists::clear_wanted_level_script_event_id = 2;
						lists::force_to_mission_script_event_id = 2;
						lists::switch_model_script_event_id = 2;
						lists::gta_banner_script_event_id = 2;
						lists::network_bail_script_event_id = 2;
						lists::insurance_message_script_event_id = 2;
						lists::off_radar_script_event_id = 2;
						lists::send_to_cutscene_script_event_id = 2;
						lists::send_to_cayo_script_event_id = 2;
						lists::send_to_location_script_event_id = 2;
						lists::sound_spam_script_event_id = 2;
						lists::spectate_message_script_event_id = 2;
						lists::teleport_script_event_id = 2;
						lists::transaction_error_script_event_id = 2;
						lists::vehicle_kick_script_event_id = 2;
						lists::activity_script_event_id = 2;
						lists::invalid_interior_script_event_id = 2;
						lists::crash_script_event_id = 2;
						lists::rotate_cam_script_event_id = 2;
						lists::notification_script_event_id = 2;
					});

				core->add_option<simple_option>("Disable All Protections", nullptr, []
					{
						lists::explosion_event_id = 0;
						lists::freeze_event_id = 0;
						lists::ptfx_event_id = 0;
						lists::ragdoll_event_id = 0;
						lists::remove_weapons_event_id = 0;
						lists::remove_all_weapons_event_id = 0;
						lists::request_control_event_id = 0;
						lists::give_control_event_id = 0;

						lists::bounty_script_event_id = 0;
						lists::ceo_ban_script_event_id = 0;
						lists::ceo_kick_script_event_id = 0;
						lists::ceo_money_script_event_id = 0;
						lists::clear_wanted_level_script_event_id = 0;
						lists::force_to_mission_script_event_id = 0;
						lists::switch_model_script_event_id = 0;
						lists::gta_banner_script_event_id = 0;
						lists::network_bail_script_event_id = 0;
						lists::insurance_message_script_event_id = 0;
						lists::off_radar_script_event_id = 0;
						lists::send_to_cutscene_script_event_id = 0;
						lists::send_to_cayo_script_event_id = 0;
						lists::send_to_location_script_event_id = 0;
						lists::sound_spam_script_event_id = 0;
						lists::spectate_message_script_event_id = 0;
						lists::teleport_script_event_id = 0;
						lists::transaction_error_script_event_id = 0;
						lists::vehicle_kick_script_event_id = 0;
						lists::activity_script_event_id = 0;
						lists::invalid_interior_script_event_id = 0;
						lists::crash_script_event_id = 0;
						lists::rotate_cam_script_event_id = 0;
						lists::notification_script_event_id = 0;
					});
			});
			m_renderer.new_sub<sub>("Join Blocking", SubProtectionsJoinBlocking, [](sub* core)
				{
					core->add_option<toggle_option<bool>>(("Block Resolves"),
						nullptr,
						&m_vars.m_block_resolves
						);

					core->add_option<toggle_option<bool>>(("Spoof Resolves"),
						nullptr,
						&m_vars.m_spoof_resolves
						);

				});

	}

	void protections_menu::script_init() {}

	void protections_menu::script_on_tick() {}

	void protections_menu::script_func()
	{
		m_protections_menu.script_init();
		while (true)
		{
			m_protections_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}