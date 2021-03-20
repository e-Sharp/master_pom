#pragma once

#include "type_list.hpp"

#include "decl/type/type.hpp"

namespace decl {

template<typename... TL> consteval
void tail(type_list<TL...>) {
	static_assert(false, "decl: Empty type list has no tail.");
}

template<typename H, typename... T> consteval
type_list<T...> tail(type_list<H, T...>) { return {}; }

}
