#pragma once

#include <cppanim/fundamentals.hpp>
#include <cppanim/drawable.hpp>

//revisit
#include <cppanim/screen.hpp>

#include "diffbuff.hpp"

#include <memory>

namespace cppanim::gfx {

	using namespace cppanim::fundamentals;
	
	//TODO(milevuletic): Singleton?
	class Screen {

		XY screenSize;
		DiffBuff diffbuff;
		
		std::vector<Drawable *> objects;

		clock_t globalClock = 0;

	public:
		Screen() : screenSize(getWindowSize()),
			   diffbuff(screenSize),
			   objects() {}
		
	};	
	
}
