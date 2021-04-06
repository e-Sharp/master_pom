#pragma once

#include "product.hpp"

#include "pom/terrain/function/tag/value.hpp"
#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

template<typename DeclContext, typename... S> constexpr
float recipe(DeclContext, value, const product<S...>& s, vec2f xy) {
	auto [l] = decl::make<value>(s.lhs, xy);
	auto [r] = decl::make<value>(s.rhs, xy);
	return l * r;
}

}
