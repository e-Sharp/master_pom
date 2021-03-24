#pragma once

#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

template<typename Terrain>
struct noise_warped {
	Terrain terrain;
};

template<typename T>
noise_warped(T&&) -> noise_warped<T>;

template<typename DeclContext, typename T>
vec2f make(DeclContext, value_, const noise_warped<T>&, vec2f pos) {
	auto wx = x(pos) + maths::easy_perlin2(pos);
	auto wy = y(pos) + maths::easy_perlin2(pos);
	return vec2f(wx, wy);
}

}
