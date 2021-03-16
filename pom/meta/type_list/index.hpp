#pragma once

#include "empty.hpp"
#include "head.hpp"
#include "tail.hpp"
#include "type_list.hpp"

#include "pom/meta/type/same.hpp"
#include "pom/meta/type/type.hpp"

#include <cstdlib>

namespace pom {
namespace meta {

template<typename... TL, typename Ty> consteval
std::size_t index(type_list<TL...> l, type<Ty> t) {
	if constexpr(empty(l)) {
		static_assert(false, "Type list does not contain given type.");
	} else if constexpr(same(head(l), t)) {
		return 0;
	} else {
		return index(tail(l), t) + 1;
	}
}

}}
