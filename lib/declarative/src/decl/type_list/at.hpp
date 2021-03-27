#pragma once

#include "empty.hpp"
#include "type_list.hpp"

#include <cstdlib>
#include <type_traits>

namespace decl {

template<std::size_t I, typename... TL> consteval
auto at(type_list<TL...> l, std::integral_constant<std::size_t, I> = {}) {
	if constexpr(empty(l)) {
		static_assert(false, "decl: Out of range.");
	} else if constexpr(I == 0) {
		return head(l);
	} else {
		return at(tail(l), std::integral_constant<std::size_t, I - 1>());
	}
}

}
