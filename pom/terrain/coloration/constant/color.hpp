#pragma once

#include "pom/terrain/coloration/tag/color.hpp"
#include "pom/terrain/function/constant/all.hpp"
#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

template<typename DeclContext> constexpr
vec3f recipe(DeclContext, target::color, constant, vec2f) {
	return vec3f(1.f, 1.f, 1.f);
}

}
