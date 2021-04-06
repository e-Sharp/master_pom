#pragma once

#include "pom/terrain/function/concept/function.hpp"
#include "pom/terrain/function/product/product.hpp"

namespace pom::terrain {

template<function Lhs, function Rhs> constexpr
auto operator*(Lhs&& l, Rhs&& r) {
	return product(std::forward<Lhs>(l), std::forward<Rhs>(r));
}

}
