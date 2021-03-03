#pragma once

#include <concepts>

namespace pom {
namespace maths {

template<interval I> constexpr
decltype(auto) length(const I& i)
noexcept(noexcept(lower(i)) && noexcept(upper(i))) {
	return upper(i) - lower(i);
}

//

template<interval I, typename Ty> constexpr
auto normalized(const I& i, const Ty& val) {
	return (val - lower(i)) / length(i);
}

}}
