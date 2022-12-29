#include "hooking.hpp"
#include "script_patcher_service.hpp"
#include "native_hooks.h"

namespace big
{
	bool hooks::hk_init_native_tables(rage::scrProgram* program)
	{
		bool ret = g_hooking->og_init_native_tables.get_original<decltype(&hooks::hk_init_native_tables)>()(program);
		//g_script_patcher_service->on_script_load(program);
		g_native_hooks->hook_program(program);

		return ret;
	}
}