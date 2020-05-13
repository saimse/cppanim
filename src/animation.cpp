#include <cppanim/animation.hpp>

#include <math.h>

namespace cppanim::gfx {

        Animation::Animation(XY size, std::size_t duration)
                             : duration(duration), data(duration, Frame(size))
                             , playRate(1)
        {
                data.reserve(duration);
        }

        Animation::Animation(XY size, std::size_t duration, float playRate)
                             : duration(duration), data(duration, Frame(size))
                             , playRate(playRate)
        {
                data.reserve(duration);
        }

        Animation::Animation(const Animation& copy) : duration(copy.duration)
                                                      , data(copy.data),
                                                      playRate(copy.playRate)
                                                      {}

        Animation::Animation(const std::vector<Frame> &data)
                                        : duration(data.size()), data(data),
                                          playRate(1) {}

        Animation::Animation(const std::vector<Frame> &data, float playRate)
                                        : duration(data.size()), data(data),
                                          playRate(playRate) {}

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
