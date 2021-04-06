#pragma once

#include "pom/terrain/imports.hpp"

#include <pom/maths/vector/all.hpp>

#include <cmath>

namespace pom {
namespace terrain {

struct torus {};

float height(const torus&, vec2f pos) {
	using namespace maths;
	auto l = std::abs(length(pos) - 1.);
	if(l < 0.5f) {
		return std::sqrt(0.25f - l * l);
	} else {
		return 0.f;
	}
}

vec3f normal(const torus&, vec2f pos) {
	using namespace maths;
	auto l = std::abs(length(pos) - 1.f);
	if(l < 0.5f) {
		auto xy = pos - normalized(pos);
		auto z = std::sqrt(0.25f - l * l);
		return normalized(vec3f({at(xy, 0), at(xy, 1), z}));
	} else {
		return vec3f({0.f, 0.f, 1.f});
	}
}

}}
