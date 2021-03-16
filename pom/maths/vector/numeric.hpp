#pragma once

#include "pom/maths/numeric/all.hpp"
#include "pom/maths/vector/concepts.hpp"

#include <pom/meta/tag/all.hpp>
#include <range/v3/view/zip.hpp>

namespace pom {
namespace maths {

template<vector V> constexpr
auto floor(const V& v) {
	auto f = similar(v, meta::defaulted);
	for(auto&& [a, b] : ranges::views::zip(f, v)) {
		a = floor(b);
	}
	return f;
}

}}
