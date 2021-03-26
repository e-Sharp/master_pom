#pragma once

#include "gradient_2.hpp"

#include "pom/maths/operation/cubic_step.hpp"
#include "pom/maths/operation/floor.hpp"
#include "pom/maths/operation/fract.hpp"
#include "pom/maths/operation/lerp.hpp"
#include "pom/maths/vector/all.hpp"

namespace pom::maths {

template<typename N> constexpr
auto value(const gradient_noise_2<N>& n, static_vector<float, 2> v) {
	auto i = floor(v);
    auto f = fract(v);
	
	auto x = cubic_step(0.f, 1.f, at(f, 0));
    auto y = cubic_step(0.f, 1.f, at(f, 1));

    constexpr auto v00 = vector_of(0.f, 0.f);
    constexpr auto v10 = vector_of(1.f, 0.f);
    constexpr auto v01 = vector_of(0.f, 1.f);
    constexpr auto v11 = vector_of(1.f, 1.f);

    return lerp(
        lerp(dot(n.hash(i + v00), f - v00), 
            dot(n.hash(i + v10), f - v10), x),
        lerp(dot(n.hash(i + v01), f - v01),
            dot(n.hash(i + v11), f - v11), x), y);
}

}
