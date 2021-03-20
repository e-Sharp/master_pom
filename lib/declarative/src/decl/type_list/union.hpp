#pragma once

#include "contains.hpp"
#include "head.hpp"
#include "tail.hpp"
#include "type_list.hpp"

#include "decl/type/type.hpp"

namespace decl {

template<typename... TL, typename T> consteval
auto union_(type_list<TL...> l, type<T> t) {
	if constexpr(contains(l, t)) {
		return l;
	} else {
		return type_list<TL..., T>();
	}
}

template<typename T, typename... TL> consteval
auto union_(type<T> t, type_list<TL...> l) {
	if constexpr(contains(l, t)) {
		return l;
	} else {
		return type_list<T, TL...>();
	}
}

template<typename... LTL, typename... RTL> consteval
auto union_(type_list<LTL...> l, type_list<RTL...> r) {
	if constexpr(empty(r)) {
		return l;
	} else if constexpr(contains(l, head(r))) {
		return union_(l, tail(r));
	} else {
		return union_(union_(l, head(r)), tail(r));
	}
}

}
