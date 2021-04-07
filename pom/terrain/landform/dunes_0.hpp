#pragma once

#include "pom/terrain/function/all.hpp"

namespace pom::terrain {

// https://en.wikipedia.org/wiki/Dune
auto dunes_0() {
	return 30.f * sin()
	| distortion{.amplitude = 1.f, .frequency = 1.f}
	| distortion{.amplitude = 2.f, .frequency = 1 / 8.f}
	//| distortion{.amplitude = 4.f, .frequency = 1 / 16.f}
	//| distortion{.amplitude = 8.f, .frequency = 1 / 32.f}
	| scaling(50.f);
}

}
