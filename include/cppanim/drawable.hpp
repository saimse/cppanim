#pragma once

#include <cppanim/fundamentals.hpp>
#include <cppanim/context.hpp>
#include <cppanim/frame.hpp>

#include <tuple>

namespace cppanim {
	class Drawable {
	protected:
		XY size, position;
		std::size_t zIndex;
	public:
		virtual void update(const Context& c) = 0;

		virtual std::tuple<const Frame&, const XY&>
		draw(const Context& c)=0;

		const XY& getSize() const { return size; }

		const XY& getPosition() const
			{ return position; }
		const std::size_t& getZIndex() const { return zIndex; }

		virtual bool operator<(const Drawable &rhs) const final
			{ return zIndex < rhs.zIndex; }
	};
}
