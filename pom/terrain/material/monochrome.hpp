#pragma once

#include "pom/terrain/imports.hpp"

namespace pom {
namespace terrain {

template<typename Terrain>
struct monochrome {
	monochrome(Terrain&& t)
		:	terrain(std::move(t))
	{}

	Terrain terrain;

	vec3f color = vec3f({0.5f, 0.5f, 0.5f});
};

template<typename T>
monochrome(T) -> monochrome<T>;

template<typename T>
auto color(const monochrome<T>& m, vec2f) {
	return m.color;
}

template<typename T>
auto height(const monochrome<T>& m, vec2f pos) {
	return height(m.terrain, pos);
}

template<typename T>
auto normal(const monochrome<T>& m, vec2f pos) {
	return normal(m.terrain, pos);
}

template<typename T>
auto weight(const monochrome<T>& m, vec2f pos) {
	return weight(m.terrain, pos);
}

}}
