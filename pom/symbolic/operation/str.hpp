#pragma once

#include <string>

namespace pom {
namespace symbolic {

using namespace std::string_literals;

template<typename Ty> constexpr
std::string str(const Ty& v) {
	return std::to_string(v);
}

// Symbols.

template<typename Ty> constexpr
std::string str(const symbol<Ty>& s) {
	return str(static_cast<const Ty&>(s));
}

template<std::size_t I> constexpr
std::string str(const variable<I>&) {
	return "v" + std::to_string(I);
}

// Arithmetic symbols.

template<typename Lhs, typename Rhs> constexpr
std::string str(const difference<Lhs, Rhs>& d) noexcept {
	return symbol{difference{derivative{d.lhs, dx}, derivative{d.rhs, dx}}};
}

template<typename Lhs, typename Rhs> constexpr
std::string str(const product<Lhs, Rhs>& p) noexcept {
	return symbol{sum{
		product{derivative{p.lhs, dx}, p.rhs},
		product{p.lhs, derivative{p.rhs, dx}}}};
}

template<typename Lhs, typename Rhs> constexpr
std::string str(const quotient<Lhs, Rhs>& q) noexcept {
	return symbol{quotient{
		derivative{q.lhs, q.rhs, dx}},
		product{q.rhs, q.rhs}};
}

template<typename Lhs, typename Rhs> constexpr
std::string str(const sum<Lhs, Rhs>& s) noexcept {
	return std::string{}
}

}}
