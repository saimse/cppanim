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
		} else{
			return;
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
		char c = getch_();
		if((c >= 32 && c < 127)
		   ||c == '\t' || c == '\b' || c == '\n'){
			//127 is DEL which is handled above
			e.data = c;
		} else{
			return;
		}

		for(auto l : listeners) {
			l->onEvent(e);
		}
	}
#endif
}
