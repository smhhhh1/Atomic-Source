#include "render.h"
#include "timer.h"
#include "natives.hpp"
#include "menu.h"
#include "caller.hpp"
#include "gta/joaat.hpp"
#include "menu.h"
#include "script_global.hpp"

namespace big::ui
{

	bool firstTick = false;
	float target = 0;
	float selectedTarget = 0;
	double current = 0;
	float scrollCurrent = 0;
	float scrollTarget = 0;
	int currentOpacity;
	int targetOpacity;
	int currentSelected, fullAmount;
	double opt_start = 0;
	double opt_end = 0;
	double lerp(double start, double end, double amount) {
		return start * (1 - amount) + end * amount;
	}
	bool FileExists(const std::string& fileName)
	{
		struct stat buffer;
		return (stat(fileName.c_str(), &buffer) == 0);
	}
	void YTD()
	{

		std::string MenuFolderPath = "C:\\Atomic\\";
		std::string name = "Textures.ytd";

		const std::string fullPath = MenuFolderPath + name;

		uint32_t textureID;
		if (FileExists(fullPath))
			g_pointers->m_register_file(&textureID, fullPath.c_str(), true, name.c_str(), false);


	}

	void renderer::OnTick()
	{
		if (!firstTick)
		{
			minusOpacity = 255;
			std::thread thr([&] {
				while (big::g_running)
				{
					//defining scopes for cleanlyness
					{
						if (minusOpacity != 0 && GetTickCount() % 2 == 0)
						{
							minusOpacity--;
						}
					}


					{
						if (currentOpacity != targetOpacity) currentOpacity = lerp(currentOpacity, targetOpacity, scroll_speed * 2);
						if ((currentOpacity > targetOpacity - 0.0005) && (currentOpacity < targetOpacity + 0.0005))
						{
							currentOpacity = targetOpacity;
						}
						minusOpacity = currentOpacity;
					}

					{
						if (scrollCurrent != scrollTarget) scrollCurrent = lerp(scrollCurrent, scrollTarget, scroll_speed);
						if ((scrollCurrent > scrollTarget - 0.0005) && (scrollCurrent < scrollTarget + 0.0005))
						{
							scrollCurrent = scrollTarget;
						}
					}

					{
						if (current != selectedTarget) current = lerp(current, selectedTarget, scroll_speed);
						if ((current > selectedTarget - 0.0005) && (current < selectedTarget + 0.0005))
						{
							current = selectedTarget;
						}
					}
					{
						if (minusOpacity != targetOpacity) minusOpacity = lerp(minusOpacity, targetOpacity, 0.0025f);
						if ((minusOpacity > targetOpacity - 2) && (minusOpacity < targetOpacity + 2))
						{
							minusOpacity = targetOpacity;
						}
						//minusOpacity = currentOpacity;
					}

					std::this_thread::sleep_for(3.5ms);
				}
				});
			thr.detach();
		}

		firstTick = true;
		std::lock_guard lock(m_Mutex);

		


		CheckForInput();
		HandleInput();
		YTD();
		DrawSprite("Textures", "arrows", m_PosX + (m_Width / m_OptionPadding) - 0.015, m_DrawBaseY + (m_OptionHeight / 2.f), 0.02, 0.02, { 0, 0, 0, 0 }, 0.0);
		if (menu::g_gui.m_opened)
		{

			
			PAD::DISABLE_CONTROL_ACTION(0, 27, true); // Disable phone

			m_DrawBaseY = m_PosY;
			DrawHeader();
			if (!m_SubmenuStack.empty())
			{

				auto sub = m_SubmenuStack.top();
				sub->Reset();
				sub->Execute();

				

				DrawSubmenuBar(sub);
				if (sub->GetNumOptions() != 0)
				{
					std::size_t startPoint = 0;
					std::size_t endPoint = sub->GetNumOptions() > m_OptionsPerPage ? m_OptionsPerPage : sub->GetNumOptions();
					if (sub->GetNumOptions() > m_OptionsPerPage && sub->GetSelectedOption() >= m_OptionsPerPage)
					{
						startPoint = sub->GetSelectedOption() - m_OptionsPerPage + 1;
						endPoint = sub->GetSelectedOption() + 1;
					}
					float tmp_base = m_DrawBaseY;
					for (std::size_t i = startPoint, j = 0; i < endPoint; ++i, ++j)
					{
						float tmp_point = tmp_base + ((m_OptionHeight) / 2.f);
						if (i == startPoint) opt_start = tmp_point;
						if (i == endPoint - 1) opt_end = tmp_point;

						DrawRect(
							m_PosX,
							tmp_point,
							m_Width,
							m_OptionHeight,
							m_OptionUnselectedBackgroundColor);
						

						fullAmount = endPoint;
						tmp_base += m_OptionHeight;
					}
					for (std::size_t i = startPoint, j = 0; i < endPoint; ++i, ++j)
					{

						

						DrawOption(sub->GetOption(i), i == sub->GetSelectedOption());
					}
				}
				if (sub->GetNumOptions() > m_OptionsPerPage) {
					DrawFooter();
				}
			}
			
			
			DrawDescription();
		}
	}

	void renderer::CheckForInput()
	{
		ResetInput();

		m_OpenKeyPressed = IsKeyPressed(VK_F4);
		m_BackKeyPressed = IsKeyPressed(VK_BACK);
		m_EnterKeyPressed = IsKeyPressed(VK_RETURN);
		m_UpKeyPressed = IsKeyPressed(VK_UP);
		m_DownKeyPressed = IsKeyPressed(VK_DOWN);
		m_LeftKeyPressed = IsKeyPressed(VK_LEFT);
		m_RightKeyPressed = IsKeyPressed(VK_RIGHT);
	}

