#include <cppanim/frame.hpp>

namespace cppanim::gfx {

        Frame::Frame(std::size_t surface, const Symbol &s)
		: buffer(surface, s) {}

	Frame::Frame(XY xy, const Symbol &s)
		: buffer(xy.x*xy.y, s) {}

        Frame::Frame(const std::vector<Symbol>& copy)
		: buffer(copy) {}

	Frame::Frame(std::initializer_list<Symbol> l)
		: buffer(l) {}
	
	const Symbol& Frame::operator[](size_t n) const
	{ return buffer[n]; }

        Symbol& Frame::operator[](size_t n)
	{ return buffer[n]; }	
	
	const Symbol& Frame::at(XY sz, XY xy) const
	{ return (*this)[sz.x * xy.y + xy.x]; }

	Symbol& Frame::at(XY sz, XY xy)
	{ return (*this)[sz.x * xy.y + xy.x]; }
	
}
