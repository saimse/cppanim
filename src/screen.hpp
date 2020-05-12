#pragma once

#include <cppanim/fundamentals.hpp>
#include <cppanim/drawable.hpp>
#include <cppanim/broadcaster.hpp>

//revisit
#include <cppanim/screen.hpp>

#include "diffbuff.hpp"

#include <memory>

namespace cppanim::gfx {

	using namespace cppanim::fundamentals;
	using namespace cppanim::util;

	//TODO(milevuletic): Singleton?
	class Screen : public KeyboardBroadcaster {

		XY screenSize;
		DiffBuff diffbuff;

		std::vector<const Drawable *> objects;

		clock_t globalClock = 0;

		// true after addDrawable(); sort flag
		bool recentlyAdded = false;

		bool isRunning = false;
		bool isPaused = false;

		void handleInput();

	public:
		Screen() : screenSize(getWindowSize()),
			   diffbuff(screenSize),
			   objects() {}

		void addDrawable(const Drawable &d);
	};

}
