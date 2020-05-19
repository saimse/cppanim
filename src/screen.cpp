#include <cppanim/screen.hpp>

#include <algorithm>
#include <stdio.h>

#include "diffbuff.hpp"

namespace cppanim::gfx {

	using namespace cppanim::fundamentals;
	using namespace cppanim::util;
	
	struct Screen::impl {
		XY screenSize;
		DiffBuff diffbuff;

		std::vector<const Drawable *> objects;

		clock_t globalClock = 0;

		// true after addDrawable(); sort flag
		bool recentlyAdded = false;

		bool isRunning = false;
		bool isPaused = false;

		void addDrawable(const Drawable &d) {
			objects.push_back(&d);
			std::sort(objects.begin(), objects.end());
		}

		impl() : screenSize(getWindowSize()), diffbuff(screenSize),
			 objects() {}
	};

	void Screen::addDrawable(const Drawable &d)
	{
		pImpl->addDrawable(d);
	}

	void Screen::handleInput()
	{
		KeyboardEvent e;

		char c = getch_();

		// TODO(milevuletic): check how this works on Windows
		if(c == 27) {
			e.setState(KeyboardEvent::E_KEYBOARD_META);
			c = getch_();
			/* ANSI terminal code */
			if(c == '[') {
				//TODO: handle ANSI codes
			}
		}

		if(c >= 'A') {
			e.data = c;
		}

		//TODO: this is UB
		fflush(stdin);

		for(auto l : listeners) {
			l->onEvent(e);
		}
	}

	Screen::Screen() : pImpl{std::make_unique<impl>()} {}
	Screen::~Screen() = default;	

}
