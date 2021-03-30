#pragma once

#include "pom/terrain/import/all.hpp"
#include "pom/terrain/operator/all.hpp"
#include "pom/terrain/primitive/sine_wave.hpp"

namespace pom::terrain {

// https://en.wikipedia.org/wiki/Dune
constexpr auto dunes_0() {
	return sine_wave()
	| amplification{.constant = 0.5f, .multiplier = 0.5f}
	| amplification{.multiplier = 1 / 3.f}
	| distortion{.amplitude = 1 / 2.f, .frequency = 1 / 2.f}
	| distortion{.amplitude = 2.f, .frequency = 1 / 8.f}
	| distortion{.amplitude = 4.f, .frequency = 1 / 16.f}
	| distortion{.amplitude = 8.f, .frequency = 1 / 32.f}
	| scaling(20.f);
}

}
