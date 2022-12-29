#pragma once
#include "option.h"
#include "render.h"

namespace big::ui
{
    template <typename NumberType, typename BoolType = bool>
    class toggle_number_option : public BaseOption<toggle_number_option<NumberType, BoolType>>
    {
    public:
        explicit toggle_number_option() = default;
        explicit toggle_number_option(const char* text, const char* description, BoolType* b00l, NumberType* number, NumberType min, NumberType max, NumberType step = 1, std::size_t precision = 3, bool actionOnHorizontal = true, const char* prefix = "", const char* suffix = "", std::function<void()> action = [] {}) :
            m_ActionOnHorizontal(actionOnHorizontal),
            m_Bool(b00l),
            m_Number(number),
            m_Min(min),
            m_Max(max),
            m_Step(step),
            m_Precision(precision)
        {
            Base::SetLeftText(text);
            if (description)
                Base::SetDescription(description);
            Base::SetAction(std::move(action));
            Base::HandleAction(*m_Bool ? OptionAction::EnterPress : OptionAction::EnterPress);
            std::strncpy(&m_Prefix[0], prefix, sizeof(m_Prefix) - 1);
            std::strncpy(&m_Suffix[0], suffix, sizeof(m_Suffix) - 1);
        }

        ~toggle_number_option() noexcept = default;
        toggle_number_option(toggle_number_option const&) = default;
        toggle_number_option& operator=(toggle_number_option const&) = default;
        toggle_number_option(toggle_number_option&&) = default;
        toggle_number_option& operator=(toggle_number_option&&) = default;

        bool GetFlag(OptionFlag flag) override
        {
            if (flag == OptionFlag::BoolAndNumber)
            {
                m_renderer.ToggledOn = *m_Bool;
                return true;
            }

            return Base::GetFlag(flag);
        }
        const char* GetRightText() override
        {
            MemoryStringStream stream(Base::m_RightText);
            stream
                << std::setprecision(m_Precision)
                << std::fixed
                << m_Prefix
                << static_cast<DisplayType>(*m_Number)
                << "/"
                << static_cast<DisplayType>(m_Max)
                << m_Suffix;
            return Base::GetRightText();
        }

        void HandleAction(OptionAction action) override
        {
            if (action == OptionAction::EnterPress)
            {
                *m_Bool = !*m_Bool;
            }
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
                Base::HandleAction(action);
            }


        }
    private:
        char m_Prefix[32] = {};
        char m_Suffix[32] = {};
        bool m_ActionOnHorizontal{};
        BoolType* m_Bool;
        NumberType* m_Number{};
        NumberType m_Min{};
        NumberType m_Max{};
        NumberType m_Step{};
        std::size_t m_Precision{};


        using Base = BaseOption<toggle_number_option<NumberType, BoolType>>;
        using DisplayType = std::conditional_t<sizeof(NumberType) == 1, std::uint32_t, NumberType>;
    };
}