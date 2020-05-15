#pragma once

#include <cppanim/fundamentals.hpp>

#include <string>

namespace cppanim::util {

	template <class T>
	struct Event {
		const std::string name;
		cppanim::fundamentals::clock_t timestamp;
		T data;
	};

	struct KeyboardEvent : public Event<char> {
		enum KeyboardState {
			E_KEYBOARD_CONTROL = 1,
			E_KEYBOARD_META = 2,
			E_KEYBOARD_SUPER = 4,
			E_KEYBOARD_SHIFT = 8,
		};

		bool isSpecialKey = false;
		enum SpecialKey {
			E_KEYBOARD_ARR_UP,
			E_KEYBOARD_ARR_DOWN,
			E_KEYBOARD_ARR_LEFT,
			E_KEYBOARD_ARR_RIGHT,
			E_KEYBOARD_BSPACE,
			E_KEYBOARD_TAB,
			E_KEYBOARD_ENTER,
			E_KEYBOARD_F1,
			E_KEYBOARD_F2,
			E_KEYBOARD_F3,
			E_KEYBOARD_F4,
			E_KEYBOARD_F5,
			E_KEYBOARD_F6,
			E_KEYBOARD_F7,
			E_KEYBOARD_F8,
			E_KEYBOARD_F9,
			E_KEYBOARD_F10,
			E_KEYBOARD_F11,
			E_KEYBOARD_F12,
			E_KEYBOARD_HOME,
			E_KEYBOARD_END,
			E_KEYBOARD_INS,
			E_KEYBOARD_DEL,
			E_KEYBOARD_PGUP,
			E_KEYBOARD_PGDN,
		} specialKey;
		
		uint8_t stateFlags;		

		bool isState(enum KeyboardState flag)
		{ return stateFlags & flag; }

		void setState(enum KeyboardState flag)
		{ stateFlags &= flag; }
	};

}
