#pragma once

#include "clamp.hpp"
#include "lerp.hpp"

namespace pom::maths {

// https://www.iquilezles.org/www/articles/smin/smin.htm
template<typename Ty, typename K> constexpr
Ty smin(const Ty& a, const Ty& b, const K& k) {
	auto h = clamp((a - b) / (K(2.f) * k) + K(0.5f), K(0), K(1));
	return lerp(a, b, h) - k * h * (K(1) - h); 
}

}
