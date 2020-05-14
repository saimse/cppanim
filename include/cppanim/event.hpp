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
			E_KEYBOARD_SUPER = 4
		};

		bool isSpecialKey = false;
		enum SpecialKey {
			E_KEYBOARD_ARR_UP,
			E_KEYBOARD_ARR_DOWN,
			E_KEYBOARD_ARR_LEFT,
			E_KEYBOARD_ARR_RIGHT,
		} specialKey;
		
		uint8_t stateFlags;		

		bool isState(enum KeyboardState flag)
		{ return stateFlags & flag; }

		void setState(enum KeyboardState flag)
		{ stateFlags &= flag; }
	};

}
