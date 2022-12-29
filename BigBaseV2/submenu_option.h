#pragma once
#include "option.h"
#include "render.h"

namespace big::ui
{
	class submenu : public BaseOption<submenu>
	{
	public:
		explicit submenu() = default;
		explicit submenu(const char* text, const char* description, std::uint32_t subId, std::function<void()> action = [] {}) :
			m_SubId(subId)
		{
			SetLeftText(text);
			if (description)
				SetDescription(description);
			SetAction(std::move(action));
		}

		~submenu() noexcept = default;
		submenu(submenu const&) = default;
		submenu& operator=(submenu const&) = default;
		submenu(submenu&&) = default;
		submenu& operator=(submenu&&) = default;

		void HandleAction(OptionAction action) override
		{
			if (action == OptionAction::EnterPress)
			{
				m_renderer.SwitchToSubmenu(m_SubId);
			}

			BaseOption::HandleAction(action);
		}

		bool GetFlag(OptionFlag flag) override
		{
			if (flag == OptionFlag::Enterable)
			{
				return true;
			}

			return BaseOption::GetFlag(flag);
		}
	private:
		std::uint32_t m_SubId{};
	};
}
