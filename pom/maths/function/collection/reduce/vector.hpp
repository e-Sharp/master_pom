#pragma once

#include "pom/maths/function/vector/throw.hpp"

namespace pom {
namespace maths {

// Single.
template<typename B, typename F, typename Acc> constexpr
auto reduced(const vector<B>& v, F reduce, Acc&& a) {
	for(auto it = begin(v); it != end(v); ++it) f(a, *it++);
	return a;
}

// Double.
template<typename B1, typename B2, typename F, typename Acc> constexpr
auto reduced(const vector<B1>& lv, const vector<B2>& rv, F f, Acc&& a) {
	throw_if_different_size(lv, rv);
	auto l = begin(lv);
	auto r = begin(rv);
	while(l != end(lv)) f(a, *l++, *r++);
	return a;
}

}}
