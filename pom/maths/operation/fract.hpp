#pragma once

#include "floor.hpp"

namespace pom::maths {

template<typename Ty> constexpr
auto fract(const Ty& x) {
	return x - floor(x);
}

}
