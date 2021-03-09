#pragma once

#include "pom/terrain/imports.hpp"

#include <pom/maths/vector/all.hpp>

#include <cmath>

namespace pom {
namespace terrain {

struct sphere {};

float weight(sphere, vec2f pos) {
	return std::sqrt(1 - maths::dot(pos, pos));
}

float height(sphere, vec2f pos) {
	auto dd = maths::dot(pos, pos);
	if(dd < 1) {
		return std::sqrt(1 - dd);
	} else {
		return 0;
	}
}

vec3f normal(sphere, vec2f pos) {
	auto dd = maths::dot(pos, pos);
	if(dd < 1) {
		return vec3f({at(pos, 0), at(pos, 1), std::sqrt(1 - dd)});
	} else {
		return vec3f({0.f, 0.f, 1.f});
	}
}

}}
