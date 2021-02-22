#pragma once

#include "concepts.hpp"

#include <range/v3/view/iota.hpp>

namespace pom {
namespace maths {

template<vector V> constexpr
auto indexes(const V& v) {
	auto z = decltype(size(v)){0};
	return ranges::views::ints(z, size(v));
}

}}
