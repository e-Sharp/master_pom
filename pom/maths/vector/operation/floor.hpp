#pragma once

#include "pom/maths/operation/floor.hpp"
#include "pom/maths/vector/concept/vector.hpp"

#include <pom/meta/tag/all.hpp>
#include <range/v3/view/zip.hpp>

namespace pom::maths {

template<typename Ty, std::size_t N> constexpr
auto floor(const static_vector<Ty, N>& v) {
	auto f = static_vector<Ty, N>();
	for(auto&& [a, b] : ranges::views::zip(f, v)) {
		a = floor(b);
	}
	return f;
}

}
