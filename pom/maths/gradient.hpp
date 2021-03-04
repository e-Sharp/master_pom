#pragma once

#include "pom/maths/vector/all.hpp"

namespace pom {
namespace maths {

template<typename F, typename XY, typename E> constexpr
auto gradient_approximation(const F& f, const XY& xy, E e) {
	auto&& [x, y] = xy.elements;
	auto dx = (f({x + e, y    }) - f({x - e, y    })) / (2.f * e);
	auto dy = (f({x    , y + e}) - f({x    , y - e})) / (2.f * e);
	return XY({dx, dy});
} 

template<typename V> constexpr
auto normal_from_gradient(const V& g) {
	auto&& [dx, dy] = g.elements;
	auto _1 = decltype(dx)(1);
	// Cross product of (1, 0, dx) and (0, 1, dy).
	return normalized(decltype(similar<3>(g))({-dx, -dy, _1}), meta::unchecked());
}

template<typename F, typename XY, typename E> constexpr
auto normal_approximation(const F& f, const XY& xy, E e) {
	return normal_from_gradient(gradient_approximation(f, xy, e));
}

}}
