#pragma once

#include "pom/terrain/function/multiplication/all.hpp"
#include "pom/terrain/function/smooth_max/all.hpp"

namespace pom::terrain {

template<typename X> constexpr
auto sabs(X&& x, float smooth) {
	return smax(X(x), constant(-1.f) * X(x), smooth);
}

}
