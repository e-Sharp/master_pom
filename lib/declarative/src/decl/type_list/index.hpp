#pragma once

#include "empty.hpp"
#include "head.hpp"
#include "tail.hpp"
#include "type_list.hpp"

#include "decl/type/same.hpp"
#include "decl/type/type.hpp"

#include <cstdlib>

namespace decl {

template<typename... TL, typename T> consteval
std::size_t index(type_list<TL...> l, type<T> t) {
	if constexpr(empty(l)) {
		static_assert(false, "decl: Type list does not contain given type.");
	} else if constexpr(same(head(l), t)) {
		return 0;
	} else {
		return index(tail(l), t) + 1;
	}
}

}
