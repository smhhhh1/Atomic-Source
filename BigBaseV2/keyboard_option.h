#pragma once
#include "option.h"

namespace big::ui
{
	class keyboard : public BaseOption<keyboard>
	{
	public:
		explicit keyboard() = default;
		explicit keyboard(const char* text, const char* description = nullptr, std::function<void()> action = [] {})
		{
			SetLeftText(text);
			if (description)
				SetDescription(description);
			SetAction(std::move(action));
		}

		bool GetFlag(OptionFlag flag) override
		{
			if (flag == OptionFlag::Keyboard)
			{
				return true;
			}

			return BaseOption::GetFlag(flag);
		}
		~keyboard() noexcept = default;
		keyboard(keyboard const&) = default;
		keyboard& operator=(keyboard const&) = default;
		keyboard(keyboard&&) = default;
		keyboard& operator=(keyboard&&) = default;
	};
}
