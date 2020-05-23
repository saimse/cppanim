#pragma once

#include <cppanim/symbol.hpp>

// std::size_t
#include <cstddef>
#include <vector>

namespace cppanim::gfx {

	using namespace cppanim::fundamentals;
	
	class Frame {
		std::vector<Symbol> buffer;
	public:
		explicit Frame(std::size_t surface,
			       const Symbol &s = Symbol());

		explicit Frame(XY xy, const Symbol &s = Symbol());

		Frame(const std::vector<Symbol>& copy);
		Frame(std::initializer_list<Symbol> l);

		const Symbol& operator[](size_t n) const;
		Symbol& operator[](size_t n);
			
		const Symbol& at(XY sz, XY xy) const;
		Symbol& at(XY sz, XY xy);
	};
	
}
