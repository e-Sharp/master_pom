#pragma once

#include "type_list.hpp"

#include "decl/type/same.hpp"
#include "decl/type/type.hpp"

namespace decl {

template<typename... TL, typename T> consteval
bool contains(type_list<TL...>, type<T> t) {
	return (same(type<TL>(), t) || ...);
}

}
