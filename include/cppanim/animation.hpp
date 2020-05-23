#pragma once

#include <cppanim/symbol.hpp>

// std::size_t
#include <cstddef>
#include <vector>

#include <cppanim/drawable.hpp>
#include <cppanim/frame.hpp>
#include "getterMacro.hpp"

namespace cppanim::gfx {

	using namespace cppanim::fundamentals;

	class Animation : public Drawable {

		std::vector<Frame> data;
		std::size_t duration;
		float playRate;

	public:
		Animation(XY size, std::size_t duration, float playRate = 1,
			  XY position = {0, 0}, int zIndex = 0);
	        explicit Animation(XY size, const std::vector<Frame>& data,
				   float playRate = 1, XY position = {0, 0},
				   int zIndex = 0);
		Animation(XY size, std::initializer_list<Frame> l,
			  float playRate = 1, XY position = {0, 0},
			  int zIndex = 0);
		Animation(const Animation& copy);

		const std::size_t& getDuration() const;

		// Gets Frame at @p t.
		const Frame& operator[](std::size_t t) const;
		Frame& operator[](std::size_t t);
		// Gets Frame at @p t with temporal transformation
		const Frame& operator()(std::size_t t) const;

		_cppanim_getterDecl(float, getPlayRate);
		void setPlayRate(float p);

		void update(const Context&) override {}
		std::tuple<const Frame&, const XY&>
		draw(const Context&) override;
	};

}
