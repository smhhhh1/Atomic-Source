#pragma once
#include "option.h"

namespace big::ui
{
	class break_option : public BaseOption<break_option>
	{
	public:
		explicit break_option() = default;
		explicit break_option(const char* text)
		{
			SetLeftText(text);

		}

		bool GetFlag(OptionFlag flag) override
		{
			if (flag == OptionFlag::Break)
			{
				return true;
			}

			return BaseOption::GetFlag(flag);
		}
		~break_option() noexcept = default;
		break_option(break_option const&) = default;
		break_option& operator=(break_option const&) = default;
		break_option(break_option&&) = default;
		break_option& operator=(break_option&&) = default;
	};
}
