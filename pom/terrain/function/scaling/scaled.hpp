#pragma once

#include "scaling.hpp"

#include "pom/terrain/function/concept/first_order_function.hpp"

#include <type_traits>

namespace pom::terrain {

template<typename Function>
struct scaled : Function {
	constexpr scaled(scaling s, Function&& f) noexcept
		: Function(std::move(f))
		, scaling(std::move(s))
	{}

	scaling scaling;
};

template<typename F>
scaled(scaling, F) -> scaled<F>;

template<typename S>
struct is_first_order_function<scaled<S>>
: std::true_type {};

}
