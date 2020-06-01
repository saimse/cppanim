#include "diffbuff.hpp"


Symbol& DiffBuff::getCurrent(std::size_t n)
{
	return curr[n];
}

Symbol& DiffBuff::getNext(std::size_t n)
{
	return next[n];
}

Symbol& DiffBuff::getDiff(std::size_t n)
{
	return diff[n];
}

Symbol& DiffBuff::operator[](std::size_t n)
{
	return getNext(n);
}

Symbol& DiffBuff::operator[](XY xy)
{
	return operator[](xy.y * size.x + xy.x);
}

void DiffBuff::swapAndClear()
{
	curr = next;

	std::fill(next.begin(), next.end(),
		  cppanim::transparent);
	std::fill(diff.begin(), diff.end(),
		  cppanim::transparent);
}

void DiffBuff::generateDiff()
{
	for(int i = 0; i < size.x * size.y; ++i){
		if((next[i] != curr[i])){
			if(next[i] == transparent) {
				diff[i] = ' ';
			} else {
				diff[i] = next[i];
			}
		}
	}
}

void DiffBuff::resize(XY newsize)
{
#define o(n)						\
	n.reserve(newsize.x * newsize.y);		\
	std::fill(n.begin(), n.end(),			\
		  cppanim::transparent);

	o(curr);
	o(next);
	o(diff);

	size = newsize;
#undef o
}
