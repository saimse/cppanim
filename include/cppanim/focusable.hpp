#pragma once

#include <cppanim/listener.hpp>
#include <cppanim/focusController.hpp>

namespace cppanim {
	class Focusable : public KeyboardListener {
	public:
		virtual void onEvent(const KeyboardEvent&)=0;
		virtual void onFocus() {}
		virtual void onFocusLoss() {}
		Focusable();
		
	};
}	
