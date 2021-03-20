#pragma once

#include "decl/type_list/type_list.hpp"

namespace decl {
namespace detail {

template<typename Ty> consteval
type_list<> prerequisites(Ty) { return {}; }

template<typename T> consteval
auto prerequisites(type<T>) {
	// Removes the need of providing a function definition.
	return decltype(prerequisites(T()))();
}

}}
