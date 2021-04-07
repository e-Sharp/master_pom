#pragma once

#include "pom/terrain/function/concept/first_order_function.hpp"

namespace pom::terrain {

struct worley {
	static vec2f hash(maths::static_vector<float, 2> v) {
        using namespace maths;
	    auto k = vector_of(0.3483099f, 0.4688794f);
        v = v * k + flipped(v);
        return fract(16.f * k * fract(at(v, 0) * at(v, 1) * (at(v, 0) + at(v, 1))));
    }
};

template<>
struct is_first_order_function<worley>
: std::true_type {};

}
