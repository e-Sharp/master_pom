#pragma once

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

// F: (v, i) -> e.
template<typename Traits, typename F> constexpr
auto mapped(const vector<Traits>& v, F f) {
    auto m = vector<Traits>{};
    for(std::size_t i = 0; i < Traits::size; ++i) {
        at(m, i) = f(v, i);
    }
    return m;
}

// Maps two vectors into a single one.
// F: (lv, rv, i) -> e.
template<typename Traits, typename F> constexpr 
auto mapped(const vector<Traits>& lv, const vector<Traits>& rv, F f) {
    auto c = vector<Traits>{};
    for(std::size_t i = 0; i < Traits::size; ++i) {
        at(c, i) = f(lv, rv, i);
    }
    return c;
}

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

template<typename Traits> constexpr
auto floored(const vector<Traits>& v) {
    return mapped(v, [](const auto& v, auto i) {
        return std::floor(at(v, i));
    });
}

} // namespace pom
