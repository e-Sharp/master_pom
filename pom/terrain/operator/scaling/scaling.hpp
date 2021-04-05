#pragma once

#include "pom/terrain/import/all.hpp"
#include "pom/terrain/operator/operation.hpp"

namespace pom::terrain {

struct scaling : vec3f {
	explicit constexpr scaling(float s)
		: vec3f(s)
	{}

	constexpr scaling(float x, float y, float z)
		: vec3f(x, y, z)
	{}
};

template<>
struct is_operation<scaling> {
	static constexpr bool value = true;
};

constexpr auto scaling_xy(float x, float y) {
	return scaling(x, y, 1.f);
}

constexpr auto scaling_z(float z) {
	return scaling(1.f, 1.f, z);
}

}
