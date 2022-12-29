#include "hooking.hpp"
#include "native_hooks.h"

namespace big
{
	rage::eThreadState hooks::hk_gta_thread_kill(GtaThread* thread)
	{
		const auto result = g_hooking->og_gta_thread_kill.get_original<decltype(&hooks::hk_gta_thread_kill)>()(thread);

		//g_native_hooks->do_cleanup_for_thread(thread);

		return result;
	}
}
