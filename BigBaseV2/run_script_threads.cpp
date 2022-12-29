#include "hooking.hpp"
#include "script_mgr.hpp"
#include "invoker.hpp"
#include "gta/script_handler.hpp"
namespace big
{
	bool hooks::run_script_threads(std::uint32_t ops_to_execute)
	{

		g_native_invoker.cache_handlers();

		if (g_running)
		{
			g_script_mgr.tick();
		}

		return g_hooking->m_run_script_threads_hook.get_original<functions::run_script_threads_t>()(ops_to_execute);

	}
}