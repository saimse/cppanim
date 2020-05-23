#include <cppanim/animation.hpp>

#include <math.h>

namespace cppanim::gfx {


        Animation::Animation(XY size, std::size_t duration, float playRate,
		             XY position, int zIndex)
                             : duration(duration)
			     , data(duration, Frame(size))
                             , playRate(playRate)
        {
                data.reserve(duration);
		this->size = size;
		this->position = position;
		this->zIndex = zIndex;
        }

        Animation::Animation(const Animation& copy) : duration(copy.duration)
                                                      , data(copy.data),
                                                      playRate(copy.playRate)
        {
		this->size = copy.size;
		this->position = copy.position;
		this->zIndex = copy.zIndex;
	}

        Animation::Animation(XY size, const std::vector<Frame> &data,
			     float playRate, XY position, int zIndex)
                                        : duration(data.size()), data(data),
                                          playRate(playRate)
	{
		this->size = size;
		this->position = position;
		this->zIndex = zIndex;
	}

	Animation::Animation(XY size, std::initializer_list<Frame> l,
			     float playRate, XY position, int zIndex)
		: data(l), duration(data.size()), playRate(playRate)
	{
		this->size = size;
		this->position = position;
		this->zIndex = zIndex;
	}
	
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
