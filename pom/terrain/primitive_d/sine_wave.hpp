#pragma once

#include "pom/terrain/import/all.hpp"

#include <pom/maths/vector/all.hpp>
#include <pom/maths/constants.hpp>

namespace pom::terrain {

struct sine_wave {
	float ordinary_frequency = 0.5f;
};

template<typename DeclContext>
float recipe(DeclContext, height_, const sine_wave& w, vec2f pos) {
	auto angular_frequency = maths::tau<float> * w.ordinary_frequency;
	return std::sin(angular_frequency * x(pos));
}

template<typename DeclContext>
vec3f recipe(DeclContext, normal_, const sine_wave& w, vec2f pos) {
	auto angular_frequency = maths::tau<float> * w.ordinary_frequency;
	auto d = std::cos(angular_frequency * x(pos));
	return maths::normalized(vec3f({-d, 0.f, 1.f}));
}

}
