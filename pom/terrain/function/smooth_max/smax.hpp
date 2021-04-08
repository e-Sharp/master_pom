#pragma once

#include "pom/terrain/function/opposite/all.hpp"
#include "pom/terrain/function/smooth_min/all.hpp"

namespace pom::terrain {

template<typename A, typename B> constexpr
auto smax(A&& a, B&& b, float smooth) {
	return - smin(
		opposed(std::forward<A>(a)),
		opposed(std::forward<B>(b)),
		smooth);
}

}
