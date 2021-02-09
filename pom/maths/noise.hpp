#pragma once

#include "pom/maths/collection/map/vector.hpp"
#include "pom/maths/interpolation.hpp"
#include "pom/maths/hash.hpp"
#include "pom/maths/vector/all.hpp"

namespace pom {
namespace maths {

template<vector V>
auto perlin(const V& p) {
    using namespace maths;

    auto i = mapped(p, [](float f) { return std::floor(f); });
    auto f = p - i;
	
	auto u = smoothstep_2(f);

    constexpr auto v00 = V{{0, 0}};
    constexpr auto v10 = V{{1, 0}};
    constexpr auto v01 = V{{0, 1}};
    constexpr auto v11 = V{{1, 1}};

    return lerp(
        lerp(dot(hash(i + v00), f - v00), 
            dot(hash(i + v10), f - v10), at(u, 0)),
        lerp(dot(hash(i + v01), f - v01), 
            dot(hash(i + v11), f - v11), at(u, 0)), at(u, 1));
}

template<typename F, vector V>
auto fbm(F noise, std::size_t octave, V p) {
    auto v = noise(p) / 2.f;
    auto e = 2.f;
    for(std::size_t i = 1; i < octave; ++i) {
        p = 2.f * p;
        v = v + noise(p) * (1 / e);
        e *= 2.f;
    }
    return v;
}

}}
