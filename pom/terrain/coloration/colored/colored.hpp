#pragma once

#include "pom/terrain/coloration/color/all.hpp"
#include "pom/terrain/function/concept/first_order_function.hpp"

namespace pom::terrain {

template<typename Function>
struct colored : Function {
	constexpr colored(color c, Function f)
		: Function(std::move(f))
		, color(std::move(c))
	{}

	color color;
};

template<typename F>
colored(color, F) -> colored<F>;

template<typename... C>
struct is_first_order_function<colored<C...>>
: std::true_type {};

}
