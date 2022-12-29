#pragma once
#include "common.hpp"
#include "text_box.h"
#include "abstract_submenu.h"
#include "gta/vector.hpp"
#include "gta/natives.hpp"
#include "natives.hpp"
namespace big::ui
{
	enum class Font : std::int32_t
	{
		ChaletLondon = 0,
		HouseScript = 1,
		Monospace = 2,
		Wingdings = 3,
		ChaletComprimeCologne = 4,
		Pricedown = 7
	};

	enum class HeaderType : std::int32_t
	{
		Static = 0,
		Gradient = 1
	};

	struct Rectangle
	{
		Vector2 m_Center;
		Vector2 m_Size;

		bool IsInBounds(Vector2 point)
		{
			auto left = m_Center.x - (m_Size.x / 2.f);
			auto right = m_Center.x + (m_Size.x / 2.f);
			auto top = m_Center.y + (m_Size.y / 2.f);
			auto bottom = m_Center.y - (m_Size.y / 2.f);

			if (point.x > right || point.x < left)
				return false;
			if (point.y > top || point.y < bottom)
				return false;

			return true;
		}
	};

	class renderer
	{
	public:
		explicit renderer() = default;
		~renderer() noexcept = default;
		renderer(renderer const&) = delete;
		renderer(renderer&&) = delete;
		renderer& operator=(renderer const&) = delete;
		renderer& operator=(renderer&&) = delete;

		template <typename SubmenuType, typename ...TArgs>
		void new_sub(TArgs&&... args)
		{
			auto sub = std::make_unique<SubmenuType>(std::forward<TArgs>(args)...);
			if (m_SubmenuStack.empty())
			{
				m_SubmenuStack.push(sub.get());
			}

			m_AllSubmenus.push_back(std::move(sub));
		}

		void SwitchToSubmenu(std::uint32_t id)
		{
			for (auto&& sub : m_AllSubmenus)
			{
				if (sub->GetId() == id)
				{
					m_SubmenuStack.push(sub.get());
					return;
				}
			}
		}

		void OnTick();
	public:
		std::mutex m_Mutex;

		Color reder{ 180, 66, 76, 255 };
		Color greener{ 117, 168, 137, 255, };

		int minusOpacity = 0;
		double scroll_speed = 0.15f;

		bool ToggledOn;
		bool m_MouseLocked = false;
		float m_PosX = 0.81f;
		float m_PosY = 0.1f;
		float m_Width = 0.22f;
		float GlareX = 1.145;
		float GlareY = 0.428f;
		float Glarewidth = 1.f;
		std::size_t m_OptionsPerPage = 14;
		bool m_Sounds = true;
		bool m_arrow_indicator = false;

		// Input
		std::int32_t m_OpenDelay = 200;
		std::int32_t m_BackDelay = 300;
		std::int32_t m_EnterDelay = 300;
		std::int32_t m_VerticalDelay = 120;
		std::int32_t m_HorizontalDelay = 120;

		Color Outline{ 74,37,217,255 };
		Font m_BreakFont = Font::HouseScript;
		float m_BreakTextSize = 0.33f;
		// Header
		float m_HeaderHeight = 0.085f;
		bool m_HeaderText = true;
		float m_HeaderTextSize = 1.f;
		Font m_HeaderFont = Font::Pricedown;
		Color m_HeaderBackgroundColor{ 74,37,217,255 };
		Color m_HeaderTextColor{ 255, 255, 255, 255 };
		HeaderType m_HeaderType = HeaderType::Static;

		bool m_HeaderGradientTransparent = false;
		bool m_HeaderGradientFlip = false;
		float m_HeaderGradientStretch = 0.f;
		float m_HeaderGradientFiller = 0.f;
		Color m_HeaderGradientColorLeft{ 0, 186, 255, 255 };
		Color m_HeaderGradientColorRight{ 252, 0, 255, 255 };

