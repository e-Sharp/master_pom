#pragma once

#include "empty.hpp"
#include "head.hpp"
#include "tail.hpp"
#include "type_list.hpp"

#include "decl/type/same.hpp"
#include "decl/type/type.hpp"

#include <cstdlib>
#include <type_traits>

namespace decl {

template<typename... TL, typename T> consteval
auto index(type_list<TL...> l, type<T> t) {
	if constexpr(empty(l)) {
		static_assert(false, "decl: Type list does not contain given type.");
	} else if constexpr(same(head(l), t)) {
		return std::integral_constant<std::size_t, 0>();
	} else {
		return std::integral_constant<std::size_t, index(tail(l), t) + 1>();
	}
}

}
