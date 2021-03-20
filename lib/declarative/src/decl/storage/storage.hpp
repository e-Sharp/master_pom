#pragma once

#include "storage_traits.hpp"

#include "decl/type_list/index.hpp"
#include "decl/type_list/std_tuple.hpp"

namespace decl {
namespace detail {

template<storage_traits Tr>
struct storage {
	static constexpr auto recipes = typename Tr::recipes();

	decltype(std_tuple_of(recipes)) data;
};

template<typename S, typename T>
decltype(auto) get(const storage<S>& s, type<T> t) {
	return get<index(S::targets(), t)>(s.data);
}

template<typename S, typename Ty>
decltype(auto) get(storage<S>& s, type<Ty> t) {
	return get<index(S::targets(), t)>(s.data);
}

}}
