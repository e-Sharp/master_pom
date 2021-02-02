#pragma once

#include "pom/maths/object/vector.hpp"

#include <cmath>

namespace pom {
namespace maths {

float fract(float x) noexcept {
    return x - std::floor(x);
}

template<typename V>
auto fract(const vector<V>& v) noexcept {
    return mapped(v, [](auto e) { return fract(e); });
}

}}
