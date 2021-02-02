#pragma once

#include <cmath>

namespace pom {

template<typename Ty, typename I> constexpr
auto lerp(const Ty& lhs, const Ty& rhs, const I& t) {
    return lhs + t * (rhs - lhs);
}

template<typename Ty> constexpr
auto smoothstep_0(const Ty& x) noexcept {
    return x;
}

// First derivative is null at 0 and 1.
template<typename Ty> constexpr
auto smoothstep_1(const Ty& x) noexcept {
    return x * x * (-2 * x + 3);
}

// First and second derivatives are null at 0 and 1.
template<typename Ty> constexpr
auto smoothstep_2(const Ty& x) noexcept {
    return x * x * x * (x * (6 * x - 15) + 10);
}

} // namespace pom
