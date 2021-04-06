#pragma once

#include "constant.hpp"

#include "pom/terrain/function/tag/gradient.hpp"
#include "pom/terrain/import/all.hpp"

#include <decl.hpp>

namespace pom::terrain {

template<typename DeclContext> constexpr
vec2f recipe(DeclContext, gradient, const constant& c, vec2f xy) {
	return vec2f(0);
}

}
