#pragma once

#include "pom/terrain/function/addition/all.hpp"
#include "pom/terrain/function/concept/function.hpp"
#include "pom/terrain/function/multiplication/multiplication_operator.hpp"

namespace pom::terrain {

template<function A, typename B, typename I> constexpr
auto lerp(A&& a, B&& b, I&& i) {
	return I(i) * A(a) + (1.f + -1.f * I(i)) * B(b);
}

}
