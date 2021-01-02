#pragma once

#include "pom/maths/vector/"

#include <cmath>

namespace pom {

float fract(float x) noexcept {
    return std::abs(std::modf(x, nullptr));
}

} // namespace pom
