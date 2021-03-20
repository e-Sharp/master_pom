#pragma once

#include "empty.hpp"
#include "head.hpp"
#include "tail.hpp"
#include "type_list.hpp"

#include "decl/type/debug.hpp"

namespace decl {

template<typename... TL>
std::ostream& operator<<(std::ostream& os, type_list<TL...> l) {
	if constexpr(empty(l)) {
		return os;
	} else {
		constexpr auto h = head(l);
		constexpr auto t = tail(l);
		return os << h << " " << t;
	}
}

}
