#pragma once

#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

struct noise {};

template<typename DeclContext> constexpr
float recipe(DeclContext, height_, noise, vec2f coords) {
	auto [h] = decl::make<value_>(gradient_noise<1>(), coords);
	return h;
}

}
