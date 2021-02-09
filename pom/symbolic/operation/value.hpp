#pragma once

#include "pom/symbolic/symbol/all.hpp"

#include <tuple>

namespace pom {
namespace symbolic {

template<typename Ty, typename... Args> constexpr
auto value(const Ty& v, Args&&...) noexcept {
	return v;
}

// Symbols.

template<typename S, typename... Args> constexpr
auto value(const symbol<S>& s, Args&&... as) noexcept {
	return value(static_cast<const S&>(s), std::forward<Args>(as)...);
}

template<std::size_t I, typename... Args> constexpr
auto value(const variable<I>&, Args&&... as) noexcept {
	return std::get<I>(std::forward_as_tuple(std::forward<Args>(as)...));
}

// Arithmetic symbols.

template<typename Lhs, typename Rhs, typename... Args> constexpr
auto value(const difference<Lhs, Rhs>& s, Args&&... as) noexcept {
	auto l = value(s.lhs, std::forward<Args>(as)...);
	auto r = value(s.rhs, std::forward<Args>(as)...);
	return l - r;
}

template<typename Lhs, typename Rhs, typename... Args> constexpr
auto value(const product<Lhs, Rhs>& s, Args&&... as) noexcept {
	auto l = value(s.lhs, std::forward<Args>(as)...);
	auto r = value(s.rhs, std::forward<Args>(as)...);
	return l * r;
}

template<typename Lhs, typename Rhs, typename... Args> constexpr
auto value(const quotient<Lhs, Rhs>& s, Args&&... as) noexcept {
	auto l = value(s.lhs, std::forward<Args>(as)...);
	auto r = value(s.rhs, std::forward<Args>(as)...);
	return l / r;
}

template<typename Lhs, typename Rhs, typename... Args> constexpr
auto value(const sum<Lhs, Rhs>& s, Args&&... as) noexcept {
	auto l = value(s.lhs, std::forward<Args>(as)...);
	auto r = value(s.rhs, std::forward<Args>(as)...);
	return l + r;
}

// Calculus symbols.

template<typename DF, typename DX, typename... Args> constexpr
auto value(const derivative<DF, DX>& d, Args&&... as) noexcept {
	return value(derivated(d.df, d.dx), std::forward<Args>(as)...);
}

}}
