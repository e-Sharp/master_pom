#pragma once

#include "pom/maths/arity.hpp"

#include <array>
#include <cmath>

namespace pom {

namespace traits {

template<typename Ty, std::size_t Size>
struct vector {
    using element = Ty;

    static constexpr auto size = Size;
};

} // namespace traits

template<typename Traits>
struct vector {
    using traits = Traits;

    std::array<typename traits::element, traits::size> elements = {};
};

template<typename Ty, std::size_t S>
using static_vector = vector<traits::vector<Ty, S>>;

// Element access.

template<typename Traits> constexpr
auto& at(vector<Traits>& v, std::size_t i) {
    return v.elements[i];
}

template<typename Traits> constexpr
const auto& at(const vector<Traits>& v, std::size_t i) {
    return v.elements[i];
}

// Generic functions.

// Reduces a vector.
// Reducer: (&acc, vec, i) -> acc'.
template<typename Traits, typename Reducer, typename Ty> constexpr
auto reduced(const vector<Traits>& v, Reducer r, Ty acc = {}) {
    for(std::size_t i = 0; i < Traits::size; ++i) {
        r(acc, v, i);
    }
    return acc;
}

// Reduces two vectors at once.
// Reducer: (&acc, lv, rv, i) -> acc'.
template<typename Traits, typename Reducer, typename Ty> constexpr
auto reduced(
    const vector<Traits>& lv,
    const vector<Traits>& rv,
    Reducer r,
    Ty acc)
{
    for(std::size_t i = 0; i < Traits::size; ++i) {
        r(acc, lv, rv, i);
    }
    return acc;
}

// Functions.

template<typename Traits> constexpr
auto dot(const vector<Traits>& lhs, const vector<Traits>& rhs) {
    auto r = [](auto& acc, const vector<Traits>& lv, const vector<Traits>& rv, auto i) {
        acc += at(lv, i) * at(rv, i);
    };
    return reduced(lhs, rhs, r, 0.f);
}

} // namespace pom
