#pragma once

#include "pom/terrain/import/all.hpp"
#include "pom/terrain/operator/operation.hpp"

namespace pom::terrain {

struct color : vec3f {
	constexpr color(float r, float g, float b) 
		: vec3f(r, g, b)
	{}
};

template<>
struct is_operation<color> {
	static constexpr bool value = true;
};

}
