#pragma once

#include "pom/terrain/imports.hpp"

#include <pom/maths/numeric/smoothstep.hpp>
#include <pom/maths/vector/all.hpp>
#include <pom/maths_impl/noise/perlin.hpp>

#include <cmath>

namespace pom {
namespace terrain {

struct snow {
	vec3f direction = maths::normalized(vec3f({0.5f, 0.f, -1.f}));
	float frequency = 8.f;
};

template<typename Terrain>
struct snowy {
	snowy(Terrain&& t)
		: terrain(std::move(t))
	{}

	snow snow = {};
	Terrain terrain;
};

template<typename T>
snowy(T) -> snowy<T>;

template<typename T>
auto normal(const snowy<T>& s, vec2f pos) {
	return normal(s.terrain, pos);
}

template<typename T>
float density(const snowy<T>& s, vec2f pos) {
	using namespace maths;

	auto a = dot(0.f - normal(s, pos), s.snow.direction);
	a = std::max(a, 0.f);
	a = std::pow(a, 2.f);

	auto p = maths_impl::easy_perlin2(s.snow.frequency * pos) / 2.f + 0.5f;

	if(p < 1. - a) {
		return 0.f;
	} else {
		return (p - (1.f - a)) / a;
	}
}

template<typename T>
auto weight(const snowy<T>& s, vec2f pos) {
	return weight(s.terrain, pos);
}

template<typename T>
auto height(const snowy<T>& s, vec2f pos) {
	using namespace maths;

	auto d = density(s, pos);
	auto h = smoothstep1(0.f, 0.3f, d) / 100.f;

	return height(s.terrain, pos) + h;
}

template<typename T>
auto color(const snowy<T>& s, vec2f pos) {
	using namespace maths;
	auto d = density(s, pos);
	d = smoothstep1(0.f, 0.1f, d);
	return (1.f - d) * color(s.terrain, pos) + d * vec3f({1, 1, 1});
}

}}
