#pragma once

#include "pom/terrain/function/concept/first_order_function.hpp"

#include <type_traits>

namespace pom::terrain {

template<function Lhs, function Rhs>
struct sum {
	template<typename... Rhss>
	constexpr sum(Lhs&& l, Rhss&&... rs)
		: lhs(std::forward<Lhs>(l))
		, rhs(sum(std::forward<Rhss>(rs)...))
	{}

	constexpr sum(Lhs&& l, Rhs&& r)
		: lhs(std::forward<Lhs>(l))
		, rhs(std::forward<Rhs>(r))
	{}

	Lhs lhs;
	Rhs rhs;
};

template<typename Lhs, typename... Rhss>
sum(Lhs, Rhss...) -> sum<Lhs, decltype(sum(Rhss...))>;

template<typename Lhs, typename Rhs>
sum(Lhs, Rhs) -> sum<Lhs, Rhs>;

template<typename... S>
struct is_first_order_function<sum<S...>>
: std::true_type {};

}
