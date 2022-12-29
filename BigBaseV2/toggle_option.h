#pragma once
#include "option.h"
#include "render.h"

namespace big::ui
{
	enum class BoolDisplay
	{
		OnOff,
		YesNo
	};

	template <typename BoolType = bool>
	class toggle_option : public BaseOption<toggle_option<BoolType>>
	{
	public:
		explicit toggle_option(const char* text, const char* description, BoolType* b00l, bool displayInverted = false, std::function<void()> action = [] {}) :
			m_Bool(b00l),
			m_DisplayInverted(displayInverted)
		{
			Base::SetLeftText(text);
			if (description)
				Base::SetDescription(description);
			Base::SetAction(std::move(action));
		}

		~toggle_option() noexcept = default;
		toggle_option(toggle_option const&) = default;
		toggle_option& operator=(toggle_option const&) = default;
		toggle_option(toggle_option&&) = default;
		toggle_option& operator=(toggle_option&&) = default;

		void HandleAction(OptionAction action) override
		{
			if (action == OptionAction::EnterPress)
			{
				*m_Bool = !*m_Bool;
			}

			Base::HandleAction(action);
		}
		bool GetFlag(OptionFlag flag) override
		{
			if (flag == OptionFlag::BoolOption)
			{
				m_renderer.ToggledOn = *m_Bool;
				return true;
			}

			return Base::GetFlag(flag);
		}
	private:
		BoolType* m_Bool;
		BoolType m_DisplayInverted = false;

		using Base = BaseOption<toggle_option<BoolType>>;
	};
}