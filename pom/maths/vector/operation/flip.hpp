#pragma once

#include "pom/maths/vector/static_vector/static_vector.hpp"

#include <algorithm>

namespace pom::maths {

template<typename Ty, std::size_t N> constexpr
auto flipped(const static_vector<Ty, N>& v) {
	auto f = static_vector<Ty, N>();
	std::reverse_copy(begin(v), end(v), begin(f));
	return f;
}

}
