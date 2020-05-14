#include "testsuite.hpp"

using namespace cppanim::test;

#include <cppanim/fundamentals.hpp>
#include <cppanim/symbol.hpp>
Unit::result_t symbol_test()
{
	cppanim::gfx::Symbol x('a', cppanim::fundamentals::white);
	cppanim::gfx::Symbol y('b');

	x = 'z';

	if(x == y)
		return Unit::result_t::error;

	return Unit::result_t::success;
}

Unit::result_t getch_test()
{
	char c;

	printf("After this line getch() will be called.\n");

	printf("Enter any letter: ");
	cppanim::fundamentals::getch_();

	printf("\nEnter y if the character didn't echo "\
	       "and enter wasn't needed: ");
	c = cppanim::fundamentals::getch_();

	printf("\n");

	if(c == 'y' || c == 'Y')
		return Unit::result_t::success;

	return Unit::result_t::warning;
}

#include <cppanim/event.hpp>
#include <cppanim/broadcaster.hpp>
#include <cppanim/listener.hpp>
Unit::result_t eventBroadcasterListener_test()
{
	class IntEventListener : public cppanim::util::EventListener<int> {
		virtual void onEvent(const cppanim::util::Event<int>& e)
		{
			if(!(e.name == "name"
			     || e.timestamp == 123
			     || e.data == 1337))
				expectedValues = false;
		}
	public:
		bool expectedValues = true;
	} listener;

	class IntEventBroadcaster
		: public cppanim::util::EventBroadcaster<int> {
	public:
		void sendEvent(cppanim::util::Event<int> intEvent)
		{
			for(auto l : listeners)
				l->onEvent(intEvent);
		}
	} broadcaster;

	broadcaster.registerListener(listener);
	broadcaster.sendEvent({"name", 123, 1337});

	if(listener.expectedValues)
		return Unit::success;

	return Unit::error;
}

#include "../screen.hpp"
Unit::result_t screenInputHandling_test()
{
	Screen s;

	class MyKBListener : public KeyboardListener {
	public:
		bool success = false;
		virtual void onEvent(const KeyboardEvent& e) override {
			if(e.isSpecialKey
			   && e.specialKey
			   == KeyboardEvent::E_KEYBOARD_TAB) {
				success = true;
			}
		}
	} l;

	s.registerListener(l);

	//s.handleInput();

	if(l.success)
		return Unit::success;
	
	return Unit::warning;
}


#include <string.h>

int main(int argc, char **argv)
{
	TestController &t = TestController::getInstance();

	t.emplaceUnit("Symbol test", symbol_test);
	t.emplaceUnit("Int event broadcaster/listener",
		      eventBroadcasterListener_test);

	//TODO: this is just dumb
	bool interactiveTests = false;
	if(argc > 1) {
		for(int i = 0; i < argc; i++) {
			if(!strcmp(argv[i], "-i")) {
				interactiveTests = true;
				break;
			}
		}
	}

	if(interactiveTests) {
		t.emplaceUnit("Getch test", getch_test);
		t.emplaceUnit("Screen kbevent handling",
			      screenInputHandling_test);
	}

	int s, w, e;
	std::tie(s, w, e) = t.runTests();

	#ifdef _WIN32
	printf("%dS/%dW/%dE\n", s, w, e);
	#else
	printf("\033[032m%dS\033[0m/"\
	       "\033[033m%dW\033[0m/"\
	       "\033[031m%dE\033[0m\n", s, w, e);
	#endif
}
