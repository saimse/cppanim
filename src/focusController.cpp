#include <cppanim/focusController.hpp>

namespace cppanim {
	FocusController& FocusController::getInstance()
	{
		static FocusController instance;
		return instance;
	}
	FocusController::FocusController(): focusables(), focusIndex(0)
	{
		cppanim::Screen::getInstance()
			.registerListener(*this);
	}

	void FocusController::registerListener(Focusable& ref)
	{
		focusables.push_back(&ref);
	}

	void FocusController::onEvent(const KeyboardEvent& ref)
	{
		if(!ref.isSpecialKey && ref.data == 9){
			focusables[focusIndex]->onFocusLoss();
			focusIndex =
				++focusIndex % focusables.size();
			focusables[focusIndex]->onFocus();
			return;
		}
		focusables[focusIndex]->onEvent(ref);
	}
}
