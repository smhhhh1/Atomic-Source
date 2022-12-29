#pragma once
#include "submenu.h"

namespace big::ui
{
	class sub : public BaseSubmenu<sub>
	{
	public:
		explicit sub() = default;
		~sub() noexcept = default;
		explicit sub(const char* name, std::uint32_t id, std::function<void(sub*)> action)
		{
			SetName(name);
			SetId(id);
			SetAction(std::move(action));
		}

		sub(sub const&) = default;
		sub& operator=(sub const&) = default;
		sub(sub&&) = default;
		sub& operator=(sub&&) = default;
	};
}
