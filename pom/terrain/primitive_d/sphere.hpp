#pragma once

#include "pom/terrain/import/all.hpp"

#include <decl.hpp>
#include <pom/maths/vector/all.hpp>

#include <cmath>

namespace pom {
namespace terrain {

struct sphere {};

template<typename C>
float recipe(C, height_, sphere, vec2f pos) {
	begin(pos);
	auto dd = maths::dot(pos, pos);
	if(dd < 1) {
		return std::sqrt(1.f - dd);
	} else {
		return 0.f;
	}
}

auto prerequisites(normal_, sphere, vec2f) -> decl::targets<height_>;

template<typename C>
vec3f recipe(C c, normal_, sphere, vec2f pos) {
	auto h = c.ref<height_>();
	if(h == 0.f) {
		return vec3f({0.f, 0.f, 1.f});
	} else {
		return vec3f({at(pos, 0), at(pos, 1), h});
	}
}

}}
