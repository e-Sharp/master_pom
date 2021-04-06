#pragma once

#include "distortion.hpp"

#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

template<typename Terrain>
struct distorted {
	distortion distortion;
	Terrain terrain;
};

template<typename T>
distorted(distortion, T&&) -> distorted<T>;

template<typename Terrain> constexpr
auto operator|(Terrain&& t, distortion d) {
	return distorted(std::move(d), std::forward<Terrain>(t));
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
