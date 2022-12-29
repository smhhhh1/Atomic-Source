#pragma once
#include "option.h"
#include "render.h"
namespace big::ui
{
	template <typename DataType, typename PositionType>
	class scroll_option : public BaseOption<scroll_option<DataType, PositionType>>
	{
	public:
		explicit scroll_option() = default;

		template <PositionType N>
		explicit scroll_option(const char* text, const char* description, DataType(*array)[N], PositionType* position, bool actionOnHorizontal = false, std::function<void()> action = [] {}) :
			m_Data(&(*array)[0]),
			m_DataSize(N),
			m_Position(position),
			m_ActionOnHorizontal(actionOnHorizontal)
		{
			Base::SetLeftText(((std::string)text + "").c_str());
			if (description)
				Base::SetDescription(description);
			Base::SetAction(std::move(action));
		}

		template <typename VectorType>
		explicit scroll_option(const char* text, const char* description, const VectorType* v, PositionType* position, bool actionOnHorizontal = false, std::function<void()> action = [] {}) :
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

		const char* GetRightText() override
		{

			MemoryStringStream stream(Base::m_RightText);

			if (m_Data)
			{
				stream << m_Data[*m_Position];
				stream << " ~c~[" << *m_Position + 1 << " / " << m_DataSize << "]";
			}
			else
			{
				stream << "Unknown ~c~[0 / 0]";
			}

			return Base::GetRightText();
		}
		bool GetFlag(OptionFlag flag) override
		{
			if (flag == OptionFlag::Chooseable)
			{
				return true;
			}

			return Base::GetFlag(flag);
		}
		void DrawSprite(const char* dict, const char* texture, float x, float y, float width, float height, Color color, float rotation)
		{
			if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(dict))
			{
				GRAPHICS::DRAW_SPRITE(dict, texture, x, y, width, height, rotation, color.r, color.g, color.b, color.a, 0);
			}
			else
			{
				GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(dict, false);
			}
		}
		Vector2 GetSpriteScale(float size)
		{
			int x;
			int y;
			GRAPHICS::_GET_ACTIVE_SCREEN_RESOLUTION(&x, &y);

			return { (static_cast<float>(y) / static_cast<float>(x)) * size, size };
		}
		void HandleAction(OptionAction action) override
		{
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
			{
				Base::HandleAction(action);

			}


		}

		~scroll_option() noexcept = default;
		scroll_option(scroll_option const&) = default;
		scroll_option& operator=(scroll_option const&) = default;
		scroll_option(scroll_option&&) = default;
		scroll_option& operator=(scroll_option&&) = default;
	private:
		const DataType* m_Data{};
		PositionType m_DataSize{};
		PositionType* m_Position{};
		bool m_ActionOnHorizontal{};

		using Base = BaseOption<scroll_option<DataType, PositionType>>;
	};
}
