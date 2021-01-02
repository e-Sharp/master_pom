#pragma once

#include "pom/maths/function/interpolation.hpp"
#include "pom/maths/function/hash.hpp"
#include "pom/maths/vector/all.hpp"

namespace pom {
namespace noise {

template<typename Traits>
auto perlin(const vector<Traits>& p) {
    auto i = floored(p);
    auto f = p - i;
	
	auto u = smoothstep_1(p);

    constexpr auto v00 = vector<Traits>{0, 0};
    constexpr auto v10 = vector<Traits>{1, 0};
    constexpr auto v01 = vector<Traits>{0, 1};
    constexpr auto v11 = vector<Traits>{1, 1};

    return lerp(
        lerp(dot(hash(i + v00), f - v00), 
            dot(hash(i + v10), f - v10), at(u, 0)),
        lerp(dot(hash(i + v01), f - v01), 
            dot(hash(i + v11), f - v11), at(u, 0)), at(u, 1));
}

} // namespace noise
} // namespace pom
