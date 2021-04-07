#pragma once

#include "pom/terrain/coloration/tag/color.hpp"
#include "pom/terrain/function/smooth_min/smin.hpp"
#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

template<typename DeclContext, typename... S> constexpr
vec3f recipe(DeclContext, target::color, const smin<S...>& s, vec2f xy) {
	auto [ca, a] = decl::make<target::color, value>(s.a, xy);
	auto [cb, b] = decl::make<target::color, value>(s.b, xy);
	auto t = maths::clamp((a - b) / (2.f * s.smooth) + 0.5f, 0.f, 1.f);
	return maths::lerp(ca, cb, t);
}

}
