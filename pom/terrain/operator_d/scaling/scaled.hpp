#pragma once

#include "scaling.hpp"

#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

template<typename Terrain>
struct scaled {
	scaling scaling;
	Terrain terrain;
};

template<typename T>
scaled(scaling, T&&) -> scaled<T>;

template<typename T> constexpr
auto operator|(T&& t, scaling s) {
	return scaled(std::move(s), std::move(t));
}

template<typename DeclContext, typename T> constexpr
vec3f recipe(DeclContext, color_, const scaled<T>& s, vec2f coords) {
	auto scs = coords / xy(s.scaling);
	auto [c] = decl::make<color_>(s.terrain, scs);
	return c;
}

template<typename DeclContext, typename T> constexpr
vec3f recipe(DeclContext, gradient, const scaled<T>& s, vec2f coords) {
	auto scs = coords / xy(s.scaling);
	auto [g] = decl::make<gradient>(s.terrain, scs);
	return z(s.scaling) * g;
}

template<typename DeclContext, typename T> constexpr
float recipe(DeclContext, height_, const scaled<T>& s, vec2f coords) {
	auto scs = coords / xy(s.scaling);
	auto [h] = decl::make<height_>(s.terrain, scs);
	return z(s.scaling) * h;
}

}
