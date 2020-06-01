#include <cppanim/mixin.hpp>

namespace cppanim {

	Mixinable::Mixinable(std::initializer_list<Mixin *> m,
			     XY size, XY position, std::size_t zIndex)
		: mixins{m}, buffer(size.x * size.y)
	{
		this->size = size;
		this->position = position;
		this->zIndex = zIndex;
	}

	void Mixinable::update(const Context &c)
	{
		buffer = Frame(size.x * size.y);
		doUpdate(c);
		for(auto m : mixins) {
			m->update(c, this, buffer);
		}
	}

	std::tuple<const Frame&, const XY&> Mixinable::draw(const Context& c)
	{
		for(auto m : mixins) {
			m->draw(c, this, buffer);
		}
		return doDraw(c);
	}

	void Mixinable::resize(XY newsize)
	{
		size = newsize;
		buffer = Frame(size);
	}
}
