#pragma once

#include "pom/terrain/function/concept/first_order_function.hpp"
#include "pom/terrain/function/concept/higher_order_function.hpp"
#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

struct translation {
	translation() = delete;

	constexpr translation(float x, float y) noexcept
		: value(std::move(x), std::move(y))
	{}

	constexpr translation(vec2f xy) noexcept
		: value(std::move(xy))
	{}

	constexpr operator const vec2f&() noexcept {
		return value;
	}

	vec2f value;
};

template<>
struct is_higher_order_function<translation>
: std::true_type {};

}
