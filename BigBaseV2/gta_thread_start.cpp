#include "hooking.hpp"
#include "native_hooks.h"

namespace big
{
	GtaThread* hooks::hk_gta_thread_start(unsigned int** a1, unsigned int a2)
	{
		GtaThread* new_thread = g_hooking->og_gta_thread_start.get_original<decltype(&hooks::hk_gta_thread_start)>()(a1, a2);

		
		return new_thread;
	}
}
