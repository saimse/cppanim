#pragma once

#include <cppanim/event.hpp>

namespace cppanim::util {

	template<typename T>
	struct GenericListener {
		virtual void onEvent(const T&) = 0;
	};

	template<typename T>
	using EventListener = GenericListener<Event<T>>;

	using KeyboardListener = GenericListener<KeyboardEvent>;

}
