#pragma once

#include "pom/terrain/function/concept/higher_order_function.hpp"

namespace pom::terrain {

struct distortion {
	float amplitude = 1.f;
	float frequency = 1.f;
};

template<>
struct is_higher_order_function<distortion>
: std::true_type {};

}
