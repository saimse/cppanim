#include "screen.hpp"

#include <algorithm>
#include <stdio.h>

namespace cppanim::gfx {

	void Screen::addDrawable(const Drawable &d)
	{
		objects.push_back(&d);
		std::sort(objects.begin(), objects.end());
	}
	
#ifndef _WIN32

#include <string.h>
#include <stdlib.h>

	void Screen::handleInput()
	{
		KeyboardEvent e;

		int n;
		ioctl(0, FIONREAD, &n);

#define o(buf)								\
		if(!strcmp(buf, "\x1B[A")) {				\
			e.isSpecialKey = true;				\
			e.specialKey					\
				= KeyboardEvent::E_KEYBOARD_ARR_UP;	\
		} else if(!strcmp(buf, "\x1B[B")) {			\
			e.isSpecialKey = true;				\
			e.specialKey					\
				= KeyboardEvent::E_KEYBOARD_ARR_DOWN;	\
		} else if(!strcmp(buf, "\x1B[C")) {			\
			e.isSpecialKey = true;				\
			e.specialKey					\
				= KeyboardEvent::E_KEYBOARD_ARR_RIGHT;	\
		} else if(!strcmp(buf, "\x1B[D")) {			\
			e.isSpecialKey = true;				\
			e.specialKey					\
				= KeyboardEvent::E_KEYBOARD_ARR_LEFT;	\
		} else {						\
			/* TODO: handle each char individually*/	\
		}

		char buf[5] = {};
	
		if(n == 3) {
			fread(buf, sizeof(char), 3, stdin);
			o(buf);	
		
			//TODO: fix this
			for(auto l : listeners) {
				l->onEvent(e);
			}
			
		} else if(n == 4) {
			fread(buf, sizeof(char), 4, stdin);

			if(buf[0] == buf[1] && buf[0] == '\x1B') {

				e.setState(KeyboardEvent::E_KEYBOARD_META);
				memmove(buf, buf+1, 3);
				o(buf);

				//TODO: fix this
				for(auto l : listeners) {
					l->onEvent(e);
				}
				
			} else {
				//TODO: handle each char individually
			}
		}

#undef o
		
		char c = getch_();

		if(c >= 'A' && c <= 'Z') {
			e.setState(KeyboardEvent::E_KEYBOARD_SHIFT);
			e.data = c;
		} else if (c >= ' ' && c < 127) {
			e.data = c;
		} else if (c == 8 || c == 9 || c == '\n') {
		        e.isSpecialKey = true;
			//TODO: fix switch
			switch(c) {
			case 8:
				e.specialKey
					= KeyboardEvent::E_KEYBOARD_BSPACE;
				break;
			case 9:
				e.specialKey = KeyboardEvent::E_KEYBOARD_TAB;
				break;
			case '\n':
				e.specialKey
					= KeyboardEvent::E_KEYBOARD_ENTER;
				break;
			}
			e.data = c;
		}

		//TODO: this is UB
		fflush(stdin);

		for(auto l : listeners) {
			l->onEvent(e);
		}
	}
	#endif
	
}
