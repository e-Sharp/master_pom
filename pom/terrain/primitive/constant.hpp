#pragma once

#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

struct constant {
	float height = 0.f;
};

template<typename DeclContext> constexpr
float recipe(DeclContext, height_, constant c, vec2f) {
	return c.height;
}

template<typename DeclContext> constexpr
vec3f recipe(DeclContext, normal_, constant, vec2f) {
	return vec3f(0, 0, 1);
}

}
