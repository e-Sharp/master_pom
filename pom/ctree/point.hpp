#pragma once

#include <array>
#include <cmath>

using point = std::array<float, 2>;

auto distance(const point& p) noexcept {
    return std::sqrt(p[0] * p[0] + p[1] * p[1]);
}
