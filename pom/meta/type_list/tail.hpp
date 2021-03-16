#pragma once

#include "type_list.hpp"

#include "pom/meta/type/type.hpp"

namespace pom {
namespace meta {

template<typename... Empty> consteval
void tail(type_list<Empty...>) {
	static_assert(false, "Empty type list has no tail.");
}

template<typename Head, typename... Tail> consteval
type_list<Tail...> tail(type_list<Head, Tail...>) { return {}; }

}}
