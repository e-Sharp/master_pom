#pragma once

#include <cmath>

namespace pom::maths {

template<typename Ty> constexpr
auto floor(const Ty& x) {
	return std::floor(x);
}

}
