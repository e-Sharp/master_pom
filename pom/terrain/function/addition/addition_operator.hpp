#pragma once

#include "pom/terrain/function/concept/function.hpp"
#include "pom/terrain/function/constant/all.hpp"
#include "pom/terrain/function/sum/sum.hpp"

namespace pom::terrain {

template<function Lhs, function Rhs> constexpr
auto operator+(Lhs&& l, Rhs&& r) {
	return sum(std::forward<Lhs>(l), std::forward<Rhs>(r));
}

template<function Lhs, function Rhs> constexpr
auto operator+(Lhs&& l, float r) {
	return sum(std::forward<Lhs>(l), constant(r));
}

template<function Lhs, function Rhs> constexpr
auto operator+(float l, Rhs&& r) {
	return sum(constant(l), std::forward<Rhs>(r));
}

}
