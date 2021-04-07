#pragma once

#include "worley.hpp"

#include "pom/terrain/function/tag/value.hpp"
#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

template<typename DeclContext> constexpr
float recipe(DeclContext, value, worley, vec2f xy) {
	using namespace maths;
	auto d = vec2f(1, 1);
    auto i = vec2f(floor(static_cast<const static_vector<float, 2>&>(xy)));
    for(float j = -1.; j <= 1.; j += 1.f)
    for(float k = -1.; k <= 1.; k += 1.f) {
        auto seed = i + vec2f(j, k) + worley::hash(i + vec2f(j, k));
        auto diff = seed - xy;
        if(dot(diff, diff) < dot(d, d)) {
            d = diff;
        }
    }
    return maths::length(d);
}
}
