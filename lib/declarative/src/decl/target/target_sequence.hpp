#pragma once

#include "decl/target/prerequisites.hpp"
#include "decl/target/target_list.hpp"
#include "decl/type_list/empty.hpp"
#include "decl/type_list/head.hpp"
#include "decl/type_list/tail.hpp"
#include "decl/type_list/union.hpp"

namespace decl {
namespace detail {

template<typename... TL> consteval
auto target_sequence(type_list<TL...> l) {
	if constexpr(empty(l)) {
		return target_list<>();
	} else {
		constexpr auto h = head(l);
		constexpr auto hps = target_sequence(prerequisites(h));
		constexpr auto ts = target_sequence(tail(l));
		return union_(union_(hps, h), ts);
	}
}

}}
