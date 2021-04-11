#pragma once

#include "pom/terrain/import/all.hpp"
#include "pom/terrain/function/all.hpp"

namespace pom::terrain {

constexpr auto islands_0() {
	auto base =
		(noise() +
		(noise() * 0.5f | scaling(1 / 2.f)) +
		(1/4.f * noise() | scaling(1 / 4.f)) +
		(1/8.f * noise() | scaling(1 / 8.f)) +
		(1/16.f * noise() | scaling(1 / 16.f)) +
		(1/32.f * noise() | scaling(1 / 32.f)))
        * 5.f
		| color(0.5f, 0.5f, 0.5f);
    
    auto island = 2.f * smax(base, constant(0.5f) | color(0.f, 0.f, 1.f), 1.5f) | scaling(4.f);
    return island;
        
}

}