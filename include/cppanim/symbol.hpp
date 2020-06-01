#pragma once

#include <cppanim/fundamentals.hpp>
#include <stdio.h>

namespace cppanim {
	
	struct Symbol {
		char_t symbol;
		int color;

		Symbol() : symbol(transparent), color(black) {}
		Symbol(char_t s, int c = black) : symbol(s), color(c) {}
		
		void operator=(char_t newSymbol)
		{ this->symbol = newSymbol; }
		
		Symbol& operator=(const Symbol& ns)
		{
			symbol = ns.symbol;
			color = ns.color;
			return *this;
		}

		void operator()(char_t symbol, int color)
		{
			this->symbol = symbol;
			this->color = color;
		}
		
		bool operator==(char_t symbol)
		{ return this->symbol == symbol; }
		
		bool operator==(const Symbol& s)
		{ return (symbol == s.symbol) && (color == s.color); }

		bool operator!=(char_t s)
		{ return !(operator==)(s); }

		bool operator!=(const Symbol& s)
		{ return !(operator==)(s); }

		void saveToFile(FILE* ref)const;
		static Symbol loadFromFile(FILE* ref);
	};
	
}
