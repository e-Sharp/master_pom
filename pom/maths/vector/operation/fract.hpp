#pragma once

#include "pom/maths/operation/fract.hpp"

namespace pom::maths {

template<typename Ty, std::size_t N>
auto fract(const static_vector<Ty, N>& v) {
	auto f = static_vector<Ty, N>();
	for(std::size_t i = 0; i < size(v); ++i) {
		at(f, i) = fract(at(v, i));
	}
	return f;
}

}
