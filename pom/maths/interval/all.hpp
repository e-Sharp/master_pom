#pragma once

#include "pom/maths/interval/concepts.hpp"

namespace pom {
namespace maths {

template<interval I> constexpr
decltype(auto) length(const I& i)
noexcept(noexcept(lower(i)) && noexcept(upper(i))) {
	return upper(i) - lower(i);
}

template<interval I> constexpr
auto mapping(const I& orig, const I& dest) {
	auto a = length(dest) / length(orig);
	auto b = lower(dest) - a * lower(orig);
	return [a, b](const auto& x) { return a * x + b; };
}

}}
