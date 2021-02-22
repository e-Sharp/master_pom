#pragma once

#include "length.hpp"

namespace pom {
namespace maths {

template<interval OI, interval DI> constexpr
auto mapping(const OI& orig, const DI& dest) {
	auto a = length(dest) / length(orig);
	auto b = lower(dest) - a * lower(orig);
	return [a, b](const auto& x) { return a * x + b; };
}

}}
