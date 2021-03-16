#pragma once

#include <pom/meta/type_list/tuple.hpp>

namespace pom {
namespace decl {

template<typename TypeList>
struct context {
	using types = TypeList;

	explicit constexpr context(TypeList) {}

	decltype(tuple_of(types())) data = {};
};

template<typename TypeList>
context(TypeList) -> context<TypeList>;

}}
