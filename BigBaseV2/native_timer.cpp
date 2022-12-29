#include "native_timer.h"
#include "natives.hpp"

namespace big::menu::timers {
	void run_timed(int* timer, int ms, std::function<void()> callback) {
		if (*timer < MISC::GET_GAME_TIMER()) {
			*timer = MISC::GET_GAME_TIMER() + ms;
			callback();
		}
	}

	void timer::start(unsigned long long ticks) {
		if (m_tick) {
			m_ready_at = GetTickCount64() + ticks;
			m_tick = false;
		}
	}

	bool timer::is_ready() {
		return GetTickCount64() > m_ready_at;
	}

	void timer::reset() {
		m_tick = true;
	}
}