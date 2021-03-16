#pragma once

#include "pom/maths_impl/all.hpp"

namespace pom {
namespace terrain {

template<typename Ty>
using interval = maths_impl::interval<Ty>;

template<typename Ty>
using mat = decltype(maths_impl::matrix<Ty>());

template<typename Ty>
using vec2 = decltype(maths_impl::vector<Ty, 2>());

using vec2f = vec2<float>;

constexpr float x(const vec2f& v) {
	return at(v, 0);
}

constexpr float& x(vec2f& v) {
	return at(v, 0);
}

constexpr float y(const vec2f& v) {
	return at(v, 1);
}

constexpr float& y(vec2f& v) {
	return at(v, 1);
}

template<typename Ty>
using vec3 = decltype(maths_impl::vector<Ty, 3>());

using vec3f = vec3<float>;

constexpr vec2f xy(const vec3f& v) {
	return vec2f({at(v, 0), at(v, 1)});
}

constexpr float x(const vec3f& v) {
	return at(v, 0);
}

constexpr float& x(vec3f& v) {
	return at(v, 0);
}

constexpr float y(const vec3f& v) {
	return at(v, 1);
}

constexpr float& y(vec3f& v) {
	return at(v, 1);
}

constexpr float z(const vec3f& v) {
	return at(v, 2);
}

constexpr float& z(vec3f& v) {
	return at(v, 2);
}

}}
