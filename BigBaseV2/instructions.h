#pragma once
#include "common.hpp"

namespace big::instructionals {
	static std::string t_open_category = "Open Category";
	static std::string t_close_menu = "Close Menu";
	static std::string t_scroll = "Scroll";
	static std::string t_select = "Select";
	static std::string t_back = "Back";
	static std::string t_rainbow_config("Rainbow Config", true, true);
	static std::string t_adjust("Adjust", true, true);
	static std::string t_input("Input", true, true);

	class instructionals {
	public:
		void setup();
		void add_instructional(std::string text, eControls control);
		void add_instructional(std::string text, eScaleformButtons button_option);
		void add_instructional(std::string text, int vk);
		void close();
	private:
		int m_count = 0;
		int m_handle = 0;
	};

	instructionals* get_instructionals();

	inline void setup() {
		get_instructionals()->setup();
	}

	inline void add_instructional(std::string text, eControls control) {
		get_instructionals()->add_instructional(text, control);
	}

	inline void add_instructional(std::string text, eScaleformButtons button_option) {
		get_instructionals()->add_instructional(text, button_option);
	}

	inline void add_instructional(std::string text, int vk) {
		get_instructionals()->add_instructional(text, vk);
	}

	inline void close() {
		get_instructionals()->close();
	}

	inline void main_menu() {
		get_instructionals()->setup();
		get_instructionals()->add_instructional((t_open_category), ControlFrontendAccept);
		get_instructionals()->add_instructional((t_close_menu), ControlFrontendCancel);
		get_instructionals()->add_instructional((t_scroll), ARROW_UP_DOWN);
		get_instructionals()->close();
	}

	inline void standard(bool scroller, bool keyboard, bool hotkey) {
		get_instructionals()->setup();
		get_instructionals()->add_instructional((t_select), ControlFrontendAccept);
		get_instructionals()->add_instructional((t_back), ControlFrontendCancel);
		get_instructionals()->add_instructional((t_scroll), ARROW_UP_DOWN);

		if (scroller) get_instructionals()->add_instructional((t_adjust), ARROW_LEFT_RIGHT);
		if (keyboard) get_instructionals()->add_instructional((t_input), ControlPhoneSelect);

		get_instructionals()->close();
	}

	inline void rainbow(bool scroller = false, bool keyboard = false, bool hotkey = false) {
		get_instructionals()->setup();
		get_instructionals()->add_instructional((t_select), ControlFrontendAccept);
		get_instructionals()->add_instructional((t_back), ControlFrontendCancel);
		get_instructionals()->add_instructional((t_scroll), ARROW_UP_DOWN);
		get_instructionals()->add_instructional((t_rainbow_config), ControlFrontendX);

		if (scroller) get_instructionals()->add_instructional((t_adjust), ARROW_LEFT_RIGHT);
		if (keyboard) get_instructionals()->add_instructional((t_input), ControlPhoneSelect);

		get_instructionals()->close();
	}
}