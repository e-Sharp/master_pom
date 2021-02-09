#pragma once

#include "pom/maths/vector/concepts.hpp"

#include <cmath>

namespace pom {
namespace maths {

float fract(float x) noexcept {
    return x - std::floor(x);
}

template<vector V>
auto fract(const V& v) noexcept {
    return mapped(v, [](auto e) { return fract(e); });
}

}}
