#pragma once

#include "pom/maths/exceptions.hpp"

#include <concepts>

namespace pom {
namespace maths {

template<typename B>
struct interval : B {
	using B::B;
};

template<typename B> constexpr
decltype(auto) lower(const interval<B>& i)
noexcept(noexcept(lower(static_cast<const B&>(i)))) {
	return lower(static_cast<const B&>(i));
}

template<typename B> constexpr
decltype(auto) upper(const interval<B>& i)
noexcept(noexcept(lower(static_cast<const B&>(i)))) {
	return upper(static_cast<const B&>(i));
}

template<typename B> constexpr
decltype(auto) length(const interval<B>& i)
noexcept(noexcept(lower(i)) && noexcept(upper(i))) {
	return upper(i) - lower(i);
}

template<typename I> constexpr
auto mapping(const interval<I>& orig, const interval<I>& dest) {
	auto a = length(dest) / length(orig);
	auto b = - a * lower(orig) + lower(dest);
	return [a, b](const auto& x) { return a * x + b; };
}

}}
