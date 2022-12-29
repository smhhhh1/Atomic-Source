#pragma once
#include "option.h"
#include "render.h"
#include "timer.h"
namespace big::ui
{
	template <typename NumberType>
	class number_option : public BaseOption<number_option<NumberType>>
	{
	public:
		explicit number_option() = default;
		explicit number_option(const char* text, const char* description, NumberType* number, NumberType min, NumberType max, NumberType step = 1, std::size_t precision = 3, bool actionOnHorizontal = true, const char* prefix = "", const char* suffix = "", std::function<void()> action = [] {}) :
			m_ActionOnHorizontal(actionOnHorizontal),
			m_Number(number),
			m_Min(min),
			m_Max(max),
			m_Step(step),
			m_Precision(precision)
		{
			Base::SetLeftText(((std::string)text).c_str());
			if (description)
				Base::SetDescription(description);
			Base::SetAction(std::move(action));
			std::strncpy(&m_Prefix[0], prefix, sizeof(m_Prefix) - 1);
			std::strncpy(&m_Suffix[0], suffix, sizeof(m_Suffix) - 1);
		}

		~number_option() noexcept = default;
		number_option(number_option const&) = default;
		number_option& operator=(number_option const&) = default;
		number_option(number_option&&) = default;
		number_option& operator=(number_option&&) = default;

		const char* GetRightText() override
		{
			MemoryStringStream stream(Base::m_RightText);
			stream
				<< std::setprecision(m_Precision)
				<< std::fixed
				<< m_Prefix
				<< static_cast<DisplayType>(*m_Number)
				<< m_Suffix;
			return Base::GetRightText();
		}
		bool GetFlag(OptionFlag flag) override
		{
			if (flag == OptionFlag::Numberable)
			{
				return true;
			}

			return Base::GetFlag(flag);
		}

		void SetValue(double text) override
		{
			if (m_Max < text)
				*m_Number = m_Max;
			else if (m_Min > text)
				*m_Number = m_Min;
			else *m_Number = text;
			std::invoke(Base::m_Action);

		}
		void HandleAction(OptionAction action) override
		{
			if (action == OptionAction::LeftPress)
			{
				if (*m_Number - m_Step < m_Min)
					*m_Number = m_Max;
				else
					*m_Number -= m_Step;

				if (m_ActionOnHorizontal && Base::m_Action)
					std::invoke(Base::m_Action);
			}
			else if (action == OptionAction::RightPress)
			{
				if (*m_Number + m_Step > m_Max)
					*m_Number = m_Min;
				else
					*m_Number += m_Step;

				if (m_ActionOnHorizontal && Base::m_Action)
					std::invoke(Base::m_Action);
			}

			Base::HandleAction(action);
		}
	private:
		char m_Prefix[32] = {};
		char m_Suffix[32] = {};
		bool m_ActionOnHorizontal{};

		NumberType* m_Number{};
		NumberType m_Min{};
		NumberType m_Max{};
		NumberType m_Step{};
		std::size_t m_Precision{};


		using Base = BaseOption<number_option<NumberType>>;
		using DisplayType = std::conditional_t<sizeof(NumberType) == 1, std::uint32_t, NumberType>;
	};
}
