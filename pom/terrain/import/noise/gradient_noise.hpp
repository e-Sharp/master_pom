#pragma once

#include "pom/terrain/import/vec/vec.hpp"
#include "pom/terrain/tag/value.hpp"

#include <pom/maths/operation/noise/gradient_2.hpp>
#include <pom/maths/operation/noise/gradient_2_value.hpp>
#include <pom/maths/operation/noise/hashes.hpp>

namespace pom::terrain {

template<std::size_t N>
struct gradient_noise {
	static_assert(N > 0);
	static_assert(N <= 2, "Not implemented.");
};

template<typename DeclContext> constexpr
float recipe(DeclContext, value_, gradient_noise<1>, vec2f xy) {
	return value(maths::gradient_noise_2(&maths::hash_1), xy);
}

template<typename DeclContext> constexpr
vec2f recipe(DeclContext, value_, gradient_noise<2>, vec2f xy) {
	return {
		value(maths::gradient_noise_2(&maths::hash_1), xy),
		value(maths::gradient_noise_2(&maths::hash_2), xy)};
}

}
