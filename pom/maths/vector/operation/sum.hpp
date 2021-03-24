#pragma once

#include "pom/maths/vector/concept/vector.hpp"
#include "pom/maths/vector/indexes.hpp"

namespace pom::maths {

template<vector V> constexpr
auto operator+(const V& lv, const V& rv) {
	auto v = V();
	for(auto i : indexes(v)) {
		at(v, i) = at(lv, i) + at(rv, i);
	}
	return v;
}

template<vector V, typename S> constexpr
auto operator+(const V& lv, const S& rs) {
	auto v = V();
	for(auto i : indexes(v)) {
		at(v, i) = at(lv, i) + rs;
	}
	return v;
}

template<typename S, vector V> constexpr
auto operator+(const S& ls, const V& rv) {
	auto v = V();
	for(auto i : indexes(v)) {
		at(v, i) = ls + at(rv, i);
	}
	return v;
}

}
