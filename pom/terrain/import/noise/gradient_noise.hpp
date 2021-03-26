#pragma once

#include "pom/terrain/import/vec/vec.hpp"
#include "pom/terrain/tag/value.hpp"

#include <pom/maths/operation/noise/gradient_2.hpp>
#include <pom/maths/operation/noise/gradient_2_value.hpp>
#include <pom/maths/operation/noise/hashes.hpp>

namespace pom::terrain {

struct gradient_noise_1 {};

template<typename DeclContext> constexpr
float recipe(DeclContext, value_, gradient_noise_1, vec2f xy) {
	return value(maths::gradient_noise_2(&maths::hash_1), xy);
}

struct gradient_noise_2 {};

template<typename DeclContext> constexpr
float recipe(DeclContext, value_, gradient_noise_2, vec2f xy) {
	return value(maths::gradient_noise_2(&maths::hash_2), xy);
}

}
