#pragma once

#include "translation.hpp"

#include "pom/terrain/function/concept/decorator.hpp"

#include <type_traits>

namespace pom::terrain {

template<typename Function>
struct translated : Function {
	constexpr translated(translation t, Function f) noexcept
		: Function(std::move(f))
		, translation(std::move(t))
	{}

	translation translation;
};

template<typename F>
translated(translation, F) -> translated<F>;

template<typename T>
struct is_decorator<translated<T>>
: std::true_type {};

}
