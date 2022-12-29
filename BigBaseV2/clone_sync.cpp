#include "hooking.hpp"
#include "notify.h"
#include "caller.hpp"
#include "gta/net_object_mgr.hpp"
#include "node_helpers.h"
#include "lists.h"
#include "CObject.h"
#include "protections_entity.h"
namespace big
{
	
	int64_t hooks::hk_received_clone_sync(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, eNetObjType object_type, uint16_t object_id, rage::datBitBuffer* buffer, uint16_t unk, uint32_t timestamp)
	{
		if (object_type < eNetObjType::NET_OBJ_TYPE_AUTOMOBILE || object_type > eNetObjType::NET_OBJ_TYPE_TRAIN)
		{
			return eAckCode::ACKCODE_FAIL;
		}

		if (auto net_obj = g_pointers->m_get_net_object(mgr, object_id, true); net_obj && net_obj->m_object_type != (int16_t)object_type)
		{

			return eAckCode::ACKCODE_FAIL;
		}

		if (auto sync_tree = g_pointers->m_get_sync_tree_for_type(mgr, object_type); sync_tree && *g_pointers->m_is_session_started)
		{
			if (!is_valid_ptr(sync_tree)) {
				return false;
			}

			if (sync_tree->m_child_node_count <= 0 || sync_tree->m_child_node_count > 100) {
				return false;
			}
		}

		if (lists::entity_type_pos == 0) {

			if (object_type == eObjType::carObjType && protections::entity::vars::m_vars.m_sync_car) {
				return false;
			}
			if (object_type == eObjType::bikeObjType && protections::entity::vars::m_vars.m_sync_bike) {
				return false;
			}
			if (object_type == eObjType::boatObjType && protections::entity::vars::m_vars.m_sync_boat) {
				return false;
			}
			if (object_type == eObjType::doorObjType && protections::entity::vars::m_vars.m_sync_door) {
				return false;
			}
			if (object_type == eObjType::heliObjType && protections::entity::vars::m_vars.m_sync_heli) {
				return false;
			}
			if (object_type == eObjType::objType && protections::entity::vars::m_vars.m_sync_object) {
				return false;
			}
			if (object_type == eObjType::pickupObjType && protections::entity::vars::m_vars.m_sync_pickup) {
				return false;
			}
			if (object_type == eObjType::pickupPlacementObjType && protections::entity::vars::m_vars.m_sync_pickup_placement) {
				return false;
			}
			if (object_type == eObjType::planeObjType && protections::entity::vars::m_vars.m_sync_plane) {
				return false;
			}
			if (object_type == eObjType::playerObjType && protections::entity::vars::m_vars.m_sync_player) {
				return false;
			}
			if (object_type == eObjType::pedObjType && protections::entity::vars::m_vars.m_sync_ped) {
				return false;
			}
			if (object_type == eObjType::submarineObjType && protections::entity::vars::m_vars.m_sync_sub) {
				return false;
			}
			if (object_type == eObjType::trainObjType && protections::entity::vars::m_vars.m_sync_train) {
				return false;
			}
			if (object_type == eObjType::trailerObjType && protections::entity::vars::m_vars.m_sync_trailer) {
				return false;
			}

		}
	
		sync_sender = src;
		return g_hooking->og_received_clone_sync.get_original<decltype(&hooks::hk_received_clone_sync)>()(mgr, src, dst, object_type, object_id, buffer, unk, timestamp);
	}
}
