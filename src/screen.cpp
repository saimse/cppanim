#include "screen.hpp"

#include <algorithm>
#include <stdio.h>

namespace cppanim::gfx {

	void Screen::addDrawable(const Drawable &d)
	{
		objects.push_back(&d);
		std::sort(objects.begin(), objects.end());
	}

#ifdef _WIN32
#define S(m)					\
	e.isSpecialKey = true;			\
	e.specialKey = KeyboardEvent::m;	\
	break;

	void Screen::handleInput()
	{
		KeyboardEvent e;

		unsigned char c = getch_();
		if(c == 224 || c == 0){
			c = getch_();
			switch(c){
			case 72:
				S(E_KEYBOARD_ARR_UP)
			case 75:
				S(E_KEYBOARD_ARR_LEFT)
			case 77:
				S(E_KEYBOARD_ARR_RIGHT)
			case 80:
				S(E_KEYBOARD_ARR_DOWN)
			case 59:
				S(E_KEYBOARD_F1)
			case 60:
				S(E_KEYBOARD_F2)
			case 61:
				S(E_KEYBOARD_F3)
			case 62:
				S(E_KEYBOARD_F4)
			case 63:
				S(E_KEYBOARD_F5)
			case 64:
				S(E_KEYBOARD_F6)
			case 65:
				S(E_KEYBOARD_F7)
			case 66:
				S(E_KEYBOARD_F8)
			case 67:
				S(E_KEYBOARD_F9)
			case 68:
				S(E_KEYBOARD_F10)
			case 133:
				S(E_KEYBOARD_F11)
			case 134:
				S(E_KEYBOARD_F12)
			case 71:
				S(E_KEYBOARD_HOME)
			case 79:
				S(E_KEYBOARD_END)
			case 82:
				S(E_KEYBOARD_INS)
			case 83:
				S(E_KEYBOARD_DEL)
			case 73:
				S(E_KEYBOARD_PGUP)
			case 81:
				S(E_KEYBOARD_PGDN)
			default:
				return;
			}
		} else if(c >= 1 && c <= 26) {
			e.setState(KeyboardEvent::E_KEYBOARD_CONTROL);
			e.data = 'A' + c - 1;
		} else if((c >= 32 && c < 127)
			  ||c == '\t' || c == '\b' || c == '\n'){
			//127 is DEL which is handled above
			e.data = c;
		}

		for(auto l : listeners){
			l->onEvent(e);
		}
	}
#undef S

#else

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

		for(auto l : listeners) {
			l->onEvent(e);
		}
	}
#endif
}
