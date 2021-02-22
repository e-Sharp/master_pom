#pragma once

#include "throw.hpp"

namespace pom {
namespace maths {

// Single.
template<vector V, typename F, typename Acc> constexpr
auto reduced(const V& v, F reduce, Acc&& a) {
	for(auto it = begin(v); it != end(v); ++it) f(a, *it++);
	return a;
}

// Double.
template<vector LV, vector RV, typename F, typename Acc> constexpr
auto reduced(const LV& lv, const RV& rv, F f, Acc&& a) {
	throw_if_different_size(lv, rv);
	auto l = begin(lv);
	auto r = begin(rv);
	while(l != end(lv)) f(a, *l++, *r++);
	return a;
}

}}
