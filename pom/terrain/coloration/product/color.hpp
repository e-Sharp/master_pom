#pragma once

#include "pom/terrain/coloration/tag/color.hpp"
#include "pom/terrain/function/product/all.hpp"
#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

template<typename DeclContext, typename... P> constexpr
vec3f recipe(DeclContext, target::color, const product<P...>& p, vec2f xy) {
	auto [l] = decl::make<target::color>(p.lhs, xy);
	auto [r] = decl::make<target::color>(p.rhs, xy);
	return l * r;
}

}

