#pragma once

#include "pom/terrain/import/all.hpp"

namespace pom {
namespace terrain {

template<typename DeclContext, typename Terrain>
vec3f recipe(DeclContext, color_, const Terrain&, vec2f) {
	return vec3f({0.5f, 0.5f, 0.5f});
}

template<typename DeclContext, typename Terrain>
float recipe(DeclContext, height_, const Terrain&, vec2f) {
	return 0.f;
}

template<typename DeclContext, typename Terrain>
vec3f recipe(DeclContext, normal_, const Terrain&, vec2f) {
	return vec3f({0.f, 0.f, 1.f});
}

template<typename DeclContext, typename Terrain>
float recipe(DeclContext, weight_, const Terrain&, vec2f) {
	return 1.f;
}

}}
