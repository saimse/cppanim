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

void DiffBuff::swapAndClear()
{
	curr = next;

	std::fill(next.begin(), next.end(),
		  cppanim::fundamentals::transparent);
	std::fill(diff.begin(), diff.end(),
		  cppanim::fundamentals::transparent);
}

void DiffBuff::generateDiff()
{
	for(int i = 0; i < size.x * size.y; ++i){
	        if(!(next[i] == curr[i])){
			diff[i] = next[i];
		}
	}
}

void DiffBuff::resize(XY newsize)
{
	curr.clear();
	next.clear();
	diff.clear();
	size.x = newsize.x;
	size.y = newsize.y;
}
