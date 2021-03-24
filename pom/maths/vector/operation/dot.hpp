#pragma once

#include "pom/maths/vector/concept/vector.hpp"

#include <range/v3/view/zip.hpp>

namespace pom::maths {

template<vector V> constexpr
auto dot(const V& lv, const V& rv) {
	auto d = decltype(at(lv, 0))(0);
	for(auto i : indexes(lv)) {
		d += at(lv, i) * at(rv, i);
	}
	return d;
}

}
