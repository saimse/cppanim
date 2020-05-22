#pragma once

#include <cppanim/fundamentals.hpp>
#include <cppanim/symbol.hpp>

#include <vector>

using namespace cppanim::gfx;
using namespace cppanim::fundamentals;

struct DiffBuff {
	std::vector<Symbol> curr;
	std::vector<Symbol> next;
	std::vector<Symbol> diff;

	XY size;
	
	Symbol& getCurrent(std::size_t n);
	Symbol& getNext(std::size_t n);
	Symbol& getDiff(std::size_t n);
	
	// Get Symbol in `next' buffer
	Symbol& operator[](std::size_t n);
	Symbol& operator[](XY xy);

	void swapAndClear();
	void generateDiff();

	void resize(XY newsize);

	//DiffBuff() = delete;
	explicit DiffBuff(XY sz) : curr(sz.x*sz.y),
				   next(sz.x*sz.y),
				   diff(sz.x*sz.y) {}
};
