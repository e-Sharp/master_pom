#pragma once

#include "pom/terrain/import/all.hpp"
#include "pom/terrain/function/all.hpp"

namespace pom::terrain {

//snowy / sandy mountains
constexpr auto randoms_0() {
	auto base =
		(noise() +
		(noise() * 0.5f | scaling(1 / 2.f)) +
		(1/4.f * noise() | scaling(1 / 4.f)) +
		(1/8.f * noise() | scaling(1 / 8.f)) +
		(1/16.f * noise() | scaling(1 / 16.f)) +
		(1/32.f * noise() | scaling(1 / 32.f)))
        * 5.f
		| color(0.21f, 0.21f, 0.21f);
    
    auto sminBase = smin(base, constant(0.5f), .5f);
    auto smaxBase = 2.f * smax(std::move(sminBase), constant(0.f), 1.f)
        | scaling(2.f);

    auto plain = noise() | scaling(4.f);

    auto bump = (noise() +
		((noise() * 0.5f | scaling(1 / 2.f)) +
		(1/4.f * noise() | scaling(1 / 4.f)) +
		(1/8.f * noise() | scaling(1 / 8.f)) +
        (1/16.f * noise() | scaling(1/16.f)))
        * 5.f)
        | scaling(10.f)
		| color(1.f, 1.f, 1.f);

    auto rockPlain = lerp(std::move(smaxBase) | color(0.21f, 0.21f, 0.21f), std::move(plain) | color(1.f, 1.f, 1.f), constant(0.5f));
    return 2.f * lerp(rockPlain, bump, constant(0.5f));
        
}

//wtf is this ?
auto randoms_1() {
	auto voronoi = worley() | distortion{.amplitude = 5.f, .frequency = 1.f} | scaling(.5f);
	auto perlin = (noise() +
		(noise() * 0.5f | scaling(1 / 2.f))+
		(noise() * 0.25f | scaling(1 / 4.f))) | scaling(.5f);
	auto wave = 1.5f * sin()
	| distortion{.amplitude = 5.f, .frequency = 5.f}
	| distortion{.amplitude = 2.f, .frequency = 1 / 8.f};
	//return perlin;	
	auto dune = lerp(voronoi, perlin, constant(.4f));
	//return dune;
	//return wave;
	auto base = lerp(dune, wave, constant(.8f));
	return base;
}

}