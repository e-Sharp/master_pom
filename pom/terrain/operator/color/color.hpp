#pragma once

#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

struct color {
	color(float r, float g, float b) {
		x(rgb) = r;
		y(rgb) = g;
		z(rgb) = b;
	}

	vec3f rgb;
};

}
