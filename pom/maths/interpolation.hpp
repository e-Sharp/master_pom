#pragma once

#include <cmath>

namespace pom {
namespace maths {

template<typename Ty, typename I> constexpr
auto lerp(const Ty& lhs, const Ty& rhs, const I& t) {
    return (1 - t) * lhs + t * rhs;
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

template<typename Ty> constexpr
auto smoothstep_1_(const Ty& x) noexcept {
    if(x <= Ty(0))      return Ty(0);
    else if(x >= Ty(1)) return Ty(1);
    else                return x * x * (-2 * x + 3);
}

// First and second derivatives are null at 0 and 1.
template<typename Ty> constexpr
auto smoothstep_2(const Ty& x) noexcept {
    return x * x * x * (x * (6 * x - 15) + 10);
}

}}