	void renderer::HandleInput()
	{
		static auto openTicker = GetTickCount();
		if (m_OpenKeyPressed && GetTickCount() - openTicker >= static_cast<std::uint32_t>(m_OpenDelay))
		{
			openTicker = GetTickCount();
			menu::g_gui.m_opened ^= true;

			if (m_Sounds)
				AUDIO::PLAY_SOUND_FRONTEND(-1, menu::g_gui.m_opened ? "SELECT" : "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
		}

		static Timer backTimer(0ms);
		backTimer.SetDelay(std::chrono::milliseconds(m_BackDelay));
		if (menu::g_gui.m_opened && m_BackKeyPressed && backTimer.Update())
		{
			if (m_Sounds)
				AUDIO::PLAY_SOUND_FRONTEND(-1, "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

			if (m_SubmenuStack.size() <= 1)
			{
				menu::g_gui.m_opened = false;
			}
			else
			{
				m_SubmenuStack.pop();
			}
		}

		if (menu::g_gui.m_opened && !m_SubmenuStack.empty())
		{
			auto sub = m_SubmenuStack.top();

			static Timer enterTimer(0ms);
			enterTimer.SetDelay(std::chrono::milliseconds(m_EnterDelay));
			if (m_EnterKeyPressed && sub->GetNumOptions() != 0 && enterTimer.Update())
			{
				if (m_Sounds)
					AUDIO::PLAY_SOUND_FRONTEND(-1, "SELECT", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				if (auto opt = sub->GetOption(sub->GetSelectedOption()))
				{
					opt->HandleAction(OptionAction::EnterPress);
				}
			}

			static Timer upTimer(0ms);
			upTimer.SetDelay(std::chrono::milliseconds(m_VerticalDelay));
			if (m_UpKeyPressed && sub->GetNumOptions() != 0 && upTimer.Update())
			{
				if (m_Sounds)
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				sub->ScrollBackward();
			}

			static Timer downTimer(0ms);
			downTimer.SetDelay(std::chrono::milliseconds(m_VerticalDelay));
			if (m_DownKeyPressed && sub->GetNumOptions() != 0 && downTimer.Update())
			{
				if (m_Sounds)
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				sub->ScrollForward();
			}

			static Timer leftTimer(0ms);
			leftTimer.SetDelay(std::chrono::milliseconds(m_HorizontalDelay));
			if (m_LeftKeyPressed && sub->GetNumOptions() != 0 && leftTimer.Update())
			{
				if (m_Sounds)
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_LEFT_RIGHT", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				if (auto opt = sub->GetOption(sub->GetSelectedOption()))
				{
					opt->HandleAction(OptionAction::LeftPress);
				}
			}

			static Timer rightTimer(0ms);
			rightTimer.SetDelay(std::chrono::milliseconds(m_HorizontalDelay));
			if (m_RightKeyPressed && sub->GetNumOptions() != 0 && rightTimer.Update())
			{
				if (m_Sounds)
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_LEFT_RIGHT", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				if (auto opt = sub->GetOption(sub->GetSelectedOption()))
				{
					opt->HandleAction(OptionAction::RightPress);
				}
			}
		}
	}

	void renderer::ResetInput()
	{
		m_OpenKeyPressed = false;
		m_BackKeyPressed = false;
		m_EnterKeyPressed = false;
		m_UpKeyPressed = false;
		m_DownKeyPressed = false;
		m_LeftKeyPressed = false;
		m_RightKeyPressed = false;
	}
	float conv360(float base, float min, float max) {

		float fVar0;
		if (min == max) return min;
		fVar0 = max - min;
		base -= round(base - min / fVar0) * fVar0;
		if (base < min) base += fVar0;
		return base;
	}
	int gGlareHandle;
	int scaleform;
	float gGlareDir;
	
	float GlareY = m_renderer.m_PosY + 0.435f;
	
	float Glareheight = 0.95f;
	void drawGlare(float PositionX = m_renderer.GlareX, float ositionY = GlareY, float width = m_renderer.Glarewidth, float height = Glareheight, int r = 255, int g = 255, int b = 200)
	{

		gGlareHandle = GRAPHICS::REQUEST_SCALEFORM_MOVIE("MP_MENU_GLARE");
		//gGlareHandle = GRAPHICS::REQUEST_SCALEFORM_MOVIE_INSTANCE("MP_MENU_GLARE");
		// Get Player Camera Rotation
		Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
		// Calculate Glare Rotation
		float dir = conv360(rot.z, 0, 360);
		// Check if custom rotation is necessary for the rotation component.
		if ((gGlareDir == 0 || gGlareDir - dir > 0.5) || gGlareDir - dir < -0.5)
		{
			// Set global variable to current direction
			gGlareDir = dir;
			// Open Data Slot Function
			GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(gGlareHandle, "SET_DATA_SLOT");
			// Set Data Slot Value/Parameter
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(gGlareDir);
			// Close Data Slot Function
			//GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION_VOID();
		}
		// Draw Scaleform
		//GRAPHICS::_SET_SCREEN_DRAW_POSITION(76, 84);
		//GRAPHICS::_0x76C641E4(-0.0755f, -0.0755f, 0.f, 0.f);
		GRAPHICS::DRAW_SCALEFORM_MOVIE(gGlareHandle, PositionX, m_renderer.m_PosY + m_renderer.GlareY, m_renderer.Glarewidth, Glareheight, r, g, b, 255, 0);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();



		//GRAPHICS::smile:RAW_SCALEFORM_MOVIE_FULLSCREEN(gGlareHandle, 255, 255, 255, 255, 0);
	}
	void renderer::DrawHeader()
	{
		switch (m_HeaderType)
		{
		case HeaderType::Static:
			DrawRect(
				m_PosX,
				m_DrawBaseY + (m_HeaderHeight / 2.f), m_Width,
				m_HeaderHeight,
				m_HeaderBackgroundColor);
			break;
		case HeaderType::Gradient:
			for (std::size_t i = 0; i < (m_HeaderGradientTransparent ? 1 : 20); ++i)
			{
				DrawSprite(
					"aircraft_dials",
					"aircraft_dials_g0",
					m_PosX - (m_HeaderGradientStretch / 2.f),
					m_DrawBaseY + (m_HeaderHeight / 2.f),
					m_Width + m_HeaderGradientStretch + m_HeaderGradientFiller,
					m_HeaderHeight,
					m_HeaderGradientColorRight,
					m_HeaderGradientFlip ? 0.f : 180.f);
				DrawSprite(
					"aircraft_dials",
					"aircraft_dials_g0",
					m_PosX + (m_HeaderGradientStretch / 2.f),
					m_DrawBaseY + (m_HeaderHeight / 2.f),
					m_Width + m_HeaderGradientStretch + m_HeaderGradientFiller,
					m_HeaderHeight,
					m_HeaderGradientColorLeft,
					m_HeaderGradientFlip ? 180.f : 0.f);
			}
			break;

			break;
		}

		if (m_HeaderText)
		{
			DrawCenteredText(
				"ozark",
				m_PosX,
				m_DrawBaseY + (m_HeaderHeight / 2.f) - (GetTextHeight(m_HeaderFont, m_HeaderTextSize) / 2.f),
				m_HeaderTextSize,
				m_HeaderFont,
				m_HeaderTextColor,
				true, true);

			drawGlare();
		}

		m_DrawBaseY += m_HeaderHeight;
	}

	void renderer::DrawSubmenuBar(AbstractSubmenu* sub)
	{
		char leftText[64] = {};
		std::strncpy(&leftText[0], sub->GetName(), sizeof(leftText) - 1);
		std::transform(std::begin(leftText), std::end(leftText), std::begin(leftText), [](char c) { return static_cast<char>(c); });

		char rightText[32] = {};
		std::snprintf(rightText, sizeof(rightText) - 1, "%zu / %zu", sub->GetSelectedOption() + 1, sub->GetNumOptions());

		DrawRect(
			m_PosX,
			m_DrawBaseY + (m_SubmenuBarHeight / 2.f),
			m_Width, m_SubmenuBarHeight,
			m_SubmenuBarBackgroundColor);
		DrawLeftText(
			&leftText[0],
			m_PosX - (m_Width / m_SubmenuBarPadding),
			m_DrawBaseY + (m_SubmenuBarHeight / 2.f) - (GetTextHeight(m_SubmenuBarFont, m_SubmenuBarTextSize) / 1.5f),
			m_SubmenuBarTextSize, m_SubmenuBarFont,
			m_SubmenuBarTextColor,
			false, true);
		DrawRightText(
			&rightText[0],
			m_PosX + (m_Width / m_SubmenuBarPadding),
			m_DrawBaseY + (m_SubmenuBarHeight / 2.f) - (GetTextHeight(m_SubmenuBarFont, m_SubmenuBarTextSize) / 1.5f),
			m_SubmenuBarTextSize, m_SubmenuBarFont,
			m_SubmenuBarTextColor,
			false, true);

		AbstractOption* opt;

		

		m_DrawBaseY += m_SubmenuBarHeight;
	}

	void renderer::DrawOption(AbstractOption* opt, bool selected)
	{
		
		auto sub = m_SubmenuStack.top();
		double testTarget = 0;
		scrollTarget = lerp(opt_start, opt_end, (double)sub->GetSelectedOption() / ((double)sub->GetNumOptions() - 1));
		if (sub->GetNumOptions() == 1) scrollTarget = opt_start;


		target = m_DrawBaseY + (m_OptionHeight / 2.f);
		if (selected) selectedTarget = m_DrawBaseY + (m_OptionHeight / 2.f);
		if (sub->GetNumOptions() == 1) current = opt_start;

		if (selected)
		{
			if (!strcmp(sub->GetName(), "Players"))
			{
				draw_player_info(getIDFromName(opt->GetLeftText()));
			}
		}

		if (selected) {
			DrawRect(
				m_PosX,
				m_DrawBaseY + (m_OptionHeight / 2.f),
				m_Width,
				m_OptionHeight,
				m_OptionSelectedBackgroundColor);
		}
		DrawLeftText(
			opt->GetLeftText(),
			m_PosX - (m_Width / m_OptionPadding),
			m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 1.5f),
			m_OptionTextSize,
			m_OptionFont,
			selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
			false, false);


		if (opt->GetFlag(OptionFlag::Enterable))
		{
			if (m_arrow_indicator) {
				DrawRightText(
					">",
					m_PosX + (m_Width / m_OptionPadding),
					m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(Font::Monospace, 0.35) / 1.725f),
					0.35,
					Font::Monospace,
					selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
					false, false);
			}
			else
			{
				DrawRect(m_PosX + (m_Width / m_rect_padddding),
					m_DrawBaseY + (m_OptionHeight / 2.f), m_rect_width,
					m_OptionHeight, { 74,37,217,220 }
				);
			}
		}
		if (opt->GetFlag(OptionFlag::Option)) {
			DrawRightText(
				opt->GetRightText(),
				m_PosX + (m_Width / m_OptionPadding),
				m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 1.5f) - 0.002,
				m_OptionTextSize,
				m_OptionFont,
				selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
				false, false);
		}
		if (opt->GetFlag(OptionFlag::BoolOption))
		{
			auto res3 = GetSpriteScale(0.026);
			auto res4 = GetSpriteScale(0.028);
			if (ToggledOn)
			{
				GRAPHICS::DRAW_SPRITE("Textures", "toggle", m_PosX + (m_Width / m_OptionPadding - 0.005f), m_DrawBaseY + (m_OptionHeight / 2.f), res4.x, res3.y, 0.0f, greener.r, greener.g, greener.b, greener.a, 1);
			}
			else if (!ToggledOn)
			{
				GRAPHICS::DRAW_SPRITE("Textures", "toggle", m_PosX + (m_Width / m_OptionPadding - 0.005f), m_DrawBaseY + (m_OptionHeight / 2.f), res4.x, res3.y, 0.0, reder.r, reder.g, reder.b, reder.a, 1);
			}
		}
		if (opt->GetFlag(OptionFlag::BoolAndNumber))
		{
			if (selected) {

				auto res = GetSpriteScale(0.030);
				auto res2 = GetSpriteScale(0.033);
				DrawSprite("Textures", ToggledOn ? "arrows" : "arrows", m_PosX + (m_Width / m_OptionPadding) - 0.015, m_DrawBaseY + (m_OptionHeight / 2.f), res2.x, res.y, selected ? m_renderer.m_OptionSelectedTextColor : m_renderer.m_OptionUnselectedTextColor, 0.0);

				DrawRightText(
					opt->GetRightText(),
					m_PosX + (m_Width / m_OptionPadding) - 0.02,
					m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 1.5f) - 0.001,
					m_OptionTextSize,
					m_OptionFont,
					selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
					false, false);
			}
			else {
				DrawRightText(
					opt->GetRightText(),
					m_PosX + (m_Width / m_OptionPadding) - 0.01,
					m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 1.5f) - 0.001,
					m_OptionTextSize,
					m_OptionFont,
					selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
					false, false);
			}

