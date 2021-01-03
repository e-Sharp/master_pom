#pragma once

#include "pom/maths/vector/vector.hpp"

namespace pom {


// Arithmetic operators.

template<typename Traits> constexpr
auto operator+(const vector<Traits>& lv, const vector<Traits>& rv) noexcept {
    return mapped(lv, rv, [](auto l, auto r, auto i) {
        return at(l, i) + at(r, i);
    });
}

template<typename Traits> constexpr
auto operator+(
    const vector<Traits>& lhs, const typename Traits::element& rhs) noexcept
{
    return mapped(lhs, [&rhs](auto lhs, auto i) {
        return at(lhs, i) + rhs;
    });
}

template<typename Traits> constexpr
auto operator+(
    const typename Traits::element& lhs, const vector<Traits>& rhs) noexcept
{
    return mapped(rhs, [&lhs](auto rhs, auto i) {
        return lhs + at(rhs, i);
    });
}

template<typename Traits> constexpr
auto operator-(const vector<Traits>& lv, const vector<Traits>& rv) noexcept {
    return mapped(lv, rv, [](auto l, auto r, auto i) {
        return at(l, i) - at(r, i);
    });
}

template<typename Traits> constexpr
auto operator-(
    const vector<Traits>& lhs, const typename Traits::element& rhs) noexcept
{
    return mapped(lhs, [&rhs](auto lhs, auto i) {
        return at(lhs, i) - rhs;
    });
}

template<typename Traits> constexpr
auto operator-(
    const typename Traits::element& lhs, const vector<Traits>& rhs) noexcept
{
    return mapped(rhs, [&lhs](auto rhs, auto i) {
        return lhs - at(rhs, i);
    });
}

template<typename Traits> constexpr
auto operator*(const vector<Traits>& lv, const vector<Traits>& rv) noexcept {
    return mapped(lv, rv, [](auto l, auto r, auto i) {
        return at(l, i) * at(r, i);
    });
}

template<typename Traits> constexpr
auto operator*(
    const vector<Traits>& lhs, const typename Traits::element& rhs) noexcept
{
    return mapped(lhs, [&rhs](auto lhs, auto i) {
        return at(lhs, i) * rhs;
    });
}

template<typename Traits> constexpr
auto operator*(
    const typename Traits::element& lhs, const vector<Traits>& rhs) noexcept
{
    return mapped(rhs, [&lhs](auto rhs, auto i) {
        return lhs * at(rhs, i);
    });
}

// Comparison operators.

template<typename Traits> constexpr
auto operator==(const vector<Traits>& lv, const vector<Traits>& rv) noexcept {
    for(std::size_t i = 0; i < Traits::size; ++i) {
        if(at(lv, i) != at(rv, i)) return false;
    }
    return true;
}

} // namespace pom
