#pragma once

#include <concepts>

namespace pom {
namespace maths {

template<std::integral I> constexpr
auto positive_ceiled_quotient(I dividend, I divisor) noexcept {
	return (dividend + divisor - 1) / divisor;
}

}}
