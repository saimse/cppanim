#include "screen.hpp"

#include <algorithm>
#include <stdio.h>

namespace cppanim::gfx {

	void Screen::addDrawable(const Drawable &d)
	{
		objects.push_back(&d);
		std::sort(objects.begin(), objects.end());
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

}
