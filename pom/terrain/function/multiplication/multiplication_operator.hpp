#pragma once

#include "pom/terrain/function/concept/function.hpp"
#include "pom/terrain/function/constant/all.hpp"
#include "pom/terrain/function/product/product.hpp"

namespace pom::terrain {

template<function Lhs, function Rhs> constexpr
auto operator*(Lhs&& l, Rhs&& r) {
	return product(std::forward<Lhs>(l), std::forward<Rhs>(r));
}

template<function Lhs> constexpr
auto operator*(Lhs&& l, float r) {
	return product(std::forward<Lhs>(l), constant(r));
}

template<function Rhs> constexpr
auto operator*(float l, Rhs&& r) {
	return product(constant(l), std::forward<Rhs>(r));
}


}
