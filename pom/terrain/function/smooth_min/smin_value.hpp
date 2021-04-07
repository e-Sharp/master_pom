#pragma once

#include "smin.hpp"

#include "pom/terrain/function/tag/value.hpp"
#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

template<typename DeclContext, typename... S> constexpr
float recipe(DeclContext, value, const smin<S...>& s, vec2f xy) {
	auto [a] = decl::make<value>(s.a, xy);
	auto [b] = decl::make<value>(s.b, xy);
	auto t = maths::clamp((a - b) / (2.f * s.smooth) + 0.5f, 0.f, 1.f);
	return maths::lerp(a, b, t) - s.smooth * t * (1.f - t);
}

}
