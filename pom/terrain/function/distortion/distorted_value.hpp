#pragma once

#include "distorted.hpp"

#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

template<typename DeclContext, typename T> constexpr
float recipe(DeclContext, value, const distorted<T>& d, vec2f xy) {
	auto dcs = xy 
		+ d.distortion.amplitude
		* get<0>(decl::make<value>(gradient_noise<2>(), 
			d.distortion.frequency * xy)); 
	return get<0>(decl::make<value>(d.terrain, dcs));
}

}
