#pragma once

#include "lerp.hpp"

#include "pom/terrain/operator/scaling/scaling.hpp"
#include "pom/terrain/operator/sum/sum.hpp"
#include "pom/terrain/operator/sum/sum_operation.hpp"

#include <tuple>

namespace pom::terrain {

template<typename Terrain0, typename Terrain1> constexpr
auto operator|(std::tuple<Terrain0, Terrain1>&& t, lerp l) {
	return std::forward_as_tuple(
		get<0>(std::move(t)) | scaling(1.f, 1.f, l.t),
		get<1>(std::move(t)) | scaling(1.f, 1.f, 1.f - l.t))
	| sum();
}

}
