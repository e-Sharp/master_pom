#pragma once

#include "constant.hpp"

#include "pom/terrain/function/tag/value.hpp"
#include "pom/terrain/import/all.hpp"

#include <decl.hpp>

namespace pom::terrain {

template<typename DeclContext> constexpr
float recipe(DeclContext, value, const constant& c, vec2f) {
	return c.value;
}

}
