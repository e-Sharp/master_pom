#pragma once

#include "pom/maths/vector/throw.hpp"

namespace pom {
namespace maths {

// Single, direct.
template<vector V, typename F> constexpr
auto mapped(const V& v, F f) {
	auto m = V(size(v));
	auto in = begin(v);
	auto out = begin(m);
	while(in != end(v)) *out++ = f(*in++);
	return m;
}

// Double, direct.
template<vector LV, vector RV, typename F> constexpr
auto mapped(const LV& lv, const RV& rv, F f) {
	throw_if_different_size(lv, rv);
	auto m = LV(size(lv));
	for(std::size_t i = 0; i < size(lv); ++i) at(m, i) = f(at(lv, i), at(rv, i));
	return m;
}

}}
