#pragma once

#include "common.hpp"
#include "node_types.h"
#include "notify.h"
#include "CObject.h"
#define CLASS_TO_MANGLED_NAME(c) "?AV"#c"@@"


namespace big
{
	inline constexpr uint32_t crash_peds[] = { RAGE_JOAAT("slod_human"), RAGE_JOAAT("slod_small_quadped"), RAGE_JOAAT("slod_large_quadped") };

	inline constexpr uint32_t crash_vehicles[] = { RAGE_JOAAT("arbitergt"), RAGE_JOAAT("astron2"), RAGE_JOAAT("cyclone2"), RAGE_JOAAT("ignus2"), RAGE_JOAAT("s95") };

	inline constexpr uint32_t crash_objects[] = { RAGE_JOAAT("prop_dummy_01"), RAGE_JOAAT("prop_dummy_car"), RAGE_JOAAT("prop_dummy_light"), RAGE_JOAAT("prop_dummy_plane"),
		RAGE_JOAAT("prop_distantcar_night"), RAGE_JOAAT("prop_distantcar_day"), RAGE_JOAAT("hei_bh1_08_details4_em_night"),
		RAGE_JOAAT("dt1_18_sq_night_slod"), RAGE_JOAAT("ss1_12_night_slod"), -1288391198, RAGE_JOAAT("h4_prop_bush_bgnvla_med_01"), RAGE_JOAAT("h4_prop_bush_bgnvla_lrg_01"),
		RAGE_JOAAT("h4_prop_bush_buddleia_low_01"), RAGE_JOAAT("h4_prop_bush_ear_aa"), RAGE_JOAAT("h4_prop_bush_ear_ab"), RAGE_JOAAT("h4_prop_bush_fern_low_01"),
		RAGE_JOAAT("h4_prop_bush_fern_tall_cc"), RAGE_JOAAT("h4_prop_bush_mang_ad"), RAGE_JOAAT("h4_prop_bush_mang_low_aa"), RAGE_JOAAT("h4_prop_bush_mang_low_ab"),
		RAGE_JOAAT("h4_prop_bush_seagrape_low_01"), RAGE_JOAAT("prop_h4_ground_cover"), RAGE_JOAAT("h4_prop_weed_groundcover_01"), RAGE_JOAAT("h4_prop_grass_med_01"),
		RAGE_JOAAT("h4_prop_grass_tropical_lush_01"), RAGE_JOAAT("h4_prop_grass_wiregrass_01"), RAGE_JOAAT("h4_prop_weed_01_plant"), RAGE_JOAAT("h4_prop_weed_01_row"),
		RAGE_JOAAT("urbanweeds02_l1"), RAGE_JOAAT("proc_forest_grass01"), RAGE_JOAAT("prop_small_bushyba"), RAGE_JOAAT("v_res_d_dildo_a"), RAGE_JOAAT("v_res_d_dildo_b"), RAGE_JOAAT("v_res_d_dildo_c"),
		RAGE_JOAAT("v_res_d_dildo_d"), RAGE_JOAAT("v_res_d_dildo_e"), RAGE_JOAAT("v_res_d_dildo_f"), RAGE_JOAAT("v_res_skateboard"), RAGE_JOAAT("prop_battery_01"), RAGE_JOAAT("prop_barbell_01"),
		RAGE_JOAAT("prop_barbell_02"), RAGE_JOAAT("prop_bandsaw_01"), RAGE_JOAAT("prop_bbq_3"), RAGE_JOAAT("v_med_curtainsnewcloth2"), RAGE_JOAAT("bh1_07_flagpoles"),
		92962485
	};

	inline bool is_crash_ped(uint32_t model)
	{
		for (auto iterator : crash_peds)
			if (iterator == model)
				return true;
		return false;
	}

	inline bool is_crash_vehicle(uint32_t model)
	{
		for (auto iterator : crash_vehicles)
			if (iterator == model)
				return true;
		return false;
	}

	inline bool is_crash_object(uint32_t model)
	{
		for (auto iterator : crash_objects)
			if (iterator == model)
				return true;
		return false;
	}

