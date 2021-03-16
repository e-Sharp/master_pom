#pragma once

#include <pom/meta/type_list/empty.hpp>
#include <pom/meta/type_list/head.hpp>
#include <pom/meta/type_list/tail.hpp>
#include <pom/meta/type_list/type_list.hpp>
#include <pom/meta/type_list/union.hpp>

namespace pom {
namespace decl {
namespace detail {

template<typename... TL> consteval
auto make_sequence(meta::type_list<TL...> l) {
	if constexpr(empty(l)) {
		return meta::type_list<>();
	} else {
		constexpr auto h = head(l);
		constexpr auto hds = make_sequence(dependencies(h));
		constexpr auto ts = make_sequence(tail(l));
		return union_(union_(hds, h), ts);
	}
}

}}}
