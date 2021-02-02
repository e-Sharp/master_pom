#pragma once

#include "pom/maths/function/fract.hpp"
#include "pom/maths/object/vector.hpp"
#include "pom/maths/exceptions.hpp"

#include <iostream>

namespace pom {
namespace maths {

template<typename B> constexpr
vector<B> hash(vector<B> v) {
    if(size(v) != 2) throw precondition_violation{
        "Vector size was expected to be 2."};
    auto k = vector<B>{{0.3183099f, 0.3678794f}};
    v = v * k + vector<B>{{at(k, 1), at(k, 0)}};
    auto h = -1.f + 2.f * fract(16.f * k * fract(at(v, 0) * at(v, 1) * (at(v, 0) + at(v, 1))));
    return h;
}

}}