			auto res3 = GetSpriteScale(0.026);
			auto res4 = GetSpriteScale(0.028);
			if (ToggledOn)
			{
				GRAPHICS::DRAW_SPRITE("Textures", "toggle", m_PosX + (m_Width / m_OptionPadding - 0.005f), m_DrawBaseY + (m_OptionHeight / 2.f), res4.x, res3.y, 0.0f, greener.r, greener.g, greener.b, greener.a, 1);
			}
			else if (!ToggledOn)
			{
				GRAPHICS::DRAW_SPRITE("Textures", "toggle", m_PosX + (m_Width / m_OptionPadding - 0.005f), m_DrawBaseY + (m_OptionHeight / 2.f), res4.x, res3.y, 0.0, reder.r, reder.g, reder.b, reder.a, 1);
			}
		}
		if (opt->GetFlag(OptionFlag::Break) && selected)
		{


			if (m_DownKeyPressed)
			{
				while (sub->GetOption(sub->GetSelectedOption())->GetFlag(OptionFlag::Break))
				{
					sub->SetSelectedOption(sub->GetSelectedOption() + 1);
				}


			}
			else if (m_UpKeyPressed)
			{
				while (sub->GetOption(sub->GetSelectedOption())->GetFlag(OptionFlag::Break))
				{
					sub->SetSelectedOption(sub->GetSelectedOption() - 1);
				}
			}

		}
		if (opt->GetFlag(OptionFlag::Break)) {
			DrawCenteredText(
				opt->GetRightText(),
				m_PosX,
				m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_BreakFont, m_BreakTextSize) / 1.5f),
				m_BreakTextSize,
				m_BreakFont,
				m_OptionUnselectedTextColor,
				false, true);

		}
		if (opt->GetFlag(OptionFlag::Keyboard)) {
			auto res = GetSpriteScale(0.0185);
			auto res2 = GetSpriteScale(0.0185);
			DrawRightText(
				opt->GetRightText(),
				m_PosX + (m_Width / m_OptionPadding - 0.01f),
				m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 2) - 0.003,
				m_OptionTextSize,
				m_OptionFont,
				selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
				false, false);
			DrawSprite("Textures", "keyboard", m_PosX + (m_Width / m_OptionPadding - 0.005f), m_DrawBaseY + (m_OptionHeight / 2.f), res2.x, res.y, selected ? m_renderer.m_OptionSelectedTextColor : m_renderer.m_OptionUnselectedTextColor, 0.0);
		}
		if (opt->GetFlag(OptionFlag::Chooseable))
		{
			if (selected) {
				auto res = GetSpriteScale(0.030);
				auto res2 = GetSpriteScale(0.033);
				DrawSprite("Textures", ToggledOn ? "arrows" : "arrows", m_PosX + (m_Width / m_OptionPadding - 0.005f), m_DrawBaseY + (m_OptionHeight / 2.f), res2.x, res.y, selected ? m_renderer.m_OptionSelectedTextColor : m_renderer.m_OptionUnselectedTextColor, 0.0);
				/* DrawRightText(
					"< >",
					m_PosX + (m_Width / m_OptionPadding),
					m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(Font::Monospace, m_OptionTextSize) / 1.725f) - 0.0040,
					m_OptionTextSize * 1.3,
					Font::Monospace,
					selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
					false, false);
				*/
				DrawRightText(
					opt->GetRightText(),
					m_PosX + (m_Width / m_OptionPadding) - 0.01,
					m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 2) - 0.003,
					m_OptionTextSize,
					m_OptionFont,
					selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
					false, false);
			}
			else {
				DrawRightText(
					opt->GetRightText(),
					m_PosX + (m_Width / m_OptionPadding),
					m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 2) - 0.003,
					m_OptionTextSize,
					m_OptionFont,
					selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
					false, false);
			}

		}
		if (opt->GetFlag(OptionFlag::ChooseBool))
		{
			auto res = GetSpriteScale(0.030);
			auto res2 = GetSpriteScale(0.033);
			auto res3 = GetSpriteScale(0.026);
			auto res4 = GetSpriteScale(0.028);
			if (selected) {

				auto res = GetSpriteScale(0.030);
				auto res2 = GetSpriteScale(0.033);
				DrawSprite("Textures", ToggledOn ? "arrows" : "arrows", m_PosX + (m_Width / m_OptionPadding) - 0.015, m_DrawBaseY + (m_OptionHeight / 2.f), res2.x, res.y, selected ? m_renderer.m_OptionSelectedTextColor : m_renderer.m_OptionUnselectedTextColor, 0.0);

				DrawRightText(
					opt->GetRightText(),
					m_PosX + (m_Width / m_OptionPadding) - 0.02,
					m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 1.5f) - 0.001,
					m_OptionTextSize,
					m_OptionFont,
					selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
					false, false);
			}
			else {
				DrawRightText(
					opt->GetRightText(),
					m_PosX + (m_Width / m_OptionPadding) - 0.01,
					m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 1.5f) - 0.001,
					m_OptionTextSize,
					m_OptionFont,
					selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
					false, false);
			}
			if (ToggledOn)
			{
				DrawSprite("commonmenu", "common_medal", m_PosX + (m_Width / m_OptionPadding - 0.005f), m_DrawBaseY + (m_OptionHeight / 2.f), res4.x, res3.y, { greener.r, greener.g, greener.b, greener.a }, 0.0f);
			}
			else if (!ToggledOn)
			{
				DrawSprite("commonmenu", "common_medal", m_PosX + (m_Width / m_OptionPadding - 0.005f), m_DrawBaseY + (m_OptionHeight / 2.f), res4.x, res3.y, { reder.r, reder.g, reder.b, reder.a }, 0.0f);
			}


		}
		if (opt->GetFlag(OptionFlag::Numberable)) {
			if (selected) {
				auto res = GetSpriteScale(0.030);
				auto res2 = GetSpriteScale(0.033);
				DrawSprite("Textures", ToggledOn ? "arrows" : "arrows", m_PosX + (m_Width / m_OptionPadding - 0.005f), m_DrawBaseY + (m_OptionHeight / 2.f), res2.x, res.y, selected ? m_renderer.m_OptionSelectedTextColor : m_renderer.m_OptionUnselectedTextColor, 0.0);
				/*
				* DrawRightText(
					"< >",
					m_PosX + (m_Width / m_OptionPadding),
					m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(Font::Monospace, m_OptionTextSize) / 1.725f) - 0.0040,
					m_OptionTextSize * 1.3,
					Font::Monospace,
					selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
					false, false);
				*/
				DrawRightText(
					opt->GetRightText(),
					m_PosX + (m_Width / m_OptionPadding) - 0.01,
					m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 1.5f) - 0.001,
					m_OptionTextSize,
					m_OptionFont,
					selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
					false, false);

			}
			else {
				DrawRightText(
					opt->GetRightText(),
					m_PosX + (m_Width / m_OptionPadding),
					m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 1.5f) - 0.00007,
					m_OptionTextSize,
					m_OptionFont,
					selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
					false, false);
			}
		}
		m_DrawBaseY += m_OptionHeight;
	}

	void renderer::DrawFooter()
	{
		DrawRect(
			m_PosX,
			m_DrawBaseY + (m_FooterHeight / 2.f),
			m_Width,
			m_FooterHeight,
			m_FooterBackgroundColor);


		

		

		float size = m_FooterSpriteSize;
		float rotation = 0.f;
		const char* texture = "shop_arrows_upanddown";

		if (!m_SubmenuStack.empty())
		{
			auto sub = m_SubmenuStack.top();
			if (sub->GetSelectedOption() == 0)
			{
				rotation = 90.f;
				texture = "arrowright";
				size *= 0.8f;
			}
			else if (sub->GetSelectedOption() + 1 == sub->GetNumOptions())
			{
				rotation = 270.f;
				texture = "arrowright";
				size *= 0.8f;
			}
		}

		auto sizee = GetSpriteScale(size);

		

		m_DrawBaseY += m_FooterHeight;
	}
	enum eJustify {
		JUSTIFY_LEFT,
		JUSTIFY_RIGHT,
		JUSTIFY_CENTER,
	};
	void draw_text(std::string text, Vector2 position, float scale, int font, Color color, eJustify justification, Vector2 wrap) {
		
		HUD::SET_TEXT_WRAP(wrap.x, wrap.y);

		if (justification != JUSTIFY_LEFT) {
			HUD::SET_TEXT_JUSTIFICATION(justification == JUSTIFY_CENTER ? 0 : 2);
		}

		HUD::SET_TEXT_CENTRE(justification == JUSTIFY_CENTER);
		HUD::SET_TEXT_SCALE(0.f, scale);
		HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, color.a);
		HUD::SET_TEXT_FONT(font);

		
		if (text.length() >= 98) {
			m_renderer.g_render_queue[m_renderer.g_render_queue_index] = text;
			m_renderer.g_render_queue_index++;
			m_renderer.g_render_queue_index %= 100;
		}

		HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
		HUD::END_TEXT_COMMAND_DISPLAY_TEXT(position.x, position.y, 0);
	}
	float get_normalized_font_scale(int font, float scale) {
		switch (font) {
		case 0: return (scale * 1.0f);
		case 1: return (scale * 1.3f);
		case 2: return (scale * 1.11f);
		case 4: return (scale * 1.11f);
		case 7: return (scale * 1.29f);
		}

		return scale;
	}

	void renderer::DrawDescription()
	{
		const char* description{};

		if (!m_SubmenuStack.empty())
		{
			auto sub = m_SubmenuStack.top();
			if (sub->GetNumOptions())
			{
				if (auto opt = sub->GetOption(sub->GetSelectedOption()))
				{
					description = opt->GetDescription();
				}
			}
		}

		if (!description || !*description)
			return;

		m_DrawBaseY += m_DescriptionHeightPadding;


		float scaled_body_height = get_normalized_font_scale(0, m_DescriptionHeight);
		HUD::SET_TEXT_FONT(0);
		HUD::SET_TEXT_SCALE(0.f, scaled_body_height);
		HUD::SET_TEXT_WRAP(m_PosX, (1.0f - (1.0f - (m_PosX + 0.1575f - (0.23f - m_Width)) - g_wrap)));
		HUD::_BEGIN_TEXT_COMMAND_LINE_COUNT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(description);

		float height = m_DescriptionHeight;

		int lines = HUD::_END_TEXT_COMMAND_LINE_COUNT(m_PosX, m_DrawBaseY + (m_DescriptionHeight / 2.f));
		if (lines > 1) {
			height = (lines * HUD::_GET_TEXT_SCALE_HEIGHT(scaled_body_height, 0)) + (0.005f * lines) + 0.005f;
		}


		DrawRect(
			m_PosX,
			m_DrawBaseY + (m_DescriptionHeight / 2.f),
			m_Width,
			height,
			m_DescriptionBackgroundColor);
		

		draw_text(
			description,
			{ m_PosX - (m_Width / m_DescriptionPadding), m_DrawBaseY + (m_DescriptionHeight / 2.f) - (GetTextHeight(m_DescriptionFont, m_DescriptionTextSize) / 1.5f) },
			m_DescriptionTextSize, 0, m_DescriptionTextColor, eJustify::JUSTIFY_LEFT, { m_PosX, (1.0f - (1.0f - (m_PosX + 0.1575f - (0.23f - m_Width)) - g_wrap)) });

		m_DrawBaseY += m_DescriptionHeight;
	}

	void renderer::DrawRect(float x, float y, float width, float height, Color color)
	{
		GRAPHICS::DRAW_RECT(x, y, width, height, color.r, color.g, color.b, color.a, 0);
	}

	void renderer::DrawSprite(const char* dict, const char* texture, float x, float y, float width, float height, Color color, float rotation)
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

	void renderer::DrawLeftText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow)
	{
		HUD::SET_TEXT_SCALE(size, size);
		HUD::SET_TEXT_FONT(static_cast<int>(font));
		HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, color.a);
		if (outline)
			HUD::SET_TEXT_OUTLINE();
		if (shadow)
			HUD::SET_TEXT_DROP_SHADOW();

		HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
		HUD::END_TEXT_COMMAND_DISPLAY_TEXT(x, y, 0);
		
	}

	void renderer::DrawLeftText2(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow)
	{
		HUD::SET_TEXT_SCALE(size, size);
		HUD::SET_TEXT_FONT(static_cast<int>(font));
		HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, color.a);
		if (outline)
			HUD::SET_TEXT_OUTLINE();
		if (shadow)
			HUD::SET_TEXT_DROP_SHADOW();

		HUD::_BEGIN_TEXT_COMMAND_LINE_COUNT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	
		lines = HUD::_END_TEXT_COMMAND_LINE_COUNT(x, y);


	}


	void renderer::DrawCenteredText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow)
	{
		HUD::SET_TEXT_CENTRE(true);
		DrawLeftText(text, x, y, size, font, color, outline, shadow);
	}

	void renderer::DrawRightText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow)
	{
		HUD::SET_TEXT_WRAP(0.f, x);
		HUD::SET_TEXT_RIGHT_JUSTIFY(true);
		DrawLeftText(text, x, y, size, font, color, outline, shadow);
	}

	float renderer::GetTextHeight(Font font, float size)
	{
		return HUD::_GET_TEXT_SCALE_HEIGHT(size, static_cast<int>(font));
	}

	Vector2 renderer::GetSpriteScale(float size)
	{
		int x;
		int y;
		GRAPHICS::_GET_ACTIVE_SCREEN_RESOLUTION(&x, &y);

		return { (static_cast<float>(y) / static_cast<float>(x)) * size, size };
	}

	bool renderer::IsMouseLocked()
	{
		return menu::g_gui.m_opened && m_MouseLocked;
	}

	Rectangle renderer::GetMenuRect()
	{
		float height = m_HeaderHeight;
		height += m_SubmenuBarHeight;

		if (!m_SubmenuStack.empty())
		{
			height += m_OptionHeight * std::min(m_SubmenuStack.top()->GetNumOptions(), m_OptionsPerPage);
		}

		height += m_FooterHeight;

		return
		{
			{ m_PosX + (m_Width / 2.f), m_PosY + (height / 2.f) },
			{ m_Width, height }
		};
	}

	Vector2 renderer::GetMousePos()
	{
		POINT point;
		GetCursorPos(&point);

		return Vector2{ static_cast<float>(point.x), static_cast<float>(point.y) };
	}
	void Text(const char* text, Color color, Vector2 position, Vector2 size, bool center)
	{
		HUD::SET_TEXT_CENTRE(center);
		HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, color.a);
		HUD::SET_TEXT_FONT(0);
		HUD::SET_TEXT_SCALE(size.x, size.y);
		HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME((char*)text);
		HUD::END_TEXT_COMMAND_DISPLAY_TEXT(position.x, position.y, 0);


	}
	int GetHealth(Ped ped) {

		int health = (int)ENTITY::GET_ENTITY_HEALTH(ped);
		int maxHealth = (int)ENTITY::GET_ENTITY_MAX_HEALTH(ped);
		int percentage = health * 100 / maxHealth;



		return percentage;
	}
	int GetArmor(Ped ped, Player player) {
		int armor = (int)PED::GET_PED_ARMOUR(ped);
		int maxArmor = (int)PLAYER::GET_PLAYER_MAX_ARMOUR(player);
		int percentage = armor * 100 / maxArmor;

		return percentage;
	}
	char* GetWanted(Player p)
	{
		char buffer[20];
		int Stars = (int)PLAYER::GET_PLAYER_WANTED_LEVEL(p);

		sprintf_s(buffer, "%i/5", Stars);


		return buffer;
	}

	int getPlayerRank(int player)
	{

		return *script_global(1853910).at(player, 862).at(205).at(6).as<int*>();
	}
	int getPlayerCash(int player)
	{

		return *script_global(1853910).at(player, 862).at(205).at(3).as<int*>();
	}
	int getPlayerWallet(int player)
	{

		return *script_global(1853910).at(player, 862).at(205).at(56).as<int*>();
	}
	int getPlayerKD(int player)
	{

		return *script_global(1853910).at(player, 862).at(205).at(26).as<int*>();
	}
	int kills(int player)
	{

		return *script_global(1853910).at(player, 862).at(205).at(28).as<int*>();
	}

	int getPlayerAmmo(Ped ped, Hash WeaponHash)
	{
		int Ammo = (int)WEAPON::GET_AMMO_IN_PED_WEAPON(ped, WeaponHash);
		if (Ammo == -1) {
			return (int)("Infinite");
		}
		else {
			return Ammo;
		}

	}
	float ItoF(int input)
	{
		float Output = *(float*)&input;
		return Output;
	}
	bool isNumericChar(char x)
	{
		return (x >= '0' && x <= '9') ? true : false;
	}
	int StoI(char* str)
	{
		if (*str == NULL)
			return 0;

		int res = 0,
			sign = 1,
			i = 0;

		if (str[0] == '-')
		{
			sign = -1;
			i++;
		}
		for (; str[i] != '\0'; ++i)
		{
			if (isNumericChar(str[i]) == false)
				return 0;
			res = res * 10 + str[i] - '0';
		}
		return sign * res;
	}
	char* ItoS(int num)
	{
		char buf[30];
		snprintf(buf, sizeof(buf), "%i", num);
		return buf;
	}
	char* FtoS(float input)
	{
		char returnvalue[64];
		int wholenumber = (int)input;
		input -= wholenumber;
		input *= 100;
		sprintf(returnvalue, "%d.%d", wholenumber, (int)input);
		return returnvalue;
	}
	const char* getPlayerVehicle(Ped ped)
	{
		bool inVehicle = PED::IS_PED_IN_ANY_VEHICLE(ped, 0);

		if (inVehicle)
		{
			Hash vehicleHash = ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_IN(ped, 0));
			const char* vehicleModel = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(vehicleHash));

			return vehicleModel;
		}
		else {
			char result[16];
			sprintf_s(result, "%s", "None");
			return result;
		}

	}


	const char* InCutscene(int player)
	{
		if (NETWORK::NETWORK_IS_PLAYER_IN_MP_CUTSCENE(player))
		{
			return "Yes";
		}
		else {
			return "No";
		}
	}
	int GetSpeed(Ped ped) {

		int speed = (int)round(ENTITY::GET_ENTITY_SPEED(ped) * 2.24);
		return speed;
	}
	bool is_player_freemode_host(std::int32_t player) {
		return (NETWORK::NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0) == player);
	}
	bool is_player_in_interior(Player player)
	{
		/*Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		int currentInterior = INTERIOR::GET_INTERIOR_FROM_ENTITY(ped);
		return INTERIOR::IS_VALID_INTERIOR(currentInterior);*/
		int interior = INTERIOR::GET_INTERIOR_FROM_ENTITY(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player));
		if (!interior) {
			interior = *script_global(2689235).at(player, 453).at(248).as<int*>();
		}
		return interior;
	}
	void renderer::draw_player_info(Player player)
	{
		if (*g_pointers->m_is_session_started && menu::g_gui.m_opened) {
			Color m_white{ 255, 255, 255, 255 };
			float PosX = m_PosX + 0.225f;

			float PosY = m_PosY + 0.168f;
			float LTextX = PosX - 0.1225;
			float RTextX = PosX + 0.009f;
			float TextY = m_PosY - 0.055;
			float SeperatorX = PosX + 0.05;

			float RTextX2 = PosX + 0.1215f;

			float rightresult = 0.49f;
			float righttext = SeperatorX - 0.048f;

			Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
			//std::string Health = ("%s", std::to_string(GetHealth(ped)));
			//std::string Armor = ("%s", std::to_string(GetArmor(ped, player)));

			std::string rank = std::to_string(getPlayerRank(player));
			std::string cash = std::to_string(getPlayerCash(player));
			std::string bank = std::to_string(getPlayerWallet(player));

			float KD_Float = ItoF(getPlayerKD(player));
			float kill_Float = ItoF(kills(player));
			std::string kd = FtoS(KD_Float);
			std::string kills = FtoS(kill_Float);

			Vector3 get_coords = ENTITY::GET_ENTITY_COORDS(ped, 0);
			std::string wantedlvl = GetWanted(player);
			std::string ammo = std::format("{}", WEAPON::GET_AMMO_IN_PED_WEAPON(ped, WEAPON::GET_SELECTED_PED_WEAPON(ped)));
			std::string coords = std::format("[{0},{1},{2}]", std::roundl(get_coords.x), std::roundl(get_coords.y), std::roundl(get_coords.z));

			

			Hash street[2]{};
			PATHFIND::GET_STREET_NAME_AT_COORD(get_coords.x, get_coords.y, get_coords.z, &street[0], &street[1]);
			std::string Street = HUD::GET_STREET_NAME_FROM_HASH_KEY(street[0]);
			std::string Zone = HUD::_GET_LABEL_TEXT(ZONE::GET_NAME_OF_ZONE(get_coords.x, get_coords.y, get_coords.z));
			std::string heading = std::format("{}", roundf(ENTITY::GET_ENTITY_HEADING(ped)));

			Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(ped, false);
			Vector3 selfCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
			float distance = MISC::GET_DISTANCE_BETWEEN_COORDS(selfCoords.x, selfCoords.y, selfCoords.z, playerCoords.x, playerCoords.y, playerCoords.z, true);
			std::string Distance = std::format("{}m", roundf(distance));
			std::string Speed = std::to_string(GetSpeed(ped));
			CNetGamePlayer* g_player = g_pointers->m_net_game_player(player);
			std::string scid = std::to_string(g_player->get_net_data()->m_gamer_handle_2.m_rockstar_id);
			std::string slot = std::format("{}", g_player->m_player_id);
			std::string public_ip = std::format("{0}.{1}.{2}.{3}", g_player->get_net_data()->m_internal_ip.m_field1, g_player->get_net_data()->m_internal_ip.m_field2, g_player->get_net_data()->m_internal_ip.m_field3, g_player->get_net_data()->m_internal_ip.m_field4);
			std::string local_ip = std::format("{0}.{1}.{2}.{3}", g_player->get_net_data()->m_external_ip.m_field1, g_player->get_net_data()->m_external_ip.m_field2, g_player->get_net_data()->m_external_ip.m_field3, g_player->get_net_data()->m_external_ip.m_field4);
			std::string token = std::to_string(g_player->get_net_data()->m_host_token);
			std::string public_port = std::to_string((uint16_t)g_player->get_net_data()->m_external_port);
			std::string local_port = std::to_string((uint16_t)g_player->get_net_data()->m_internal_port);
			std::string peer_id = std::to_string((uint64_t)g_player->get_net_data()->m_peer_id);
			std::string host = g_player->is_host() ? std::format("Yes") : std::format("No");
			std::string scripthost = is_player_freemode_host(ped) ? "Yes" : "No";




			std::string passive = PLAYER::IS_PLAYER_BATTLE_AWARE(ped) ? "Yes" : "No";
			std::string rockstar = NETWORK::NETWORK_PLAYER_IS_ROCKSTAR_DEV(ped) ? "Yes" : "No";
			DrawRect(PosX, PosY + 0.0202f, 0.25f, 0.375f, m_player_info_bg_color);//draw main info rect
			DrawRect(PosX, PosY - 0.0220f * 7.652f, 0.25f, 0.002f, m_HeaderBackgroundColor);//draw main info top bar 


			DrawRect(PosX + 0.195, PosY + 0.0202f, 0.135f, 0.375f, m_player_info_bg_color);//draw ped preview rect
			DrawRect(PosX + 0.195, PosY - 0.0220f * 7.652f, 0.135f, 0.002f, m_HeaderBackgroundColor);//draw ped preview top bar 


			//geo info


			DrawRect(PosX, PosY + 0.28, 0.25f, 0.125, m_player_info_bg_color);//draw geo info rect
			DrawRect(PosX, PosY + 0.31 - 0.09375, 0.25f, 0.002f, m_HeaderBackgroundColor);//draw geo info top bar 



			/*if (m_player_info.IPDataCompleted == false)
			{
				m_player_info.ip_data = get_ip_data(fmt::format(("{}.{}.{}.{}"), g_player->get_net_data()->m_external_ip.m_field1, g_player->get_net_data()->m_external_ip.m_field2, g_player->get_net_data()->m_external_ip.m_field3, g_player->get_net_data()->m_external_ip.m_field4));
				m_player_info.IPDataCompleted = true;
			}*/


			Text("Zip", { m_white }, { LTextX, TextY + 0.445f }, { 0.23f, 0.23f }, false);
			if (m_player_info.ip_data.find(("zip")) != m_player_info.ip_data.end()) {
				if (m_player_info.ip_data[("zip")].is_string()) {
					std::string zip = m_player_info.ip_data[("zip")];
					DrawRightText(zip.c_str(), SeperatorX - 0.0523f, TextY + 0.445f, 0.23f, Font::ChaletLondon, m_white, 0, 0);
				}
			}
			DrawRect(SeperatorX - 0.05, TextY + 0.455f, 0.001f, 0.015f, m_white);
			Text("Region", { m_white }, { SeperatorX - 0.048f, TextY + 0.445f }, { 0.23f, 0.23f }, false);
			if (m_player_info.ip_data.find(("regionName")) != m_player_info.ip_data.end()) {
				if (m_player_info.ip_data[("regionName")].is_string()) {
					std::string region = m_player_info.ip_data[("regionName")];
					DrawRightText(region.c_str(), RTextX2, TextY + 0.445f, 0.23f, Font::ChaletLondon, m_white, 0, 0);
				}
			}
			Text("City", { m_white }, { LTextX, TextY + 0.47f }, { 0.23f, 0.23f }, false);
			if (m_player_info.ip_data.find(("city")) != m_player_info.ip_data.end()) {
				if (m_player_info.ip_data[("city")].is_string()) {
					std::string city = m_player_info.ip_data[("city")];
					DrawRightText(city.c_str(), SeperatorX - 0.0523f, TextY + 0.47f, 0.23f, Font::ChaletLondon, m_white, 0, 0);
				}
			}
			DrawRect(SeperatorX - 0.05, TextY + 0.48f, 0.001f, 0.015f, m_white);
			Text("Country", { m_white }, { SeperatorX - 0.048f, TextY + 0.47f }, { 0.23f, 0.23f }, false);
			if (m_player_info.ip_data.find(("country")) != m_player_info.ip_data.end()) {
				if (m_player_info.ip_data[("country")].is_string()) {
					std::string country = m_player_info.ip_data[("country")];
					DrawRightText(country.c_str(), RTextX2, TextY + 0.47f, 0.23f, Font::ChaletLondon, m_white, 0, 0);
				}
			}
			Text("Timezone", { m_white }, { LTextX, TextY + 0.495f }, { 0.23f, 0.23f }, false);
			if (m_player_info.ip_data.find(("timezone")) != m_player_info.ip_data.end()) {
				if (m_player_info.ip_data[("timezone")].is_string()) {
					std::string zone = m_player_info.ip_data[("timezone")];
					DrawRightText(zone.c_str(), RTextX2, TextY + 0.495f, 0.23f, Font::ChaletLondon, m_white, 0, 0);
				}
			}
			Text("Isp", { m_white }, { LTextX, TextY + 0.52f }, { 0.23f, 0.23f }, false);
			if (m_player_info.ip_data.find(("isp")) != m_player_info.ip_data.end()) {
				if (m_player_info.ip_data[("isp")].is_string()) {
					std::string isp = m_player_info.ip_data[("isp")];
					DrawRightText(isp.c_str(), RTextX2, TextY + 0.52f, 0.23f, Font::ChaletLondon, m_white, 0, 0);
				}
			}
			Text("Org", { m_white }, { LTextX, TextY + 0.545f }, { 0.23f, 0.23f }, false);
			if (m_player_info.ip_data.find(("org")) != m_player_info.ip_data.end()) {
				if (m_player_info.ip_data[("org")].is_string()) {
					std::string org = m_player_info.ip_data[("org")];
					DrawRightText(org.c_str(), RTextX2, TextY + 0.545f, 0.23f, Font::ChaletLondon, m_white, 0, 0);
				}
			}



			//main info
			Text("Rank", { m_white }, { LTextX, TextY + 0.06f }, { 0.23f, 0.23f }, false);
			DrawRightText(rank.c_str(), SeperatorX - 0.0523f, TextY + 0.06f, 0.23f, Font::ChaletLondon, m_white, 0, 0);
			DrawRect(SeperatorX - 0.05, TextY + 0.07f, 0.001f, 0.015f, m_white);
			Text("Health", { m_white }, { SeperatorX - 0.048f, TextY + 0.06f }, { 0.23f, 0.23f }, false);
			DrawRightText("100", RTextX2, TextY + 0.06f, 0.23f, Font::ChaletLondon, m_white, 0, 0);

			Text("Cash", { m_white }, { LTextX, TextY + 0.085f }, { 0.23f, 0.23f }, false);
			DrawRightText(cash.c_str(), SeperatorX - 0.0523f, TextY + 0.085f, 0.23f, Font::ChaletLondon, m_white, 0, 0);
			DrawRect(SeperatorX - 0.05, TextY + 0.095f, 0.001f, 0.015f, m_white);
			Text("Armor", { m_white }, { SeperatorX - 0.048f, TextY + 0.085f }, { 0.23f, 0.23f }, false);
			DrawRightText("100", RTextX2, TextY + 0.085f, 0.23f, Font::ChaletLondon, m_white, 0, 0);

			Text("Bank", { m_white }, { LTextX, TextY + 0.11f }, { 0.23f, 0.23f }, false);
			DrawRightText(bank.c_str(), SeperatorX - 0.0523f, TextY + 0.11f, 0.23f, Font::ChaletLondon, m_white, 0, 0);
			DrawRect(SeperatorX - 0.05, TextY + 0.12f, 0.001f, 0.015f, m_white);
			Text("Wanted Level", { m_white }, { SeperatorX - 0.048f, TextY + 0.11f }, { 0.23f, 0.23f }, false);
			DrawRightText(wantedlvl.c_str(), RTextX2, TextY + 0.11f, 0.23f, Font::ChaletLondon, m_white, 0, 0);

			Text("K/D Ratio", { m_white }, { LTextX, TextY + 0.135f }, { 0.23f, 0.23f }, false);
			DrawRightText(kd.c_str(), SeperatorX - 0.0523f, TextY + 0.135f, 0.23f, Font::ChaletLondon, m_white, 0, 0);
			DrawRect(SeperatorX - 0.05, TextY + 0.145f, 0.001f, 0.015f, m_white);
			Text("Ammo", { m_white }, { SeperatorX - 0.048f, TextY + 0.135f }, { 0.23f, 0.23f }, false);
			DrawRightText(ammo.c_str(), RTextX2, TextY + 0.135f, 0.23f, Font::ChaletLondon, m_white, 0, 0);

			Text("Weapon", { m_white }, { LTextX, TextY + 0.16f }, { 0.23f, 0.23f }, false);
			DrawRightText("~c~None", RTextX2, TextY + 0.16f, 0.23f, Font::ChaletLondon, m_white, 0, 0);

			Text("Zone", { m_white }, { LTextX, TextY + 0.185f }, { 0.23f, 0.23f }, false);
			DrawRightText(Zone.c_str(), RTextX2, TextY + 0.185, 0.23f, Font::ChaletLondon, m_white, 0, 0);

			Text("Street", { m_white }, { LTextX, TextY + 0.21f }, { 0.23f, 0.23f }, false);
			DrawRightText(Street.c_str(), RTextX2, TextY + 0.21, 0.23f, Font::ChaletLondon, m_white, 0, 0);


			Text("Coords", { m_white }, { LTextX, TextY + 0.235f }, { 0.23f, 0.23f }, false);
			DrawRightText(coords.c_str(), SeperatorX - 0.0523f, TextY + 0.235f, 0.23f, Font::ChaletLondon, m_white, 0, 0);
			DrawRect(SeperatorX - 0.05, TextY + 0.245f, 0.001f, 0.015f, m_white);
			Text("Heading", { m_white }, { SeperatorX - 0.048f, TextY + 0.235f }, { 0.23f, 0.23f }, false);
			DrawRightText(heading.c_str(), RTextX2, TextY + 0.235f, 0.23f, Font::ChaletLondon, m_white, 0, 0);

			Text("Distance", { m_white }, { LTextX, TextY + 0.26f }, { 0.23f, 0.23f }, false);
			DrawRightText(Distance.c_str(), SeperatorX - 0.0523f, TextY + 0.26f, 0.23f, Font::ChaletLondon, m_white, 0, 0);
			DrawRect(SeperatorX - 0.05, TextY + 0.27f, 0.001f, 0.015f, m_white);
			Text("Speed", { m_white }, { SeperatorX - 0.048f, TextY + 0.26f }, { 0.23f, 0.23f }, false);
			DrawRightText(Speed.c_str(), RTextX2, TextY + 0.26f, 0.23f, Font::ChaletLondon, m_white, 0, 0);

			Text("Public Ip", { m_white }, { LTextX, TextY + 0.285f }, { 0.23f, 0.23f }, false);
			DrawRightText(public_ip.c_str(), SeperatorX - 0.0523f, TextY + 0.285f, 0.23f, Font::ChaletLondon, m_white, 0, 0);
			DrawRect(SeperatorX - 0.05, TextY + 0.295f, 0.001f, 0.015f, m_white);
			Text("Local Ip", { m_white }, { SeperatorX - 0.048f, TextY + 0.285f }, { 0.23f, 0.23f }, false);
			DrawRightText(local_ip.c_str(), RTextX2, TextY + 0.285f, 0.23f, Font::ChaletLondon, m_white, 0, 0);

			Text("Public Port", { m_white }, { LTextX, TextY + 0.31f }, { 0.23f, 0.23f }, false);
			DrawRightText(public_port.c_str(), SeperatorX - 0.0523f, TextY + 0.31f, 0.23f, Font::ChaletLondon, m_white, 0, 0);
			DrawRect(SeperatorX - 0.05, TextY + 0.32f, 0.001f, 0.015f, m_white);
			Text("Local Port", { m_white }, { SeperatorX - 0.048f, TextY + 0.31f }, { 0.23f, 0.23f }, false);
			DrawRightText(local_port.c_str(), RTextX2, TextY + 0.31f, 0.23f, Font::ChaletLondon, m_white, 0, 0);

			Text("Host", { m_white }, { LTextX, TextY + 0.335f }, { 0.23f, 0.23f }, false);
			DrawRightText(host.c_str(), SeperatorX - 0.0523f, TextY + 0.335f, 0.23f, Font::ChaletLondon, m_white, 0, 0);
			DrawRect(SeperatorX - 0.05, TextY + 0.345f, 0.001f, 0.015f, m_white);
			Text("Script Host", { m_white }, { SeperatorX - 0.048f, TextY + 0.335f }, { 0.23f, 0.23f }, false);
			DrawRightText(scripthost.c_str(), RTextX2, TextY + 0.335f, 0.23f, Font::ChaletLondon, m_white, 0, 0);

			Text("Peer", { m_white }, { LTextX, TextY + 0.36f }, { 0.23f, 0.23f }, false);
			DrawRightText(peer_id.c_str(), SeperatorX - 0.0523f, TextY + 0.36f, 0.23f, Font::ChaletLondon, m_white, 0, 0);
			DrawRect(SeperatorX - 0.05, TextY + 0.37f, 0.001f, 0.015f, m_white);
			Text("Token", { m_white }, { SeperatorX - 0.048f, TextY + 0.36f }, { 0.23f, 0.23f }, false);
			DrawRightText(token.c_str(), RTextX2, TextY + 0.36f, 0.23f, Font::ChaletLondon, m_white, 0, 0);
			if (is_valid_ptr(g_player->get_net_data()->m_gamer_handle_2.m_rockstar_id))
			{
				Text("Scid", { m_white }, { LTextX, TextY + 0.385f }, { 0.23f, 0.23f }, false);
				DrawRightText(scid.c_str(), SeperatorX - 0.0523f, TextY + 0.385f, 0.23f, Font::ChaletLondon, m_white, 0, 0);
			}
			
			DrawRect(SeperatorX - 0.05, TextY + 0.395f, 0.001f, 0.015f, m_white);
			Text("Slot", { m_white }, { SeperatorX - 0.048f, TextY + 0.385f }, { 0.23f, 0.23f }, false);
			DrawRightText(slot.c_str(), RTextX2, TextY + 0.385f, 0.23f, Font::ChaletLondon, m_white, 0, 0);

			Text("Passive", { m_white }, { LTextX, TextY + 0.41f }, { 0.23f, 0.23f }, false);
			DrawRightText(passive.c_str(), SeperatorX - 0.0523f, TextY + 0.41f, 0.23f, Font::ChaletLondon, m_white, 0, 0);
			DrawRect(SeperatorX - 0.05, TextY + 0.42f, 0.001f, 0.015f, m_white);
			Text("Rockstar", { m_white }, { SeperatorX - 0.048f, TextY + 0.41f }, { 0.23f, 0.23f }, false);
			DrawRightText(rockstar.c_str(), RTextX2, TextY + 0.41f, 0.23f, Font::ChaletLondon, m_white, 0, 0);

			/*rage::joaat_t scene_hash = 0x390DCCF5;//0xAD197067, 0x390DCCF5, 0x3D8F5C29, 0x5ADFAFD0
			rage::joaat_t element = 0;
			CPed* local_ped = g_player->m_player_info->m_ped;
			uintptr_t ui_3d_draw_manager = *(uint64_t*)(g_pointers->ui_3d_draw_manager);*/

			//ped preview 



			rage::joaat_t scene_hash = 0x390DCCF5;//0xAD197067, 0x390DCCF5, 0x3D8F5C29, 0x5ADFAFD0
			rage::joaat_t element = 0;
			CPed* local_ped = g_player->m_player_info->m_ped;
			uintptr_t ui_3d_draw_manager = *(uint64_t*)(g_pointers->ui_3d_draw_manager);

			Vector3 pos = { PosX - 0.56f, PosY * 6.2f, 0.0f };

			if (ui_3d_draw_manager) {

				DWORD* preset2 = call<DWORD*>(g_pointers->get_scene_preset, ui_3d_draw_manager, &scene_hash);
				DWORD* preset = preset2 + (0x2A0 * element);

				if (preset) {

					*(float*)(preset + 0x12) = 0;
					*(float*)(preset + 0x9) = -3.8f;//size
				}
				if (call<bool>(g_pointers->push_scene_preset_manager, ui_3d_draw_manager, &scene_hash)) {
					if (call<bool>(g_pointers->add_element_to_scene, ui_3d_draw_manager, &scene_hash, element, local_ped, pos, 1.0f)) {
						call<bool>(g_pointers->set_scene_element_lighting, ui_3d_draw_manager, &scene_hash, element, 1.6f);
					}
				}
			}
		}


	}
}
