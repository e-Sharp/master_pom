#pragma once

#include <cstdlib>

namespace pom {

template<std::size_t D, typename Ty = void>
struct dimension {
	operator dimension<D>() const noexcept {
		return {};
	}

	operator const Ty& () const noexcept {
		return value;
	}

	Ty value = {};
};

template<std::size_t D>
struct dimension<D, void> {};

template<std::size_t D, typename Ty>
auto& operator++(dimension<D, Ty>& d) {
	++d.value;
	return d;
}

using col = dimension<0, std::size_t>;
using row = dimension<1, std::size_t>;

} // namespace pom
