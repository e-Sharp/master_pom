#pragma once

#include "pom/maths/vector/all.hpp"

#include <cmath>

namespace pom::maths {

constexpr static_vector<float, 2> hash_1(static_vector<float, 2> x) {
	return vector_of(
		fract(std::sin(dot(x, vector_of(27.609f, 57.583f))) * 43.7585453f),
		fract(std::sin(dot(x, vector_of(33.211f, 53.899f))) * 74.5116299f))
	* 2.f - 1.f;
}

constexpr static_vector<float, 2> hash_2(static_vector<float, 2> x) {
	return vector_of(
		fract(std::sin(dot(x, vector_of(37.699f, 27.953f))) * 23.0889299f),
		fract(std::sin(dot(x, vector_of(63.541f, 13.063f))) * 44.2856371f))
	* 2.f - 1.f;
}

}
