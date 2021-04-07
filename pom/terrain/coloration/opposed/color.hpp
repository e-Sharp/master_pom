#pragma once

#include "pom/terrain/coloration/tag/color.hpp"
#include "pom/terrain/function/opposed/opposed.hpp"
#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

template<typename DeclContext, typename... L> constexpr
vec3f recipe(DeclContext, target::color, const lerped<L...>& l, vec2f xy) {
	auto [a] = decl::make<target::color>(l.a, xy);
	auto [b] = decl::make<target::color>(l.b, xy);
	auto [i] = decl::make<value>(l.i, xy);
	return maths::lerp(a, b, i);
}

}
