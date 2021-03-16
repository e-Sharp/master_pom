#pragma once

#include "type_list.hpp"

#include "pom/meta/type/type.hpp"

namespace pom {
namespace meta {

template<typename... Empty> consteval
void head(type_list<Empty...>) {
	static_assert(false, "Empty type list has no head.");
}

template<typename Head, typename... Tail> consteval
type<Head> head(type_list<Head, Tail...>) { return {}; }

}}
