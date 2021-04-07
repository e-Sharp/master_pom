#pragma once

#include "pom/terrain/function/lerped/all.hpp"

namespace pom::terrain {

template<typename A, typename B, typename I> constexpr
auto lerp(A a, B b, I i) {
	return lerped(std::move(a), std::move(b), std::move(i));
}

}
