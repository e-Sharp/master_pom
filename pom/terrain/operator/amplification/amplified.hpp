#pragma once

#include "amplification.hpp"

namespace pom::terrain {

template<typename Terrain>
struct amplified {
	amplification amplification = {};
	Terrain terrain;
};

template<typename T>
amplified(amplification, T&&) -> amplified<T>;

template<typename Terrain> constexpr
auto operator|(Terrain&& t, amplification a) {
	return amplified(std::move(a), std::forward<Terrain>(t));
}

template<typename DeclContext, typename T> constexpr
float recipe(DeclContext, height_, const amplified<T>& a, vec2f coords) {
	auto g = a.amplification.gain;
	auto [h] = decl::make<height_>(a.terrain, coords);
	return g * h;
}

}
