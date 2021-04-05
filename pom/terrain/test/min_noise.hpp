#pragma once

#include "pom/terrain/operator/all.hpp"
#include "pom/terrain/primitive/all.hpp"

#include <tuple>

namespace pom::terrain {

auto min_noise() {
	return std::forward_as_tuple(
		noise() | color(1.f, 0.f, 0.f),
		noise() | color(0.f, 0.f, 1.f) | translation({250.f, 120.f}))
	| smin(0.1f);
}

}
