#pragma once

#include "pom/terrain/import/all.hpp"
#include "pom/terrain/operator/operation.hpp"

namespace pom::terrain {

struct translation : vec3f {
	constexpr translation(float x, float y, float z)
		: vec3f(x, y, z)
	{}
};

template<>
struct is_operation<translation> {
	static constexpr bool value = true;
};

constexpr auto translation_xy(float x, float y) {
	return translation(x, y, 0.f);
}

constexpr auto translation_z(float z) {
	return translation(0.f, 0.f, z);
}

}
