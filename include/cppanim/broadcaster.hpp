#pragma once

#include <cppanim/event.hpp>
#include <cppanim/listener.hpp>

#include <vector>

namespace cppanim::util {

	template<typename T>
	class GenericBroadcaster {
		std::vector<const GenericListener<T> *> listeners;
	public:
		virtual void registerListener(const GenericListener<T>& l)
		{
			listeners.push_back(&l);
		}
	};

	template<typename T>
	using EventBroadcaster = GenericBroadcaster<Event<T>>;

	using KeyboardBroadcaster = GenericBroadcaster<KeyboardEvent>;
	
}
