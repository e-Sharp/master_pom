#pragma once

#include "concepts.hpp"

namespace pom {
namespace maths {

template<matrix M, typename F, matrix R = M> constexpr
auto mapped(const M& m, F mapping, R = {}) {
	auto s = size(m);
	auto r = R(s);
	for(decltype(s) ij = {0, 0}; at(ij, 1) < at(s, 1); ++at(ij, 1))
	for(at(ij, 0) = 0; at(ij, 0) < at(s, 0); ++at(ij, 0)) {
		at(r, ij) = mapping(at(m, ij));
	}
	return r;
}

}}
