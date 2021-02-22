#pragma once

#include "concepts.hpp"

#include <range/v3/view/iota.hpp>

namespace pom {
namespace maths{

template<interval I> constexpr
auto range(const I& i) {
	return ranges::view::ints(lower(i), upper(i));
}

}}
