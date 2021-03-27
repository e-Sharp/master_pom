#pragma once

#include "decl/type/type.hpp"
#include "decl/type/what.hpp"
#include "decl/type_list/type_list.hpp"

namespace decl {
namespace detail {

template<typename Target, typename... Args> consteval
type_list<> prerequisites(Target, Args...);

template<typename Target, typename... Args> consteval
auto prerequisites(type<Target>, type_list<Args...>) {
	return decltype(prerequisites(Target(), what(type<Args>())...))();
}

}}
