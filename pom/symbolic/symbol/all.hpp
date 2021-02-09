#pragma once

#include <cstdlib>

namespace pom {
namespace symbolic {

// Type annotation.
template<typename Type>
struct symbol : Type {};

template<typename Type>
symbol(Type) -> symbol<Type>;

template<std::size_t I>
struct variable {};

// Constants.

struct zero {
	template<typename Ty> constexpr
	operator Ty() const noexcept {
		return 0;
	}
};

struct one {
	template<typename Ty> constexpr
	operator Ty() const noexcept {
		return 1;
	}
};

// Arithmetic.

template<typename Lhs, typename Rhs>
struct difference {
	Lhs lhs = {};
	Rhs rhs = {};
};

template<typename Lhs, typename Rhs>
difference(Lhs, Rhs) -> difference<Lhs, Rhs>;

template<typename Lhs, typename Rhs>
struct product {
	Lhs lhs = {};
	Rhs rhs = {};
};

template<typename Lhs, typename Rhs>
product(Lhs, Rhs) -> product<Lhs, Rhs>;

template<typename Lhs, typename Rhs>
struct quotient {
	Lhs lhs = {};
	Rhs rhs = {};
};

template<typename Lhs, typename Rhs>
quotient(Lhs, Rhs) -> quotient<Lhs, Rhs>;

template<typename Lhs, typename Rhs>
struct sum {
	Lhs lhs = {};
	Rhs rhs = {};
};

template<typename Lhs, typename Rhs>
sum(Lhs, Rhs) -> sum<Lhs, Rhs>;

// Calculus.

template<typename DF, typename DX>
struct derivative {
	DF df = {};
	DX dx = {};
};

template<typename DF, typename DX>
derivative(DF, DX) -> derivative<DF, DX>;

}}
