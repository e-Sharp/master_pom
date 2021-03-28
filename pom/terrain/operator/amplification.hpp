#pragma once

#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

struct amplification {
	float constant = 0.f;
	float multiplier = 1.f;
};

template<typename Terrain>
struct amplified {
	amplification amplification;
	Terrain terrain;
};

template<typename T>
amplified(amplification, T&&) -> amplified<T>;

template<typename T> constexpr
auto operator|(T&& t, amplification a) {
	return amplified(std::move(a), std::move(t));
}

template<typename DeclContext, typename T> constexpr
float recipe(DeclContext, height_, const amplified<T>& a, vec2f coords) {
	auto c = a.amplification.constant;
	auto m = a.amplification.multiplier;
	auto h = get<0>(decl::make<height_>(a.terrain, coords));
	return m * h + c;
}

}
