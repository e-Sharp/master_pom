#pragma once

#include "pom/terrain/imports.hpp"

#include <pom/maths_impl/noise/perlin.hpp>

namespace pom {
namespace terrain {

struct erosion {};

auto value(const erosion&, vec2f pos, vec3f normal) {
	using namespace maths;
	auto a = 1.f - dot(normal, vec3f({0.f, 0.f, 1.f}));
	auto p = maths_impl::easy_perlin2(32.f * xy(normal)) / 2.f - 0.5f;
	p /= 5.f;
	return a * p;
}

template<typename Terrain>
struct eroded {
	Terrain terrain;

	erosion erosion = {};
};

template<typename T>
eroded(T) -> eroded<T>;

template<typename T>
auto height(const eroded<T>& e, vec2f pos) {
	return height(e.terrain, pos) + value(e.erosion, pos, normal(e.terrain, pos));
}

}}
