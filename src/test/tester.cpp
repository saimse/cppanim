#include "testsuite.hpp"

#include <cppanim.hpp>

using namespace cppanim::test;

Unit::result_t symbol_test()
{
	cppanim::gfx::Symbol x('a', cppanim::fundamentals::white);
	cppanim::gfx::Symbol y('b');

	x = 'z';
	if(!(x == 'z') || x == y)
		return Unit::result_t::error;

	return Unit::result_t::success;
}

int main()
{
	TestController &t = TestController::getInstance();

	t.emplaceUnit("Symbol test", symbol_test);
	
	int s, w, e;
	std::tie(s, w, e) = t.runTests();

	#ifdef _WIN32
	printf("%dS/%dW/%dE\n", s, w, e);
	#else
	printf("\033[032m%dS\033[0m/\033[033m%dW\033[0m/\033[031m%dE\033[0m\n", s, w, e);
	#endif
}
