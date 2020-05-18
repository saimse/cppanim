#include <cppanim/focusable.hpp>

namespace cppanim::util{
	Focusable::Focusable()
	{
		FocusController::getInstance()
			.registerListener(*this);
	}
}
