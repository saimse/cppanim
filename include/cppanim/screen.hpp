#pragma once

#include <cppanim/fundamentals.hpp>
#include <cppanim/drawable.hpp>
#include <cppanim/broadcaster.hpp>

#include <memory>
#include <experimental/propagate_const>
#include <vector>

namespace cppanim::gfx {

	using namespace cppanim::fundamentals;
	using namespace cppanim::util;

	class Screen : public KeyboardBroadcaster {

		struct impl;
		std::experimental::propagate_const<
			std::unique_ptr<
				impl>> pImpl;

		void handleInput();
		Screen();
	public:
		static Screen& getInstance()
		{
			static Screen instance;
			return instance;
		}
		void operator=(const Screen&) = delete;
		Screen(const Screen&) = delete;

		void addDrawable(const Drawable &d);

		~Screen();
	};

}
