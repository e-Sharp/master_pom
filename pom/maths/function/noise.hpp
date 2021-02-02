#pragma once

#include "pom/maths/function/collection/map/vector.hpp"
#include "pom/maths/function/interpolation.hpp"
#include "pom/maths/function/hash.hpp"
#include "pom/maths/object/vector.hpp"

namespace pom {
namespace maths {

template<typename B>
auto perlin(const vector<B>& p) {
    auto i = mapped(p, [](float f) { return std::floor(f); });
    auto f = p - i;
	
	auto u = smoothstep_2(f);

    constexpr auto v00 = vector<B>{{0, 0}};
    constexpr auto v10 = vector<B>{{1, 0}};
    constexpr auto v01 = vector<B>{{0, 1}};
    constexpr auto v11 = vector<B>{{1, 1}};

    return lerp(
        lerp(dot(hash(i + v00), f - v00), 
            dot(hash(i + v10), f - v10), at(u, 0)),
        lerp(dot(hash(i + v01), f - v01), 
            dot(hash(i + v11), f - v11), at(u, 0)), at(u, 1));
}

template<typename F, typename B>
auto fbm(F noise, std::size_t octave, vector<B> p) {
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