		// Submenu bar
		float m_SubmenuBarHeight = 0.032f;
		float m_SubmenuBarTextSize = 0.282f;
		Font m_SubmenuBarFont = Font::ChaletLondon;
		float m_SubmenuBarPadding = 2.1f;
		Color m_SubmenuBarBackgroundColor{ 0, 0, 0, 255 };
		Color m_SubmenuBarTextColor{ 255, 255, 255, 255 };

		float m_rect_width{ 0.0055f };

		// Options
		float m_OptionHeight = 0.0315f;
		float m_OptionTextSize = 0.3f;
		Font m_OptionFont = Font::ChaletLondon;
		float m_OptionPadding = 2.1f;
		float m_rect_padddding = 2.055;
		Color m_OptionSelectedTextColor{ 10, 10, 10, 255 };
		Color m_OptionUnselectedTextColor{ 255, 255, 255, 255 };
		Color m_OptionSelectedBackgroundColor{ 255,255,255,255 };
		Color m_OptionUnselectedBackgroundColor{ 0, 0, 0, 160 };

		// Footer
		float m_FooterHeight = 0.026f;
		float m_FooterSpriteSize = 0.025f;
		float m_FooterSpriteSizeX = 0.028f;
		Color m_FooterBackgroundColor{ 0, 0, 0, 255 };
		Color m_FooterSpriteColor{ 255, 255, 255, 255 };

		int g_render_queue_index = 0;
		std::string g_render_queue[100];
		float g_wrap = 0.063f;

		// Description
		float m_DescriptionHeightPadding = 0.022f;
		float m_DescriptionHeight = 0.03f;
		float m_DescriptionTextSize = 0.25f;
		Font m_DescriptionFont = Font::ChaletLondon;
		Color m_DescriptionBackgroundColor{ 0, 0, 0, 180 };
		Color m_DescriptionTextColor{ 255, 255, 255, 255 };
		float m_DescriptionSpriteSize = 0.005f;
		float m_DescriptionPadding = 2.1f;
		Color m_DescriptionSpriteColor{ 255, 255, 255, 255 };

		void draw_player_info(Player player);
		bool m_enable_player_info;
		Color m_player_info_bg_color{ 0, 0, 0, 190 };

		inline int getIDFromName(const char* name)
		{
			for (std::uint32_t i = 0; i < 32; ++i)
			{
				if (!strcmp(PLAYER::GET_PLAYER_NAME(i), name))
					return i;
			}
			return 0;
		}
		void ResetInput();
		int lines;
	private:
		bool m_OpenKeyPressed = false;
		bool m_BackKeyPressed = false;
		bool m_EnterKeyPressed = false;
		bool m_UpKeyPressed = false;
		bool m_DownKeyPressed = false;
		bool m_LeftKeyPressed = false;
		bool m_RightKeyPressed = false;
		void CheckForInput();
		void HandleInput();
		

		float m_DrawBaseY{};
		void DrawHeader();
		void DrawSubmenuBar(AbstractSubmenu* sub);
		void DrawOption(AbstractOption* opt, bool selected);
		void DrawFooter();
		void DrawDescription();

		void DrawRect(float x, float y, float width, float height, Color color);
		void DrawSprite(const char* dict, const char* texture, float x, float y, float width, float height, Color color, float rotation);
		void DrawLeftText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow);
		void DrawLeftText2(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow);
		void DrawCenteredText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow);
		void DrawRightText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow);
		float GetTextHeight(Font font, float size);
		Vector2 GetSpriteScale(float size);

		bool IsMouseLocked();
		Rectangle GetMenuRect();
		Vector2 GetMousePos();

		std::vector<std::unique_ptr<AbstractSubmenu>> m_AllSubmenus;
		std::stack<AbstractSubmenu*, std::vector<AbstractSubmenu*>> m_SubmenuStack;
	};
}

namespace big
{
	inline ui::renderer m_renderer;
}
