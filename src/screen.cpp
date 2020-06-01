#include <cppanim/screen.hpp>

#include <algorithm>
#include <stdio.h>
#include <thread>
#include <mutex>

#include "diffbuff.hpp"

#ifndef _WIN32
#include <map>
#include <regex>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#endif

#include <iostream>

namespace cppanim {

	static inline void drawSymbol(const Symbol &s)
	{
		// TODO: Implement color printing
		//	printf("asd\n");
		//std::cout << s.symbol;
		printf("%c", s.symbol);
	}

	struct Screen::impl {
		XY screenSize;
		DiffBuff diffbuff;

		std::vector<Drawable *> objects;

		clock_t globalClock = 0;

		std::unique_ptr<std::thread> drawingThread;
		std::unique_ptr<std::thread> inputThread;

		bool isRunning = false;
		bool isPaused = false;

		void addDrawable(Drawable &d) {
			objects.push_back(&d);
			sortDrawables();
		}

		void start()
		{
			isRunning = true;

			Screen &s = Screen::getInstance();
			inputThread.reset(new std::thread([&](){
				while(isRunning) {
					s.handleInput();
				}
			}));

			clrscr();
			drawingThread.reset(new std::thread([&](){
				while(isRunning) {
					if(isPaused) {
						continue;
					}

					sortDrawables();

					XY screenWH = getWindowSize();
					if(screenWH.x != screenSize.x
					   || screenWH.y != screenSize.y) {
						diffbuff.resize(screenWH);
						screenSize = screenWH;
						clrscr();
					}

					generateBufferFromDrawables();
					drawToScreen();

					globalClock++;

					cppanim::sleep( 1000 / framerate );
				}
			}));
		}

		void stop() { isRunning = false; }
		void wait()
		{
			stop();
			drawingThread->join();
			inputThread->join();
		}
		void pause() { isPaused = true; }
		void unpause() { isPaused = false; }

		impl() : screenSize(getWindowSize()), diffbuff(screenSize),
			 objects()
		{
		}

	private:
		void sortDrawables()
		{
			std::sort(objects.begin(), objects.end(),
				  [](Drawable *l, Drawable *r) -> bool
				  {return l->getZIndex() < r->getZIndex();});
		}

		inline bool isWithinBounds(const XY& coords) const
		{
			return (( coords.x >= 0
				  && coords.x < screenSize.x )
				&& (coords.y >= 0
				    && coords.y < screenSize.y ));
		}

		void generateBufferFromDrawables()
		{
			for(auto d : objects) {
				auto context = generateContext();

				d->update(context);
				auto tuple = d->draw(context);

				const Frame& f = std::get<0>(tuple);
				const XY& xy   = std::get<1>(tuple);

				if(!isWithinBounds(xy)) continue;

				auto drawPos = d->getPosition();
				auto drawSz  = d->getSize();

				// translated from conanim; probably works
				for(int j = 0; j < std::min(drawSz.y, screenSize.y - drawPos.y); j++) {
					for(int k = 0; k < std::min(drawSz.x, screenSize.x - drawPos.x); k++) {
						auto currSym = f.at(xy, {k, j});
						if(!(currSym == transparent)) {
							diffbuff[{k + drawPos.x, j + drawPos.y}] = currSym;
						}
					}
				}
			}
		}

		void drawToScreen()
		{
			diffbuff.generateDiff();

			for(int i = 0; i < screenSize.y; i++) {
				for(int j = 0; j < screenSize.x; j++) {
					auto s = diffbuff.getDiff(i * screenSize.x + j);
					if(s != transparent) {
						gotoxy(j, i);
						drawSymbol(s);
					}
				}
			}
			fflush(stdout);

			diffbuff.swapAndClear();
		}

		Context generateContext()
		{
			return {
				globalClock,
			};
		}
	};

	void Screen::addDrawable(Drawable &d)
	{
		pImpl->addDrawable(d);
	}

	void Screen::start() { pImpl->start(); }
	void Screen::stop() { pImpl->stop(); }
	void Screen::wait() { pImpl->wait(); }
	void Screen::pause() { pImpl->pause(); }
	void Screen::unpause() { pImpl->unpause(); }

#ifdef _WIN32
#define S(m)					\
	e.isSpecialKey = true;			\
	e.specialKey = KeyboardEvent::m;	\
	break;

	void Screen::handleInput()
	{
		KeyboardEvent e;

		unsigned char c = getch_();
		if(c == 224 || c == 0){
			c = getch_();
			switch(c){
			case 72:
				S(E_KEYBOARD_ARR_UP)
			case 75:
				S(E_KEYBOARD_ARR_LEFT)
			case 77:
				S(E_KEYBOARD_ARR_RIGHT)
			case 80:
				S(E_KEYBOARD_ARR_DOWN)
			case 59:
				S(E_KEYBOARD_F1)
			case 60:
				S(E_KEYBOARD_F2)
			case 61:
				S(E_KEYBOARD_F3)
			case 62:
				S(E_KEYBOARD_F4)
			case 63:
				S(E_KEYBOARD_F5)
			case 64:
				S(E_KEYBOARD_F6)
			case 65:
				S(E_KEYBOARD_F7)
			case 66:
				S(E_KEYBOARD_F8)
			case 67:
				S(E_KEYBOARD_F9)
			case 68:
				S(E_KEYBOARD_F10)
			case 133:
				S(E_KEYBOARD_F11)
			case 134:
				S(E_KEYBOARD_F12)
			case 71:
				S(E_KEYBOARD_HOME)
			case 79:
				S(E_KEYBOARD_END)
			case 82:
				S(E_KEYBOARD_INS)
			case 83:
				S(E_KEYBOARD_DEL)
			case 73:
				S(E_KEYBOARD_PGUP)
			case 81:
				S(E_KEYBOARD_PGDN)
			default:
				return;
			}
		} else if((c >= 32 && c < 127)
			  ||c == '\t' || c == '\b' || c == '\n') {
			//127 is DEL which is handled above
			e.data = c;
		} else if(c >= 1 && c <= 26) {
			e.setState(KeyboardEvent::E_KEYBOARD_CONTROL);
			e.data = 'A' + c - 1;
		} else {
			return;
		}

		for(auto l : listeners){
			l->onEvent(e);
		}
	}
#undef S

#else

