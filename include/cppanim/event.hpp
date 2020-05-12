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
			E_KEYBOARD_CONTROL = 0x1,
			E_KEYBOARD_META,
			E_KEYBOARD_SUPER
		};
		uint8_t stateFlags;

		bool isState(enum KeyboardState flag)
		{ return stateFlags & flag; }

		void setState(enum KeyboardState flag)
		{ stateFlags &= flag; }
	};

}
