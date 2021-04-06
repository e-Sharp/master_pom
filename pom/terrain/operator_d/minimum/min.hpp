#pragma once

#include "pom/terrain/operator/operation.hpp"

namespace pom::terrain {

struct min {
	min() = delete;

	explicit constexpr min(float s)
        : smooth(s)
	{}

	float smooth;
};

template<>
struct is_operation<min> {
	static constexpr bool value = true;
};

}
