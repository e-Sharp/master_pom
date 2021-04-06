#pragma once

#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

struct worley {
	static vec2f hash(maths::static_vector<float, 2> v) {
        using namespace maths;
	    auto k = vector_of(0.3483099f, 0.4688794f);
        v = v * k + flipped(v);
        return fract(16.f * k * fract(at(v, 0) * at(v, 1) * (at(v, 0) + at(v, 1))));
    }
};

auto prerequisites(height_, worley, vec2f coords) -> decl::targets<value_>;

template<typename DeclContext> constexpr
float recipe(DeclContext c, height_, worley, vec2f) {
	auto v = c.ref<value_>();
    return maths::length(v);
}

template<typename DeclContext> constexpr
vec2f recipe(DeclContext, value_, worley, vec2f coords) {
	using namespace maths;
	auto d = vec2f(1, 1);
    auto i = vec2f(floor(static_cast<const static_vector<float, 2>&>(coords)));
    for(float j = -1.; j <= 1.; j += 1.f)
    for(float k = -1.; k <= 1.; k += 1.f) {
        auto seed = i + vec2f(j, k) + worley::hash(i + vec2f(j, k));
        auto diff = seed - coords;
        if(dot(diff, diff) < dot(d, d)) {
            d = diff;
        }
    }
    return d;
}

}