	template<typename T>
	inline T* get_node_from_object(rage::netSyncNodeBase* node)
	{
		constexpr uint64_t hash = CLASS_TO_MANGLED_NAME(T)""_fnv1a;
		if (node->IsParentNode())
		{
			for (auto child = node->m_first_child; child; child = child->m_next_sibling)
			{
				T* attach_node = get_node_from_object<T>(child);
				if (attach_node != nullptr)
					return attach_node;
			}
		}
		else if (node->IsDataNode())
		{
			if (typeid(*node).hash_code() == hash)
				return dynamic_cast<T*>(node);
		}
		return nullptr;
	}

	inline bool detach_node(CPhysicalAttachDataNode* node, uint16_t object_id)
	{
		if (rage::netObject* attached_object = (*g_pointers->m_network_object_mgr)->find_object_by_id(node->m_attached_to, false); attached_object)
		{
			if (rage::netSyncTree* tree = attached_object->GetSyncTree(); tree)
			{
				if (rage::netSyncNodeBase* base_node = tree->m_sync_node; base_node)
				{
					const auto attached_attach_node = get_node_from_object<CPhysicalAttachDataNode>(base_node);
					if (attached_attach_node && attached_attach_node->m_attached)
					{
						if (attached_attach_node->m_attached_to == object_id) {
							return true;
						}
						else {
							return detach_node(attached_attach_node, object_id);
						}
					}
				}
			}
		}

		return false;
	}

	inline bool detach_ped(CPedAttachDataNode* node, uint16_t object_id)
	{
		if (rage::netObject* attached_object = (*g_pointers->m_network_object_mgr)->find_object_by_id(node->m_attached_to, false); attached_object)
		{
			if (rage::netSyncTree* tree = attached_object->GetSyncTree(); tree)
			{
				if (rage::netSyncNodeBase* base_node = tree->m_sync_node; base_node)
				{
					const auto attached_attach_node = get_node_from_object<CPedAttachDataNode>(base_node);
					if (attached_attach_node && attached_attach_node->m_attached)
					{
						if (attached_attach_node->m_attached_to == object_id) {
							return true;
						}
						else {
							return detach_ped(attached_attach_node, object_id);
						}
					}
				}
			}
		}

		return false;
	}

	inline bool get_creation_node(rage::netSyncNodeBase* node, CNetGamePlayer* sender, rage::netObject* object)
	{
		if (node->IsParentNode())
		{
			for (auto child = node->m_first_child; child; child = child->m_next_sibling)
			{
				if (get_creation_node(child, sender, object))
					return true;
			}
		}
		else if (node->IsDataNode())
		{
			switch (typeid(*node).hash_code())
			{
			case "?AVCDoorCreationDataNode@@"_fnv1a:
			{
				const auto creation_node = dynamic_cast<CDoorCreationDataNode*>(node);
				if (is_crash_object(creation_node->m_model))
				{
					LOG(INFO) << "Protections | Blocked Invalid Object (Door Creation) From:  " << sender->get_name();
					ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Invalid Object (Door Creation) From %s", sender->get_name() });
					return true;
				}
				break;
			}
			case "?AVCPickupCreationDataNode@@"_fnv1a:
			{
				const auto creation_node = dynamic_cast<CPickupCreationDataNode*>(node);
				if (is_crash_object(creation_node->m_custom_model))
				{
					LOG(INFO) << "Protections | Blocked Invalid Object (Pickup Creation) From:  " << sender->get_name();
					ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Invalid Object (Pickup Creation) From %s", sender->get_name() });
					return true;
				}
				break;
			}
			case "?AVCPedCreationDataNode@@"_fnv1a:
			{
				const auto creation_node = dynamic_cast<CPedCreationDataNode*>(node);
				if (is_crash_ped(creation_node->m_model))
				{
					LOG(INFO) << "Protections | Blocked Invalid Object (Ped Creation) From:  " << sender->get_name();
					ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Invalid Object (Ped Creation) From %s", sender->get_name() });
					return true;
				}
				else if (creation_node->m_has_prop && is_crash_object(creation_node->m_prop_model))
				{
					LOG(INFO) << "Protections | Blocked Invalid Object (Ped Creation) From:  " << sender->get_name();
					ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Invalid Object (Ped Creation) From %s", sender->get_name() });
					return true;
				}
				break;
			}
			case "?AVCVehicleCreationDataNode@@"_fnv1a:
			{
				const auto vehicle_creation_node = dynamic_cast<CVehicleCreationDataNode*>(node);
				if (is_crash_vehicle(vehicle_creation_node->m_model))
				{
					LOG(INFO) << "Protections | Blocked Invalid Object (Vehicle Creation) From:  " << sender->get_name();
					ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Invalid Object (Vehicle Creation) From %s", sender->get_name() });
					return true;
				}
				break;
			}
			case "?AVCObjectCreationDataNode@@"_fnv1a:
			{
				const auto creation_node = dynamic_cast<CObjectCreationDataNode*>(node);
				if (is_crash_object(creation_node->m_model))
				{
					LOG(INFO) << "Protections | Blocked Invalid Object (Object Creation) From:  " << sender->get_name();
					ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Invalid Object (Object Creation) From %s", sender->get_name() });
					return true;
				}
				break;
			}
			}
		}
		return false;
	}

