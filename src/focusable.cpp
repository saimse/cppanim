#include <cppanim/focusable.hpp>

namespace cppanim {
	Focusable::Focusable()
	{
		FocusController::getInstance()
			.registerListener(*this);
	}
}
