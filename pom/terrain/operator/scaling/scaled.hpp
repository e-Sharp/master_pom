#pragma once

#include "scaling.hpp"

#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

template<typename Terrain>
struct scaled {
	scaling scaling = {};
	Terrain terrain;
};

template<typename T>
scaled(scaling, T&&) -> scaled<T>;

template<typename T> constexpr
auto operator|(T&& t, scaling s) {
	return scaled(std::move(s), std::move(t));
}

template<typename DeclContext, typename T> constexpr
float recipe(DeclContext, color_, const scaled<T>& s, vec2f coords) {
	auto scs = s.factor * coords;
	auto [c] = decl::make<color_>(s.terrain, scs);
	return c;
}

template<typename DeclContext, typename T> constexpr
float recipe(DeclContext, gradient, const scaled<T>& s, vec2f coords) {
	auto scs = s.factor * coords;
	auto [g] = decl::make<gradient>(s.terrain, scs);
	return g;
}

template<typename DeclContext, typename T> constexpr
float recipe(DeclContext, height_, const scaled<T>& s, vec2f coords) {
	auto sf = s.scaling.factor;
	auto scs = coords / sf;
	auto [h] = decl::make<height_>(s.terrain, scs);
	return sf * h;
}

template<typename DeclContext, typename T> constexpr
float recipe(DeclContext, normal_, const scaled<T>& s, vec2f coords) {
	auto scs = s.factor * coords;
	auto [n] = decl::make<normal_>(s.terrain, scs);
	return n;
}

}
