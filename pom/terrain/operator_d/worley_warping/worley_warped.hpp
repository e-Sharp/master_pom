#pragma once

#include "worley_warping.hpp"

namespace pom::terrain {

template<typename Terrain>
struct worley_warped {
	Terrain terrain;
};

template<typename Terrain>
worley_warped() -> worley_warped<Terrain>;

}
