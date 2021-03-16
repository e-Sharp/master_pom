#pragma once

#include "head.hpp"
#include "tail.hpp"
#include "type_list.hpp"

#include "pom/meta/type/same.hpp"
#include "pom/meta/type/type.hpp"

namespace pom {
namespace meta {

template<typename... Ts, typename Ty> consteval
bool has(type_list<Ts...> l, type<Ty> t) {
	(void) t; // Disables unreferenced parameter warning on MSVC.
	if constexpr(empty(l)) {
		return false;
	} else if constexpr(same(head(l), t)) {
		return true;
	} else {
		return has(tail(l), t);
	}
}

}}
