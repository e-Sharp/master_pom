#pragma once

#include "pom/terrain/coloration/all.hpp"
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

auto dunes_1() {
	auto sine = 5.f * sin() | color(0.f, 0.f, 0.f);

	return smin(sine, constant(0.f) | color(1.f, 1.f, 1.f), 1.5f);
}

constexpr auto dunes_2() {
	auto voronoi =  1.5f * (worley() | distortion{.amplitude = 5.f, .frequency = 1.f} | scaling(5.f));
	auto base =
		((noise() +
		(noise() * 0.5f | scaling(1 / 2.f)))
        * 8.f) | color(0.5f, 0.5f, 0.5f);
    
    auto sminBase = smin(base, constant(.65f), .5f);
    auto smaxBase = 2.f * smax(std::move(sminBase), constant(0.f), 1.5f)
        | scaling(2.f);

    auto plains = 5.f * noise() | scaling(4.f) | color(0.5f, 0.5f, 0.5f);

    auto land = lerp(smaxBase, plains, 0.5f) | color(0.5f, 0.5f, 0.5f);

    auto dune1 = lerp(land, base, 0.95f) | color(0.5f, 0.5f, 0.5f);

	auto dune2 = lerp(dune1, voronoi, 0.3f) | color(0.5f, 0.5f, 0.5f);

    return dune2;
        
}

}
