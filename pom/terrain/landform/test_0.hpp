#pragma once

#include "pom/terrain/function/all.hpp"

namespace pom::terrain {

auto test_0() {
	return lerp(noise(), sin(), constant(0.5f));
}

}