	inline bool get_attach_node(rage::netSyncNodeBase* node, CNetGamePlayer* sender, rage::netObject* object)
	{
		if (node->IsParentNode())
		{
			for (auto child = node->m_first_child; child; child = child->m_next_sibling)
			{
				if (get_attach_node(child, sender, object))
					return true;
			}
		}
		else if (node->IsDataNode())
		{
			switch (typeid(*node).hash_code())
			{
			case "?AVCPhysicalAttachDataNode@@"_fnv1a:
			{
				const auto attach_node = dynamic_cast<CPhysicalAttachDataNode*>(node);

				static int32_t model_hash = object->GetGameObject() ? object->GetGameObject()->m_model_info->m_hash : 0;
				if (attach_node->m_attached && attach_node->m_attached_to == object->m_object_id && (model_hash != RAGE_JOAAT("hauler2") && model_hash != RAGE_JOAAT("phantom3")))
				{
					LOG(INFO) << "Protections | Blocked Invalid Attachment (Physical) From:  " << sender->get_name();
					ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Invalid Attachment (Physical) From %s", sender->get_name() });
					return true;
				}
				break;
			}
			case "?AVCPedAttachDataNode@@"_fnv1a:
			{
				const auto attach_node = dynamic_cast<CPedAttachDataNode*>(node);
				if (attach_node->m_attached && attach_node->m_attached_to == object->m_object_id)
				{
					LOG(INFO) << "Protections | Blocked Invalid Attachment (Ped) From:  " << sender->get_name();
					ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Invalid Attachment (Ped) From %s", sender->get_name() });
					return true;
				}
				break;
			}
			}
		}
		return false;
	}

	inline bool get_position_node(rage::netSyncNodeBase* node, CNetGamePlayer* sender, rage::netObject* object)
	{
		if (node->IsParentNode())
		{
			for (auto child = node->m_first_child; child; child = child->m_next_sibling)
			{
				if (get_position_node(child, sender, object))
					return true;
			}
		}
		else if (node->IsDataNode())
		{
			switch (typeid(*node).hash_code())
			{
			case "?AVCSectorDataNode@@"_fnv1a:
			{
				const auto sector_node = dynamic_cast<CSectorDataNode*>(node);
				if (sector_node->m_pos_x == 712 || sector_node->m_pos_y == 712 || sector_node->m_pos_z == 712)
				{
					LOG(INFO) << "Protections | Blocked Crash (Host) From:  " << sender->get_name();
					ImGui::InsertNotification({ ImGuiToastType_None, 2600, "Blocked Crash (Host) From %s", sender->get_name() });
					return true;
				}
				break;
			}
			}
		}
		return false;
	}
}