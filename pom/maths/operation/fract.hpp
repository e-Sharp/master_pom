#pragma once

#include <cmath>

namespace pom::maths {

float fract(float x) noexcept {
	float i;
	return std::abs(std::modf(x, &i));
}

}
