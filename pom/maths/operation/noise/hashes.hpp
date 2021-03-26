#pragma once

#include "pom/maths/vector/all.hpp"

namespace pom::maths {

constexpr static_vector<float, 2> hash_1(static_vector<float, 2> x) {
	auto k = vector_of(0.3183099f, 0.3678794f);
    x = x * k + flipped(x);
    return -1.f + 2.f * fract(16.f * k * fract(at(x, 0) * at(x, 1) * (at(x, 0) + at(x, 1))));
}

constexpr static_vector<float, 2> hash_2(static_vector<float, 2> x) {
	auto k = vector_of(0.7283409f, 0.1720874f);
    x = x * k + flipped(x);
    return -1.f + 2.f * fract(16.f * k * fract(at(x, 0) * at(x, 1) * (at(x, 0) + at(x, 1))));
}

}
