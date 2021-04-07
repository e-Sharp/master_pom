#pragma once

#include "colored/all.hpp"

#include "pom/terrain/coloration/tag/color.hpp"
#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

template<typename DeclContext, typename... C> constexpr
vec3f recipe(DeclContext, target::color, const colored<C...>& c, vec2f) {
	return c.color.value;
}

}
