#pragma once

#include <cppanim/fundamentals.hpp>
#include <chrono>

namespace cppanim {
        struct Context {
		clock_t globalClock;
		std::chrono::milliseconds::rep lastCycle;
		float framerate;
	};
}
