#pragma once

#include "decl/target/prerequisites.hpp"
#include "decl/target/targets.hpp"
#include "decl/type_list/empty.hpp"
#include "decl/type_list/head.hpp"
#include "decl/type_list/tail.hpp"
#include "decl/type_list/union.hpp"

namespace decl {
namespace detail {

template<typename... TL, typename... Args> consteval
auto target_sequence(type_list<TL...> l, type_list<Args...> as) {
	if constexpr(empty(l)) {
		(void) as;
		return type_list<>();
	} else {
		constexpr auto h = head(l);
		constexpr auto hps = target_sequence(prerequisites(h, as), as);
		constexpr auto ts = target_sequence(tail(l), as);
		return union_(union_(hps, h), ts);
	}
}

}}
