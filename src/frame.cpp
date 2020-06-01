#include <cppanim/frame.hpp>

#include <stdio.h>
#include <wchar.h>

namespace cppanim {

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

	void Frame::saveToFile(FILE* ref)const
	{
		for(int i = 0; i < buffer.size(); ++i){
			buffer[i].saveToFile(ref);
		}
	}
	Frame Frame::loadFromFile(XY size, FILE* ref)
	{
		Frame s(size);
		for(int i = 0; i < (size.x * size.y); ++i){
			s[i] = Symbol::loadFromFile(ref);
		}
		return s;
	}
		
}
