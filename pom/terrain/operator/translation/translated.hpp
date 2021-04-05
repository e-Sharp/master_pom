#pragma once

#include "translation.hpp"

#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

template<typename Terrain>
struct translated {
	translation translation = {};
	Terrain terrain;
};

template<typename T>
translated(translation, T&&) -> translated<T>;

template<typename Terrain> constexpr
auto operator|(Terrain&& te, translation tr) {
	return translated(std::move(tr), std::forward<Terrain>(te));
}

template<typename DeclContext, typename Tag, typename T> constexpr
vec3f recipe(DeclContext, Tag, const translated<T>& t, vec2f coords) {
	auto& tr = t.translation.value;
	auto [v] = decl::make<Tag>(t.terrain, coords - tr);
	return v;
}

template<typename DeclContext, typename T> constexpr
float recipe(DeclContext, height_, const translated<T>& t, vec2f coords) {
	auto tr = t.translation.value;
	auto [h] = decl::make<height_>(t.terrain, coords - tr);
	return h;
}

}
