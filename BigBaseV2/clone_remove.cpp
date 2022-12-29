#include "hooking.hpp"
#include "gta/net_object_mgr.hpp"
#include "lists.h"
#include "CObject.h"
#include "gta_util.hpp"
namespace big
{
	bool hooks::hk_clone_remove(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, int32_t object_id, int32_t unk)
	{
		auto object = g_pointers->m_get_net_object(mgr, object_id, true);

		if (gta_util::get_local_ped()) {
			if (object == gta_util::get_local_ped()->m_net_object || object == gta_util::get_local_ped()->m_net_object->GetGameObject()->m_net_object) {
				return false;
			}
		}

		return g_hooking->og_clone_remove.get_original<decltype(&hooks::hk_clone_remove)>()(mgr, src, dst, object_id, unk);
	}
}