#pragma once

#include <pom/meta/type/all.hpp>
#include <pom/meta/type_list/all.hpp>

#include <tuple>


#include <iostream>

namespace pom {
namespace decl {

template<typename... Ts>
struct data {};

template<typename TagList, typename TypeList>
struct data<TagList, TypeList> {
	static_assert(size(TagList) == size(TypeList));

	template<typename Ty>
	decltype(auto) get(meta::type<Ty> tag) {
		static_assert(has(TagList, tag));
		return get(d, at(TypeList(), index(TagList)));
	}

	decltype(tuple_of(TypeList())) d = {};
};

template<typename... TL, typename... Args>
auto data_of(meta::type_list<TL...>, Args&&... args) {
	// return data<decltype(make(data<int>(), meta::type<TL>(), args...))...>();
	return type_list<decltype(make(data<>(), TL(), args...))...>();
}

}}
