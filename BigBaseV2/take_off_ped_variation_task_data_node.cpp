#include "hooking.hpp"
#include "lists.h"
#include "notify.h"
namespace big
{
	void hooks::hk_serialize_take_off_ped_variation_task(ClonedTakeOffPedVariationInfo* info, rage::CSyncDataBase* serializer)
	{
		g_hooking->og_serialize_take_off_ped_variation_task.get_original<decltype(&hooks::hk_serialize_take_off_ped_variation_task)>()(info, serializer);
		if (info->m_parachute_override_model_hash != 0 && info->m_parachute_override_model_hash != RAGE_JOAAT("p_parachute_s"))
		{
			info->m_parachute_override_model_hash = 0;
		}
	}
}