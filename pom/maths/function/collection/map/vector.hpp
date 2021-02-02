#pragma once

#include "pom/maths/function/vector/throw.hpp"

namespace pom {
namespace maths {

// Single, direct.
template<typename B, typename F> constexpr
auto mapped(const vector<B>& v, F f) {
	auto m = vector<B>(size(v));
	auto in = begin(v);
	auto out = begin(m);
	while(in != end(v)) *out++ = f(*in++);
	return m;
}

// Double, direct.
template<typename B1, typename B2, typename F, typename BR = B1> constexpr
auto mapped(const vector<B1>& lv, const vector<B2>& rv, F f) {
	throw_if_different_size(lv, rv);
	auto m = vector<BR>(size(lv));
	for(std::size_t i = 0; i < size(lv); ++i) at(m, i) = f(at(lv, i), at(rv, i));
	return m;
}

}}
