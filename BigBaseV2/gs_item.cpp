#include "hooking.hpp"
#include "protections.h"

namespace big
{
	bool hooks::hk_update_presence_attribute_int(void* data, int index, char* attribute, std::uint64_t value)
	{
		auto hash = rage::joaat(attribute);
		if (protections::vars::m_vars.m_block_resolves &&
			(hash == RAGE_JOAAT("gstok") || hash == RAGE_JOAAT("gsid") || hash == RAGE_JOAAT("gstype") || hash == RAGE_JOAAT("gshost") || hash == RAGE_JOAAT("gsjoin")))
		{
			return true;
		}

		return g_hooking->og_update_presence_attribute_int.get_original<decltype(&hooks::hk_update_presence_attribute_int)>()(data, index, attribute, value);
	}

	bool hooks::hk_update_presence_attribute_string(void* data, int index, char* attribute, char* value)
	{
		auto hash = rage::joaat(attribute);
		if (protections::vars::m_vars.m_block_resolves && hash == RAGE_JOAAT("gsinfo"))
		{
			return true;
		}


		return g_hooking->og_update_presence_attribute_string.get_original<decltype(&hooks::hk_update_presence_attribute_string)>()(data, index, attribute, value);
	}
}