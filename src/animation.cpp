#include <cppanim/animation.hpp>

#include <wchar.h>
#include <stdio.h>
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

        std::tuple<const Frame&, const XY&> Animation::draw
	(const Context& c)
	{
		return std::tuple<const Frame&, const XY&>(
			(*this)(c.globalClock),
		        size);
	}

	void Animation::saveToFile(FILE* ref)const
	{
      		fprintf(ref, "%u\036", duration);
		fprintf(ref, "%f%c", playRate, 30);
		fprintf(ref, "%d%c", size.x, 30);
		fprintf(ref, "%d%c", size.y, 30);
		fprintf(ref, "%d%c", position.x, 30);
		fprintf(ref, "%d%c", position.y, 30);
		fprintf(ref, "%d%c", zIndex, 30);
		for(int i = 0; i < (size.x * size.y); ++i){
			data[i].saveToFile(ref);
		}
	}

	Animation Animation::loadFromFile(FILE* ref)
	{
		std::size_t duration;
		float playRate;
		XY xy, position;
		std::size_t zIndex;
		fscanf(ref, "%u\036%f\036%d\036%d\036%d\036%d\036%d\036",
			&duration, &playRate, &xy.x, &xy.y, &position.x,
			&position.y, &zIndex);
		Animation s(xy, duration, playRate, position, zIndex);
		for(int i = 0; i < (xy.x * xy.y); ++i){
			s[i] = Frame::loadFromFile(xy, ref);
		}
		return s;
	}
			
}
