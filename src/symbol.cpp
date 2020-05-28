#include <cppanim/symbol.hpp>

#include <stdio.h>
#include <wchar.h>

namespace cppanim::gfx{
	void Symbol::saveToFile(FILE* ref)const
	{fprintf(ref, "%c%c%d%c", symbol, 30, color,30);}
	Symbol Symbol::loadFromFile(FILE* ref)
	{
		Symbol s;
		fscanf(ref, "%c\036%d\036", &s.symbol, &s.color);
		return s;
	}
}
