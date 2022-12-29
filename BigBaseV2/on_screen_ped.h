#pragma once
#include "common.hpp"
#include "generic_types.h"

namespace big::menu::screen::ped {
	void draw_on_screen_ped(CPed* ped, Vector2 pos, Vector2  scale, Vector3 position_offset = { 0.00f, -2.00f, 0.40f });
}