#include "hooking.hpp"
#include "gta_util.hpp"
#include "gta/player.hpp"
#include "lists.h"
#include "notify.h"
namespace big
{
	bool hooks::scripted_game_event(CScriptedGameEvent* scripted_game_event, CNetGamePlayer* player)
	{
		const auto args = scripted_game_event->m_args;

		const auto hash = static_cast<eRemoteEvent>(args[0]);
		const auto player_name = player->get_name();
		
		if (*(int*)&args[1] != player->m_player_id && player->m_player_id != -1) {
			return true;
		}

		switch (hash)
		{
		case eRemoteEvent::Bounty:

			switch (lists::bounty_script_event_id) {
			case 0:
				break;
			case 1:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Bounty";
				return true;
				break;
			case 2:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Bounty";
				ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Bounty From %s", player_name });
				return true;
				break;
			}
			break;
		case eRemoteEvent::CeoBan:
			switch(lists::ceo_ban_script_event_id) {
		case 0:
			break;
		case 1:
			LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Ceo Ban";
			return true;
			break;
		case 2:
			LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Ceo Ban";
			ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Ceo Ban From %s", player_name });
			return true;
			break;
			}
			break;
		case eRemoteEvent::CeoKick:
			switch (lists::ceo_kick_script_event_id) {
			case 0:
				break;
			case 1:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Ceo Kick";
				return true;
				break;
			case 2:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Ceo Kick";
				ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Ceo Kick From %s", player_name });
				return true;
				break;
			}
			break;
		case eRemoteEvent::CeoMoney:
			switch (lists::ceo_money_script_event_id) {
			case 0:
				break;
			case 1:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Ceo Money";
				return true;
				break;
			case 2:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Ceo Money";
				ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Ceo Money From %s", player_name });
				return true;
				break;
			}
			break;
		case eRemoteEvent::ClearWantedLevel:
			switch (lists::clear_wanted_level_script_event_id) {
			case 0:
				break;
			case 1:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Clear Wanted Level";
				return true;
				break;
			case 2:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Clear Wanted Level";
				ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Clear Wanted Level From %s", player_name });
				return true;
				break;
			}
			break;
		case eRemoteEvent::Crash:
		case eRemoteEvent::Crash2:
			switch (lists::crash_script_event_id) {
			case 0:
				break;
			case 1:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Crash";
				return true;
				break;
			case 2:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Crash";
				ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked a Scripted Crash From %s", player_name });
				return true;
				break;
			}
			break;
		case eRemoteEvent::Notification:
			switch (static_cast<eRemoteEvent>(args[2]))
			{
			case eRemoteEvent::NotificationMoneyBanked:
			case eRemoteEvent::NotificationMoneyRemoved:
			case eRemoteEvent::NotificationMoneyStolen:
				switch (lists::notification_script_event_id) {
				case 0:
					break;
				case 1:
					LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Fake Deposit";
					return true;
					break;
				case 2:
					LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Fake Deposit";
					ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Fake Deposit From %s", player_name });
					return true;
					break;
				}
				break;
			}
			break;
		case eRemoteEvent::ForceMission:
			switch (lists::force_to_mission_script_event_id) {
			case 0:
				break;
			case 1:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Force to Mission";
				return true;
				break;
			case 2:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Force to Mission";
				ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Force to Mission From %s", player_name });
				return true;
				break;
			}
			break;
		case eRemoteEvent::GiveCollectible:
			switch (lists::force_to_mission_script_event_id) {
			case 0:
				break;
			case 1:
				if (args[2] == 8) {
					LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Switch Model";
					return true;
				}
				break;
			case 2:
				if (args[2] == 8) {
					LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Switch Model";
					ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Switch Model From %s", player_name });
					return true;
				}
				break;
			}
			break;
		case eRemoteEvent::GtaBanner:
			switch (lists::gta_banner_script_event_id) {
			case 0:
				break;
			case 1:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Gta Banner";
				return true;
				break;
			case 2:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Gta Banner";
				ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Gta Banner From %s", player_name });
				return true;
				break;
			}
			break;
		case eRemoteEvent::MCTeleport:
			switch (lists::teleport_script_event_id) {
			case 0:
				break;
			case 1:
				if (args[3] <= 32) {
					LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Teleport";
					return true;
				}
				break;
			case 2:
				if (args[3] <= 32) {
					LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Teleport";
					ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Remote Teleport From %s", player_name });
					return true;
				}
				break;
			}
			switch (lists::crash_script_event_id) {
			case 0:
				break;
			case 1:
				if (args[3] > 32) {
					LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Crash";
					return true;
				}
				break;
			case 2:
				if (args[3] > 32) {
					LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Crash";
					ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked a Scripted Crash From %s", player_name });
					return true;
				}
				break;
			}

			break;
		case eRemoteEvent::PersonalVehicleDestroyed:
			switch (lists::insurance_message_script_event_id) {
			case 0:
				break;
			case 1:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Insurance Message";
				return true;
				break;
			case 2:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Insurance Message";
				ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Insurance Message From %s", player_name });
				return true;
				break;
			}
			break;
		case eRemoteEvent::RemoteOffradar:
			switch (lists::off_radar_script_event_id) {
			case 0:
				break;
			case 1:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Off the Radar";
				return true;
				break;
			case 2:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Off the Radar";
				ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Off the Radar From %s", player_name });
				return true;
				break;
			}
			break;
		case eRemoteEvent::TSECommand:
			switch (lists::rotate_cam_script_event_id) {
			case 0:
				break;
			case 1:
				if (static_cast<eRemoteEvent>(args[2]) == eRemoteEvent::TSECommandRotateCam) {
					LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Rotate Cam";
					return true;
				}
				break;
			case 2:
				if (static_cast<eRemoteEvent>(args[2]) == eRemoteEvent::TSECommandRotateCam) {
					LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Rotate Cam";
					ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Rotate Cam From %s", player_name });
					return true;
				}
				break;
			}
			break;
		case eRemoteEvent::SendToCayoPerico:
			switch (lists::send_to_cayo_script_event_id) {
			case 0:
				break;
			case 1:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Send to Cayo";
				return true;
				break;
			case 2:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Send to Cayo";
				ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Send to Cayo From %s", player_name });
				return true;
				break;
			}
			break;
		case eRemoteEvent::SendToCutscene:
			switch (lists::send_to_cutscene_script_event_id) {
			case 0:
				break;
			case 1:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Send to Cutscene";
				return true;
				break;
			case 2:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Send to Cutscene";
				ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Send to Cutscene From %s", player_name });
				return true;
				break;
			}
			break;
		case eRemoteEvent::SendToLocation:
		{
			bool known_location = false;

			if (args[2] == 0 && args[3] == 0)
			{
				if (args[4] == 4 && args[5] == 0)
				{
					known_location = true;
					switch (lists::send_to_location_script_event_id) {
					case 0:
						break;
					case 1:
						LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Send to Location";
						return true;
						break;
					case 2:
						LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Send to Location";
						ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Send to Location From %s", player_name });
						return true;
						break;
					}
				}
				else if ((args[4] == 3 || args[4] == 4) && args[5] == 1)
				{
					known_location = true;

					switch (lists::send_to_location_script_event_id) {
					case 0:
						break;
					case 1:
						LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Send to Location";
						return true;
						break;
					case 2:
						LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Send to Location";
						ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Send to Location From %s", player_name });
						return true;
						break;
					}
				}
			}

			if (!known_location)
			{
				switch (lists::send_to_location_script_event_id) {
				case 0:
					break;
				case 1:
					LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Send to Location";
					return true;
					break;
				case 2:
					LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Send to Location";
					ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Send to Location From %s", player_name });
					return true;
					break;
				}
			}
			break;
		}
		case eRemoteEvent::SoundSpam:
			switch (lists::sound_spam_script_event_id) {
			case 0:
				break;
			case 1:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Sound Spam";
				return true;
				break;
			case 2:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Sound Spam";
				ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Sound Spam From %s", player_name });
				return true;
				break;
			}
			break;
		case eRemoteEvent::Spectate:
			switch (lists::spectate_message_script_event_id) {
			case 0:
				break;
			case 1:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Spectate Message";
				return true;
				break;
			case 2:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Spectate Message";
				ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Spectate Message From %s", player_name });
				return true;
				break;
			}
			break;
		case eRemoteEvent::Teleport:
			switch (lists::teleport_script_event_id) {
			case 0:
				break;
			case 1:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Remote Teleport";
				return true;
				break;
			case 2:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Remote Teleport";
				ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Remote Teleport From %s", player_name });
				return true;
				break;
			}
			break;
		case eRemoteEvent::TransactionError:
			switch (lists::transaction_error_script_event_id) {
			case 0:
				break;
			case 1:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Transaction Error";
				return true;
				break;
			case 2:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Transaction Error";
				ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Transaction Error From %s", player_name });
				return true;
				break;
			}
			break;
		case eRemoteEvent::VehicleKick:
			switch (lists::vehicle_kick_script_event_id) {
			case 0:
				break;
			case 1:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Vehicle Kick";
				return true;
				break;
			case 2:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Vehicle Kick";
				ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Vehicle Kick From %s", player_name });
				return true;
				break;
			}
			break;
		case eRemoteEvent::ForceMission2:
			switch (lists::force_to_mission_script_event_id) {
			case 0:
				break;
			case 1:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Force to Mission";
				return true;
				break;
			case 2:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Force to Mission";
				ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Force to Mission From %s", player_name });
				return true;
				break;
			}
			break;
		case eRemoteEvent::NetworkBail:
			switch (lists::network_bail_script_event_id) {
			case 0:
				break;
			case 1:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Network Bail";
				return true;
				break;
			case 2:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Network Bail";
				ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Network Bail From %s", player_name });
				return true;
				break;
			}
			break;
		case eRemoteEvent::TeleportToWarehouse:
			switch (lists::teleport_script_event_id) {
			case 0:
				break;
			case 1:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Remote Teleport";
				return true;
				break;
			case 2:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Remote Teleport";
				ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Remote Teleport From %s", player_name });
				return true;
				break;
			}
			break;
		case eRemoteEvent::StartActivity:
		{
			eActivityType activity = static_cast<eActivityType>(args[2]);
			switch (lists::activity_script_event_id) {
			case 0:
				break;
			case 1:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Start Activity";
				return true;
				break;
			case 2:
				LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Start Activity";
				ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Start Activity From %s", player_name });
				return true;
				break;
			}
			break;
		}
		case eRemoteEvent::InteriorControl:
			int interior = (int)args[2];
			if (interior < 0 || interior > 161) 
			{
				switch (lists::invalid_interior_script_event_id) {
				case 0:
					break;
				case 1:
					LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Invalid Interior";
					return true;
					break;
				case 2:
					LOG(INFO) << "Protections | Blocked Script Event From " << player_name << " Type: Invalid Interior";
					ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Invalid Interior From %s", player_name });
					return true;
					break;
				}
			}
			break;
		}

		return false;
	}
}
