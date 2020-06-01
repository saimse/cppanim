#include <cppanim.hpp>

using namespace cppanim;

class MoveWithArrows : public Animation, public KeyboardListener {
public:
	MoveWithArrows() = delete;
	explicit MoveWithArrows(const Animation& a) : Animation(a)
	{
		// Register this class for listening to keypresses
		Screen::getInstance().registerListener(*this);
	}

	virtual void onEvent(const KeyboardEvent& e) override
	{
		// Arrow keys are special keys, so isSpecialKey is set
		// For a full list of special keys, see cppanim/event.hpp
		if(e.isSpecialKey) {
			if(e.specialKey == KeyboardEvent::E_KEYBOARD_ARR_UP) {
				if(position.y > 0) position.y--;
			} else if(e.specialKey == KeyboardEvent::E_KEYBOARD_ARR_DOWN) {
				if(position.y < getWindowSize().y - size.y) position.y++;
			} else if(e.specialKey == KeyboardEvent::E_KEYBOARD_ARR_LEFT) {
				if(position.x > 0) position.x--;
			} else if(e.specialKey == KeyboardEvent::E_KEYBOARD_ARR_RIGHT) {
				if(position.x < getWindowSize().x - size.x) position.x++;
			}
		}
	}
};

int main()
{
	Screen &s = Screen::getInstance();

	// MoveWithArrows inherits Animation, and takes a reference to one
	// in its ctor, so as to copy it over. Animation and underlying classes
	// can be implicitly constructed with brace initializers
	MoveWithArrows a ({
		{3, 3},
		{
			{'O', 'O', 'O', 'O', transparent, 'O', 'O', 'O', 'O'},
		},
		1,
		{0, 0},
		2,
	});
	Animation b{
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
                1,
                {4, 4},
                1,
	};
	// Add the object to the screen
	s.addDrawable(a);
        s.addDrawable(b);

	// Start drawing. This will start two new threads.
	// Using std{in, out} before a call to stop() or wait()
	// is ill-advised.
	s.start();

	// Sleep in the main thread
	cppanim::sleep(1000000);

	// Join the drawing threads
	s.wait();
	return 0;
}
