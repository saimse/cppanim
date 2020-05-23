#include <cppanim/fundamentals.hpp>

namespace cppanim::fundamentals {

	// #ifdef _WIN32
	// 	void gotoxy(int x, int y)
	// 	{ SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
	// 				   (COORD){(x), (y)}); }
	// #else
	//         void gotoxy(int x, int y)
	// 	{ printf("%c[%d;%dH",0x1B, (y-1), (x-1)); }
	// #endif

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

	XY getWindowSize()
	{
		XY xy;
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
		struct timespec t = {milliseconds/1000,
				     milliseconds%1000*1000000};
		nanosleep(&t, NULL);
	#endif
	}

	#ifndef _WIN32
	static struct termios old, current;
	static inline void initTermios(int echo)
	{
		tcgetattr(0, &old);
		current = old;
		current.c_lflag &= ~ICANON; /* disable buffered i/o */
		if (echo) {
			current.c_lflag |= ECHO; /* set echo mode */
		} else {
			current.c_lflag &= ~ECHO; /* set no echo mode */
		}
		tcsetattr(0, TCSANOW, &current);
	}

	static inline void resetTermios(void){ tcsetattr(0, TCSANOW, &old); }

	#endif

	__attribute__((visibility("default")))
	char getch_()
	{
		#ifdef _WIN32
		return getch();
		#else
		char ch;
		initTermios(0);
		ch = getchar();
		resetTermios();
		return ch;
		#endif
	}

	bool iskbhit()
	{
		#ifdef _WIN32
		return kbhit();
		#else
		int n;
		return ioctl(0, FIONREAD, &n) == 0 && n > 0;
		#endif
	}


}
