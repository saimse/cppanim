#include <cppanim/focusController.hpp>

namespace cppanim::util{
	FocusController::FocusController(): focusables(), focusIndex(0)
	{
		cppanim::gfx::Screen::getInstance()
			.registerListener(*this);
	}

	void FocusController::registerListener(Focusable& ref)
	{
		focusables.push_back(&ref);
	}

	void FocusController::onEvent(const KeyboardEvent& ref)
	{
		if(ref.data == '\t'){
			focusables[focusIndex]->onFocusLoss();
			focusIndex =
				++focusIndex % focusables.size();
			focusables[focusIndex]->onFocus();
			return;
		}
		focusables[focusIndex]->onEvent(ref);
	}
}
