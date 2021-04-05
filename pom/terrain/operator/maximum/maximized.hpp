#pragma once

#include "max.hpp"

#include <pom/maths/operation/clamp.hpp>
#include <pom/maths/operation/lerp.hpp>

#include <tuple>

namespace pom::terrain {

template<typename TerrainA, typename TerrainB>
struct maximized {
	max max;
	TerrainA a;
	TerrainB b;
};

template<typename TA, typename TB>
maximized(max, TA&&, TB&&) -> maximized<TA, TB>;

template<typename TA, typename TB> constexpr
auto operator|(std::tuple<TA, TB>&& t, max m) {
	return maximized(
		std::move(m),
		std::get<0>(std::move(t)),
		std::get<1>(std::move(t)));
}

template<typename DeclContext, typename TA, typename TB> constexpr
vec3f recipe(DeclContext, color_, const maximized<TA, TB>& m, vec2f coords) {
	auto [ca, ha] = decl::make<color_, height_>(m.a, coords);
	ha = -ha;
	auto [cb, hb] = decl::make<color_, height_>(m.b, coords);
	hb = -hb;
	auto t = maths::clamp((ha - hb) / (2.f * m.max.smooth) + 0.5f, 0.f, 1.f);
	return maths::lerp(ca, cb, t);
}

template<typename DeclContext, typename TA, typename TB> constexpr
float recipe(DeclContext, height_, const maximized<TA, TB>& m, vec2f coords) {
	auto [ha] = decl::make<height_>(m.a, coords);
	ha = -ha;
	auto [hb] = decl::make<height_>(m.b, coords);
	hb = -hb;
	auto t = maths::clamp((ha - hb) / (2.f * m.max.smooth) + 0.5f, 0.f, 1.f);
	return -(maths::lerp(ha, hb, t) - m.max.smooth * t * (1.f - t));
}

}
