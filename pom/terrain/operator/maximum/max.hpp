#pragma once

#include "pom/terrain/operator/operation.hpp"

namespace pom::terrain {

struct max {
	max() = delete;

	explicit constexpr max(float s)
        : smooth(s)
	{}

	float smooth;
};

template<>
struct is_operation<max> {
	static constexpr bool value = true;
};

}
