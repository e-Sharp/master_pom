#pragma once

#include "color.hpp"

#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

template<typename Terrain>
struct colored : Terrain {
	colored(color c, Terrain&& t)
		: Terrain(std::move(t))
		, color(std::move(c))
	{}

	color color;
};

template<typename T>
colored(color, T&&) -> colored<T>;

template<typename T> constexpr
auto operator|(T&& t, color c) {
	return colored(std::move(c), std::forward<T>(t));
}

template<typename DeclContext, typename C> constexpr
vec3f recipe(DeclContext, color_, const colored<C>& c, vec2f) {
	return c.color;
}

}
