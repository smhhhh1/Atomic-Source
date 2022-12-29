#include "hooking.hpp"
#include "lists.h"
#include "notify.h"
#include "CObject.h"
#include "caller.hpp"
namespace big
{
	void hooks::hk_vehicle_control_data_node(rage::netObject* object, CVehicleControlDataNode* node)
	{

		if (*(bool*)(node + 0x119)) {
			uint64_t net_obj = *(uint64_t*)((uint64_t)object - 0x1B0);
			if (!is_valid_ptr(net_obj)) {
				return;
			}

			uint64_t vtable = *(uint64_t*)net_obj;
			if (is_valid_vtable(vtable)) {
				if (call<uint64_t>(*(uint64_t*)(vtable + 0x620), net_obj) == 0) {
					return;
				}
			}
		}

		auto veh = *reinterpret_cast<rage::fwEntity**>(reinterpret_cast<uint64_t>(object) - 432);
		if (node->m_unk && veh->m_model_info->m_hash != rage::joaat("stromberg") && veh->m_model_info->m_hash != rage::joaat("toreador"))
		{
			LOG(INFO) << "[Protections] Blocked Vehicle Control";
			return;
		}
		if (lists::crash_model_check(veh->m_model_info->m_hash))
		{
			return;
		}

		g_hooking->og_vehicle_control_data_node.get_original<decltype(&hk_vehicle_control_data_node)>()(object, node);
	}
}