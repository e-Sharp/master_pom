#pragma once

#include "has.hpp"
#include "head.hpp"
#include "tail.hpp"
#include "type_list.hpp"

#include "pom/meta/type/type.hpp"

namespace pom {
namespace meta {

template<typename... TL, typename Ty> consteval
auto union_(type_list<TL...> l, type<Ty> t) {
	if constexpr(has(l, t)) {
		return l;
	} else {
		return type_list<TL..., Ty>();
	}
}

template<typename Ty, typename... TL> consteval
auto union_(type<Ty> t, type_list<TL...> l) {
	if constexpr(has(l, t)) {
		return l;
	} else {
		return type_list<Ty, TL...>();
	}
}

template<typename... LTs, typename... RTs> consteval
auto union_(type_list<LTs...> l, type_list<RTs...> r) {
	if constexpr(empty(r)) {
		return l;
	} else if constexpr(has(l, head(r))) {
		return union_(l, tail(r));
	} else {
		return union_(union_(l, head(r)), tail(r));
	}
}

template<typename TL1, typename TL2, typename... Ts> consteval
auto union_(type_list<TL1...> l1, type_list<TL2...> l2, Ts...) {
	return union_(union_(l1, l2), Ts...);
}

}}
