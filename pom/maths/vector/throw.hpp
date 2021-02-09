#pragma once

#include "pom/maths/exceptions.hpp"
#include "pom/maths/vector/concepts.hpp"

namespace pom {
namespace maths {

// Unary.

template<vector V> constexpr
void throw_if_empty(const V& v) {
	if(size(v) == 0) throw precondition_violation{
		"Vector mustn't be empty."};
}

// Binary.

template<vector LV, vector RV> constexpr
void throw_if_different_size(const LV& lv, const RV& rv) {
	if(size(lv) != size(rv)) throw precondition_violation{
		"Vectors must have the same size."};
}

}}
