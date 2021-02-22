#pragma once

#include "concepts.hpp"

namespace pom {
namespace maths {

template<interval I> constexpr
auto length(const I& i)
noexcept(noexcept(lower(i)) && noexcept(upper(i))) {
	return upper(i) - lower(i);
}

}}
