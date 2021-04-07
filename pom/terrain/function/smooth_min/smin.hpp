#pragma once

#include "pom/terrain/function/concept/first_order_function.hpp"
#include "pom/terrain/function/concept/function.hpp"

#include <type_traits>

namespace pom::terrain {

template<function A, function B>
struct smin {
	constexpr smin(A a, B b, float smooth) noexcept
		: a(std::move(a))
		, b(std::move(b))
		, smooth(smooth)
	{}

	A a;
	B b;
	float smooth;
};

template<typename A, typename B>
smin(A, B, float) -> smin<A, B>;

template<typename... S>
struct is_first_order_function<smin<S...>>
: std::true_type {};

}
