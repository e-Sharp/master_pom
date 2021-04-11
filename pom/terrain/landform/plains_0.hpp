#pragma once

#include "pom/terrain/import/all.hpp"
#include "pom/terrain/function/all.hpp"

namespace pom::terrain {

constexpr auto plains_0() {
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
    
    auto hills = lerp(land, bump, 0.8f) | color(0.5f, 0.5f, 0.5f);

    return hills;
        
}

constexpr auto plains_1() {
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
    
    auto hills = lerp(land, bump, 0.8f) | color(0.5f, 0.5f, 0.5f);

    auto base2 =
		((noise() +
		(noise() * 0.5f | scaling(1 / 2.f)) +
		(1/4.f * noise() | scaling(1 / 4.f)) +
		(1/8.f * noise() | scaling(1 / 8.f)) +
		(1/16.f * noise() | scaling(1 / 16.f)) +
		(1/32.f * noise() | scaling(1 / 32.f)))
        * 8.f) | scaling(8.f);

    auto hills2 = lerp(hills, base2, 0.75) | color(0.5f, 0.5f, 0.5f);

    return hills2;
        
}

}