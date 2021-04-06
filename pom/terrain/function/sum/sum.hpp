#pragma once

#include "pom/terrain/function/concept/first_order_function.hpp"

#include <type_traits>

namespace pom::terrain {

template<function Lhs, function Rhs>
struct sum {
	Lhs lhs;
	Rhs rhs;
};

template<typename Lhs, typename Rhs>
sum(Lhs, Rhs) -> sum<Lhs, Rhs>;

template<typename... S>
struct is_first_order_function<sum<S...>>
: std::true_type {};

}
