#pragma once

#include "pom/maths/object/vector.hpp"
#include "pom/maths/exceptions.hpp"

namespace pom {
namespace maths {

// Unary.

template<typename B> constexpr
void throw_if_empty(const vector<B>& v) {
	if(size(v) == 0) throw precondition_violation{
		"Vector mustn't be empty."};
}

// Binary.

template<typename BL, typename BR> constexpr
void throw_if_different_size(const vector<BL>& lv, const vector<BR>& rv) {
	if(size(lv) != size(rv)) throw precondition_violation{
		"Vectors must have the same size."};
}

}}
