#pragma once

#ifdef _WIN32
#include <windows.h>
	#define gotoxy(x, y) { SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){(x), (y)}); }
#elif defined(__APPLE__)
	#error "Unsupported platform"
#elif defined(__linux__)
	#include <stdio.h>
	#include <sys/ioctl.h>
	#include <unistd.h>
	#include <time.h>
	#define gotoxy(x, y) { printf("%c[%d;%df",0x1B, (y), (x)); }
#elif defined(__unix__) // all unices not caught above
	#include <stdio.h>
	#include <sys/ioctl.h>
	#include <unistd.h>
	#include <time.h>
	#define gotoxy(x, y) { printf("%c[%d;%df",0x1B, (y), (x)); }
#elif defined(_POSIX_VERSION)
	#include <stdio.h>
	#include <sys/ioctl.h>
	#include <unistd.h>
	#include <time.h>
	#define gotoxy(x, y) { printf("%c[%d;%df",0x1B, (y), (x)); }
#else
	#error "Unknown host/target"
#endif

namespace cppanim::fundamentals {
	//TODO(milevuletic): Determine all char types; Detect them.
	typedef char char_t;

        #ifdef _WIN32
            	#define gotoxy(x, y) { SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){(x), (y)}); }
        #else
                #define gotoxy(x, y) { printf("%c[%d;%df",0x1B, (y), (x)); }
        #endif

	// 12 fps (83ms delay) should be enough, and is just slow enough
	// to be able to print on time on Windows
	const int framerate = 12;

	const char_t transparent = 0x11;
	const char_t blank       = ' ';

	const char_t black = 0;
	const char_t white = 1;

	//TODO(milevuletic): OS detection, terminal detection,
	//                   terminal fundamentals (clear, gotoxy)


	void clrscr()
	{
	#ifdef _WIN32
		COORD coordScreen = { 0, 0 };
		DWORD cCharsWritten;
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		DWORD dwConSize;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		/* get the number of character cells in the current buffer */
		GetConsoleScreenBufferInfo( hConsole, &csbi );
		dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

		/* fill the entire screen with blanks */
		FillConsoleOutputCharacter( hConsole, (TCHAR) ' ',
					    dwConSize, coordScreen,
					    &cCharsWritten );

		/* get the current text attribute */
		GetConsoleScreenBufferInfo( hConsole, &csbi );

		/* now set the buffer's attributes accordingly */
		FillConsoleOutputAttribute( hConsole, csbi.wAttributes,
					    dwConSize, coordScreen,
					    &cCharsWritten );

		/* put the cursor at (0, 0) */
		SetConsoleCursorPosition( hConsole, coordScreen );
	#else
		printf("\x1B[2J\x1B[H");
	#endif // _WIN32
	}

	struct XY { int x, y; };
	XY getWindowSize()
	{
		XY xy = {0, 0};
	#ifdef _WIN32
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),
					   &csbi);
		xy = (XY){csbi.srWindow.Right - csbi.srWindow.Left + 1,
			  csbi.srWindow.Bottom - csbi.srWindow.Top + 1};
        #else
		struct winsize w;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		xy = (XY){ w.ws_col, w.ws_row };
        #endif
		return xy;
	}

	void sleep(int milliseconds)
	{
        #ifdef _WIN32
		Sleep(milliseconds);
        #else
		struct timespec t = {0, 1000*milliseconds};
		nanosleep(&t, NULL);
        #endif
	}

}
