#pragma once

#include "type_list.hpp"

#include "decl/type/type.hpp"

namespace decl {

template<typename... TL> consteval
void head(type_list<TL...>) {
	static_assert(false, "decl: Empty type list has no head.");
}

template<typename H, typename... T> consteval
type<H> head(type_list<H, T...>) { return {}; }

}
