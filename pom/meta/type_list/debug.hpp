#pragma once

#include "type_list.hpp"

#include "pom/meta/type/debug.hpp"

namespace pom {
namespace meta {

template<typename... Ts>
std::ostream& operator<<(std::ostream& os, type_list<Ts...> l) {
	if constexpr(!empty(l)) {
		constexpr auto h = head(l);
		constexpr auto t = tail(l);
		return os << h << " " << t;
	} else {
		return os;
	}
}

}}
