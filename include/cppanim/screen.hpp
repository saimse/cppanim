#pragma once

#include <cppanim/fundamentals.hpp>
#include <cppanim/drawable.hpp>
#include <cppanim/broadcaster.hpp>

#include <cppanim/diffbuff.hpp>
#include <memory>

#include <vector>

namespace cppanim::gfx {

	using namespace cppanim::fundamentals;
	using namespace cppanim::util;

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
		
		Screen() : screenSize(getWindowSize()),
			   diffbuff(screenSize),
			   objects() {}
	public:
		static Screen& getInstance()
		{
			static Screen instance;
			return instance;
		}
		void operator=(const Screen&) = delete;
		Screen(const Screen&) = delete;

		void addDrawable(const Drawable &d);
	};
	
}
