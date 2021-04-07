#pragma once

#include "pom/terrain/function/smooth_min/all.hpp"

namespace pom::terrain {

template<typename A, typename B> constexpr
auto smax(A&& a, B&& b, float smooth) {
	return constant(-1.f) * smin(
		constant(-1.f) * std::forward<A>(a),
		constant(-1.f) * std::forward<B>(b),
		smooth);
}

}
