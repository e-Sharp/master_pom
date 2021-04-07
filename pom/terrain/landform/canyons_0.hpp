#pragma once

#include "pom/terrain/import/all.hpp"
#include "pom/terrain/function/all.hpp"

namespace pom::terrain {

constexpr auto canyons_0() {
	auto base =
		(noise() +
		(noise() * 0.5f | scaling(1 / 2.f)) +
		(1/4.f * noise() | scaling(1 / 4.f)) +
		(1/8.f * noise() | scaling(1 / 8.f)) +
		(1/16.f * noise() | scaling(1 / 16.f)) +
		(1/32.f * noise() | scaling(1 / 32.f)))
        * 8.f;
    
    auto sminBase = smin(base, constant(.65f), .5f);
    auto smaxBase = 2.f * smax(std::move(sminBase), constant(0.f), 1.5f)
        | scaling(2.f);

    auto plain = noise() | scaling(4.f);

    auto bump = 
		(((noise() * 0.5f | scaling(1 / 2.f)) +
		(1/4.f * noise() | scaling(1 / 4.f)) +
		(1/8.f * noise() | scaling(1 / 8.f)) +
        (1/16.f * noise() | scaling(1/16.f)) +
		(1/32.f * noise() | scaling(1 / 32.f)))
        * 0.25f)
        | scaling(2.f);

    auto bumpCanyon = lerp(std::move(smaxBase), std::move(plain), constant(0.5f));
    return 2.f * lerp(bumpCanyon, bump, constant(0.5f));
        
}

}