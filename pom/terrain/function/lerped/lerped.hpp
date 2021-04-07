#pragma once

#include "pom/terrain/function/concept/first_order_function.hpp"

namespace pom::terrain {

template<typename A, typename B, typename I>
struct lerped {
	constexpr lerped(A a, B b, I i) noexcept
		: a(std::move(a))
		, b(std::move(b))
		, i(std::move(i))
	{}

	A a;
	B b;
	I i;
};

template<typename... L>
struct is_first_order_function<lerped<L...>>
: std::true_type {};

}
