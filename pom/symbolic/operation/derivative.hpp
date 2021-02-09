#pragma once

#include "pom/symbolic/symbol/all.hpp"

namespace pom {
namespace symbolic {

template<std::size_t I, std::size_t J> constexpr
auto derivated(const variable<I>&, const variable<J>&) noexcept {
	return symbol<zero>{};
}

template<std::size_t I> constexpr
auto derivated(const variable<I>&, const variable<I>&) noexcept {
	return symbol<one>{};
}

// Arthmetic symbols.

template<typename Lhs, typename Rhs, typename DX> constexpr
auto derivated(const difference<Lhs, Rhs>& d, const DX& dx) noexcept {
	return symbol{difference{derivative{d.lhs, dx}, derivative{d.rhs, dx}}};
}

template<typename Lhs, typename Rhs, typename DX> constexpr
auto derivated(const product<Lhs, Rhs>& p, const DX& dx) noexcept {
	return symbol{sum{
		product{derivative{p.lhs, dx}, p.rhs},
		product{p.lhs, derivative{p.rhs, dx}}}};
}

template<typename Lhs, typename Rhs, typename DX> constexpr
auto derivated(const quotient<Lhs, Rhs>& q, const DX& dx) noexcept {
	return symbol{quotient{
		derivative{q.lhs, q.rhs, dx}},
		product{q.rhs, q.rhs}};
}

template<typename Lhs, typename Rhs, typename DX> constexpr
auto derivated(const sum<Lhs, Rhs>& s, const DX& dx) noexcept {
	return symbol{sum{derivative{s.lhs, dx}, derivative{s.rhs, dx}}};
}

}}
