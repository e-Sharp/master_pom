#pragma once

#include "max.hpp"

#include <cmath>

namespace pom::terrain {

template<typename Terrain>
struct maximized {
	max max = {};
	Terrain terrain;
};

template<typename T>
maximized(max, T&&) -> maximized<T>;

template<typename Terrain> constexpr
auto operator|(Terrain&& t, max m) {
	return maximized(std::move(m), std::forward<Terrain>(t));
}

template<typename DeclContext, typename T> constexpr
float recipe(DeclContext, height_, const maximized<T>& m, vec2f coords) {
	auto [h] = decl::make<height_>(m.terrain, coords);
	return std::max(h, m.max.value);
}

}
