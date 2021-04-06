#pragma once

#include "noise.hpp"

#include "pom/terrain/function/tag/value.hpp"
#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

template<typename DeclContext> constexpr
float recipe(DeclContext, value, noise, vec2f xy) {
	auto [h] = decl::make<value>(gradient_noise<1>(), xy);
	return h;
}

}
