#include "hooking.hpp"
#include "script.hpp"
namespace big
{
	void* hooks::convert_thread_to_fiber(void* param)
	{
		TRY_CLAUSE
		{
			if (IsThreadAFiber())
			{
				return GetCurrentFiber();
			}

			return g_hooking->m_convert_thread_to_fiber_hook.get_original<decltype(&convert_thread_to_fiber)>()(param);
		} EXCEPT_CLAUSE
			return nullptr;
	}
}