#pragma once

#include "pom/symbolic/symbol/all.hpp"

namespace pom {
namespace symbolic {

////////////////////////////////////////////////////////////////////////////////
// Arithmetic.

// (symbol, symbol)

template<typename Lhs, typename Rhs> constexpr
auto operator*(const symbol<Lhs>& lhs, const symbol<Rhs>& rhs) noexcept {
	return symbol{product{lhs, rhs}};
}

template<typename Lhs, typename Rhs> constexpr
auto operator/(const symbol<Lhs>& lhs, const symbol<Rhs>& rhs) noexcept {
	return symbol{quotient{lhs, rhs}};
}

template<typename Lhs, typename Rhs> constexpr
auto operator+(const symbol<Lhs>& lhs, const symbol<Rhs>& rhs) noexcept {
	return symbol{sum{lhs, rhs}};
}

template<typename Lhs, typename Rhs> constexpr
auto operator-(const symbol<Lhs>& lhs, const symbol<Rhs>& rhs) noexcept {
	return symbol{difference{lhs, rhs}};
}

// (symbol, Ty)

template<typename Lhs, typename Rhs> constexpr
auto operator*(const symbol<Lhs>& lhs, const Rhs& rhs) noexcept {
	return symbol{product{lhs, rhs}};
}

template<typename Lhs, typename Rhs> constexpr
auto operator/(const symbol<Lhs>& lhs, const Rhs& rhs) noexcept {
	return symbol{quotient{lhs, rhs}};
}

template<typename Lhs, typename Rhs> constexpr
auto operator+(const symbol<Lhs>& lhs, const Rhs& rhs) noexcept {
	return symbol{sum{lhs, rhs}};
}

template<typename Lhs, typename Rhs> constexpr
auto operator-(const symbol<Lhs>& lhs, const Rhs& rhs) noexcept {
	return symbol{difference{lhs, rhs}};
}

// (Ty, symbol)

template<typename Lhs, typename Rhs> constexpr
auto operator*(const Lhs& lhs, const symbol<Rhs>& rhs) noexcept {
	return symbol{product{lhs, rhs}};
}

template<typename Lhs, typename Rhs> constexpr
auto operator/(const Lhs& lhs, const symbol<Rhs>& rhs) noexcept {
	return symbol{quotient{lhs, rhs}};
}

template<typename Lhs, typename Rhs> constexpr
auto operator+(const Lhs& lhs, const symbol<Rhs>& rhs) noexcept {
	return symbol{sum{lhs, rhs}};
}

template<typename Lhs, typename Rhs> constexpr
auto operator-(const Lhs& lhs, const symbol<Rhs>& rhs) noexcept {
	return symbol{difference{lhs, rhs}};
}

}}
