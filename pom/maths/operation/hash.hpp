#pragma once

#include "pom/maths/fract.hpp"
#include "pom/maths/vector/concepts.hpp"
#include "pom/maths/exceptions.hpp"

#include <iostream>

namespace pom {
namespace maths {

template<vector V> constexpr
V hash(V v) {
    if(size(v) != 2) throw precondition_violation{
        "Vector size was expected to be 2."};
    auto k = V{{0.3183099f, 0.3678794f}};
    v = v * k + V{{at(k, 1), at(k, 0)}};
    auto h = -1.f + 2.f * fract(16.f * k * fract(at(v, 0) * at(v, 1) * (at(v, 0) + at(v, 1))));
    return h;
}

}}
