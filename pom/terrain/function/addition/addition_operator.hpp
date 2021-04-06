#pragma once

#include "pom/terrain/function/concept/function.hpp"
#include "pom/terrain/function/sum/sum.hpp"

namespace pom::terrain {

template<function Lhs, function Rhs> constexpr
auto operator+(Lhs&& l, Rhs&& r) {
	return sum(std::forward<Lhs>(l), std::forward<Rhs>(r));
}

}
