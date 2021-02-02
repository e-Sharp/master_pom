#pragma once

#include "pom/maths/function/collection/reduce/vector.hpp"

#include <type_traits>

namespace pom {
namespace maths {

////////////////////////////////////////////////////////////////////////////////
// Arithmetic operators.

// Vector - vector.

template<typename LV, typename RV> constexpr
auto operator+(const vector<LV>& lv, const vector<RV>& rv) {
    throw_if_different_size(lv, rv);
    return mapped(lv, rv, [](auto l, auto r) { return l + r; });
}

template<typename LV, typename RV> constexpr
auto operator-(const vector<LV>& lv, const vector<RV>& rv) {
    throw_if_different_size(lv, rv);
    return mapped(lv, rv, [](auto l, auto r) { return l - r; });
}

template<typename LV, typename RV> constexpr
auto operator*(const vector<LV>& lv, const vector<RV>& rv) {
    throw_if_different_size(lv, rv);
    return mapped(lv, rv, [](auto l, auto r) { return l * r; });
}

// Vector - component.

template<typename B, typename Ty> constexpr
auto operator+(const vector<B>& v, const Ty& c) noexcept {
    return mapped(v, [&c](auto e) { return e + c; });
}

template<typename B, typename Ty> constexpr
auto operator-(const vector<B>& v, const Ty& c) noexcept {
    return mapped(v, [&c](auto e) { return e - c; });
}

template<typename B, typename Ty> constexpr
auto operator*(const vector<B>& v, const Ty& c) noexcept {
    return mapped(v, [&c](auto e) { return e * c; });
}

// Component - vector.

template<typename Ty, typename B> constexpr
auto operator+(const Ty& c, const vector<B>& v) noexcept {
    return mapped(v, [&c](auto e) { return c + e; });
}

template<typename Ty, typename B> constexpr
auto operator-(const Ty& c, const vector<B>& v) noexcept {
    return mapped(v, [&c](auto e) { return c - e; });
}

template<typename Ty, typename B> constexpr
auto operator*(const Ty& c, const vector<B>& v) noexcept {
    return mapped(v, [&c](auto e) { return c * e; });
}

////////////////////////////////////////////////////////////////////////////////
// Vector specific arithmetic.

template<typename LV, typename RV> constexpr
auto dot(const vector<LV>& lv, const vector<RV>& rv) {
    throw_if_different_size(lv, rv);
    return reduced(
        lv, rv,
        [](auto& acc, auto l, auto r) { acc += l * r; },
        std::remove_cvref_t<decltype(at(lv, 0))>{});
}

////////////////////////////////////////////////////////////////////////////////
// Distance.



}}
