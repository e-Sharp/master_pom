#pragma once

#include "length.hpp"

namespace pom {
namespace maths {

template<typename Ty>
struct mapping_object {
	template<typename U>
	constexpr Ty operator()(U x) const {
		return a * x + b;
	}

	Ty a = 1;
	Ty b = 0;
};

template<typename Ty>
mapping_object(Ty, Ty) -> mapping_object<Ty>;

template<interval OI, interval DI> constexpr
auto mapping(const OI& orig, const DI& dest) {
	auto a = length(dest) / length(orig);
	auto b = lower(dest) - a * lower(orig);
	return mapping_object(a, b);
}

}}
