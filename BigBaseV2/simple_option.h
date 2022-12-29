#pragma once
#include "option.h"

namespace big::ui
{
	class simple_option : public BaseOption<simple_option>
	{
	public:
		explicit simple_option() = default;
		explicit simple_option(const char* text, const char* description = nullptr, std::function<void()> action = [] {})
		{
			SetLeftText(text);
			if (description)
				SetDescription(description);
			SetAction(std::move(action));
		}

		bool GetFlag(OptionFlag flag) override
		{
			if (flag == OptionFlag::Option)
			{
				return true;
			}

			return BaseOption::GetFlag(flag);
		}
		~simple_option() noexcept = default;
		simple_option(simple_option const&) = default;
		simple_option& operator=(simple_option const&) = default;
		simple_option(simple_option&&) = default;
		simple_option& operator=(simple_option&&) = default;
	};
}
