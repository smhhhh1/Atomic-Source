#include "hooking.hpp"
#include "gta/net_object_mgr.hpp"
#include "lists.h"
#include "CObject.h"
#include "protections_entity.h"
namespace big
{
	bool hooks::hk_received_clone_create(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, eNetObjType object_type, int32_t object_id, int32_t object_flag, rage::datBitBuffer* buffer, int32_t timestamp)
	{
		if (object_type < eNetObjType::NET_OBJ_TYPE_AUTOMOBILE || object_type > eNetObjType::NET_OBJ_TYPE_TRAIN)
		{
			return true;
		}
		if (auto net_obj = g_pointers->m_get_net_object(mgr, object_id, true); net_obj && net_obj->m_object_type != (int16_t)object_type)
		{

			return eAckCode::ACKCODE_FAIL;
		}

		if (lists::entity_type_pos == 1) {

			if (object_type == eObjType::carObjType && protections::entity::vars::m_vars.m_car) {
				return false;
			}
			if (object_type == eObjType::bikeObjType && protections::entity::vars::m_vars.m_bike) {
				return false;
			}
			if (object_type == eObjType::boatObjType && protections::entity::vars::m_vars.m_boat) {
				return false;
			}
			if (object_type == eObjType::doorObjType && protections::entity::vars::m_vars.m_door) {
				return false;
			}
			if (object_type == eObjType::heliObjType && protections::entity::vars::m_vars.m_heli) {
				return false;
			}
			if (object_type == eObjType::objType && protections::entity::vars::m_vars.m_object) {
				return false;
			}
			if (object_type == eObjType::pickupObjType && protections::entity::vars::m_vars.m_pickup) {
				return false;
			}
			if (object_type == eObjType::pickupPlacementObjType && protections::entity::vars::m_vars.m_pickup_placement) {
				return false;
			}
			if (object_type == eObjType::planeObjType && protections::entity::vars::m_vars.m_plane) {
				return false;
			}
			if (object_type == eObjType::playerObjType && protections::entity::vars::m_vars.m_player) {
				return false;
			}
			if (object_type == eObjType::pedObjType && protections::entity::vars::m_vars.m_ped) {
				return false;
			}
			if (object_type == eObjType::submarineObjType && protections::entity::vars::m_vars.m_sub) {
				return false;
			}
			if (object_type == eObjType::trainObjType && protections::entity::vars::m_vars.m_train) {
				return false;
			}
			if (object_type == eObjType::trailerObjType && protections::entity::vars::m_vars.m_trailer) {
				return false;
			}

		}

		return g_hooking->og_received_clone_create.get_original<decltype(&hooks::hk_received_clone_create)>()(mgr, src, dst, object_type, object_id, object_flag, buffer, timestamp);
	}
}