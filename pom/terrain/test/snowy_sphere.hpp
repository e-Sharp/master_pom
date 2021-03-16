#pragma once

#include <pom/terrain/effect/snow.hpp>
#include <pom/terrain/material/monochrome.hpp>
#include <pom/terrain/primitive/sphere.hpp>

namespace pom {
namespace terrain {

auto snowy_sphere_terrain() {
	auto s = sphere();
	auto ms = monochrome(std::move(s));
	ms.color = vec3f({1.f, 0.f, 0.f});
	auto sms = snowy(std::move(ms));
	return sms;
}

struct snowy_sphere {
	decltype(snowy_sphere_terrain()) terrain = snowy_sphere_terrain();
};

float height(const snowy_sphere& s, vec2f pos) {
	return height(s.terrain, pos);
}

auto color(const snowy_sphere& s, vec2f pos) {
	return color(s.terrain, pos);
}

}}
