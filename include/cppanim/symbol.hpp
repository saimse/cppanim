#include <cppanim/fundamentals.hpp>

namespace cppanim::gfx {
	
	struct Symbol {
		fundamentals::char_t symbol;
		int color;
		
		Symbol(fundamentals::char_t s, int c) : symbol(s), color(c)
		{}
		Symbol(fundamentals::char_t s) : symbol(s),
						 color(fundamentals::black)
		{}
		
		void operator=(fundamentals::char_t newSymbol)
		{ this->symbol = newSymbol; }
		
		void operator=(const Symbol& ns)
		{
			symbol = ns.symbol;
			color = ns.color;
		}

		void operator()(fundamentals::char_t symbol, int color)
		{
			this->symbol = symbol;
			this->color = color;
		}
		
		bool operator==(fundamentals::char_t symbol)
		{ return this->symbol == symbol; }
		
		bool operator==(const Symbol& s)
		{ return (symbol == s.symbol) && (color == s.color); }
	};
	
}
