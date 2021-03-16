#pragma once

#include "pom/maths_impl/noise/perlin.hpp"
#include "pom/terrain/imports.hpp"

namespace pom {
namespace terrain {

struct billow {};

float height(billow, vec2f pos) {
	using namespace maths;
	auto h = maths_impl::easy_perlin2(2.f * pos);
	h = std::abs(h);
	return h;
}

struct orange_peel {};

float height(orange_peel, vec2f pos) {
	using namespace maths;
	auto h = maths_impl::easy_perlin2(2.f * pos) / 2.f + 0.5;
	h = std::sqrt(1.f - h * h);
	h = h * h;
	return h;
}

///////////////////////////////////////////////

struct picot {};

float height(picot, vec2f pos) {
	using namespace maths;
	auto h = height(billow(), pos);
	h = 1.f - std::sqrt(1.f - h * h);
	return h;
}

float smoothstep(float a, float b, float x) {
	x = std::min(std::max(x, a), b);
	x = (x - a) / (b - a);
	return 3 * x * x - 2 * x * x * x;
}

struct paint {};

float height(paint, vec2f pos) {
	using namespace maths;
	auto pic = height(picot(), pos);
	auto pe = height(orange_peel(), pos);
	pe = smoothstep(-4.f, 2.f, at(pos, 1)) * pe;
	return 2.f * (1.f - pe) * pic + pe;
}

}}
