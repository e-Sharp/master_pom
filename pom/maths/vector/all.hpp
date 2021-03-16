#pragma once

#include "ranges.hpp"
#include "map.hpp"
#include "numeric.hpp"
#include "reduce.hpp"

#include "pom/maths/exceptions.hpp"

#include "pom/meta/tag/checked.hpp"
#include "pom/meta/tag/unchecked.hpp"

#include <cmath>
#include <range/v3/view/zip.hpp>
#include <type_traits>

namespace pom {
namespace maths {

////////////////////////////////////////////////////////////////////////////////
// Arithmetic operators.

// Vector, vector.

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

// Vector, component.

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

// Component, vector.

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
auto dot(const LV& lv, const RV& rv, meta::unchecked) {
    auto s = decltype(at(lv, 0))(0);
    for(auto&& [l, v] : ranges::views::zip(lv, rv)) {
        s += l * v;
    }
    return s;
}

template<vector LV, vector RV> constexpr
auto dot(const LV& lv, const RV& rv, meta::checked = {}) {
    throw_if_different_size(lv, rv);
    return dot(lv, rv, meta::unchecked());
}

////////////////////////////////////////////////////////////////////////////////
// Distance.

template<vector V>
auto length(const V& v) {
    return std::sqrt(dot(v, v));
}

template<vector V>
auto normalized(const V& v, meta::unchecked) {
    return v / length(v);
}

template<vector V>
auto normalized(const V& v, meta::checked = {}) {
    auto l = length(v);
    if(l == 0) throw precondition_violation(""); // Use an epsilon ?
    return v / l;
}

}}
