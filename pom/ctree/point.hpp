#pragma once

#include "pom/maths/vector/all.hpp"

#include <array>
#include <cmath>

using namespace pom;

using point = vector<traits::vector<float, 2>>;

auto distance(const point& p) noexcept {
    return std::sqrt(dot(p, p));
}
