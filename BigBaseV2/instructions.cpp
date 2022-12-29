#include "instructions.h"
#include "natives.hpp"
namespace big::instructionals {
	static const char* g_key_names_instructional[254] = {
		"F10",
		"F10",
		"F10",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"BACKSPACE",
		"TAB",
		"TAB",
		"TAB",
		"NUM 5",
		"ENTER",
		"ENTER",
		"ENTER",
		"SHIFT",
		"CTRL",
		"ALT",
		"ALT",
		"CAPSLOCK",
		"CAPSLOCK",
		"CAPSLOCK",
		"CAPSLOCK",
		"CAPSLOCK",
		"CAPSLOCK",
		"CAPSLOCK",
		"ESC",
		"ESC",
		"ESC",
		"ESC",
		"ESC",
		"SPACE",
		"NUM 9",
		"NUM 3",
		"NUM 1",
		"NUM 7",
		"LEFT",
		"UP",
		"RIGHT",
		"DOWN",
		"NUM 2",
		"NUM 2",
		"NUM 2",
		"NUM 2",
		"NUM 0",
		"DELETE",
		"NUM DECIMAL",
		"0",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"9",
		"9",
		"9",
		"9",
		"9",
		"9",
		"9",
		"A",
		"B",
		"C",
		"D",
		"E",
		"F",
		"G",
		"H",
		"I",
		"J",
		"K",
		"L",
		"M",
		"N",
		"O",
		"P",
		"Q",
		"R",
		"S",
		"T",
		"U",
		"V",
		"W",
		"X",
		"Y",
		"Z",
		"Z",
		"Z",
		"Z",
		"Z",
		"Z",
		"N0",
		"N1",
		"N2",
		"N3",
		"N4",
		"N5",
		"N6",
		"N7",
		"N8",
		"N9",
		"*",
		"NUM PLUS",
		"NUM PLUS",
		"NUM SUB",
		"NUM DECIMAL",
		"/",
		"F1",
		"F2",
		"F3",
		"F4",
		"F5",
		"F6",
		"F7",
		"F8",
		"F9",
		"F10",
		"F11",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"Pause",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SHIFT",
		"RIGHT SHIFT",
		"CTRL",
		"CTRL",
		"ALT",
		"ALT",
		"ALT",
		"ALT",
		"ALT",
		"ALT",
		"ALT",
		"ALT",
		"M",
		"D",
		"C",
		"B",
		"P",
		"Q",
		"J",
		"G",
		"G",
		"G",
		"G",
		"F",
		"F",
		"F",
		";",
		"=",
		",",
		"-",
		".",
		"/",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"[",
		"null",
		"]",
		"ACUTE/CEDILLA",
		"ACUTE/CEDILLA",
		"ACUTE/CEDILLA",
		"ACUTE/CEDILLA",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null"
	};

	void instructionals::setup() {
		if (!GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(m_handle)) {
			m_handle = GRAPHICS::REQUEST_SCALEFORM_MOVIE("instructional_buttons");
			return;
		}

		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(m_handle, "CLEAR_ALL");
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();

		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(m_handle, "TOGGLE_MOUSE_BUTTONS");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(1);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();

		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(m_handle, "SET_MAX_WIDTH");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(1.f);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}

	void instructionals::add_instructional(std::string text, eControls control) {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(m_handle, "SET_DATA_SLOT");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(m_count++);

		//GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING(GRAPHICS::get_control_instructional_button(0, control, true)); // problem!

		GRAPHICS::BEGIN_TEXT_COMMAND_SCALEFORM_STRING("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
		GRAPHICS::END_TEXT_COMMAND_SCALEFORM_STRING();

		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(true);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(control);

		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}

	void instructionals::add_instructional(std::string text, eScaleformButtons button_option) {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(m_handle, "SET_DATA_SLOT");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(m_count++);

		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(button_option);

		GRAPHICS::BEGIN_TEXT_COMMAND_SCALEFORM_STRING("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
		GRAPHICS::END_TEXT_COMMAND_SCALEFORM_STRING();

		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(true);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(button_option);

		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}

	void instructionals::add_instructional(std::string text, int vk) {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(m_handle, "SET_DATA_SLOT");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(m_count++);

		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING(("t_" + (std::string)g_key_names_instructional[vk]).c_str());
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING(text.c_str());
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(true);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(vk);

		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}

	void instructionals::close() {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(m_handle, "SET_BACKGROUND_COLOUR");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(0);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(0);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(0);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(80);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();

		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(m_handle, "DRAW_INSTRUCTIONAL_BUTTONS");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(0);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();

		GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(m_handle, 255, 255, 255, 255, 0);
		m_count = 0;
	}

	instructionals* get_instructionals() {
		static instructionals instance;
		return &instance;
	}
}