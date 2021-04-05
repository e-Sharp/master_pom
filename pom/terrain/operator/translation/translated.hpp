#pragma once

#include "translation.hpp"

#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

template<typename Terrain>
struct translated : Terrain {
	constexpr translated(translation&& tr, Terrain&& te)
		: Terrain(std::move(te)),
		translation(std::move(tr))
	{}

	translation translation;
};

template<typename T>
translated(translation, T&&) -> translated<T>;

template<typename Terrain> constexpr
auto operator|(Terrain&& te, translation tr) {
	return translated(std::move(tr), std::forward<Terrain>(te));
}

template<typename DeclContext, typename T> constexpr
float recipe(DeclContext, height_, const translated<T>& t, vec2f coords) {
	auto [h] = decl::make<height_>(static_cast<const T&>(t), coords - xy(t.translation));
	return h + z(t.translation);
}

}
