#pragma once

#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

struct scaling {
	float factor = 1.f;
};

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

//template<typename DeclContext, typename T> constexpr
//float recipe(DeclContext, color_, const scaled<T>& s, vec2f coords) {
//	auto cs = s.factor * coords;
//	return get<0>(decl::make<color_>(s.terrain, cs));
//}

template<typename DeclContext, typename T> constexpr
float recipe(DeclContext, height_, const scaled<T>& s, vec2f coords) {
	auto scs = coords / s.scaling.factor;
	return s.scaling.factor * get<0>(decl::make<height_>(s.terrain, scs));
}

//template<typename DeclContext, typename T> constexpr
//vec3f recipe(DeclContext, normal_, const scaled<T>& s, vec2f coords) {
//	auto cs = s.factor * coords;
//	return get<0>(decl::make<normal_>(s.terrain, cs));
//}

}
