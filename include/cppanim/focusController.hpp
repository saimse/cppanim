#pragma once

#include <cppanim/listener.hpp>
#include <cppanim/broadcaster.hpp>
#include <cppanim/focusable.hpp>
#include <cppanim/screen.hpp>

#include <vector>

namespace cppanim::util {
	class Focusable;
	class FocusController : public KeyboardBroadcaster
			      , public KeyboardListener {
	private:
		std::vector<Focusable*> focusables;
		std::size_t focusIndex;
		FocusController();

	public:
		virtual void registerListener(KeyboardListener& l) override
		{
			return;
		}

		static FocusController& getInstance();

		void registerListener(Focusable& ref);

		virtual void onEvent(const KeyboardEvent& ref) override;
	};
}
