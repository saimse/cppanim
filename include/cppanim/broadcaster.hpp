#pragma once

#include <cppanim/event.hpp>
#include <cppanim/listener.hpp>

#include <vector>

namespace cppanim::util {

	template<typename T, class C = GenericListener<T>>
	class GenericBroadcaster {
	protected:
		std::vector<GenericListener<T> *> listeners;
	public:
		virtual void registerListener(C& l)
		{
			listeners.push_back(&l);
		}

		GenericBroadcaster() : listeners() {}
		explicit GenericBroadcaster(
			std::initializer_list<C *> i)
			: listeners(i) {}
			
	};

	template<typename T>
	using EventBroadcaster = GenericBroadcaster<Event<T>,
						    EventListener<T>>;

	using KeyboardBroadcaster = GenericBroadcaster<KeyboardEvent>;
	
}
