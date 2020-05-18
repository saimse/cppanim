#pragma once

#include <cppanim/listener.hpp>
#include <cppanim/focusController.hpp>

namespace cppanim::util {
	class Focusable : public KeyboardListener {
	public:
		virtual void onEvent(const KeyboardEvent&);
		virtual void onFocus() {}
		virtual void onFocusLoss() {}
		Focusable();
		
	};
}	
