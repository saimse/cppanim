#pragma once

#define _cppanim_getterDecl(t, n)		\
	t& n();					\
	const t& n() const;

#define _cppanim_getterDefin(c, t, f, n)	\
	t& c::n() {return this->f;}		\
	const t& c::n() const {return this->f;}
