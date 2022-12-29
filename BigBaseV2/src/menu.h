#pragma once
#include "common.hpp"
namespace big::menu
{




	class gui
	{
	public:
		
		void dx_on_tick();

		void script_init();
		void script_on_tick();
		static void script_func();
	public:
		
		bool m_opened{};


	};

	inline gui g_gui;
}
