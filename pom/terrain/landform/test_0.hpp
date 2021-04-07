#pragma once

#include "pom/terrain/function/all.hpp"

namespace pom::terrain {

auto test_0() {
	return sin()
	| distortion{.amplitude = 2.f, .frequency = 1 / 2.f}
	| distortion{.amplitude = 1.f, .frequency = 1.f};
}

}
