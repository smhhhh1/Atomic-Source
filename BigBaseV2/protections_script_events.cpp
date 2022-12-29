#include "common.hpp"
#include "gta_util.hpp"
#include "protections_script_events.h"
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
#include "xorstr.h"	

namespace big::menu
{

	void protections_script_events_menu::menu()
	{
		using namespace ui;

		m_renderer.new_sub<sub>("Script Events", SubProtectionsScriptEvents, [](sub* core)
			{
				m_renderer.m_enable_player_info = false;

				core->add_option<simple_option>("Enable All", nullptr, []
					{
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

				core->add_option<simple_option>("Disable All", nullptr, []
					{
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

				core->add_option<break_option>(std::move(break_option()
					.SetRightText("Events"))
				);

				core->add_option<scroll_option<const char*, std::size_t>>(XOR("Crashes"), nullptr,
					&lists::crash_script_event, &lists::crash_script_event_id,
					true
				);

				core->add_option<scroll_option<const char*, std::size_t>>(XOR("Network Bail"), nullptr,
					&lists::network_bail_script_event, &lists::network_bail_script_event_id,
					true
				);

				core->add_option<scroll_option<const char*, std::size_t>>(XOR("Bounty"), nullptr,
					&lists::bounty_script_event, &lists::bounty_script_event_id,
					true
				);

				core->add_option<scroll_option<const char*, std::size_t>>(XOR("Ceo Ban"), nullptr,
					&lists::ceo_ban_script_event, &lists::ceo_ban_script_event_id,
					true
				);

				core->add_option<scroll_option<const char*, std::size_t>>(XOR("Ceo Kick"), nullptr,
					&lists::ceo_kick_script_event, &lists::ceo_kick_script_event_id,
					true
				);

				core->add_option<scroll_option<const char*, std::size_t>>(XOR("Ceo Money"), nullptr,
					&lists::ceo_money_script_event, &lists::ceo_money_script_event_id,
					true
				);

				core->add_option<scroll_option<const char*, std::size_t>>(XOR("Clear Wanted Level"), nullptr,
					&lists::clear_wanted_level_script_event, &lists::clear_wanted_level_script_event_id,
					true
				);

				core->add_option<scroll_option<const char*, std::size_t>>(XOR("Force to Mission"), nullptr,
					&lists::force_to_mission_script_event, &lists::force_to_mission_script_event_id,
					true
				);

				core->add_option<scroll_option<const char*, std::size_t>>(XOR("Switch Model"), nullptr,
					&lists::switch_model_script_event, &lists::switch_model_script_event_id,
					true
				);

				core->add_option<scroll_option<const char*, std::size_t>>(XOR("Gta Banner"), nullptr,
					&lists::gta_banner_script_event, &lists::gta_banner_script_event_id,
					true
				);

				core->add_option<scroll_option<const char*, std::size_t>>(XOR("Insurance Message"), nullptr,
					&lists::insurance_message_script_event, &lists::insurance_message_script_event_id,
					true
				);

				core->add_option<scroll_option<const char*, std::size_t>>(XOR("Off the Radar"), nullptr,
					&lists::off_radar_script_event, &lists::off_radar_script_event_id,
					true
				);

				core->add_option<scroll_option<const char*, std::size_t>>(XOR("Send to Cayo"), nullptr,
					&lists::send_to_cayo_script_event, &lists::send_to_cayo_script_event_id,
					true
				);

				core->add_option<scroll_option<const char*, std::size_t>>(XOR("Send to Cutscene"), nullptr,
					&lists::send_to_cutscene_script_event, &lists::send_to_cutscene_script_event_id,
					true
				);

				core->add_option<scroll_option<const char*, std::size_t>>(XOR("Send to Location"), nullptr,
					&lists::send_to_location_script_event, &lists::send_to_location_script_event_id,
					true
				);

				core->add_option<scroll_option<const char*, std::size_t>>(XOR("Sound Spam"), nullptr,
					&lists::sound_spam_script_event, &lists::sound_spam_script_event_id,
					true
				);

				core->add_option<scroll_option<const char*, std::size_t>>(XOR("Spectate Message"), nullptr,
					&lists::spectate_message_script_event, &lists::spectate_message_script_event_id,
					true
				);

				core->add_option<scroll_option<const char*, std::size_t>>(XOR("Teleport"), nullptr,
					&lists::teleport_script_event, &lists::teleport_script_event_id,
					true
				);

				core->add_option<scroll_option<const char*, std::size_t>>(XOR("Transaction Error"), nullptr,
					&lists::transaction_error_script_event, &lists::transaction_error_script_event_id,
					true
				);

				core->add_option<scroll_option<const char*, std::size_t>>(XOR("Vehicle Kick"), nullptr,
					&lists::vehicle_kick_script_event, &lists::vehicle_kick_script_event_id,
					true
				);

				core->add_option<scroll_option<const char*, std::size_t>>(XOR("Start Activity"), nullptr,
					&lists::activity_script_event, &lists::activity_script_event_id,
					true
				);

				core->add_option<scroll_option<const char*, std::size_t>>(XOR("Invalid Interior"), nullptr,
					&lists::invalid_interior_script_event, &lists::invalid_interior_script_event_id,
					true
				);

				core->add_option<scroll_option<const char*, std::size_t>>(XOR("Rotate Cam"), nullptr,
					&lists::rotate_cam_script_event, &lists::rotate_cam_script_event_id,
					true
				);

				core->add_option<scroll_option<const char*, std::size_t>>(XOR("Notifications"), nullptr,
					&lists::notification_script_event, &lists::notification_script_event_id,
					true
				);

			});
	}

	void protections_script_events_menu::script_init() {}

	void protections_script_events_menu::script_on_tick() {}

	void protections_script_events_menu::script_func()
	{
		m_protections_script_events_menu.script_init();
		while (true)
		{
			m_protections_script_events_menu.script_on_tick();
			script::get_current()->yield();
		}
	}
}