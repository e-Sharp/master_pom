#pragma once

#include <cmath>

namespace pom::maths {

float fract(float x) noexcept {
	float i;
	auto f = std::modf(x, &i);
	return f + (f < 0.f);
}

}
