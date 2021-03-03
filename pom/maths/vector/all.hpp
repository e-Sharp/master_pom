#pragma once

#include "ranges.hpp"
#include "map.hpp"
#include "reduce.hpp"

#include <cmath>
#include <type_traits>

namespace pom {
namespace maths {

////////////////////////////////////////////////////////////////////////////////
// Arithmetic operators.

// Vector / vector.

template<vector LV, vector RV> constexpr
auto operator+(const LV& lv, const RV& rv) {
    throw_if_different_size(lv, rv);
    return mapped(lv, rv, [](auto l, auto r) { return l + r; });
}

template<vector LV, vector RV> constexpr
auto operator-(const LV& lv, const RV& rv) {
    throw_if_different_size(lv, rv);
    return mapped(lv, rv, [](auto l, auto r) { return l - r; });
}

template<vector LV, vector RV> constexpr
auto operator*(const LV& lv, const RV& rv) {
    throw_if_different_size(lv, rv);
    return mapped(lv, rv, [](auto l, auto r) { return l * r; });
}

// Vector / component.

template<vector V, typename Ty> constexpr
auto operator+(const V& v, const Ty& c) noexcept {
    return mapped(v, [&c](auto e) { return e + c; });
}

template<vector V, typename Ty> constexpr
auto operator-(const V& v, const Ty& c) noexcept {
    return mapped(v, [&c](auto e) { return e - c; });
}

template<vector V, typename Ty> constexpr
auto operator*(const V& v, const Ty& c) noexcept {
    return mapped(v, [&c](auto e) { return e * c; });
}

template<vector V, typename Ty> constexpr
auto operator/(const V& v, const Ty& c) noexcept {
    return mapped(v, [&c](auto e) { return e / c; });
}

// Component / vector.

template<typename Ty, vector V> constexpr
auto operator+(const Ty& c, const V& v) noexcept {
    return mapped(v, [&c](auto e) { return c + e; });
}

template<typename Ty, vector V> constexpr
auto operator-(const Ty& c, const V& v) noexcept {
    return mapped(v, [&c](auto e) { return c - e; });
}

template<typename Ty, vector V> constexpr
auto operator*(const Ty& c, const V& v) noexcept {
    return mapped(v, [&c](auto e) { return c * e; });
}

////////////////////////////////////////////////////////////////////////////////
// Vector arithmetic.

template<vector LV, vector RV> constexpr
auto cross(const LV& lv, const RV& rv) {
    throw_if_different_size(lv, rv);
    auto v = same_size(lv);
    for(auto i : indexes(lv)) {
        auto i1 = (i + 1) % size(v);
        auto i2 = (i + 2) % size(v);
        at(v, i) = at(lv, i1) * at(rv, i2) - at(lv, i2) * at(rv, i1);
    }
    return v;
}

template<vector LV, vector RV> constexpr
auto dot(const LV& lv, const RV& rv) {
    throw_if_different_size(lv, rv);
    return reduced(
        lv, rv,
        [](auto& acc, auto l, auto r) { acc += l * r; },
        std::remove_cvref_t<decltype(at(lv, 0))>{});
}

////////////////////////////////////////////////////////////////////////////////
// Distance.

template<vector V>
auto length(const V& v) {
    return std::sqrt(dot(v, v));
}

}}
