#pragma once

#include "pom/terrain/import/all.hpp"
#include "pom/terrain/operator/all.hpp"
#include "pom/terrain/primitive/all.hpp"

namespace pom::terrain {

constexpr auto mountains_0() {
	return std::forward_as_tuple(
		noise(),
		noise() | scaling(1 / 2.f),
		noise() | scaling(1 / 4.f))
	| sum()
	| scaling(100.f);
}

}
