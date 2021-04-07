#pragma once

#include "pom/terrain/function/concept/higher_order_function.hpp"
#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

struct color {
	constexpr color(float r, float g, float b)
		: value(r, g, b)
	{}

	vec3f value;
};

template<>
struct is_higher_order_function<color> 
: std::true_type {};

}
