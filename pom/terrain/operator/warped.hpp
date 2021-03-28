#pragma once

#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

template<typename Warping, typename Terrain>
struct warped {
	Warping warping;
	Terrain terrain;
};

template<typename W, typename T>
warped(W&&, T&&) -> warped<W, T>;

// Height.

template<typename W, typename T>
auto prerequisites(height_, const warped<W, T>& w, vec2f xy)
-> decl::targets<value_>;

template<typename DeclContext, typename W, typename T> constexpr
float recipe(DeclContext c, height_, const warped<W, T>& w, vec2f xy) {
	auto v = c.ref<value_>();
	return get<0>(decl::make<height_>(w.terrain, v));
}

// Value.

template<typename DeclContext, typename W, typename T> constexpr
vec2f recipe(DeclContext, value_, const warped<W, T>& w, vec2f xy) {
	return w.warping(xy);
}

}
