#include <cppanim/animation.hpp>

#include <math.h>

namespace cppanim::gfx {

	const std::size_t& Animation::getDuration() const { return duration;}
	_cppanim_getterDefin(Animation, float, playRate, getPlayRate);
	void Animation::setPlayRate(float p) { playRate = p; }

	const Frame& Animation::operator[](std::size_t n) const
	{ return data[n]; }

	Frame& Animation::operator[](std::size_t n)
	{ return data[n]; }

	const Frame& Animation::operator()(std::size_t t) const
	{ return (*this)[ floor( fmod( t, duration/playRate ) ) ]; }
	
        std::tuple<const Frame&, const XY&> Animation::draw(const Context& c)
	{
		return std::tuple<const Frame&, const XY&>(
			(*this)(c.globalClock),
		        size);
	}
	
}
