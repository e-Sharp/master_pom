#pragma once

#include "pom/maths/collection/reduce/vector.hpp"
#include "pom/maths/vector/concepts.hpp"

#include <type_traits>

namespace pom {
namespace maths {

////////////////////////////////////////////////////////////////////////////////
// Arithmetic operators.

// Vector - vector.

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

// Vector - component.

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

// Component - vector.

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
// Vector specific arithmetic.

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



}}
