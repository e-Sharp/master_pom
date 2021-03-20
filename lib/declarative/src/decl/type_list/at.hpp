#pragma once

#include "empty.hpp"
#include "type_list.hpp"

#include <cstdlib>
#include <type_traits>

namespace decl {

template<std::size_t N, typename... TL> consteval
auto at(type_list<TL...> l) {
	if constexpr(empty(l)) {
		static_assert(false, "decl: Out of range.");
	} else if constexpr(N == 0) {
		return head(l);
	} else {
		return at<N - 1>(tail(l));
	}
}

}
