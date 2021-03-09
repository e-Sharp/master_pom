#pragma once

#include "pom/maths_impl/vector.hpp"

#include <pom/maths/vector/all.hpp>

namespace pom {
namespace maths_impl {

auto hash2(static_vector<float, 2> x) {
	using namespace maths;
	auto k = vector<2>({0.3183099, 0.3678794});
    x = x * k + vector<2>({at(x, 1), at(x, 0)});
    return -1.0 + 2.0 * fract(16.0 * k * fract(at(x, 0) * at(x, 1) * (at(x, 0) + at(x, 1))));
}	

struct perlin2_generator {
	
};

auto perlin2() {
	
}

float compute(perlin2_generator, static_vector<float, 2> p) {
	using namespace maths;

    auto i = mapped(p, [](float f) { return std::floor(f); });
    auto f = p - i;
	
	auto u = smoothstep_2(f);

    constexpr auto v00 = vector<2>({0.f, 0.f});
    constexpr auto v10 = vector<2>({1.f, 0.f});
    constexpr auto v01 = vector<2>({0.f, 1.f});
    constexpr auto v11 = vector<2>({1.f, 1.f});

    return lerp(
        lerp(dot(hash2(i + v00), f - v00), 
            dot(hash2(i + v10), f - v10), at(u, 0)),
        lerp(dot(hash2(i + v01), f - v01), 
            dot(hash2(i + v11), f - v11), at(u, 0)), at(u, 1));
}

auto easy_perlin2(static_vector<float, 2> p) {
    return compute(perlin2_generator(), p);
}

}}
