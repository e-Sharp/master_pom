#pragma once

#include "pom/terrain/import/all.hpp"
#include "pom/terrain/function/all.hpp"

namespace pom::terrain {

constexpr auto mountains_0() {
	return
		noise() +
		(noise() * 0.5f | scaling(1 / 2.f)) +
		(1/4.f * noise() | scaling(1 / 4.f)) +
		(1/8.f * noise() | scaling(1 / 8.f)) +
		(1/16.f * noise() | scaling(1 / 16.f)) +
		(1/32.f * noise() | scaling(1 / 32.f));
}

constexpr auto mountains_1() {
	auto base =
		((noise() +
		(noise() * 0.5f | scaling(1 / 2.f)) +
		(1/4.f * noise() | scaling(1 / 4.f)) +
		(1/8.f * noise() | scaling(1 / 8.f)) +
		(1/16.f * noise() | scaling(1 / 16.f)) +
		(1/32.f * noise() | scaling(1 / 32.f)))
        * 8.f) | color(0.5f, 0.5f, 0.5f);
    
    auto sminBase = smin(base, constant(.65f), .5f);
    auto smaxBase = 2.f * smax(std::move(sminBase), constant(0.f), 1.5f)
        | scaling(2.f);

    auto plains = 5.f * noise() | scaling(4.f) | color(0.5f, 0.5f, 0.5f);

    auto land = lerp(smaxBase, plains, 0.5f) | color(0.5f, 0.5f, 0.5f);

    auto bump = 
		(((noise() * 0.5f | scaling(1 / 2.f)) +
		(1/4.f * noise() | scaling(1 / 4.f)) +
		(1/8.f * noise() | scaling(1 / 8.f)) +
        (1/16.f * noise() | scaling(1/16.f)) +
		(1/32.f * noise() | scaling(1 / 32.f)))
        * 0.25f)
        | scaling(2.f);
    
    auto mountain = lerp(land, bump, 0.8f) | color(0.5f, 0.5f, 0.5f);

    auto mountain2 = lerp(mountain, base, 0.95f) | color(0.5f, 0.5f, 0.5f);

    return mountain2;
        
}

//desert mountain
constexpr auto mountains_2() {
	auto voronoi =  3.f * (worley() | distortion{.amplitude = 5.f, .frequency = 1.f} | scaling(2.f)) | color(0.87f, 0.75f, 0.66f);
	auto base =
		((noise() +
		(noise() * 0.5f | scaling(1 / 2.f)) +
		(1/4.f * noise() | scaling(1 / 4.f)) +
		(1/8.f * noise() | scaling(1 / 8.f)) +
		(1/16.f * noise() | scaling(1 / 16.f)) +
		(1/32.f * noise() | scaling(1 / 32.f)))
        * 8.f) | color(1.f, 0.2f, 0.03f);
    
    auto sminBase = smin(base, constant(.65f), .5f);
    auto smaxBase = 2.f * smax(std::move(sminBase), constant(0.f), 1.5f)
        | scaling(2.f) | color(0.87f, 0.75f, 0.66f);

    auto plains = 5.f * noise() | scaling(4.f) | color(0.83f, 0.44f, 0.24f);

    auto land = lerp(smaxBase, plains, 0.5f);

    auto bump = 
		(((noise() * 0.5f | scaling(1 / 2.f)) +
		(1/4.f * noise() | scaling(1 / 4.f)) +
		(1/8.f * noise() | scaling(1 / 8.f)) +
        (1/16.f * noise() | scaling(1/16.f)) +
		(1/32.f * noise() | scaling(1 / 32.f)))
        * 0.25f)
        | scaling(2.f)
		| color(0.83f, 0.57f, 0.43f);
    
    auto mountain = lerp(land, bump, 0.8f);// | color(0.5f, 0.5f, 0.5f);

    auto mountain2 = lerp(mountain, base, 0.95f);// | color(0.5f, 0.5f, 0.5f);

	auto mountain3 = lerp(mountain2, voronoi, 0.75f);// | color(0.5f, 0.5f, 0.5f);

    return smax(mountain3, constant(0.5f) | color(0.87f, 0.75f, 0.66f), 0.65f);
        
}

}
