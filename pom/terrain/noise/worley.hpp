#pragma once

#include "pom/terrain/imports.hpp"

namespace pom {
namespace terrain {

struct worley {};

vec2f worley_hash(vec2f pos) {
	using namespace maths;
	auto k = vec2f({0.3483099f, 0.4688794f});
    pos = pos * k + vec2f({y(k), x(k)});
    return fract(16.f * k * fract(x(pos) * y(pos) * (x(pos) + y(pos))));
}

auto noise(const worley&, vec2f pos) {
	using namespace maths;
	auto d = vec2f({1.f, 1.f});
    auto i = floor(pos);
    for(float j = -1.; j <= 1.; j += 1.f)
    for(float k = -1.; k <= 1.; k += 1.f) {
        auto seed = i + vec2f({j, k}) + worley_hash(i + vec2f({j, k}));
        auto diff = seed - pos;
        if(dot(diff, diff) < dot(d, d)) {
            d = diff;
        }
    }
    return d;
}

auto height(const worley& w, vec2f pos) {
    auto h = maths::length(noise(w, pos)) / std::sqrt(2.f);
    h = std::sqrt(1. - h * h);
    return h;
}

auto color(const worley& w, vec2f pos) {
    auto c = maths::length(noise(w, pos)) / std::sqrt(2.f);
    return vec3f({c, c, c});
}

}}
