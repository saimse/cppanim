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
		Animation(XY size, std::size_t duration);
		Animation(XY size, std::size_t duration, float playRate);
		Animation(const std::vector<Frame> &data);
		Animation(const std::vector<Frame> &data, float playRate);
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
