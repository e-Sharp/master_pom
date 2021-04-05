#pragma once

#include "smin.hpp"

namespace pom::maths {

template<typename Ty, typename K> constexpr
Ty smax(const Ty& a, const Ty& b, const K& k) {
	return - smin(-a, -b, k);
}

}
