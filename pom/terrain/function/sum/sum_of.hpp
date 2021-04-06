#pragma once

#include "sum.hpp"

#include <tuple>

namespace pom::terrain {

template<typename Lhs, typename... Rhss> constexpr
auto sum_of(Lhs&& l, Rhss&&... rs) {
	return sum(
		std::forward<Lhs>(l),
		sum_of(std::forward<Rhss>(rs)...));
}

template<typename Lhs, typename Rhs> constexpr
auto sum_of(Lhs&& l, Rhs&& r) {
	return sum(std::forward<Lhs>(l), std::forward<Rhs>(r));
}

}
