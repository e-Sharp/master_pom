#pragma once

#include "pom/maths/numeric/floor.hpp"
#include "pom/maths/vector/concept/vector.hpp"

#include <pom/meta/tag/all.hpp>
#include <range/v3/view/zip.hpp>

namespace pom {
namespace maths {

template<vector V> constexpr
auto floor(const V& v) {
	auto f = V();
	for(auto&& [a, b] : ranges::views::zip(f, v)) {
		a = floor(b);
	}
	return f;
}

}}
