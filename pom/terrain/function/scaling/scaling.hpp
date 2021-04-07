#pragma once

#include "pom/terrain/function/concept/higher_order_function.hpp"
#include "pom/terrain/import/all.hpp"

#include <type_traits>

namespace pom::terrain {

struct scaling {
	scaling() = delete;

	constexpr scaling(float s)
		: value(std::move(s))
	{}

	constexpr scaling(float sx, float sy)
		: value(std::move(sx), std::move(sy))
	{}

	constexpr scaling(vec2f xy) noexcept
		: value(std::move(xy))
	{}

	constexpr operator const vec2f&() noexcept {
		return value;
	}

	vec2f value;
};

template<>
struct is_higher_order_function<scaling>
: std::true_type {};

}
