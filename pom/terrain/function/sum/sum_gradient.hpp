#pragma once

#include "sum.hpp"

#include "pom/terrain/function/tag/gradient.hpp"
#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

template<typename DeclContext, typename... S> constexpr
vec2f recipe(DeclContext, gradient, const sum<S...>& s, vec2f xy) {
	auto [l] = decl::make<gradient>(s.lhs, xy);
	auto [r] = decl::make<gradient>(s.rhs, xy);
	return l + r;
}

}
