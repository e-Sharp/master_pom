#pragma once

#include "pom/maths/vector/concept/vector.hpp"

#include <range/v3/view/iota.hpp>

namespace pom::maths {

template<vector V> constexpr
auto indexes(const V& v) {
	auto s = size(v);
	return ranges::views::ints(decltype(s)(0), s);
}

}