	static const constexpr int bufsize = 8;

	static std::tuple<KeyboardEvent, int> parseOne(char buf[bufsize])
	{
		KeyboardEvent e;
		int parsed = 0;

		const std::map<std::string, KeyboardEvent::SpecialKey> map{
			{"^\033\\[A",   KeyboardEvent::E_KEYBOARD_ARR_UP},
			{"^\033\\[B",   KeyboardEvent::E_KEYBOARD_ARR_DOWN},
			{"^\033\\[C",   KeyboardEvent::E_KEYBOARD_ARR_RIGHT},
			{"^\033\\[D",   KeyboardEvent::E_KEYBOARD_ARR_LEFT},
			{"^\033OP",     KeyboardEvent::E_KEYBOARD_F1},
			{"^\033OQ",     KeyboardEvent::E_KEYBOARD_F2},
			{"^\033OR",     KeyboardEvent::E_KEYBOARD_F3},
			{"^\033OS",     KeyboardEvent::E_KEYBOARD_F4},
			{"^\033\\[15", KeyboardEvent::E_KEYBOARD_F5},
			{"^\033\\[17", KeyboardEvent::E_KEYBOARD_F6},
			{"^\033\\[18", KeyboardEvent::E_KEYBOARD_F7},
			{"^\033\\[19", KeyboardEvent::E_KEYBOARD_F8},
			{"^\033\\[20", KeyboardEvent::E_KEYBOARD_F9},
			{"^\033\\[21", KeyboardEvent::E_KEYBOARD_F10},
			{"^\033\\[23", KeyboardEvent::E_KEYBOARD_F11},
			{"^\033\\[24", KeyboardEvent::E_KEYBOARD_F12},
			{"^\033\\[1",  KeyboardEvent::E_KEYBOARD_HOME},
			{"^\033\\[2",  KeyboardEvent::E_KEYBOARD_INS},
			{"^\033\\[4",  KeyboardEvent::E_KEYBOARD_END},
			{"^\033\\[5",  KeyboardEvent::E_KEYBOARD_PGUP},
			{"^\033\\[6",  KeyboardEvent::E_KEYBOARD_PGDN},
		};

		for(auto it = map.begin(); it != map.end(); it++) {
			std::cmatch m;
			if(std::regex_search(buf+parsed, m,
					std::basic_regex<char>(it->first))) {
				e.isSpecialKey = true;
				e.specialKey = it->second;
				parsed += m.length();


				if(std::regex_match(buf + m.length(),
					 std::basic_regex<char>(";2(F|H)"))){
					e.setState(KeyboardEvent::E_KEYBOARD_SHIFT);
					parsed += 3;
				}

				else if(std::regex_match(buf + m.length(),
					 std::basic_regex<char>(";5(F|H)"))){
					e.setState(KeyboardEvent::E_KEYBOARD_CONTROL);
					parsed += 3;
				}

				return {e, parsed};
			}
		}

		if(buf[0] == '\033' && buf[1] != '[') {
			e.setState(KeyboardEvent::E_KEYBOARD_META);
			parsed++;
		}

		if((buf[parsed] >= 32 && buf[parsed] < 127)
			  || buf[parsed] == '\t'|| buf[parsed] == '\b'
			  || buf[parsed] == '\n') {
			e.data = buf[parsed];
			parsed++;
		} else if(buf[parsed] >= 1 && buf[parsed] <= 26) {
			e.setState(KeyboardEvent::E_KEYBOARD_CONTROL);
			e.data = 'A' + buf[parsed] - 1;
			parsed++;
		}

		return {e, parsed};
	}

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


	void Screen::handleInput()
	{
		struct {char buf[bufsize]; int size;} inbuf = {{}, 0};

		// This disables echoing and turns off canonical mode.
		// While in non-canonical mode, read(2) will be non-blocking
		// TODO: move into global init, reset in dtor/sighandler
		initTermios(0);

		inbuf.size = read(0, inbuf.buf, bufsize - 1);

		// Buffer might have more than one inputted character,
		// so, reparse until you fail. Then, flush.
		while(inbuf.size > 0) {
			auto parse = parseOne(inbuf.buf);

			KeyboardEvent e = std::get<0>(parse);
			int parsed = std::get<1>(parse);

			if(parsed == 0) {
				memmove(inbuf.buf, inbuf.buf+1, bufsize - 1);
				inbuf.size -= parsed;
			} else {
				for(auto l : listeners) {
					l->onEvent(e);
				}
				memmove(inbuf.buf, inbuf.buf + parsed,
					bufsize - parsed);
				inbuf.size -= parsed;
			}
		}

		resetTermios();

	}
#endif

	Screen& Screen::getInstance()
	{
		static Screen *instance = nullptr;
		static std::mutex m;
		if(instance == nullptr) {
			m.lock();
			if(instance == nullptr) {
				instance = new Screen();
			}
			m.unlock();
		}
		return *instance;
	}

	Screen::Screen() : pImpl{std::make_unique<impl>()} {}
	Screen::~Screen() = default;

}
