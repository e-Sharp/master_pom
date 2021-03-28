#pragma once

#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

template<typename A, typename B>
struct sum {
	A a;
	B b;
};

template<typename A, typename B>
sum(A&&, B&&) -> sum<A, B>;

template<typename DeclContext, typename A, typename B> constexpr
float recipe(DeclContext, height_, const sum<A, B>& s, vec2f coords) {
	auto [ha] = decl::make<height_>(s.a, coords);
	auto [hb] = decl::make<height_>(s.b, coords);
	return ha + hb;
}

}
