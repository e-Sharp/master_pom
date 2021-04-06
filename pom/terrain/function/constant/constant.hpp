#pragma once

#include "pom/terrain/function/concept/first_order_function.hpp"

#include <type_traits>

namespace pom::terrain {

struct constant {
	constant() = delete;

	constexpr constant(float v) noexcept
		: value(v)
	{}

	constexpr operator float() noexcept {
		return value;
	}

	float value;
};

template<>
struct is_first_order_function<constant>
: std::true_type {};

}
