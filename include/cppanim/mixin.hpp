#pragma once

#include <cppanim/drawable.hpp>

#include <vector>
#include <memory>

namespace cppanim::gfx {

	class Mixinable;
	class Mixin {
	public:
		//TODO: ensure proper type safety
		virtual void update(const Context& c, Mixinable *m,
				    Frame& f)=0;
		virtual void draw(const Context& c, Mixinable *m,
				  Frame& f)=0;
	};

	class Mixinable : public Drawable {

		friend Mixin;

	protected:
		std::vector<Mixin *> mixins;
		Frame buffer;

		void resize(XY newsize);

	public:
		explicit Mixinable(std::initializer_list<Mixin *> m,
				   XY size = {0,0}, XY position = {0,0},
				   std::size_t zIndex = 10);

		virtual void doUpdate(const Context& c) {}

		virtual std::tuple<const Frame&, const XY&>
		doDraw(const Context& c) { return {buffer, size}; }

		virtual void update(const Context& c) override final;	

		virtual std::tuple<const Frame&, const XY&>
		draw(const Context& c) override final;
			
	};

}
