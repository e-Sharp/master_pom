#pragma once

#include "offset.hpp"

#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

template<typename Terrain>
struct offsetted {
	offset offset = {};
	Terrain terrain;
};

template<typename T>
offsetted(offset, T&&) -> offsetted<T>;

template<typename Terrain> constexpr
auto operator|(Terrain&& t, offset o) {
	return offsetted(std::move(o), std::forward<Terrain>(t));
}

template<typename DeclContext, typename T> constexpr
float recipe(DeclContext, height_, const offsetted<T>& o, vec2f coords) {
	auto ov = o.offset.value;
	auto [h] = decl::make<height_>(o.terrain, coords);
	return h + ov;
}

}
