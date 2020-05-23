#pragma once

#ifdef _WIN32
	#include <conio.h>
	#include <windows.h>
#elif defined(__APPLE__)
	#error "Unsupported platform"
#elif defined(__linux__) || defined(__unix__) || defined(_POSIX_VERSION)
	#include <termios.h>
	#include <stdio.h>
	#include <sys/ioctl.h>
	#include <unistd.h>
	#include <time.h>
#else
	#error "Unknown host/target"
#endif

namespace cppanim::fundamentals {

	#ifdef _WIN32
		inline void gotoxy(int x, int y)
		{ SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
					   (COORD){(x), (y)}); }
	#else
	        inline void gotoxy(int x, int y)
		{ printf("%c[%d;%dH",0x1B, (y+1), (x+1)); }
	#endif

        char getch_();
	bool iskbhit();
	
	//TODO(milevuletic): Determine all char types; Detect them.
	typedef char char_t;

	typedef unsigned long long clock_t;

	// 12 fps (83ms delay) should be enough, and is just slow enough
	// to be able to print on time on Windows
	const int framerate = 12;

	const char_t transparent = 0x11;
	const char_t blank       = ' ';

	const char_t black = 0;
	const char_t white = 1;


	void clrscr();

	struct XY { int x, y; };
	XY getWindowSize();

	void sleep(int milliseconds);

}
