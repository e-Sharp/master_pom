#pragma once

#include "pom/terrain/function/concept/first_order_function.hpp"
#include "pom/terrain/function/concept/function.hpp"

namespace pom::terrain {

template<function Lhs, function Rhs>
struct product {
	template<typename... Rhss>
	constexpr product(Lhs l, Rhss&&... rs)
		: lhs(std::move(l))
		, rhs(product(std::forward<Rhss>(rs)...))
	{}

	constexpr product(Lhs l, Rhs r)
		: lhs(std::move(l))
		, rhs(std::move(r))
	{}

	Lhs lhs;
	Rhs rhs;
};

template<typename Lhs, typename... Rhss>
product(Lhs, Rhss...) -> product<Lhs, decltype(product(std::declval<Rhss>()...))>;

template<typename Lhs, typename Rhs>
product(Lhs, Rhs) -> product<Lhs, Rhs>;

template<typename... S>
struct is_first_order_function<product<S...>>
: std::true_type {};

}
