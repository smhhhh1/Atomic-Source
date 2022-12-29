#pragma once
#include "option.h"
#include "render.h"
namespace big::ui
{
	template <typename DataType, typename PositionType, typename BoolType>
	class toggle_scroll : public BaseOption<toggle_scroll<DataType, PositionType, BoolType>>
	{
	public:
		explicit toggle_scroll() = default;

		template <PositionType N>
		explicit toggle_scroll(const char* text, const char* description, BoolType* b00l, DataType(*array)[N], PositionType* position, bool actionOnHorizontal = false, std::function<void()> action = [] {}) :
			m_Bool(b00l),
			m_Data(&(*array)[0]),
			m_DataSize(N),
			m_Position(position),
			m_ActionOnHorizontal(actionOnHorizontal)
		{
			Base::SetLeftText(text);
			if (description)
				Base::SetDescription(description);
			Base::SetAction(std::move(action));
		}

		template <typename VectorType>
		explicit toggle_scroll(const char* text, const char* description, BoolType* b00l, const VectorType* v, PositionType* position, bool actionOnHorizontal = true, std::function<void()> action = [] {}) :
			m_Bool(b00l),
			m_Data(v->data()),
			m_DataSize(v->size()),
			m_Position(position),
			m_ActionOnHorizontal(actionOnHorizontal)
		{
			Base::SetLeftText(text);
			if (description)
				Base::SetDescription(description);
			Base::SetAction(std::move(action));
		}

		enum class BoolDisplay
		{
			OnOff,
			YesNo
		};
		template <typename BoolType = bool>
		explicit toggle_scroll(const char* text, const char* description, BoolType* b00l, PositionType* position, BoolDisplay displayType, bool displayInverted = true, std::function<void()> action = [] {}) :
			m_Bool(b00l),
			m_DisplayInverted(displayInverted),
			m_DisplayType(displayType)
		{
			Base::SetLeftText(text);
			if (description)
				Base::SetDescription(description);
			Base::SetAction(std::move(action));
		}

		const char* GetRightText() override
		{
			MemoryStringStream stream(Base::m_RightText);

			if (m_Data)
			{
				stream << m_Data[*m_Position];
				stream << " ~c~[" << *m_Position + 1 << "/" << m_DataSize << "]";
			}
			else
			{
				stream << "Unknown ~c~[0/0]";
			}

			return Base::GetRightText();
		}

		bool GetFlag(OptionFlag flag) override
		{
			if (flag == OptionFlag::ChooseBool)
			{
				g_UiManager.ToggledOn = *m_Bool;
				return true;
			}

			return Base::GetFlag(flag);
		}

		void HandleAction(OptionAction action) override
		{
			if (action == OptionAction::EnterPress)
			{
				*m_Bool = !*m_Bool;
			}
			if (action == OptionAction::LeftPress)
			{
				if (m_Data)
				{
					if (*m_Position > 0)
						--(*m_Position);
					else
						*m_Position = static_cast<PositionType>(m_DataSize - 1);

					if (m_ActionOnHorizontal && Base::m_Action)
						std::invoke(Base::m_Action);
				}
			}
			else if (action == OptionAction::RightPress)
			{
				if (m_Data)
				{
					if (*m_Position < m_DataSize - 1)
						++(*m_Position);
					else
						*m_Position = 0;

					if (m_ActionOnHorizontal && Base::m_Action)
						std::invoke(Base::m_Action);
				}
			}

			if (m_Data)
				Base::HandleAction(action);
		}

		~toggle_scroll() noexcept = default;
		toggle_scroll(toggle_scroll const&) = default;
		toggle_scroll& operator=(toggle_scroll const&) = default;
		toggle_scroll(toggle_scroll&&) = default;
		toggle_scroll& operator=(toggle_scroll&&) = default;
	private:
		const DataType* m_Data{};
		PositionType m_DataSize{};
		PositionType* m_Position{};
		bool m_ActionOnHorizontal{};

		BoolType* m_Bool;
		BoolDisplay m_DisplayType;
		BoolType m_DisplayInverted = false;

		using Base = BaseOption<toggle_scroll<DataType, PositionType, BoolType>>;
	};
}
