#pragma once

#include "pom/terrain/function/concept/first_order_function.hpp"

namespace pom::terrain {

template<typename Function>
struct opposed : Function {
	template<typename F> constexpr
	opposed(F&& f) noexcept
		: Function(std::forward<F>(f))
	{}
};

template<typename F>
opposed(F) -> opposed<F>;

template<typename... O>
struct is_first_order_function<opposed<O...>>
: std::true_type {};

}
