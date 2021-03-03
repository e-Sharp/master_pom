#pragma once

#include "concepts.hpp"

#include <range/v3/view/iota.hpp>

namespace pom {
namespace maths {

template<vector V> constexpr
auto indexes(const V& v) {
	auto s = size(v);
	return ranges::views::ints(decltype(s){0}, s);
}

}}
