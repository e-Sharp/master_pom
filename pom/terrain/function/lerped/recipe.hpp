#pragma once

#include "lerped.hpp"

#include "pom/terrain/function/tag/value.hpp"
#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

template<typename DeclContext, typename Target, typename... L> constexpr
auto recipe(DeclContext, Target, const lerped<L...>& l, vec2f xy) {
	return get<0>(decl::make<Target>(
		l.i * l.a + (1.f + -1.f * l.i) * l.b, 
		xy));
}

}
