#pragma once

#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

struct distortion {
	float amplitude = 1.f;
	float frequency = 1.f;
};

template<typename Terrain>
struct distorted {
	distortion distortion;
	Terrain terrain;
};

template<typename T>
distorted(distortion, T&&) -> distorted<T>;

template<typename T> constexpr
auto operator|(T&& t, distortion d) {
	return distorted(std::move(d), std::move(t));
}

template<typename DeclContext, typename T> constexpr
float recipe(DeclContext, height_, const distorted<T>& d, vec2f coords) {
	auto dcs = coords 
		+ d.distortion.amplitude
		* get<0>(decl::make<value_>(gradient_noise<2>(), 
			d.distortion.frequency * coords)); 
	return get<0>(decl::make<height_>(d.terrain, dcs));
}

}
