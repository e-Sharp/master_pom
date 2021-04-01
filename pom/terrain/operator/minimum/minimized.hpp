#pragma once

#include "min.hpp"

#include <cmath>

namespace pom::terrain {

template<typename Terrain>
struct minimized {
	min min = {};
	Terrain terrain;
};

template<typename T>
minimized(min, T&&) -> minimized<T>;

template<typename Terrain> constexpr
auto operator|(Terrain&& t, min m) {
	return minimized(std::move(m), std::forward<Terrain>(t));
}

template<typename DeclContext, typename T> constexpr
float recipe(DeclContext, height_, const minimized<T>& m, vec2f coords) {
	auto [h] = decl::make<height_>(m.terrain, coords);
	return std::min(h, m.min.value);
}

}
