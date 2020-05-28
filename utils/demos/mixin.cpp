#include <cppanim.hpp>
#include <stdio.h>

using namespace cppanim::gfx;

class Border : public Mixin {
public:
	virtual void update(const Context& c, Mixinable *m, Frame& f)
	{}
	
	virtual void draw(const Context& c, Mixinable *m, Frame& f)
	{
		auto sz = m->getSize();
		for(int i = 0; i < sz.x; i++) {
			f.at(sz, {i, 0})        = '#';
			f.at(sz, {i, sz.y - 1}) = '#';
		}
		for(int i = 0; i < sz.y; i++) {
			f.at(sz, {0, i})        = '#';
			f.at(sz, {sz.x - 1, i}) = '#';
		}
	}
};

class Fill : public Mixin {
	public:
	virtual void update(const Context& c, Mixinable *m, Frame& f)
	{}
	
	virtual void draw(const Context& c, Mixinable *m, Frame& f)
	{
		auto sz = m->getSize();
		for(int i = 0; i < sz.x; i++) {
			for(int j = 0; j < sz.y; j++) {
				f.at(sz, {i, j}) = '.';
			}
		}
	}
};

class MyMixinable : public Mixinable, KeyboardListener {
public:
	MyMixinable() : Mixinable({new Fill, new Border}, {15, 5})
	{
		Screen::getInstance().registerListener(*this);
	}

	explicit MyMixinable(std::initializer_list<Mixin *> m) : Mixinable(m, {15, 5})
	{
		Screen::getInstance().registerListener(*this);
	}
						      
	void onEvent(const KeyboardEvent &e) override
	{
		if(e.isSpecialKey) {
			if(e.specialKey == KeyboardEvent::E_KEYBOARD_ARR_UP
			   && size.y > 1){
			        resize({size.x, --size.y});
			} else if(e.specialKey == KeyboardEvent::E_KEYBOARD_ARR_DOWN
				  && size.y < getWindowSize().y - 1){
			        resize({size.x, ++size.y});
			} else if(e.specialKey == KeyboardEvent::E_KEYBOARD_ARR_LEFT
				  && size.x > 1){
			        resize({--size.x, size.y});
			} else if(e.specialKey == KeyboardEvent::E_KEYBOARD_ARR_RIGHT
				  && size.x < getWindowSize().x - 1){
			        resize({++size.x, size.y});
			}
		}
	}
};

int main()
{
	Screen &s = Screen::getInstance();

	MyMixinable m{new Fill};	
	s.addDrawable(m);
	
	s.start();
	sleep(10000);
	s.wait();

	return 0;
}
