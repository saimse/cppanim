#include <cppanim.hpp>
#include <signal.h>

void handle(int a)
{
	printf("%d\n", a);
}

using namespace cppanim::gfx;
using namespace cppanim::util;

int main()
{
	Screen &s = Screen::getInstance();
	Animation a {
		{3, 3},
		{
			{'O', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', 'O', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', 'O', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', 'O', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', 'O', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', 'O', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', 'O', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', 'O', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'O'},
		},
	};
	s.addDrawable(a);
	s.start();

	cppanim::fundamentals::sleep(1000000);

	s.wait();
	return 0;
}
