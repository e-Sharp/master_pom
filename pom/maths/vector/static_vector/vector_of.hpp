#pragma once

#include "static_vector.hpp"

namespace pom::maths {

template<typename Ty> constexpr
auto vector_of(const Ty& v0, const Ty& v1) {
	auto v = static_vector<Ty, 2>();
	at(v, 0) = v0;
	at(v, 1) = v1;
	return v;
}

template<typename Ty> constexpr
auto vector_of(const Ty& v0, const Ty& v1, const Ty& v2) {
	auto v = static_vector<Ty, 3>();
	at(v, 0) = v0;
	at(v, 1) = v1;
	at(v, 2) = v2;
	return v;
}

}
